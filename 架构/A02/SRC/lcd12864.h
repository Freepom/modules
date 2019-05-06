#include <reg51.h>
#include <intrins.h>

#define nop _nop_()

//==========================================================
//==========
//函数声明
void Delay(uint ms); //延时子程序
//void Write_cmd(cmd); //写指令子程序
//void Write_data(uchar _data); //写数据子程序
//void Position(ucha 不不
//vvvvvvvvvvv
//vvvvvvvvvvvvvvvvvvvvvvvvvvvv r pos); //定位函数
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
sbit LCD_PSB =  P3^7;            //串/并方式控制