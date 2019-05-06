#ifndef _MAIN_H
#define _MAIN_H

#include "stc15w.h"

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

#define FOSC    33177600L//22118400//11092500L
#define BAUD    9600//460800//
#define T0Cycle    125//625//us
#define T0Timer (65536-FOSC/100*T0Cycle/10000L)//FOSC*T1Cycleֱ������ѳ������ݳ��ȣ�������СFOSC

		    
#define ClrWDT	{WDT_CONTR |= 0x10;}//�忴�Ź���ι������			
#define IAP_ENABLE 0x60 //IAP����
sfr IAP_CNTR = 0xC7; //IAP���ƼĴ���
//---------------------------------------------
#define CALL_isr_UART1()    TI = 1         //���ڷ���ʹ��

#endif
