#ifndef __AT24C_H
#define __AT24C_H

#include<stc15w.h>
#include <intrins.h>

sbit sda=P3^5;                          //IO¿Ú¶¨Òå
sbit scl=P3^4;

void  Delay_AT24C(unsigned char x);
void flash();
void Init_AT24C();
void start();
void stop();
void writex(unsigned char j);
unsigned char readx();
void clock();
unsigned char AT24C_Read(unsigned char address);
void AT24C_Write(unsigned char address,unsigned char info);
/////////////////////////////////////////////////

#endif