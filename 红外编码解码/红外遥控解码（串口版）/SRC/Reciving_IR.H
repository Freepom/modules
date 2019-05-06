/*****************************************************/
//   红外接收解码
//作者：林其平  QQ：578218949
//版本：V00
//日期：2017年08月06日 完成
//备注：利用定时器中断扫描IO，扫描周期125us，电平时间计算需配合定时器时间
/*****************************************************/
#ifndef _RECIVING_IR_H_
#define _RECIVING_IR_H_

#include "stc15w.h"

//sbit Pin_led=P5^0;
sbit Pin_IR=P3^2;

#define D_TimerDuty 125	//定时器周期

#define D_LeadTm9Ms (9000-1000)/D_TimerDuty	//9MS的引导码
#define D_LeadTm45Ms (4500-1000)/D_TimerDuty	//4.5MS的引导码
#define D_LeadTm2Ms (2000-400)/D_TimerDuty	//2MS的引导码，做长按键时判断条件
#define D_HightTm169Ms (1690-400)/D_TimerDuty	//大于这个时间表示逻辑“1”，小于表示“0”
#define D_LowTm056Ms (560)/D_TimerDuty
//#define D_LeadTm9Ms (9000)/D_TimerDuty-3	//9MS的引导码
//#define D_LeadTm45Ms (4300)/D_TimerDuty-3	//4.5MS的引导码
//#define D_LeadTm2Ms (2000)/D_TimerDuty-3	//2MS的引导码，做长按键时判断条件
//#define D_HightTm169Ms (1600)/D_TimerDuty-5	//大于这个时间表示逻辑“1”，小于表示“0”
//#define D_LowTm056Ms (560)/D_TimerDuty

#define D_RxByteCnt 4	//更改此处的值可以改变接收的字节数
extern unsigned char R_RxByteCnt;//可接收字节数，默认4个字节
extern unsigned char RxData_Tab[D_RxByteCnt];//byte0:用户码，byte1:用户码反码，byte2:操作码，byte3:操作码反码
extern bit Flg_RxIROK;	//接收完成标志位，
extern bit Flg_IRReplayKey;//连续键
void REciving_IR();

#endif