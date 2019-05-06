#ifndef _Communication_H_
#define _Communication_H_
#include "stc15w.h"
#include <intrins.h>

//sbit Pin_Bit0=P2^6;
//sbit Pin_Bit1=P1^1;
//sbit Pin_Bit2=P2^7;
//sbit Pin_Bit3=P3^6;
//sbit Pin_Bit4=P3^3;
//sbit Pin_Bit5=P3^5;
//sbit Pin_Bit6=P3^4;
//sbit Pin_Bit7=P3^2;

sbit Pin_Bit0=P1^0;
sbit Pin_Bit1=P1^1;
sbit Pin_Bit2=P1^2;
sbit Pin_Bit3=P1^3;
sbit Pin_Bit4=P1^4;
sbit Pin_Bit5=P1^5;
sbit Pin_Bit6=P5^4;
sbit Pin_Bit7=P5^5;

sbit Pin_RW=P3^7;
sbit Pin_Cs=P3^6;

extern unsigned char R_SendData1,R_SendData2;
extern unsigned char R_RecData1,R_RecData2;
extern bit Flg_ToSend;

void SetPin();
unsigned char ReadPin();
void WritePin(unsigned char R_Data);
//unsigned char CheckBusy(void);
//void WriteData(unsigned char Data);
//unsigned char ReadData(void);
void RecData();
void SendData(unsigned char Data1,Data2);
#endif
