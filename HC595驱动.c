#include <intrins.h>

#define NOP() _nop_()

sbit SEG_SCK=P2^7;
sbit SEG_DT=P0^6;
sbit SEG_STCK=P0^7;

//--------------------------------------------------------
//数码管SEG口的数据发送
//
//
//--------------------------------------------------------
void HC595SendData_Seg(unsigned char SendVal)
{
unsigned char i;

for(i=0;i<8;i++)
{
	SEG_SCK=0;
	NOP();
	NOP();
	if((SendVal<<i)&0x80)SEG_DT=1;
		else SEG_DT=0;
	NOP();
	NOP();
	SEG_SCK=1;
	}
	SEG_STCK=0;
	NOP();
	NOP();
	SEG_STCK=1;
}