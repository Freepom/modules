#ifndef _12864_H_
#define _12864_H_

#include<main.h>
#include<intrins.h>

sbit cs1=P2^0;
sbit cs2=P2^1;
sbit rs=P2^2;
sbit wr=P2^3;
sbit en=P2^4;

void lcd_init();
void lcd_clear_scr();
void lcd_ch(uchar x,uchar y,uchar *ch);

void lcd_hanzi(uchar x,uchar y,uchar *ch);
void lcd_ch_str(uchar x,uchar y,uchar *date,uchar n);
void lcd_hanzi_str(uchar x,uchar y,uchar *date,uchar n);

#endif
