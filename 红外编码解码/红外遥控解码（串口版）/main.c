/*--------------------------------------------------------------
/项目名：
/开发工程师：
/日期：
/版本：
/主控MCU：51单片机，stc15W系列，晶振：11.0592MHz
/备注：红外接收头：1838B型号
/
/
*///------------------------------------------------------------------

#include "main.h"
#include "Reciving_IR.h"

	
#define FOSC    11092500L//22118400L//
#define BAUD    9600
#define D_T1Timer 0xFc00	//17.7MS
#define D_T0Timer (65536-FOSC/8000)
#define PinPP(Pn,n) {switch(Pn){\							
			case 0:P0M1 &= ~(1 << n);P0M0 |=  (1 << n);break;\
			case 1:P1M1 &= ~(1 << n);P1M0 |=  (1 << n);break;\
			case 2:P2M1 &= ~(1 << n);P2M0 |=  (1 << n);break;\
			case 3:P3M1 &= ~(1 << n);P3M0 |=  (1 << n);break;\
			case 4:P4M1 &= ~(1 << n);P4M0 |=  (1 << n);break;\
			case 5:P5M1 &= ~(1 << n);P5M0 |=  (1 << n);break;\										
    			default:break;\    									     										
			}\
		    }
		    
#define ClrWDT	{WDT_CONTR |= 0x10;}//清看门狗，喂狗程序			
#define IAP_ENABLE 0x60 //IAP允许
sfr IAP_CNTR = 0xC7; //IAP控制寄存器
//---------------------------------------------


//-----------------主循环架构的定义-----------------------------------

u16 R_MainTemper;
//u8 	R_TimerMSCnt;
u8	R_2ms=0;//2ms计时
bit	Flg_2ms=0;
bit 	Flg_500MsFlash;
char	R_JmpmsCnt=0;


u8	R_MainMode=0;
//----------------------------------------------------------

//----------------------------------------------------------
#define	D_BeepTm 10	//20MS
#define	Beep() {R_BeepTm=D_BeepTm;R_BeepFrq=10;}
u8 R_BeepCnt;
u8 R_BeepTm=D_BeepTm;


u8 R_BeepFrq,R_BeepFrqBak;

sbit Pin_Beep	= P0^4;

//-----------------------------------------
//
//函数声明
//
//-----------------------------------------

u8 DealRFKey(u8 R_Data);
void BeepDrv();

void	Timer50msCnt();
void 	Init_System();
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
    u8 Cnt;
	Init_System();	//定时器初始化
    Pin_IR=1;
	ClrWDT;				
	while(1)
	{
	ClrWDT;	


	if(Flg_2ms)	//2毫秒分时处理
		{
		Flg_2ms=0;
        
     if(Flg_RxIROK)//红外接收完成
    {
       
        if(Cnt<D_RxByteCnt)
        {
            SBUF=RxData_Tab[Cnt];
            while(!TI);
            TI=0;
             Cnt++;
        }
        else
        {
        Cnt=0; Flg_RxIROK=0;
       }
       
    }       
		if(++R_JmpmsCnt == 10)R_JmpmsCnt=0;
		switch(R_JmpmsCnt)	//2毫秒分时处理
			{
			case	0:
            				
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
					Timer50msCnt();	//20毫秒计时
				break;
			default:
				break;																
			}
		}	
	}
}
/*输入：定时器T0中断
/输出：2毫秒标志Flg_2ms=1，按键扫描
/备注：定时器0方式2,16位自动重载，定时125us
/
*/
//-------------------------------------------
void et0()interrupt 1
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
	BeepDrv();
	REciving_IR();
						
}
void	Timer50msCnt()
{
	static char R_500msCnt,R_100msCnt;		
	R_500msCnt++;
	R_100msCnt++;
		
//----------计时50ms------------------------------------		
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
						
        	
//------	----此段为1s------------------------------------			
        	
			}		
//----------计时1s---END---------------------------------					
		}
//----------计时500ms--END----------------------------------

			
			
}
//-------------------------------------------
/*---------------定时器中断子程序------------
/输入：定时器T0中断
/输出：RGB输出控制，时钟显示
/备注：定时器0方式2,16位自动重载，
/
*/
//-------------------------------------------

//串行中断函数
void serial() interrupt 4
{

//	RxDataTemp_Tab[R_RxCnt]=SBUF;//	
	RI=0;
 	if(0x7F == SBUF) //? ? ? ? ? ? ?//判断是否为下载流信息
 	{
 	IAP_CNTR =IAP_ENABLE; //?//允许IAP, 也就是直接进入下载程序
	// soft_reset();
 	}

}

//-------------------------------------------
/*---------------蜂鸣器子程序------------
//--------------------------------------------
/输入：
/输出：
/备注：
/
*/
//-------------------------------------------	
void BeepDrv()
{
	if(R_BeepTm)
		{
		if(R_BeepFrq)
			{
			R_BeepFrq--;
			if(R_BeepFrq==0)
				{
				R_BeepFrq=R_BeepFrqBak;
				Pin_Beep=!Pin_Beep;	
				}
				
			}
			
		}	
		else
			{
			Pin_Beep=1;	
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
void Init_System()
{
    	P0M0 = 0x00;
    	P0M1 = 0x00;
    	P1M0 = 0x00;
    	P1M1 = 0x00;
    	P2M0 = 0x00;
    	P2M1 = 0x00;
    	P3M0 = 0x0a;
    	P3M1 = 0x08;
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
	TL0 = D_T0Timer;		//设置定时初值
	TH0 = D_T0Timer>>8;		//设置定时初值125us 
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
