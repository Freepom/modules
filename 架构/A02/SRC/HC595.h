#ifndef _hc595_H_
#define _hc595_H_
#include "stc15w.h"
#include <intrins.h>

sbit SEG_SCK=P2^5;
sbit SEG_DT=P2^3;
sbit SEG_STCK=P2^4;

//#define NOP() _nop_()
void HC595(unsigned char Data_COM,unsigned char Data_Seg);

#endif
