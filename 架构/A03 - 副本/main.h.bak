#ifndef _MAIN_H
#define _MAIN_H

#include "stc15w.h"

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

#define FOSC    33177600L//22118400//11092500L
#define BAUD    460800//9600
#define T0Cycle    125//625//us
#define T0Timer (65536-FOSC/100*T0Cycle/10000L)//FOSC*T1Cycle直接相乘已超过数据长度，故先缩小FOSC

		    
#define ClrWDT	{WDT_CONTR |= 0x10;}//清看门狗，喂狗程序			
#define IAP_ENABLE 0x60 //IAP允许
sfr IAP_CNTR = 0xC7; //IAP控制寄存器
//---------------------------------------------
#define CALL_isr_UART1()    TI = 1         //串口发送使能

#endif
