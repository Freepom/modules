
#include "HC595.h"

//--------------------------------------------------------
//数码管SEG口的数据发送
//
//
//--------------------------------------------------------
void HC595(unsigned char Data_COM,unsigned char Data_Seg)
{
unsigned char i;


		
	for(i=0;i<8;i++)//SEG口数据
		{
		SEG_SCK=0;
		_nop_();
		_nop_();
		if((Data_Seg<<i)&0x80)SEG_DT=1;
			else SEG_DT=0;
		_nop_();
		_nop_();
		SEG_SCK=1;
 		_nop_();
		_nop_();
		}
	i=0;	
	for(i=0;i<8;i++)//COM口数据
		{
		SEG_SCK=0;
		_nop_();
		_nop_();
		if((Data_COM<<i)&0x80)SEG_DT=1;
			else SEG_DT=0;
		_nop_();
		_nop_();
		SEG_SCK=1;
		_nop_();
		_nop_();
		}				
	SEG_STCK=0;
	_nop_();
	_nop_();
	SEG_STCK=1;
}