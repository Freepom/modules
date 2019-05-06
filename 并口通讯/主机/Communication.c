
#include "Communication.h"
bit Flg_ToSend,Flg_ToRec;
u8 R_RecMode;
u8 R_RecCnt;
u8 R_CSMode;
unsigned char R_RecDataA1,R_RecDataA2;
unsigned char R_RecDataB1,R_RecDataB2;
unsigned char R_RecDataC1,R_RecDataC2;
unsigned char R_RecDataD1,R_RecDataD2;
void RecData()
{

	if(R_RecCnt)
		{
		R_RecCnt--;	
		}
	switch(R_RecMode)
	{
		case 0://打开片选，准备接收数据
			Pin_Cs1=1;Pin_Cs2=1;
			Pin_Cs3=1;Pin_Cs4=1;
			switch(R_CSMode)
			{
				case 0:
					Pin_Cs1=0;
					break;
				case 1:
					Pin_Cs2=0;
					break;	
				case 2:
					Pin_Cs3=0;
					break;
				case 3:
					Pin_Cs4=0;
					break;	
				default:
					break;																
			}
 			
			Pin_RW=0;			
			R_RecCnt=2;
			R_RecMode=1;	
			break;
		case 1://片选保持2个单位时间
//			if(R_RecCnt==0)
				{
				R_RecMode=2;
				R_RecCnt=2;	
				}
			break;	
		case 2://读取数据保持2个单位时间
			switch(R_CSMode)
			{
				case 0:
					R_RecDataA1=ReadPin();
					break;
				case 1:
					R_RecDataB1=ReadPin();
					break;	
				case 2:
					R_RecDataC1=ReadPin();
					break;
				case 3:
					R_RecDataD1=ReadPin();
					break;	
				default:
					break;																
			}			
			
//			if(R_RecCnt==0)
				{
				R_RecMode=3;
				R_RecCnt=2;
						
				}
			break;
		case 3://片选关闭保持2个单位时间
			Pin_Cs1=1;Pin_Cs2=1;
			Pin_Cs3=1;Pin_Cs4=1;			
//			switch(R_CSMode)
//			{
//				case 0:
//					Pin_Cs1=1;
//					break;
//				case 1:
//					Pin_Cs2=1;
//					break;	
//				case 2:
//					Pin_Cs3=1;
//					break;
//				case 3:
//					Pin_Cs4=1;
//					break;	
//				default:
//					break;																
//			}			
//			if(R_RecCnt==0)
				{
				R_RecMode=4;
				R_RecCnt=2;
					
				}		
			break;	
		case 4://打开片选，准备接收数据第二个数据
			switch(R_CSMode)
			{
				case 0:
					Pin_Cs1=0;
					break;
				case 1:
					Pin_Cs2=0;
					break;	
				case 2:
					Pin_Cs3=0;
					break;
				case 3:
					Pin_Cs4=0;
					break;	
				default:
					break;																
			}			
			Pin_RW=0;			
			R_RecCnt=2;
			R_RecMode=5;
			break;	
		case 5://片选保持2个单位时间
//			if(R_RecCnt==0)
				{
				R_RecMode=6;
				R_RecCnt=2;		
				}
			break;	
		case 6://读取保持2个单位时间
			switch(R_CSMode)
			{
				case 0:
					R_RecDataA2=ReadPin();
					break;
				case 1:
					R_RecDataB2=ReadPin();
					break;	
				case 2:
					R_RecDataC2=ReadPin();
					break;
				case 3:
					R_RecDataD2=ReadPin();
					break;	
				default:
					break;																
			}
//			if(R_RecCnt==0)
				{
				R_RecMode=7;
				R_RecCnt=2;
//				Pin_Cs3=1;		
				}
			break;
		case 7://片选保持2个单位时间
			Pin_Cs1=1;Pin_Cs2=1;
			Pin_Cs3=1;Pin_Cs4=1;			
//			switch(R_CSMode)
//			{
//				case 0:
//					Pin_Cs1=1;
//					break;
//				case 1:
//					Pin_Cs2=1;
//					break;	
//				case 2:
//					Pin_Cs3=1;
//					break;
//				case 3:
//					Pin_Cs4=1;
//					break;	
//				default:
//					break;																
//			}			
//			if(R_RecCnt==0)
				{
				R_RecMode=0;
				R_RecCnt=2;
				Flg_ToRec=0;
				}
			R_CSMode++;
			if(R_CSMode==4)
				{
				R_CSMode=0;	
				}	
			break;							
		default:
			break;										
	}			
}
void SendData(unsigned char Data1,Data2)
{
	static u8 R_SendMode;
	static u8 R_SendCnt;
	
	if(R_SendCnt)
		{
		R_SendCnt--;	
		}
	switch(R_SendMode)
	{
		case 0:
			Pin_Cs1=0;Pin_Cs2=0;
			Pin_Cs3=0;Pin_Cs4=0;
			Pin_RW=1;			
			WritePin(Data1);
			R_SendCnt=2;
			R_SendMode=1;	
			break;
		case 1://数据保持2个单位时间
			if(R_SendCnt==0)
				{
				R_SendMode=2;
				R_SendCnt=2;	
				}
			break;	
		case 2://片选保持2个单位时间
			Pin_Cs1=1;Pin_Cs2=1;
			Pin_Cs3=1;Pin_Cs4=1;
			if(R_SendCnt==0)
				{
				R_SendMode=3;
				R_SendCnt=2;		
				}
			break;
		case 3:
			Pin_Cs1=0;Pin_Cs2=0;
			Pin_Cs3=0;Pin_Cs4=0;
			Pin_RW=1;			
			WritePin(Data2);
			R_SendCnt=2;
			R_SendMode=4;			
			break;	
		case 4://数据保持2个单位时间
			if(R_SendCnt==0)
				{
				R_SendMode=5;
				R_SendCnt=2;	
				}
			break;	
		case 5://片选保持2个单位时间
			Pin_Cs1=1;Pin_Cs2=1;
			Pin_Cs3=1;Pin_Cs4=1;
			
			if(R_SendCnt==0)
				{
				R_SendMode=0;
				R_SendCnt=2;
				Flg_ToSend=0;
				WritePin(0xff);
				R_RecMode=0;
				R_RecCnt=0;
				R_CSMode=0;			
				}
			
			break;	
		default:
			break;										
	}
}

void WritePin(unsigned char R_Data)
{
	if(R_Data&0x01)
		{
		Pin_Bit0=1;	
		}
		else
			{
			Pin_Bit0=0;	
			}
	if(R_Data&0x02)
		{
		Pin_Bit1=1;	
		}
		else
			{
			Pin_Bit1=0;	
			}
	if(R_Data&0x04)
		{
		Pin_Bit2=1;	
		}
		else
			{
			Pin_Bit2=0;	
			}
	if(R_Data&0x08)
		{
		Pin_Bit3=1;	
		}
		else
			{
			Pin_Bit3=0;	
			}
	if(R_Data&0x10)
		{
		Pin_Bit4=1;	
		}
		else
			{
			Pin_Bit4=0;	
			}
	if(R_Data&0x20)
		{
		Pin_Bit5=1;	
		}
		else
			{
			Pin_Bit5=0;	
			}
	if(R_Data&0x40)
		{
		Pin_Bit6=1;	
		}
		else
			{
			Pin_Bit6=0;	
			}
	if(R_Data&0x80)
		{
		Pin_Bit7=1;	
		}
		else
			{
			Pin_Bit7=0;	
			}									
}

unsigned char ReadPin()
{
	unsigned char R_temp=0;
	if(Pin_Bit0)
		{
		R_temp|=0x01;	
		}
	if(Pin_Bit1)
		{
		R_temp|=0x02;	
		}
	if(Pin_Bit2)
		{
		R_temp|=0x04;	
		}
	if(Pin_Bit3)
		{
		R_temp|=0x08;	
		}
	if(Pin_Bit4)
		{
		R_temp|=0x10;	
		}
	if(Pin_Bit5)
		{
		R_temp|=0x20;	
		}
	if(Pin_Bit6)
		{
		R_temp|=0x40;	
		}
	if(Pin_Bit7)
		{
		R_temp|=0x80;	
		}
	return 	R_temp;				
}
void SetPin()
{
	//输出
	P0M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
	P0M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
	//输入
	P0M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
	P0M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
	
	//输出
	P1M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
	P1M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
	//输入
	P1M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
	P1M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
	
	//输出
	P2M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
	P2M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
	//输入
	P2M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
	P2M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
	
	//输出
	P3M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
	P3M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
	//输入
	P3M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
	P3M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
	//输出
	P4M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
	P4M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
	//输入
	P4M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
	P4M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
	
	//输出
	P5M0|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
	P5M1&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);
	//输入
	P5M0&=~(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);	
	P5M1|=(0x01|0x02|0x04|0x08|0x10|0x20|0x40|0x80);					
}
