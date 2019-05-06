////////��������ֻ�����void lcd_system_reset(); /*LCD1602 ��ʼ��*/
/////////////////////////void lcd_char_write(unsigned char ,unsigned char,unsigned char); /*LCD1602 �ַ�д��*/
/////////////////////////��������������unsigned char code lcd_mun_to_char[16]={"0123456789ABCDEF"};
/////////////////////////////////////////
//sbit dula=P2^6;//����ܵĶ�ѡ�ź�
//sbit wela=P2^7; //����ܵ�λѡ�ź�
//void delay1 (void)//�ر��������ʱ����
//{
//	int k;
//	for (k=0; k<1000; k++);
//
//}
//   /////////////////////////////////////////////////////////////////
//	P0=0X00;//�ص�����ܵ��źš���ֹ������ܵ�P0���źŵ�Ӱ�졣
//	dula=1;
//	wela=0;
//	delay1();
//	dula=0;
//	wela=0;
//	delay1();
//////////////////////////////////////////////////////////////////
//	P0 = 0xff; /*�ͷ�P0�˿�*/
#include<intrins.h>
#include"lcd1602.h"
#define _Nop() _nop_()
#define TURE 1
#define FALSE 0

void lcd_delay(unsigned char ms) /*LCD1602 ��ʱ*/
{
    unsigned char j;
    while(ms--){
        for(j=0;j<250;j++)
            {;}
        }   
}

//////////////////////////////////////////////

void lcd_busy_wait() /*LCD1602 æ�ȴ�*/
{
    lcd_rs_port = 0;
    lcd_rw_port = 1;
    lcd_en_port = 1;
    lcd_data_port = 0xff;
    _Nop();
    _Nop();
	_Nop();
    _Nop();
    while (lcd_data_port&0x80);
    lcd_en_port = 0; 

}

///////////////////////////////////////////////

void lcd_command_write(unsigned char command) /*LCD1602 ������д��*/
{
    lcd_busy_wait();
    lcd_rs_port = 0;
    lcd_rw_port = 0;
    lcd_en_port = 0;
    lcd_data_port = command;
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    lcd_en_port = 1;
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    lcd_en_port = 0;     
}
static void lcd_clearDispAddr(void)
{
    lcd_command_write(0x02);
}
void lcd_openCursor(void)
{
    lcd_command_write(0x0f);
}
void lcd_closeCursor(void)
{
    lcd_command_write(0x0c);
}
void lcd_setCursorAddr(char y_pos, char addr)
{
    // lcd_delay(5);
    lcd_clearDispAddr();
    // lcd_delay(5);
    addr &= 0x0f; /* Xλ�÷�Χ 0~15 */
    y_pos &= 0x01; /* Yλ�÷�Χ 0~ 1 */
    if(y_pos==1) addr += 0x40;
    addr += 0x80;
    lcd_command_write(addr);
}
/////////////////////////////////////////

void lcd_system_reset() /*LCD1602 ��ʼ��*/
{
    lcd_delay(20);
    lcd_command_write(0x38);
    lcd_delay(100);
    lcd_command_write(0x38);
    lcd_delay(50);
    lcd_command_write(0x38);
    lcd_delay(10);
    lcd_command_write(0x08);
    lcd_command_write(0x01);
    lcd_command_write(0x06);
    lcd_command_write(0x0c); 
}

//////////////////////////////////////////////////

void lcd_char_write(unsigned char x_pos,y_pos,lcd_dat) /*LCD1602 �ַ�д��*/
{
    x_pos &= 0x0f; /* Xλ�÷�Χ 0~15 */
    y_pos &= 0x01; /* Yλ�÷�Χ 0~ 1 */
    if(y_pos==1) x_pos += 0x40;
    x_pos += 0x80;
    lcd_command_write(x_pos);
    lcd_busy_wait();
    lcd_rs_port = 1;
    lcd_rw_port = 0;
    lcd_en_port = 0;
    lcd_data_port = lcd_dat;
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    lcd_en_port = 1;
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    lcd_en_port = 0; 

}
void lcd_str_write(unsigned char x_pos,y_pos,char *lcd_dat) /*LCD1602 �ַ�д��*/
{
    x_pos &= 0x0f; /* Xλ�÷�Χ 0~15 */
    y_pos &= 0x01; /* Yλ�÷�Χ 0~ 1 */
    if(y_pos==1) x_pos += 0x40;
    x_pos += 0x80;
	while(*lcd_dat){		
		lcd_command_write(x_pos);
		lcd_busy_wait();
		lcd_rs_port = 1;
		lcd_rw_port = 0;
		lcd_en_port = 0;
		lcd_data_port = *lcd_dat;
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		lcd_en_port = 1;
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		_Nop();
		lcd_en_port = 0; 

		lcd_dat++;
		x_pos++;
	}
	
}
