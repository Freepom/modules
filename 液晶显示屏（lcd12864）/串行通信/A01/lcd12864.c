///////////void lcd_wdate(u8 X,u8 Y,u8 *date)
///////////void LCD_Init(void)
#include "lcd12864.h"
/********************************************************************
********************************************************************/

sbit CS=P2^7; //CS=RS
sbit SID=P1^1; //RW=SID
sbit SCLK=P2^6; //E=SCLK
//sbit LCD_PSB =  P3^7;  //��Ӳ�����ͣ�����ͨ��
/******************************************************************/
void LCD_Init(void)
{

	u8 cmd;
	//LCD_PSB=0;
	cmd=0x30; //�������� 8 λ���ݣ�����ָ��
	W_1byte(0,0,cmd);
	Delay(1);
	cmd=0x0C; //��ʾ״̬ ON���α�OFF������OFF
	W_1byte(0,0,cmd); //дָ��
	Delay(1);
	cmd=0x01; //�����ʾ
	W_1byte(0,0,cmd); //дָ��
	Delay(1);
	cmd=0x02; //��ַ��λ
	W_1byte(0,0,cmd); //дָ��
	Delay(1);
	cmd=0x80; //����DDRAM ��ַ
	W_1byte(0,0,cmd); //дָ��
	Delay(1); //��ʱ
}
/*********************************************************/
/*                                                       */
/* �趨��ʾλ��                                          */
/*                                                       */
/*********************************************************/
void lcd_wdate(u8 X,u8 Y,u8 date)
{                          
   u8  pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;  
   W_1byte(0,0,pos);     //��ʾ��ַ
   W_1byte(0,1,date);
}
void lcd_wstr(u8 X,u8 Y,u8 *date)
{                          
   u8  pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;  
   W_1byte(0,0,pos);     //��ʾ��ַ
   while(*date != '\0')
   {
   W_1byte(0,1,*date);
         date++;
        }
  *date = 0;
}
/*******************************************************************
���� ����W_1byte
��ڲ�����RW��RS��W_data
���ڲ�������
�������ã�дһ���ֽڵ����ݵ�12864 Һ��������ָ�������
˵ ����RW=1����Һ�������ݵ�MCU��RW=0��дһ�����ݵ�Һ����
��һ��RW ����Ϊ0����ֻ��Һ��д���ݣ��������ݣ�
RS="1"��д��������ݣ�RS=0��д�����ָ�
һ��ģʽ��RW=0��RS=1;д����
RW="0"��RS=0;дָ��
********************************************************************/
void W_1byte(u8 RW, u8 RS, u8 W_data)
{
	u16 H_data,L_data,S_ID = 0xf8; //11111RWRS0
	if(RW == 0)
	{
	S_ID &=~ 0x04;
	}
		else //if(RW==1)
		{
		S_ID |= 0X04;
		}
	if(RS == 0)
	{
	S_ID &=~ 0x02;
	}
		else //if(RS==1)
		{
		S_ID |= 0X02;
		}
	H_data = W_data;
	H_data &= 0xf0; //���ε�4 λ������
	L_data = W_data; //xxxx0000 ��ʽ
	L_data &= 0x0f; //���θ�4 λ������
	L_data <<= 4; //xxxx0000 ��ʽ
	CS = 1;
	Write_8bits(S_ID); //����S_ID
	Write_8bits(H_data); //����H_data
	Write_8bits(L_data); //����L_data
	CS = 0;
}
/********************************************************************
���� ����Write_8bits
��ڲ�����W_bits
���ڲ�������
�������ã����������8 ��bit λ
********************************************************************/
void Write_8bits(u16 W_bits)
{
	u16 i,Temp_data;
	for(i=0; i<8; i++)
	{
		Temp_data = W_bits;
		Temp_data <<= i;
		if((Temp_data&0x80)==0) //bit7 is zero
			{
			SID = 0;
			nop;
			SCLK = 1;
			nop;
			nop;
			SCLK = 0;
			nop;
			SID = 0;
			}
			else //bit7 is one
				{
				SID = 1;
				nop;
				SCLK = 1;
				nop;
				nop;
				SCLK = 0;
				nop;
				SID = 0;
				}
	}
}
/********************************************************************
���� ����Delay
��ڲ�����ms
���ڲ�������
�������ã����뼶����ʱ���򣬵�����Ϊ12Mhz ʱ��xtal=12;
********************************************************************/
void Delay(u16 ms)
{

	while(ms--)
	{
	//for(i=1;i<(u16)(2);i++)
	//;
	nop;
	nop;
	nop;
	nop;
	}
} 