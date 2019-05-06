//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//项目名称：软件架构DEMO
//开发人员：林其平
//联系方式：doit0827@foxmail.com/15915979843
//开发环境：C51语言
//开发工具：keil-V5
//适用MCU型号：STC15W**
//软件版本：A03
//更新日期：2017-10-29 17:21:52
//更新内容：
//--------1、子程序命名 2、添加串口通讯内容 3、完善说明注释
//--------
//--------
//备注：
//		晶振频率：33.1776M Hz
//		串口波特率：460800Bps
//		
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "main.h"
#include "display.h"
#include "ReadKey.h"
#include "eerom.h"
//-----------------主循环架构的定义-----------------------------------

sbit Pin_Relay1=P3^5;//
sbit Pin_Relay2=P3^4;//
sbit Pin_Relay3=P3^3;//

u8 R_RlDelayOpen;

u16 R_MainTemper;
//u8 	R_TimerMSCnt;
u8	R_2ms=0;//2ms计时
bit	Flg_2ms=0;
bit 	Flg_500MsFlash;
char	R_JmpmsCnt=0;

u8 idata RxUART_Tab[30];
u8 idata TxUART_Tab[30]; 
bit Flg_StartUART;

char	R_WkMode;
#define	D_WkMode_Auto	0
#define	D_WkMode_Hand	1
#define	D_WkMode_Error	2
#define	D_WkMode4	3
#define	D_WkMode5	4
#define	D_WkMode6	5



u8 bdata R_Flag;	//22
sbit Flg_AutoMode=R_Flag^0;	//=1：自动模式，=0：手动模式
sbit Flg_SetMode=R_Flag^1;	//=1：设置模式，=0：非设置模式
sbit Flg_RelayWk1=R_Flag^2;		//继电器1
sbit Flg_RelayWk2=R_Flag^3;		//继电器1
sbit Flg_RelayWk3=R_Flag^4;		//继电器1
sbit Flg_ToAdd=R_Flag^5;		//
sbit Flg_RelayWkBak1=R_Flag^6;		//
sbit Flg_RelayWkBak2=R_Flag^7;		//

//----------------------------------------------------------
/**********************************************************************************/
//----按键扫描、按键检测、按键处理的定义-----------------------------------

sbit Pin_TimerSet	= P3^1;
sbit Pin_KeyDown	= P2^1;
sbit Pin_KeyUp	 	= P3^0;
sbit Pin_Key3	 	= P1^7;
sbit Pin_Key4	 	= P5^4;

#define	nokey		0
#define	D_keyUp		1
#define	D_keyDown	2
#define	D_key3		3
#define	D_key4		4
#define	D_keyTimerSet	5
#define	D_keyRelease	6


//----------------------------------------------------------

//----------------------------------------------------------
u8 R_Second,R_SecondDS,R_Minute,R_Hour;
bit Flg_Second;
bit Flg_ToErrom;
u8 R_DelaySave;


u8 R_Protect;	//40
#define	D_Nomal			0
#define	D_Protect_E1	1
#define	D_Protect_E2	2
#define	D_Protect_E3	3
#define	D_Protect_E4	4
#define	D_Protect_E5	5
#define	D_Protect_E6	6
#define	D_Protect_E7	7

u8 bdata R_Flag2;	//41
sbit Flg_E1=R_Flag2^0;
sbit Flg_E2=R_Flag2^1;
sbit Flg_E3=R_Flag2^2;
sbit Flg_E4=R_Flag2^3;
sbit Flg_E5=R_Flag2^4;
sbit Flg_E6=R_Flag2^5;
sbit Flg_E7=R_Flag2^6;

//----------------------------------------------------------
//----------------------------------------------------------
//void Delay10us()		//@11.0592MHz
//{
//	unsigned char i;
//
//	_nop_();
//	i = 10;
//	while (--i);
//}
//-----------------------------------------
//
//函数声明
//
//-----------------------------------------
void Recovery();
void CheckError();
void	ClearData_UART(bit Flg_Sta);
void	SendData_UART();
void	RecData_UART();
void RelayDrv();
void SaveDateToErrom();
void	DealKey();
void	KeyScan();
void	UpdateDisplay();
void	Timer50msCnt();
void 	Sys_Initial();
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
	Sys_Initial();	//定时器初始化

//	if(IapReadByte(0x0000)!=0x55)//保存区域分界线的值
		{
		IapEraseSector(0x000);
		IapProgramByte(0x001,0>>8);	//
		IapProgramByte(0x002,0);
		IapProgramByte(0x003,0>>8);	//
		IapProgramByte(0x004,0);	
		IapProgramByte(0x005,0>>8);	//
		IapProgramByte(0x006,0);
		IapProgramByte(0x007,0>>8);	//
		IapProgramByte(0x008,0);	
		IapProgramByte(0x009,0>>8);	//
		IapProgramByte(0x00a,0);
		IapProgramByte(0x00b,0>>8);	//
		IapProgramByte(0x00c,0);	
		IapProgramByte(0x00d,00>>8);	//
		IapProgramByte(0x00e,00);
		IapProgramByte(0x00f,0);	//
		IapProgramByte(0x010,0);					
		IapProgramByte(0x011,0);
		IapProgramByte(0x012,0);
		IapProgramByte(0x013,0);
		IapProgramByte(0x000,0x55);
		Flg_ToErrom=0;				
		}
//	R_Data_Day	=(u16)IapReadByte(0x0001)>>8|IapReadByte(0x0002);	
//	R_Data_Min	=(u16)IapReadByte(0x0003)>>8|IapReadByte(0x0004);	
//	R_Data_V1	=(u16)IapReadByte(0x0005)>>8|IapReadByte(0x0006);	
//	R_Data_V2	=(u16)IapReadByte(0x0007)>>8|IapReadByte(0x0008);	
//	R_Data_K	=(u16)IapReadByte(0x0009)>>8|IapReadByte(0x000a);	
//	R_Data_Frc	=(u16)IapReadByte(0x000b)>>8|IapReadByte(0x000c);	
//	R_DataTmp_TV	=(u16)IapReadByte(0x000d)>>8|IapReadByte(0x000e);
//	R_Flag		=IapReadByte(0x000f);
//	R_SetMode	=IapReadByte(0x0010);
//	R_NT_V2		=IapReadByte(0x0011);
//	R_NT_K		=IapReadByte(0x0012);
//	R_NT_TV		=IapReadByte(0x0013);
	ClrWDT;				
	while(1)
	{
	ClrWDT;	
	RecData_UART();
	
	DealKey();	//按键处理
	CheckError();
	Recovery();
	RelayDrv();
	
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
					SaveDateToErrom();
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
					CheckError();	
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
//	if(Flg_PinSta) 
//		{
//		if(R_PinCnt)
//			{
//			R_PinCnt--;
//			Pin_Pluse=!Pin_Pluse;	
//			}
//			else
//				{
//				Pin_Pluse=1;	
//				}	
//		}

	R_MSCnt++;				
	if(R_MSCnt == 2000/T0Cycle)
		{
		R_MSCnt=0;
		Flg_2ms=1;	
		}
	
//	BeepDrv();
	KeyScan();	//按键扫描
//	DispDrv();	
	
}
//-------------------------------------------
/*---------------串口中断子程序------------
/输入：串口中断
/输出：
/备注：
/
*/
//-------------------------------------------
void Inter_Serial() interrupt 4
{
   	unsigned char len, i;
  	unsigned int j=0;	
  	static u8 R_RCnt;
//	RI=0;
// 	if(0x7F == SBUF) //? ? ? ? ? ? ?//判断是否为下载流信息
// 	{
// 	IAP_CNTR =IAP_ENABLE; //?//允许IAP, 也就是直接进入下载程序
//	// soft_reset();
// 	}

  	if(RI)//780ms,22MHz 接收一个数据要80us
	{		
		if(Flg_StartUART==0)
			{
			len=SBUF;
			RI=0;					
			if(len==0xff)
				{
				R_RCnt++;	
				if(R_RCnt==2)
					{
					Flg_StartUART=1;	
					}	
				}
			
			}
			else
				{
					len=SBUF;
					RI=0;						
					for(i=0;i<len;i++)
					{
						while(!RI)
						{
							j++;
							if(j>200)
							{
							    break;
							}
						}
						if(j<200)
						{
							RxUART_Tab[i]=SBUF;
							RI=0;	
							j=0;
										
						}
						else
						{
						    break;
						}
						
					}
//					if(i==len)//接收完成
					{
						REN=0;
 						Flg_StartUART=0;
 						R_RCnt=0;
					}					
				}
	}
	else if(!RI && TI)//发送
	{
		TI=0;
		len=TxUART_Tab[2];
		for(i=0;i<len;i++)
		{
//			Pin_Pluse=!Pin_Pluse;
			SBUF=TxUART_Tab[i];
			while(!TI);
			TI=0;	
			//Delay10us();//Delay10us();//Delay10us();
//			Delay10us();//Delay10us();			
		}
		REN=1;
	}		

}

//-------------------------------------------
/*---------------外部中断0子程序------------
//--------------------------------------------
/输入：
/输出：
/备注：下降沿触发
/
*/
//-------------------------------------------
void Inter_Ext0() interrupt 0       //INT0中断入口
{
//    FLAG = INT0;                //保存INT0口的状态, INT0=0(下降沿); INT0=1(上升沿)
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
//	Flg_DispOK=0;
//	R_DBUF1=0,R_DBUF2=0,R_DBUF3=0,R_DBUF4=0,R_DBUF5=0;
//	Flg_DispOK=1;					
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
void	Timer50msCnt()
{
	static char R_500msCnt,R_100msCnt;		
	R_500msCnt++;
	R_100msCnt++;

//	R_PinCnt=5;	
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
//		CALL_isr_UART1();
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
/*---------------串口发送数据处理子程序------------
//--------------------------------------------
/输入：
/输出：
/备注：主循环中调用
/
*/
//-------------------------------------------
void	SendData_UART()
{
	TxUART_Tab[0]=0xff;
	TxUART_Tab[1]=0xff;	
	TxUART_Tab[2]=24;
	TxUART_Tab[3]=0;
	TxUART_Tab[4]=0x07;
//----------------------
	TxUART_Tab[5]=2;	
//----------------------				
	TxUART_Tab[6]=0>>8;
	TxUART_Tab[7]=0;
//----------------------				
	TxUART_Tab[8]=0>>8;
	TxUART_Tab[9]=0;
//----------------------			
	TxUART_Tab[10]=0>>8;
	TxUART_Tab[11]=0;
//----------------------				
	TxUART_Tab[12]=0>>8;
	TxUART_Tab[13]=0;
	TxUART_Tab[14]=0;	
//----------------------				
	TxUART_Tab[15]=0>>8;
	TxUART_Tab[16]=0;
	TxUART_Tab[17]=0;	
//----------------------				
	TxUART_Tab[18]=0>>8;
	TxUART_Tab[19]=0;
//----------------------				
	TxUART_Tab[20]=0>>8;
	TxUART_Tab[21]=0;
	TxUART_Tab[22]=0;
		
	TxUART_Tab[23]=TxUART_Tab[0]+TxUART_Tab[1]+TxUART_Tab[2]+TxUART_Tab[3]+TxUART_Tab[4];
	TxUART_Tab[23]+=TxUART_Tab[5]+TxUART_Tab[6]+TxUART_Tab[7]+TxUART_Tab[8]+TxUART_Tab[9];
	TxUART_Tab[23]+=TxUART_Tab[10]+TxUART_Tab[11]+TxUART_Tab[12]+TxUART_Tab[13]+TxUART_Tab[14];	
	TxUART_Tab[23]+=TxUART_Tab[15]+TxUART_Tab[16]+TxUART_Tab[17]+TxUART_Tab[18]+TxUART_Tab[19];
	TxUART_Tab[23]+=TxUART_Tab[20]+TxUART_Tab[21]+TxUART_Tab[22];			
}
//-------------------------------------------
/*---------------串口接收数据处理子程序------------
//--------------------------------------------
/输入：
/输出：
/备注：主循环中调用
/
*/
//-------------------------------------------
void	RecData_UART()
{
//	if(Flg_StartUART)
//		{
//		return;	
//		}

	if(RxUART_Tab[1]==0)
		{
		return;	
		}
//	if(RxUART_Tab[0]!=R_MachCnt)
//		{
//		return;		
//		}
	switch(RxUART_Tab[1]&0x0f)
	{
		case 0x01://

			break;
		case 0x02://

						
			break;
		case 0x03://

			break;
		case 0x04://
		
			break;
		case 0x05://
	
			break;
		case 0x06://
	
			break;
		case 0x07:
				SendData_UART();
			break;
		default:			
			break;								
	}

	CALL_isr_UART1();	//发送ACK
	ClearData_UART(1);	
}
//-------------------------------------------
/*---------------UART数据处理子程序------------
//--------------------------------------------
/输入：
/输出：
/备注：主循环中调用
/
*/
//-------------------------------------------
void	ClearData_UART(bit Flg_Sta)//Flg_Sta=1接收数据缓存清零，Flg_Sta=0发送数据缓存清零
{
	u8 i;
	
	for(i=0;i<6;i++)
		{
		if(Flg_Sta)
			RxUART_Tab[i]=0;
			else
				{
				TxUART_Tab[i]=0;	
				}		
		}	
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
		R_DelaySave=3;	
		 R_BottomMode = R_CurKey;
		 switch(R_BottomMode)
			{
			case D_keyUp:	
						EnableLongKeyS(2);
						if(Flg_LongKey==0)
							{
							Flg_EnableRelease=1;
							if(Flg_KeyRelease==0)	
							break;	
							}
						if(Flg_LongKey)//长按键响应
							{
	
							}
							else//释放键响应
								{
 
								}
						Flg_LongKey=0;	
						Flg_KeyRelease=0;			                    		
				break;

			case D_keyDown:

						EnableLongKeyS(2);
						if(Flg_LongKey==0)
							{
							Flg_EnableRelease=1;
							if(Flg_KeyRelease==0)	
							break;	
							}
						if(Flg_LongKey)//长按键响应
							{
						
							}
							else//释放键响应
								{
								
								}
						Flg_LongKey=0;	
						Flg_KeyRelease=0;			                    		

				break;
															
			case D_keyTimerSet:
//						if(FLG_keymark)
//							{
//							break;	
//							}
//						EnableDoubleKey();
//						if(!FLG_keyDouble)
//							{
//							break;	
//							}
//						FLG_keyDouble=0;
						EnableLongKeyS(2);
						if(Flg_LongKey==0)
							{
//							Flg_EnableRelease=1;
//							if(Flg_KeyRelease==0)	
							break;	
							}
						Flg_LongKey=0;	

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
	if(!Pin_KeyUp)
		{
		R_KeyValue=D_keyUp;
		}
		else
			{

			}
	if(!Pin_KeyDown)
		{
		R_KeyValue=D_keyDown;
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
/*---------------报警检测子程序------------
//--------------------------------------------
/输入：
/输出：
/备注：
/
*/
//-------------------------------------------	
void CheckError()
{
		
	if(Flg_E1)
		{
		R_Protect=D_Protect_E1;
		}	
	if(Flg_E2)
		{
		R_Protect=D_Protect_E2;
		}
	if(Flg_E3)
		{
		R_Protect=D_Protect_E3;
		}					
	if(R_Protect)
		{
		R_WkMode=D_WkMode_Error;	
		}	
		else
			{
			}
}
//-------------------------------------------
/*--------------保护恢复子程序------------
//--------------------------------------------
/输入：
/输出：
/备注：
/
*/
//-------------------------------------------	
void Recovery()
{
	switch(R_Protect)
	{
		case 0:
			
			break;
		case D_Protect_E1:
			if(Flg_E1==0)
				{
				R_WkMode=0;
				R_Protect=0;	
				}
			break;
		case D_Protect_E2:
			if(Flg_E2==0)
				{
				R_WkMode=0;
				R_Protect=0;	
				}			
			break;
		case D_Protect_E3:
			if(Flg_E3==0)
				{
				R_WkMode=0;
				R_Protect=0;	
				}			
			break;
		case D_Protect_E4:
			
			break;
		case D_Protect_E5:
			
			break;
		case D_Protect_E6:
			
			break;
		case D_Protect_E7:
			
			break;
		default:
			break;														
	}
}

//-------------------------------------------
/*---------------继电器驱动子程序------------
//--------------------------------------------
/输入：
/输出：
/备注：
/
*/
//-------------------------------------------	
void RelayDrv()
{

	if(Flg_RelayWk1)
		{
		Pin_Relay1=1;
		}
		else
			{
			Pin_Relay1=0;	
			}
	if(Flg_RelayWk2)
		{
		Pin_Relay2=1;
		}
		else
			{
			Pin_Relay2=0;	
			}
	if(Flg_RelayWk3)
		{
		Pin_Relay3=1;
		}
		else
			{
			Pin_Relay3=0;	
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
void Sys_Initial()
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
//	//输出
//	P0M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P0M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//输入
//	P0M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P0M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	
//	//输出
//	P1M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P1M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//输入
//	P1M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P1M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	
//	//输出
//	P2M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P2M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//输入
//	P2M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P2M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	
//	//输出
//	P3M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P3M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//输入
//	P3M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P3M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//输出
//	P4M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P4M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//输入
//	P4M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P4M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	
//	//输出
//	P5M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P5M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//输入
//	P5M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P5M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	

//------------------------------------------定时器0配置	    	
   	 AUXR |= 0x80;      //定时器0为1T模式
// 	 AUXR &= 0x7f;      //定时器0为12T模式
	TMOD &= 0xf0;		//设置定时器模式 工作方式0,16位自动重载	
	TL0 = T0Timer;		//设置定时初值
	TH0 = T0Timer>>8;	//设置定时初值125us 
    TR0 = 1;            //定时器0开始计时
    ET0 = 1;            //使能定时器0中断
//------------------------------------------串口波特率配置：0检验位，1停止位
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
   	T2L = (65536 - (FOSC/4/BAUD));   //设置波特率重装值
    T2H = (65536 - (FOSC/4/BAUD))>>8;
	AUXR |= 0x10;		//启动定时器2
	ES = 1;             //串口中断打开
//------------------------------------------    
//	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
//	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
//    	SCON = 0x5a;                    //8 bit data ,no parity bit
//    	TMOD = 0x20;                    //T1 as 8-bit auto reload
////    	TH1 = TL1 = -(FOSC/32/BAUD); //Set Uart baudrate
//   	T1L = (65536 - (FOSC/4/BAUD));   //设置波特率重装值
//    T1H = (65536 - (FOSC/4/BAUD))>>8;
//  TR1 = 1;                        //T1 start running
////---------------------------------------------外部中断0配置	
    INT0 = 1;
    IT0 = 1;                    //设置INT0的中断类型 (1:仅下降沿 0:上升沿和下降沿)
    EX0 = 1;                    //使能INT0中断
    
//------------------------------------------ 总中断配置
    EA = 1;
    	
//-------------------------------------------看门狗配置
    WDT_CONTR = 0x02;       //看门狗定时器溢出时间计算公式: (12 * 32768 * PS) / FOSC (秒)
                            //设置看门狗定时器分频数为32,溢出时间如下:
                            //11.0592M : 1.14s
                            //18.432M  : 0.68s
                            //20M      : 0.63s
    WDT_CONTR |= 0x20;      //启动看门狗  
    
}

void SaveDateToErrom()
{

	if(Flg_ToErrom)//保存区域分界线的值
		{
		IapEraseSector(0x000);
		IapProgramByte(0x001,0>>8);	//
		IapProgramByte(0x002,0);
		IapProgramByte(0x003,0>>8);	//
		IapProgramByte(0x004,0);	
		IapProgramByte(0x005,0>>8);	//
		IapProgramByte(0x006,0);
		IapProgramByte(0x007,0>>8);	//
		IapProgramByte(0x008,0);	
		IapProgramByte(0x009,0>>8);	//
		IapProgramByte(0x00a,0);
		IapProgramByte(0x00b,0>>8);	//
		IapProgramByte(0x00c,0);	
		IapProgramByte(0x00d,00>>8);	//
		IapProgramByte(0x00e,00);
		IapProgramByte(0x00f,0);	//
		IapProgramByte(0x010,0);					
		IapProgramByte(0x011,0);
		IapProgramByte(0x012,0);
		IapProgramByte(0x013,0);
		IapProgramByte(0x000,0x55);
		Flg_ToErrom=0;				
		}

}