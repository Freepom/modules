#include<reg52.h>
#define u8 unsigned char
#define u16 unsigned int

sbit MDO=P1^0;
sbit SCK=P3^6;
sbit CE=P3^2;
sbit IRQ=P1^1;
sbit MDI=P3^7;
sbit CSN=P3^3;

u8 SPI(u8 byte);
void REG_write(u8 address,u8 command);
void FIFO_read(u8 DATA_IN[]);
void FIFO_write(u8 DATA_OUT[]);
void RX_mode();
void TX_mode();
