
#ifndef __DS1302_H__
#define __DS1302_H__

#include <stc15w.h>
#include<intrins.h>

sbit Pin_DSSCK=P2^3;		
sbit Pin_DSSDA=P2^4;		
sbit Pin_DSRST=P2^5;
//��λ��
#define RST_CLR	Pin_DSRST=0//��ƽ�õ�
#define RST_SET	Pin_DSRST=1//��ƽ�ø�


//˫������ 
#define IO_CLR	Pin_DSSDA=0//��ƽ�õ�
#define IO_SET	Pin_DSSDA=1//��ƽ�ø�
#define IO_R	Pin_DSSDA  //��ƽ��ȡ


//ʱ���ź�
#define SCK_CLR	Pin_DSSCK=0//ʱ���ź�
#define SCK_SET	Pin_DSSCK=1//��ƽ�ø�


#define ds1302_sec_add			0x80		//�����ݵ�ַ
#define ds1302_min_add			0x82		//�����ݵ�ַ
#define ds1302_hr_add			0x84		//ʱ���ݵ�ַ
#define ds1302_date_add			0x86		//�����ݵ�ַ
#define ds1302_month_add		0x88		//�����ݵ�ַ
#define ds1302_day_add			0x8a		//�������ݵ�ַ
#define ds1302_year_add			0x8c		//�����ݵ�ַ
#define ds1302_control_add		0x8e		//�������ݵ�ַ
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe

extern unsigned char time_buf1[8];//��������ʱ������
extern unsigned char time_buf[8] ;//��������ʱ������

/*------------------------------------------------
           ��DS1302д��һ�ֽ�����
------------------------------------------------*/
void Ds1302_Write_Byte(unsigned char addr, unsigned char d);
/*------------------------------------------------
           ��DS1302����һ�ֽ�����
------------------------------------------------*/
unsigned char Ds1302_Read_Byte(unsigned char addr) ;
/*------------------------------------------------
           ��DS1302д��ʱ������
------------------------------------------------*/
//void Ds1302_Write_Time(void) ;
/*------------------------------------------------
           ��DS1302����ʱ������
------------------------------------------------*/
void Ds1302_Read_Time(void)  ;
/*------------------------------------------------
                DS1302��ʼ��
------------------------------------------------*/
void Init_DS1302(void);

#endif
