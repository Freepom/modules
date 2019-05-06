#include "stc15w.h"
#define lcd_data_port P2

/*端口定义*/

sbit lcd_rs_port = P3^4;  /*定义LCD控制端口*/
sbit lcd_rw_port = P3^5;
sbit lcd_en_port = P3^6;

void lcd_delay(unsigned char ms); /*LCD1602 延时*/
void lcd_busy_wait(); /*LCD1602 忙等待*/
void lcd_command_write(unsigned char command); /*LCD1602 命令字写入*/
void lcd_system_reset(); /*LCD1602 初始化*/
void lcd_char_write(unsigned char ,unsigned char,unsigned char); /*LCD1602 字符写入*/
void lcd_str_write(unsigned char x_pos,y_pos,char *lcd_dat);
void lcd_openCursor(void);
void lcd_closeCursor(void);
void lcd_setCursorAddr(char y_pos, char addr);
