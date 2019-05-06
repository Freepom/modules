#include "stc15w.h"
#define lcd_data_port P2

/*�˿ڶ���*/

sbit lcd_rs_port = P3^4;  /*����LCD���ƶ˿�*/
sbit lcd_rw_port = P3^5;
sbit lcd_en_port = P3^6;

void lcd_delay(unsigned char ms); /*LCD1602 ��ʱ*/
void lcd_busy_wait(); /*LCD1602 æ�ȴ�*/
void lcd_command_write(unsigned char command); /*LCD1602 ������д��*/
void lcd_system_reset(); /*LCD1602 ��ʼ��*/
void lcd_char_write(unsigned char ,unsigned char,unsigned char); /*LCD1602 �ַ�д��*/
void lcd_str_write(unsigned char x_pos,y_pos,char *lcd_dat);
void lcd_openCursor(void);
void lcd_closeCursor(void);
void lcd_setCursorAddr(char y_pos, char addr);
