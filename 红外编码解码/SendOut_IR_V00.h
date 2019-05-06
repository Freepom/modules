/*****************************************************/
//   红外编码发送
//作者：林其平  QQ：578218949
//版本：V00
//日期：2017年08月06日 完成
//备注：利用定时器中断扫描IO，扫描周期125us，电平时间计算需配合定时器时间
/*****************************************************/
#ifndef _SENDOUT_IR_H_
#define _SENDOUT_IR_H_

#include "stc15w.h"

sbit Pin_PWM=P3^0;

#define D_ModeCycleWait 	0	//Flg_TxSta=0
#define D_ModeTxHight 		1       //Flg_TxSta=1
#define D_ModeTxLow		2       //Flg_TxSta=0
#define D_ModeTxLead9ms		3       //Flg_TxSta=1
#define D_ModeTxLead45ms	4       //Flg_TxSta=0

#define D_TimerDuty 125	//定时器周期
#define D_TxTm168ms	1680/D_TimerDuty
#define D_TxTm056ms	560/D_TimerDuty
#define D_TxTm9ms	9000/D_TimerDuty
#define D_TxTm45ms	4500/D_TimerDuty
#define D_TxTm108ms	128000UL/D_TimerDuty

#define D_SendByteCnt 4	//更改此处的值可以改变接收的字节数
extern unsigned char R_SendByteCnt;//可接收字节数，默认4个字节
extern unsigned char SendData_Tab[D_SendByteCnt];
extern bit Flg_TxStart;	//=1，使能发送，=0，不发送，默认=0，不发送
extern bit Flg_TxSta;	//实际控制标志，对应每个状态
void SendOut_IR();

#endif