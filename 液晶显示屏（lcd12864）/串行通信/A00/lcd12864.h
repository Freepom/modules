#include <reg51.h>
#include <intrins.h>

#define nop _nop_()

//==========================================================
//==========
//��������
void Delay(uint ms); //��ʱ�ӳ���
//void Write_cmd(cmd); //дָ���ӳ���
//void Write_data(uchar _data); //д�����ӳ���
//void Position(ucha ����
//vvvvvvvvvvv
//vvvvvvvvvvvvvvvvvvvvvvvvvvvv r pos); //��λ����
//void Display(uchar address); //
//void Init_12864();
//void LcdSetXY(uchar x, uchar y, uchar *pt);
void lcd_wdate(uchar X,uchar Y,uchar *date);
void W_1byte(uchar RW, uchar RS, uchar W_data);
void Write_8bits(uint W_bits);
void LCD_Init(void);
/********************************************************************
********************************************************************/
sbit CS=P3^5; //CS=RS
sbit SID=P3^6; //RW=SID
sbit SCLK=P3^4; //E=SCLK
sbit LCD_PSB =  P3^7;            //��/����ʽ����