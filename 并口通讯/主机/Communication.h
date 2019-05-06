#ifndef _Communication_H_
#define _Communication_H_
#include "stc15w.h"
#include <intrins.h>

sbit Pin_Bit0=P2^6;
sbit Pin_Bit1=P2^7;
sbit Pin_Bit2=P1^1;
sbit Pin_Bit3=P1^2;
sbit Pin_Bit4=P1^3;
sbit Pin_Bit5=P1^4;
sbit Pin_Bit6=P1^5;
sbit Pin_Bit7=P5^4;

//sbit Pin_Bit0=P2^0;
//sbit Pin_Bit1=P2^1;
//sbit Pin_Bit2=P2^2;
//sbit Pin_Bit3=P2^3;
//sbit Pin_Bit4=P2^4;
//sbit Pin_Bit5=P2^5;
//sbit Pin_Bit6=P2^6;
//sbit Pin_Bit7=P2^7;

sbit Pin_RW=P5^5;
sbit Pin_Cs1=P3^5;
sbit Pin_Cs2=P3^6;
sbit Pin_Cs3=P2^5;
sbit Pin_Cs4=P3^7;

extern bit Flg_ToSend,Flg_ToRec;
extern unsigned char R_RecDataA1,R_RecDataA2;
extern unsigned char R_RecDataB1,R_RecDataB2;
extern unsigned char R_RecDataC1,R_RecDataC2;
extern unsigned char R_RecDataD1,R_RecDataD2;
void SetPin();
unsigned char ReadPin();
void WritePin(unsigned char R_Data);
//unsigned char CheckBusy(void);
//void WriteData(unsigned char Data);
//unsigned char ReadData(void);
void SendData(unsigned char Data1,Data2);
void RecData();
#endif
