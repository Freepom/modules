#ifndef __IIC_H_
#define __IIC_H_
#include<stc15w.h>
#include <intrins.h>

sbit sda=P3^6;                          //IO�ڶ���
sbit scl=P3^5;

void  delay1_IIC(unsigned char x);
void flash();
void x24c08_init();
void start();
void stop();
void writex(unsigned char j);
unsigned char readx();
void clock();
unsigned char x24c08_read(unsigned char address);
void x24c08_write(unsigned char address,unsigned char info);
/////////////////////////////////////////////////

#endif