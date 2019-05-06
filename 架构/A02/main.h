#ifndef _MAIN_H
#define _MAIN_H

#include "stc15w.h"

#define u8 unsigned char
#define u16 unsigned int

#define FOSC    11092500L
#define BAUD    9600
#define T1Timer (65536-FOSC/8000)
#define PinPP(Pn,n) {switch(Pn){\							
			case 0:P0M1 &= ~(1 << n);P0M0 |=  (1 << n);break;\
			case 1:P1M1 &= ~(1 << n);P1M0 |=  (1 << n);break;\
			case 2:P2M1 &= ~(1 << n);P2M0 |=  (1 << n);break;\
			case 3:P3M1 &= ~(1 << n);P3M0 |=  (1 << n);break;\
			case 4:P4M1 &= ~(1 << n);P4M0 |=  (1 << n);break;\
			case 5:P5M1 &= ~(1 << n);P5M0 |=  (1 << n);break;\										
    			default:break;\    									     										
			}\
		    }
		    
#define ClrWDT	{WDT_CONTR |= 0x10;}//�忴�Ź���ι������			
#define IAP_ENABLE 0x60 //IAP����
sfr IAP_CNTR = 0xC7; //IAP���ƼĴ���
//---------------------------------------------


#endif
