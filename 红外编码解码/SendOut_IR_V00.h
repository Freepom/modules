/*****************************************************/
//   ������뷢��
//���ߣ�����ƽ  QQ��578218949
//�汾��V00
//���ڣ�2017��08��06�� ���
//��ע�����ö�ʱ���ж�ɨ��IO��ɨ������125us����ƽʱ���������϶�ʱ��ʱ��
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

#define D_TimerDuty 125	//��ʱ������
#define D_TxTm168ms	1680/D_TimerDuty
#define D_TxTm056ms	560/D_TimerDuty
#define D_TxTm9ms	9000/D_TimerDuty
#define D_TxTm45ms	4500/D_TimerDuty
#define D_TxTm108ms	128000UL/D_TimerDuty

#define D_SendByteCnt 4	//���Ĵ˴���ֵ���Ըı���յ��ֽ���
extern unsigned char R_SendByteCnt;//�ɽ����ֽ�����Ĭ��4���ֽ�
extern unsigned char SendData_Tab[D_SendByteCnt];
extern bit Flg_TxStart;	//=1��ʹ�ܷ��ͣ�=0�������ͣ�Ĭ��=0��������
extern bit Flg_TxSta;	//ʵ�ʿ��Ʊ�־����Ӧÿ��״̬
void SendOut_IR();

#endif