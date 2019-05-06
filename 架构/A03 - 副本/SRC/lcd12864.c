///////////void lcd_wdate(uchar X,uchar Y,uchar *date)
///////////void LCD_Init(void)
///注意：中文字符前后不能空一个英文空格“ ”，否则显示乱码
#include "lcd12864.h"
/******************************************************************/
void LCD_Init(void)
{

uchar cmd;
LCD_PSB=0;
cmd=0x30; //功能设置 8 位数据，基本指令
W_1byte(0,0,cmd);
Delay(2);
cmd=0x0C; //显示状态 ON，游标OFF，反白OFF
W_1byte(0,0,cmd); //写指令
Delay(2);
cmd=0x01; //清除显示
W_1byte(0,0,cmd); //写指令
Delay(2);
cmd=0x02; //地址归位
W_1byte(0,0,cmd); //写指令
Delay(2);
cmd=0x80; //设置DDRAM 地址
W_1byte(0,0,cmd); //写指令
Delay(2); //延时
}
/*********************************************************/
/*                                                       */
/* 设定显示位置                                          */
/*                                                       */
/*********************************************************/
void lcd_wdate(uchar X,uchar Y,uchar *date)
{                          
   uchar  pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;  
   W_1byte(0,0,pos);     //显示地址
   
   while(*date != '\0')
   {
   W_1byte(0,1,*date);
         date++;
        }
  *date = 0;
}
/*******************************************************************
函数 名：W_1byte
入口参数：RW、RS、W_data
出口参数：无
函数作用：写一个字节的数据到12864 液晶，包括指令和数据
说 明：RW=1，从液晶读数据到MCU；RW=0，写一个数据到液晶；
（一般RW 都设为0，即只向液晶写数据，不读数据）
RS="1"，写入的是数据；RS=0，写入的是指令；
一般模式：RW=0，RS=1;写数据
RW="0"，RS=0;写指令
********************************************************************/
void W_1byte(uchar RW, uchar RS, uchar W_data)
{
uint H_data,L_data,S_ID = 0xf8; //11111RWRS0
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
H_data &= 0xf0; //屏蔽低4 位的数据
L_data = W_data; //xxxx0000 格式
L_data &= 0x0f; //屏蔽高4 位的数据
L_data <<= 4; //xxxx0000 格式
CS = 1;
Write_8bits(S_ID); //发送S_ID
Write_8bits(H_data); //发送H_data
Write_8bits(L_data); //发送L_data
CS = 0;
}
/********************************************************************
函数 名：Write_8bits
入口参数：W_bits
出口参数：无
函数作用：负责串行输出8 个bit 位
********************************************************************/
void Write_8bits(uint W_bits)
{
uint i,Temp_data;
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
函数 名：Delay
入口参数：ms
出口参数：无
函数作用：毫秒级的延时程序，当晶振为12Mhz 时，xtal=12;
********************************************************************/
void Delay(uint ms)
{
uint i;
while(ms--)
{
for(i=1;i<(uint)(8*143-2);i++)
;
}
}