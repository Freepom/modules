#include "main.h"
#include "display.h"
#include "ReadKey.h"

//-----------------主循环架构的定义-----------------------------------

u16 R_MainTemper;
//u8 	R_TimerMSCnt;
u8	R_2ms=0;//2ms计时
bit	Flg_2ms=0;
bit 	Flg_500MsFlash;
char	R_JmpmsCnt=0;

//char	R_MMode=0;
//#define	D_Mode1	0
//#define	D_Mode2	1
//#define	D_Mode3	2
//#define	D_Mode4	3
//#define	D_Mode5	4
//#define	D_Mode6	5

//----------------------------------------------------------
/**********************************************************************************/
//----按键扫描、按键检测、按键处理的定义-----------------------------------

sbit Pin_TimerSet	= P3^2;
sbit Pin_Key1	 	= P1^5;
sbit Pin_Key2	 	= P1^6;
sbit Pin_Key3	 	= P1^7;
sbit Pin_Key4	 	= P5^4;

#define	nokey		0
#define	D_key1		1
#define	D_key2		2
#define	D_key3		3
#define	D_key4		4
#define	D_keyTimerSet	5
#define	D_keyRelease	6


//----------------------------------------------------------

//----------------------------------------------------------
u8 R_Second,R_Minute,R_Hour;

//----------------------------------------------------------
//-----------------------------------------
//
//函数声明
//
//-----------------------------------------

void 	NewDisplay2();
void	DealKey();
void	KeyScan();
void	UpdateDisplay();
void	Timer20msCnt();
void 	initial();
//-------------------------------------------
/*---------------主循环---------------------
//--------------------------------------------
/输入：
/输出：
/备注：
/	
*/
//-------------------------------------------
main()
{
	initial();	//定时器初始化

	ClrWDT;				
	while(1)
	{
	ClrWDT;	

	DealKey();	//按键处理

	if(Flg_2ms)	//10毫秒计时处理
		{
		Flg_2ms=0;

		if(++R_JmpmsCnt == 10)R_JmpmsCnt=0;
		switch(R_JmpmsCnt)	//2毫秒分时处理
			{
			case	0:
            
				break;
			case	1:
					UpdateDisplay();
				break;
			case	2:

					
				break;												
			case	3:

				break;
			case	4:
//					
				break;
			case	5:
					ReadR_KeyValue();	//按键转换
				break;
			case	6:
					UpdateDisplay();
				break;
			case	7:
//					
					
				break;												
			case	8:
//					
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
//-------------------------------------------
/*---------------定时器中断子程序------------
/输入：定时器T0中断
/输出：2毫秒标志Flg_2ms=1，按键扫描
/备注：定时器0方式2,16位自动重载，定时125us
/
*/
//-------------------------------------------
void Inter_Timer0()interrupt 1
{
	static u8 R_MSCnt=0;
//	TL0 = 0x9A;		//设置定时初值
//	TH0 = 0xFA;		//设置定时初值125us  	
		
	R_MSCnt++;				
	if(R_MSCnt == 16)
		{
		R_MSCnt=0;
		Flg_2ms=1;	
		}
	
//	BeepDrv();
	KeyScan();	//按键扫描


}

//串行中断函数
void serial() interrupt 4
{

 	if(0x7F == SBUF) //? ? ? ? ? ? ?//判断是否为下载流信息
 	{
 	IAP_CNTR =IAP_ENABLE; //?//允许IAP, 也就是直接进入下载程序
	// soft_reset();
 	}
}

//-------------------------------------------
/*---------------显示数据更新子程序------------
//--------------------------------------------
/输入：需要显示的数据
/输出：显示缓存R_DBUF1,R_DBUF2,R_DBUF3,R_DBUF4等，用于显示驱动层
/备注：放在2毫米分时中调用
/
*/
//-------------------------------------------
void 	UpdateDisplay()
{

	R_DBUF1=0,R_DBUF2=0,R_DBUF3=0,R_DBUF4=0;
						
}

//-------------------------------------------
/*---------------20毫秒计时子程序------------
//--------------------------------------------
/输入：需要计时的变量
/输出：个变量预算后的结果
/备注：放在2毫米分时中调用
/	计时单位有：20ms，500ms，1S
*/
//-------------------------------------------
void	Timer20msCnt()
{
	static char R_500msCnt,R_100msCnt;		
	R_500msCnt++;
	R_100msCnt++;

		
//----------计时20ms------------------------------------		
	{
	if(R_100msCnt==5)
		{
		R_100msCnt=0;
		}	
			
	}
//----------计时20ms---END---------------------------------	

//----------计时500ms------------------------------------	
	if(R_500msCnt == 25)
		{
		R_500msCnt=0;	
		
//----------此段为500ms------------------------------------

		Flg_500MsFlash=!Flg_500MsFlash;	

//----------计时1s------------------------------------				
		if(Flg_500MsFlash)
			{
						
			R_Second++;

			if(R_Second==60)
				{
				R_Second=0;
								
				R_Minute++;
				if(R_Minute==60)
					{
					R_Minute=0;
					R_Hour++;
					if(R_Hour==24)
						{
						R_Hour=0;	
						}
		
					}	
				}
        	
//------	----此段为1s------------------------------------			
        	
			}		
//----------计时1s---END---------------------------------					
		}
//----------计时500ms--END----------------------------------

			
			
}

//-------------------------------------------
/*---------------按键处理子程序------------
//--------------------------------------------
/输入：按键产生标志Flg_HaveKey，按键键值R_CurKey，双击键产生标志FLG_keyDouble，
/	按键未释放标志FLG_keymark,长按键产生标志Flg_LongKey
/输出：各个按键功能
/备注：主循环中调用
/
*/
//-------------------------------------------
void	DealKey()//放在主循环中执行
{
	u8	R_BottomMode=0;
	if(Flg_HaveKey == 0)
		{
		return;	
		}
	Flg_HaveKey=0;	

		 R_BottomMode = R_CurKey;

		 switch(R_BottomMode)
			{
			case D_key1:	

				break;

			case D_key2:

				break;
			case D_key3: 

				break;
			case D_key4:	

				break;	
			case D_keyRelease://按键释放键	

				break;															
			case D_keyTimerSet:
//					EnableDoubleKey();
//					if(!FLG_keyDouble)
//						{
//						break;	
//						}
//					FLG_keyDouble=0;						

				break;


				break;				
		
			 default:;		           
			 	 break;
			}

}

//-------------------------------------------
/*---------------按键扫描子程序------------
//--------------------------------------------
/输入：
/输出：各个按键键值R_KeyValue，用于按键中间层使用
/备注：定时器中断子程序中调用
/
*/
//-------------------------------------------	
void	KeyScan()//放在中断函数中执行125us执行一次
{
	R_KeyValue=0;
	if(!Pin_Key1)
		{
		R_KeyValue=D_key1;
		}
		else
			{

			}
	if(!Pin_Key2)
		{
		R_KeyValue=D_key2;
		}
		else
			{

			}		
	if(!Pin_Key3)
		{
		R_KeyValue=D_key3;
		}
		else
			{

			}		
	if(!Pin_Key4)
		{
		R_KeyValue=D_key4;
		}
		else
			{
	
			}				
	if(!Pin_TimerSet)
		{
		R_KeyValue=D_keyTimerSet;	
		}
				

																
}

//-------------------------------------------
/*---------------初始化子程序------------
//--------------------------------------------
/输入：
/输出：
/备注：定时器初始化，看门狗初始化
/
*/
//-------------------------------------------	
void initial()
{
    	P0M0 = 0x00;
    	P0M1 = 0x00;
    	P1M0 = 0x00;
    	P1M1 = 0x00;
    	P2M0 = 0x00;
    	P2M1 = 0x00;
    	P3M0 = 0x00;
    	P3M1 = 0x00;
    	P4M0 = 0x00;
    	P4M1 = 0x00;
    	P5M0 = 0x00;
    	P5M1 = 0x00;
    	P6M0 = 0x00;
    	P6M1 = 0x00;
   	 AUXR |= 0x80;                   //定时器0为1T模式
// 	 AUXR &= 0x7f;                   //定时器0为12T模式
	TMOD &= 0xf0;		//设置定时器模式 工作方式0,16位自动重载	
//	TL0 = 0x9A;		//设置定时初值
//	TH0 = 0xFA;		//设置定时初值 
//	TL0 = 0x33;		//设置定时初值
//	TH0 = 0xF5;		//设置定时初值
	TL0 = T1Timer;		//设置定时初值
	TH0 = T1Timer>>8;		//设置定时初值125us 
    	TR0 = 1;                        //定时器0开始计时
    	ET0 = 1;                        //使能定时器0中断
//------------------------------------------

	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器 9600
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
//	T2L = 0xC0;		//设定定时初值	22.M
//	T2H = 0xFD;		//设定定时初值
	T2L = 0xE0;		//设定定时初值
	T2H = 0xFE;		//设定定时初值	11092500L
	AUXR |= 0x10;		//启动定时器2
//------------------------------------------    
//	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
//	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
//    	SCON = 0x5a;                    //8 bit data ,no parity bit
//    	TMOD = 0x20;                    //T1 as 8-bit auto reload
////    	TH1 = TL1 = -(FOSC/32/BAUD); //Set Uart baudrate
//	TL1 = 0xB8;		//设定定时初值
//	TH1 = 0xB8;		//设定定时器重装值
//    	TR1 = 1;                        //T1 start running
////---------------------------------------------	
	ES = 1;                 //Enable UART interrupt
    	EA = 1;
    	
//---------------------------------------------------------------------
    WDT_CONTR = 0x02;       //看门狗定时器溢出时间计算公式: (12 * 32768 * PS) / FOSC (秒)
                            //设置看门狗定时器分频数为32,溢出时间如下:
                            //11.0592M : 1.14s
                            //18.432M  : 0.68s
                            //20M      : 0.63s
    WDT_CONTR |= 0x20;      //启动看门狗  
    
 
}
