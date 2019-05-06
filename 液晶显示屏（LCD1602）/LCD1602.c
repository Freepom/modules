////////主函数里只需调用void lcd_system_reset(); /*LCD1602 初始化*/
/////////////////////////void lcd_char_write(unsigned char ,unsigned char,unsigned char); /*LCD1602 字符写入*/
/////////////////////////这两个函数即可unsigned char code lcd_mun_to_char[16]={"0123456789ABCDEF"};
/////////////////////////////////////////
//sbit dula=P2^6;//数码管的段选信号
//sbit wela=P2^7; //数码管的位选信号
//void delay1 (void)//关闭数码管延时程序
//{
//	int k;
//	for (k=0; k<1000; k++);
//
//}
//   /////////////////////////////////////////////////////////////////
//	P0=0X00;//关掉数码管的信号。阻止数码管受到P0口信号的影响。
//	dula=1;
//	wela=0;
//	delay1();
//	dula=0;
//	wela=0;
//	delay1();
//////////////////////////////////////////////////////////////////
//	P0 = 0xff; /*释放P0端口*/
#include<intrins.h>
#include"lcd1602.h"
#define _Nop() _nop_()
#define TURE 1
#define FALSE 0

void lcd_delay(unsigned char ms) /*LCD1602 延时*/
{
    unsigned char j;
    while(ms--){
        for(j=0;j<250;j++)
            {;}
        }   
}

//////////////////////////////////////////////

void lcd_busy_wait() /*LCD1602 忙等待*/
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

void lcd_command_write(unsigned char command) /*LCD1602 命令字写入*/
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
    addr &= 0x0f; /* X位置范围 0~15 */
    y_pos &= 0x01; /* Y位置范围 0~ 1 */
    if(y_pos==1) addr += 0x40;
    addr += 0x80;
    lcd_command_write(addr);
}
/////////////////////////////////////////

void lcd_system_reset() /*LCD1602 初始化*/
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

void lcd_char_write(unsigned char x_pos,y_pos,lcd_dat) /*LCD1602 字符写入*/
{
    x_pos &= 0x0f; /* X位置范围 0~15 */
    y_pos &= 0x01; /* Y位置范围 0~ 1 */
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
void lcd_str_write(unsigned char x_pos,y_pos,char *lcd_dat) /*LCD1602 字符写入*/
{
    x_pos &= 0x0f; /* X位置范围 0~15 */
    y_pos &= 0x01; /* Y位置范围 0~ 1 */
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
