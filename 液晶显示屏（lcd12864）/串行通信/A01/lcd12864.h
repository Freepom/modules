#ifndef _lcd12864_H
#define _lcd12864_H

#include "stc15w.h"
#include <intrins.h>
#define nop _nop_()

//==========================================================
//x-������y-����
//==========
//��������
void Delay(u16 ms); //��ʱ�ӳ���
void lcd_wdate(u8 X,u8 Y,u8 date);	//д����ʾ���ݣ�һ���ֽ�
void lcd_wstr(u8 X,u8 Y,u8 *date);	//д����ʾ���ݣ�һ���ַ���
void W_1byte(u8 RW, u8 RS, u8 W_data);	//д�����ݣ����������
void Write_8bits(u16 W_bits);		//����ͨ��
void LCD_Init(void);			//��ʼ��

#endif