//#include<stc15w.h> 
#include"NRF2401.h"
#define u8 unsigned char
#define u16 unsigned int

#define FOSC 11059200L

#define T1MS (65536-FOSC/1000)      //1T模式
//#define T1MS (65536-FOSC/12/1000) //12T模式

sbit T2CLKO   = P3^0;               //定时器2的时钟输出脚

#define F38_4KHz (65536-FOSC/2/38400)    //1T模式
//#define F38_4KHz (65536-FOSC/2/12/38400) //12T模式
//-----------------主循环架构的定义-----------------------------------
u8	R_2ms=0;//2ms计时
bit	Flg_2ms=0;
char	R_Jmp2msCnt=0;

char	R_MMode=0;
#define	D_Mode1	0
#define	D_Mode2	1
#define	D_Mode3	2
#define	D_Mode4	3
#define	D_Mode5	4
#define	D_Mode6	5

//----------------------------------------------------------
/**********************************************************************************/
//----按键扫描、按键检测、按键处理的定义-----------------------------------
sbit key_onoff	 = P5^5;
sbit key_add	 = P5^4;
sbit key_sub	 = P2^0;
sbit key_slt	 = P2^4; 
#define	nokey		0
#define	addkey		1
#define	subkey		2
#define	onoffkey	3
#define	sltkey		4

u8	KeyDly		=0;
u8	KeyMarkDly	=0;
bit	FLG_keymark	=0;
char	KeyValue	=0;
char	R_curkey	=0;
char	R_keybuf	=0;
//----------------------------------------------------------
//*************分别是5个从机对应的固定通信频道
u8 R_CHtab[5]={0x40,0x45,0x48,0x4a,0x4f};	//频道
//**********************用户码+地址码+data1+data2+data3，分别对应5个从机		  
u8 R_SendData_Tab[5][6]={{0xf1,0xe0,10,0,0,0},{0xf2,0xe0,60,0,0,0},
			 {0xf4,0xe0,110,0,0,0},{0xf8,0xe0,160,0,0,0},
			 {0xfa,0xe0,210,0,0,0}};	//每个频道的数据数组
#define	D_RFChance1	0
#define	D_RFChance2	1
#define	D_RFChance3	2
#define	D_RFChance4	3
#define	D_RFChance5	4
//sfr P1M0=0x91;	//IO口控制寄存器
//
//sfr ADC_CONTR=0xc5;	//ADC控制寄存器
//sfr ADC_DATA=0xc6;
//sfr ADC_LOW2=0xbe;
//
//sfr AUXR=0x8e;

//sbit	led=P5^5;
sbit	led=P1^5;
u8 ad[4];	//4个电位器的AD值
u8 tx[6];	//6个发送数据
u8 w;

void initial()
{

   	 AUXR |= 0x80;                   //定时器0为1T模式
// 	 AUXR &= 0x7f;                   //定时器0为12T模式

    	TMOD = 0x00;                    //设置定时器为模式0(16位自动重装载)
	TL0 = 0x9A;		//设置定时初值
	TH0 = 0xFA;		//设置定时初值125us    
    	TR0 = 1;                        //定时器0开始计时
    	ET0 = 1;                        //使能定时器0中断
    	
    	AUXR |= 0x04;                   //定时器2为1T模式
//  	AUXR &= ~0x04;                  //定时器2为12T模式

    	AUXR &= ~0x08;                  //T2_C/T=0, 对内部时钟进行时钟输出
//  	AUXR |= 0x08;                   //T2_C/T=1, 对T2(P3.1)引脚的外部时钟进行时钟输出

    	T2L = F38_4KHz;                 //初始化计时值
    	T2H = F38_4KHz >> 8;
    
    	AUXR |= 0x10;                   //定时器2开始计时
    	INT_CLKO = 0x04;                //使能定时器2的时钟输出功能
    
    	EA = 1;    
}

void	DealKey();
void	ReadKeyValue();
void	KeyScan();
void	Timer20msCnt();
//void	RF_CH_Change(unsigned char	RF_CH);

main()
{
	initial();	//定时器初始化
	TX_mode();	//无线模块初始化

	while(1)
	{	     
	
	DealKey();	//按键处理
	if(Flg_2ms)	//2毫秒计时处理
		{
		Flg_2ms=0;
		if(++R_Jmp2msCnt == 10)R_Jmp2msCnt=0;
		switch(R_Jmp2msCnt)	//2毫秒分时处理
			{
			case	0:
					ReadKeyValue();	//按键转换
				break;
			case	1:
				
				break;
			case	2:
				
				break;												
			case	3:
				
				break;
			case	4:
				
				break;
			case	5:
				
				break;
			case	6:
				
				break;
			case	7:
				
				break;
			case	8:
				
				break;	
			case	9:
					Timer20msCnt();	//20毫秒计时
				break;
			default:
				break;																
			}
		}	
	}
}

void et0()interrupt 1
{
	static	char	temper=0,R_2msCnt=0;
	temper++;
	R_2msCnt++;
	
	if(R_2msCnt == 16)
		{
		R_2msCnt=0;
		Flg_2ms=1;	
		}
	KeyScan();	//按键扫描
	
}

void	Timer20msCnt()
{
	static char	R_500msCnt=0,ii;	
	static char	R_CHtmp=0;		
	R_500msCnt++;
	
//----------计时20ms------------------------------------		
	{
	R_CHtmp++;
	if(R_CHtmp == 5)R_CHtmp=0;
//		RF_CH_Change(R_CHtmp);	
	FIFO_write(R_SendData_Tab[R_CHtmp]);	//发射数据每个频道的周期：20*5ms
//	for(ii==1;ii<5;ii++)
//		{
//		R_SendData_Tab[R_CHtmp][2]=0;	
//		}
	}
//----------计时20ms---END---------------------------------	

//----------计时500ms------------------------------------	
	if( (R_500msCnt == 25) || (R_500msCnt == 0) )
		{
//----------此段为500ms------------------------------------			
		}
//----------计时500ms--END----------------------------------

//----------计时1s------------------------------------				
	if(R_500msCnt == 50)
		{
		R_500msCnt=0;
//----------此段为1s------------------------------------			

		led=!led;		
//		if(led)R_SendData_Tab[R_CHtmp][1]=255;
//			else
//				R_SendData_Tab[R_CHtmp][1]=0;	
	
				
		}		
//----------计时1s---END---------------------------------				
			
}
void	DealKey()//放在主循环中执行
{
	char	R_BottomMode=0;
	static	char	n=0;
	if(R_curkey != 0)
		{
		 R_BottomMode = R_curkey;
		 R_curkey=0;

		 switch(R_BottomMode)
			{
			case addkey:	  	
//					led=!led;		
//					if(led)R_SendData_Tab[D_RFChance1][1]=255;
//						else
//							R_SendData_Tab[D_RFChance1][1]=0;
				break;
			case subkey:	  	
				  
				break;
			case onoffkey:		
					led=!led;		
					
					if(n==5)n=0;		
					if(led)R_SendData_Tab[D_RFChance1+n][2]=255,n++;
						else
							R_SendData_Tab[D_RFChance1+n][2]=5;
				break;
			case sltkey:	  
				
				break;
			 default:;		           
			 	 break;
			}			
		}
	}
void	ReadKeyValue()//放在2ms分时中执行，20ms执行一次
{
	if((KeyDly++ >= 2))
		{ 
		 R_keybuf=0;
		 FLG_keymark=0;
		 KeyDly=0;
		 KeyValue=0;
		 KeyMarkDly=0;
		}
	if(KeyValue != 0)
		{ 
		KeyDly=0;
		if(KeyValue == R_keybuf)
			{
				KeyMarkDly++;
				if(FLG_keymark==0)
					{
					if(KeyMarkDly >= 50)
						{
						KeyMarkDly=0;
						FLG_keymark=1;
						R_keybuf=R_curkey=KeyValue;	
						KeyValue=0;						
						}
						else
							{
							KeyValue=0;
							}
					}
					else
						{
					 	if(KeyMarkDly >= 25)
							{
							KeyMarkDly=0;
							FLG_keymark=1;
							R_keybuf=R_curkey=KeyValue;	
							KeyValue=0;				
							}
						else
							{
							KeyValue=0;
							}						
						}		
			 }
			else//非连续建
				{
				R_keybuf=R_curkey=KeyValue;
				KeyValue=0;
				FLG_keymark=0;
				KeyMarkDly=0;	
				}		
			}
		else //无按键按下
			{
				//R_keybuf=0;
			 //FLG_keymark=0;
			 //KeyDly=0;
			 //KeyValue=0;
			 //KeyMarkDly=0;
			}
	}
	
void	KeyScan()//放在中断函数中执行125us执行一次
{
	KeyValue=0;
	if(!key_add)
		{
			KeyValue=addkey;		
		}
	if(!key_sub)
		{

			KeyValue=subkey;	
		}
	if(!key_slt)
		{
			KeyValue=sltkey;	
		}
	if(!key_onoff)
		{
			KeyValue=onoffkey;	
		}
	}
//void	RF_CH_Change(unsigned char	RF_CH)
//{
//	CE=0;
//	SCK=0;
////	REG_write(0x00,0x0a); //CRC,8 bit,Power on,TX
////	REG_write(0x01,0x00); //unable ACK
////	REG_write(0x02,0x01); //enable P0
////	REG_write(0x04,0x00); //unable ACK
//	REG_write(0x05,R_CHtab[RF_CH]); //可自定义
////	REG_write(0x06,0x07); //1Mbps,0dBm
////	REG_write(0x11,0x06);//DATA 6 bytes	
//	CE=1;		
//}
	