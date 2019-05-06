#include "SendOut_IR.h"

unsigned int R_SendTm=1;
unsigned char R_SendMode=D_ModeCycleWait;
unsigned char R_SendDataTemp;
unsigned char R_SendBitCnt,R_SendByteCnt=D_SendByteCnt;
unsigned char SendData_Tab[D_SendByteCnt]={0x00,0xff,0xaa,0x55};

bit Flg_TxSta,Flg_TxStart;
void SendOut_IR()
{
	if(Flg_TxStart==0)
		{
		R_SendMode=D_ModeCycleWait;
		R_SendBitCnt=0;
		R_SendTm=1;
		return;	
		}
	switch(R_SendMode)
	{
		case D_ModeCycleWait://间隔时间
				if(R_SendTm)
					{
					R_SendTm--;
					if(!R_SendTm)
						{
						R_SendMode=D_ModeTxLead9ms;
						R_SendTm=D_TxTm9ms;	
						}	
					}
				Flg_TxSta=0;	
			break;
		case D_ModeTxLead9ms://引导码9毫秒时间
				if(R_SendTm)
					{
					R_SendTm--;
					if(!R_SendTm)
						{
						R_SendMode=D_ModeTxLead45ms;
						R_SendTm=D_TxTm45ms;	
						}	
					}
				Flg_TxSta=1;//=1，发红外，接收端输出低电平				
			break;
		case D_ModeTxLead45ms://引导码4.5毫秒时间
				if(R_SendTm)
					{
					R_SendTm--;
					if(!R_SendTm)
						{
						R_SendMode=D_ModeTxHight;
						R_SendTm=D_TxTm056ms;	
						}	
					}
				Flg_TxSta=0;//=0，不发红外，接收端输出高电平				
			break;						
		case D_ModeTxHight://高电平时间0.56毫秒,对应接收端的低电平
				if(R_SendTm)
					{
					R_SendTm--;
					if(!R_SendTm)
						{
						
						if(R_SendBitCnt%8==0)//结果=0,1,2,3
							{
							R_SendDataTemp=SendData_Tab[R_SendBitCnt/8];	
							}
						R_SendBitCnt++;	
						R_SendMode=D_ModeTxLow;
						if( (R_SendDataTemp>>(R_SendBitCnt%8)) & 0x01)
							R_SendTm=D_TxTm168ms;//逻辑“1”时的时间
							else
								R_SendTm=D_TxTm056ms;//逻辑“0”时的时间									
						}	
					}
				Flg_TxSta=1;//=1，发红外，接收端输出低电平				
			break;
		case D_ModeTxLow://根据数据逻辑“0”=D_TxTm056ms，或“1”=D_TxTm168ms,对应接收端的高电平
				if(R_SendTm)
					{
					R_SendTm--;
					if(!R_SendTm)
						{
						R_SendMode=D_ModeTxHight;
						R_SendTm=D_TxTm056ms;
						if(R_SendBitCnt==R_SendByteCnt*8+1)//发完最后一个bit	
							{
							R_SendBitCnt=0;	
							R_SendMode=D_ModeCycleWait;
							R_SendTm=D_TxTm108ms;	
							}	
						}	
					}
				Flg_TxSta=0;//=0，不发红外，接收端输出高电平				
			break;
		default:
			break;										
	}

	if(Flg_TxSta)
		{
		AUXR |=  (1<<4);    //开始运行	
		INT_CLKO |=  0x04;  //输出时钟
		}
		
		else
			{
			AUXR &=  ~(1<<4);    //停止运行	
			INT_CLKO &=  ~0x04;  //停止输出时钟
			Pin_PWM=1;
	
			}
					
}