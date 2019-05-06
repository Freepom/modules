#ifndef _lcd12864_H
#define _lcd12864_H

#include "stc15w.h"
#include <intrins.h>
#define nop _nop_()

//==========================================================
//x-行数，y-列数
//==========
//函数声明
void Delay(u16 ms); //延时子程序
void lcd_wdate(u8 X,u8 Y,u8 date);	//写入显示数据，一个字节
void lcd_wstr(u8 X,u8 Y,u8 *date);	//写入显示数据，一个字符串
void W_1byte(u8 RW, u8 RS, u8 W_data);	//写入数据，命令或数据
void Write_8bits(u16 W_bits);		//串行通信
void LCD_Init(void);			//初始化

#endif