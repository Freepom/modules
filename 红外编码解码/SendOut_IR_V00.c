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
		case D_ModeCycleWait://���ʱ��
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
		case D_ModeTxLead9ms://������9����ʱ��
				if(R_SendTm)
					{
					R_SendTm--;
					if(!R_SendTm)
						{
						R_SendMode=D_ModeTxLead45ms;
						R_SendTm=D_TxTm45ms;	
						}	
					}
				Flg_TxSta=1;//=1�������⣬���ն�����͵�ƽ				
			break;
		case D_ModeTxLead45ms://������4.5����ʱ��
				if(R_SendTm)
					{
					R_SendTm--;
					if(!R_SendTm)
						{
						R_SendMode=D_ModeTxHight;
						R_SendTm=D_TxTm056ms;	
						}	
					}
				Flg_TxSta=0;//=0���������⣬���ն�����ߵ�ƽ				
			break;						
		case D_ModeTxHight://�ߵ�ƽʱ��0.56����,��Ӧ���ն˵ĵ͵�ƽ
				if(R_SendTm)
					{
					R_SendTm--;
					if(!R_SendTm)
						{
						
						if(R_SendBitCnt%8==0)//���=0,1,2,3
							{
							R_SendDataTemp=SendData_Tab[R_SendBitCnt/8];	
							}
						R_SendBitCnt++;	
						R_SendMode=D_ModeTxLow;
						if( (R_SendDataTemp>>(R_SendBitCnt%8)) & 0x01)
							R_SendTm=D_TxTm168ms;//�߼���1��ʱ��ʱ��
							else
								R_SendTm=D_TxTm056ms;//�߼���0��ʱ��ʱ��									
						}	
					}
				Flg_TxSta=1;//=1�������⣬���ն�����͵�ƽ				
			break;
		case D_ModeTxLow://���������߼���0��=D_TxTm056ms����1��=D_TxTm168ms,��Ӧ���ն˵ĸߵ�ƽ
				if(R_SendTm)
					{
					R_SendTm--;
					if(!R_SendTm)
						{
						R_SendMode=D_ModeTxHight;
						R_SendTm=D_TxTm056ms;
						if(R_SendBitCnt==R_SendByteCnt*8+1)//�������һ��bit	
							{
							R_SendBitCnt=0;	
							R_SendMode=D_ModeCycleWait;
							R_SendTm=D_TxTm108ms;	
							}	
						}	
					}
				Flg_TxSta=0;//=0���������⣬���ն�����ߵ�ƽ				
			break;
		default:
			break;										
	}

	if(Flg_TxSta)
		{
		AUXR |=  (1<<4);    //��ʼ����	
		INT_CLKO |=  0x04;  //���ʱ��
		}
		
		else
			{
			AUXR &=  ~(1<<4);    //ֹͣ����	
			INT_CLKO &=  ~0x04;  //ֹͣ���ʱ��
			Pin_PWM=1;
	
			}
					
}