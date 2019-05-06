#include "Reciving_IR.h"

bit Flg_IRSta;//电平状态标志位
bit Flg_RxStart;//开始接收数据
bit Flg_RxIROK;//接收数据完成
bit Flg_IRReplayKey;//连续键
unsigned char R_HightCnt,R_LowCnt,R_RxDataCnt;//高电平计数，低电平计数，字节计数
unsigned char R_RxDataTemp;
unsigned char R_RxByteCnt=D_RxByteCnt;
unsigned char RxData_Tab[D_RxByteCnt];//接收数据缓存

void REciving_IR()
{
	if(Pin_IR)
		{
		if(R_HightCnt<0xff)
		R_HightCnt++;

//		if((R_LowCnt>D_LeadTm9Ms)&& (Flg_IRSta==0))
//			{
//			R_LowCnt=0;//引导码9ms	
//			}
		R_LowCnt=0;	
		Flg_IRSta=1;	
		}	
		else
			{
			if(R_LowCnt<0xff)	
			R_LowCnt++;
			if(Flg_RxStart&&Flg_IRSta)//从高变低时，判断逻辑“1”或“0”
				{
				R_RxDataCnt++;	
				R_RxDataTemp <<= 1;
				if(R_HightCnt>D_HightTm169Ms&&R_HightCnt<D_LeadTm45Ms)
					{					
					R_RxDataTemp |= 0x01;	//逻辑“1”
					}
					else
						{ 
						R_RxDataTemp &= ~0x01;	//逻辑“0”	
						}
						

				if(R_RxDataCnt%8==0)
					{
					RxData_Tab[R_RxDataCnt/8-1]=R_RxDataTemp;	
					}
				if(R_RxDataCnt == R_RxByteCnt*8)
					{
//					RxData_Tab[3]=R_RxDataTemp;
					Flg_RxStart=0;//接收完成
					Flg_RxIROK=1;
					Flg_IRReplayKey=0;
					}																							
				}
			if(((R_HightCnt>D_LeadTm45Ms)&&R_HightCnt<D_LeadTm9Ms)&&(Flg_IRSta)&&(!Flg_RxStart))//引导码4.5ms
				{					
				R_RxDataCnt=0;
				Flg_RxStart=1;	//开始接收数据
				Flg_IRReplayKey=0;
				}
			if((R_HightCnt>D_LeadTm2Ms)&&R_HightCnt<D_LeadTm45Ms)//引导码2ms 长按键判断
				{
//				Flg_IRReplayKey=1;
//				Flg_RxIROK=1;	
				}
				else
					Flg_IRReplayKey=0;					
//				else if(((R_HightCnt<=25)||R_HightCnt>=60)&&(Flg_IRSta)&&(!Flg_RxStart))
//					{
//					Flg_RxStart=0;	
//					}
					
			R_HightCnt=0;
			Flg_IRSta=0;	
			}			
}