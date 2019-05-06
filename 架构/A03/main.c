//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//��Ŀ���ƣ�����ܹ�DEMO
//������Ա������ƽ
//��ϵ��ʽ��doit0827@foxmail.com/15915979843
//����������C51����
//�������ߣ�keil-V5
//����MCU�ͺţ�STC15W**
//����汾��A03
//�������ڣ�2017-10-29 17:21:52
//�������ݣ�
//--------1���ӳ������� 2����Ӵ���ͨѶ���� 3������˵��ע��
//--------
//--------
//��ע��
//		����Ƶ�ʣ�33.1776M Hz
//		���ڲ����ʣ�460800Bps
//		
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "main.h"
#include "display.h"
#include "ReadKey.h"
#include "eerom.h"
//-----------------��ѭ���ܹ��Ķ���-----------------------------------

sbit Pin_Relay1=P3^5;//
sbit Pin_Relay2=P3^4;//
sbit Pin_Relay3=P3^3;//

u8 R_RlDelayOpen;

u16 R_MainTemper;
//u8 	R_TimerMSCnt;
u8	R_2ms=0;//2ms��ʱ
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
sbit Flg_AutoMode=R_Flag^0;	//=1���Զ�ģʽ��=0���ֶ�ģʽ
sbit Flg_SetMode=R_Flag^1;	//=1������ģʽ��=0��������ģʽ
sbit Flg_RelayWk1=R_Flag^2;		//�̵���1
sbit Flg_RelayWk2=R_Flag^3;		//�̵���1
sbit Flg_RelayWk3=R_Flag^4;		//�̵���1
sbit Flg_ToAdd=R_Flag^5;		//
sbit Flg_RelayWkBak1=R_Flag^6;		//
sbit Flg_RelayWkBak2=R_Flag^7;		//

//----------------------------------------------------------
/**********************************************************************************/
//----����ɨ�衢������⡢��������Ķ���-----------------------------------

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
//��������
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
/*---------------��ѭ��---------------------
//--------------------------------------------
/���룺
/�����
/��ע��
/	
*/
//-------------------------------------------
main()
{
	Sys_Initial();	//��ʱ����ʼ��

//	if(IapReadByte(0x0000)!=0x55)//��������ֽ��ߵ�ֵ
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
	
	DealKey();	//��������
	CheckError();
	Recovery();
	RelayDrv();
	
	if(Flg_2ms)	//10�����ʱ����
		{
		Flg_2ms=0;

		if(++R_JmpmsCnt == 10)R_JmpmsCnt=0;
		switch(R_JmpmsCnt)	//2�����ʱ����
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
					ReadR_KeyValue();	//����ת��
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
					Timer50msCnt();	//20�����ʱ
				break;
			default:
				break;																
			}
		}	
	}
}
//-------------------------------------------
/*---------------��ʱ���ж��ӳ���------------
/���룺��ʱ��T0�ж�
/�����2�����־Flg_2ms=1������ɨ��
/��ע����ʱ��0��ʽ2,16λ�Զ����أ���ʱ125us
/
*/
//-------------------------------------------
void Inter_Timer0()interrupt 1
{
	static u8 R_MSCnt=0;
//	TL0 = 0x9A;		//���ö�ʱ��ֵ
//	TH0 = 0xFA;		//���ö�ʱ��ֵ125us
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
	KeyScan();	//����ɨ��
//	DispDrv();	
	
}
//-------------------------------------------
/*---------------�����ж��ӳ���------------
/���룺�����ж�
/�����
/��ע��
/
*/
//-------------------------------------------
void Inter_Serial() interrupt 4
{
   	unsigned char len, i;
  	unsigned int j=0;	
  	static u8 R_RCnt;
//	RI=0;
// 	if(0x7F == SBUF) //? ? ? ? ? ? ?//�ж��Ƿ�Ϊ��������Ϣ
// 	{
// 	IAP_CNTR =IAP_ENABLE; //?//����IAP, Ҳ����ֱ�ӽ������س���
//	// soft_reset();
// 	}

  	if(RI)//780ms,22MHz ����һ������Ҫ80us
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
//					if(i==len)//�������
					{
						REN=0;
 						Flg_StartUART=0;
 						R_RCnt=0;
					}					
				}
	}
	else if(!RI && TI)//����
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
/*---------------�ⲿ�ж�0�ӳ���------------
//--------------------------------------------
/���룺
/�����
/��ע���½��ش���
/
*/
//-------------------------------------------
void Inter_Ext0() interrupt 0       //INT0�ж����
{
//    FLAG = INT0;                //����INT0�ڵ�״̬, INT0=0(�½���); INT0=1(������)
}
//-------------------------------------------
/*---------------��ʾ���ݸ����ӳ���------------
//--------------------------------------------
/���룺��Ҫ��ʾ������
/�������ʾ����R_DBUF1,R_DBUF2,R_DBUF3,R_DBUF4�ȣ�������ʾ������
/��ע������2���׷�ʱ�е���
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
/*---------------20�����ʱ�ӳ���------------
//--------------------------------------------
/���룺��Ҫ��ʱ�ı���
/�����������Ԥ���Ľ��
/��ע������2���׷�ʱ�е���
/	��ʱ��λ�У�20ms��500ms��1S
*/
//-------------------------------------------
void	Timer50msCnt()
{
	static char R_500msCnt,R_100msCnt;		
	R_500msCnt++;
	R_100msCnt++;

//	R_PinCnt=5;	
//----------��ʱ50ms------------------------------------		
	{
	if(R_100msCnt==5)
		{
		R_100msCnt=0;
		
		}	
			
	}

//----------��ʱ20ms---END---------------------------------	

//----------��ʱ500ms------------------------------------	
	if(R_500msCnt == 25)
		{
		R_500msCnt=0;	
//		CALL_isr_UART1();
//----------�˶�Ϊ500ms------------------------------------

		Flg_500MsFlash=!Flg_500MsFlash;	

//----------��ʱ1s------------------------------------
				
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
        	
//------	----�˶�Ϊ1s------------------------------------			
        	
			}		
//----------��ʱ1s---END---------------------------------					
		}

//----------��ʱ500ms--END----------------------------------
}
//-------------------------------------------
/*---------------���ڷ������ݴ����ӳ���------------
//--------------------------------------------
/���룺
/�����
/��ע����ѭ���е���
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
/*---------------���ڽ������ݴ����ӳ���------------
//--------------------------------------------
/���룺
/�����
/��ע����ѭ���е���
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

	CALL_isr_UART1();	//����ACK
	ClearData_UART(1);	
}
//-------------------------------------------
/*---------------UART���ݴ����ӳ���------------
//--------------------------------------------
/���룺
/�����
/��ע����ѭ���е���
/
*/
//-------------------------------------------
void	ClearData_UART(bit Flg_Sta)//Flg_Sta=1�������ݻ������㣬Flg_Sta=0�������ݻ�������
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
/*---------------���������ӳ���------------
//--------------------------------------------
/���룺����������־Flg_HaveKey��������ֵR_CurKey��˫����������־FLG_keyDouble��
/	����δ�ͷű�־FLG_keymark,������������־Flg_LongKey
/�����������������
/��ע����ѭ���е���
/
*/
//-------------------------------------------
void	DealKey()//������ѭ����ִ��
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
						if(Flg_LongKey)//��������Ӧ
							{
	
							}
							else//�ͷż���Ӧ
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
						if(Flg_LongKey)//��������Ӧ
							{
						
							}
							else//�ͷż���Ӧ
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
/*---------------����ɨ���ӳ���------------
//--------------------------------------------
/���룺
/���������������ֵR_KeyValue�����ڰ����м��ʹ��
/��ע����ʱ���ж��ӳ����е���
/
*/
//-------------------------------------------	
void	KeyScan()//�����жϺ�����ִ��125usִ��һ��
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
/*---------------��������ӳ���------------
//--------------------------------------------
/���룺
/�����
/��ע��
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
/*--------------�����ָ��ӳ���------------
//--------------------------------------------
/���룺
/�����
/��ע��
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
/*---------------�̵��������ӳ���------------
//--------------------------------------------
/���룺
/�����
/��ע��
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
/*---------------��ʼ���ӳ���------------
//--------------------------------------------
/���룺
/�����
/��ע����ʱ����ʼ�������Ź���ʼ��
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
//	//���
//	P0M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P0M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//����
//	P0M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P0M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	
//	//���
//	P1M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P1M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//����
//	P1M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P1M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	
//	//���
//	P2M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P2M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//����
//	P2M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P2M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	
//	//���
//	P3M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P3M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//����
//	P3M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P3M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//���
//	P4M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P4M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//����
//	P4M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P4M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	
//	//���
//	P5M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P5M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
//	//����
//	P5M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
//	P5M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	

//------------------------------------------��ʱ��0����	    	
   	 AUXR |= 0x80;      //��ʱ��0Ϊ1Tģʽ
// 	 AUXR &= 0x7f;      //��ʱ��0Ϊ12Tģʽ
	TMOD &= 0xf0;		//���ö�ʱ��ģʽ ������ʽ0,16λ�Զ�����	
	TL0 = T0Timer;		//���ö�ʱ��ֵ
	TH0 = T0Timer>>8;	//���ö�ʱ��ֵ125us 
    TR0 = 1;            //��ʱ��0��ʼ��ʱ
    ET0 = 1;            //ʹ�ܶ�ʱ��0�ж�
//------------------------------------------���ڲ��������ã�0����λ��1ֹͣλ
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
   	T2L = (65536 - (FOSC/4/BAUD));   //���ò�������װֵ
    T2H = (65536 - (FOSC/4/BAUD))>>8;
	AUXR |= 0x10;		//������ʱ��2
	ES = 1;             //�����жϴ�
//------------------------------------------    
//	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
//	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
//    	SCON = 0x5a;                    //8 bit data ,no parity bit
//    	TMOD = 0x20;                    //T1 as 8-bit auto reload
////    	TH1 = TL1 = -(FOSC/32/BAUD); //Set Uart baudrate
//   	T1L = (65536 - (FOSC/4/BAUD));   //���ò�������װֵ
//    T1H = (65536 - (FOSC/4/BAUD))>>8;
//  TR1 = 1;                        //T1 start running
////---------------------------------------------�ⲿ�ж�0����	
    INT0 = 1;
    IT0 = 1;                    //����INT0���ж����� (1:���½��� 0:�����غ��½���)
    EX0 = 1;                    //ʹ��INT0�ж�
    
//------------------------------------------ ���ж�����
    EA = 1;
    	
//-------------------------------------------���Ź�����
    WDT_CONTR = 0x02;       //���Ź���ʱ�����ʱ����㹫ʽ: (12 * 32768 * PS) / FOSC (��)
                            //���ÿ��Ź���ʱ����Ƶ��Ϊ32,���ʱ������:
                            //11.0592M : 1.14s
                            //18.432M  : 0.68s
                            //20M      : 0.63s
    WDT_CONTR |= 0x20;      //�������Ź�  
    
}

void SaveDateToErrom()
{

	if(Flg_ToErrom)//��������ֽ��ߵ�ֵ
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