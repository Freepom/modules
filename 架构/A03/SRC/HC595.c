
#include "HC595.h"

//--------------------------------------------------------
//�����SEG�ڵ����ݷ���
//
//
//--------------------------------------------------------
void HC595(unsigned char Data_COM,unsigned char Data_Seg)
{
unsigned char i;


		
	for(i=0;i<8;i++)//SEG������
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
	for(i=0;i<8;i++)//COM������
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