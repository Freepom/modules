#include<12864.h>


/****
******Һ�����æ����
****/
void check_busy()
{
	uchar busy;

	wr=1;
	rs=0;
	do
	{
		P0=0x00;
		en=1;
		busy=P0;
		en=0;
		busy&=0x80;
	}while(busy);
}

/****
******Һ��д�����
****/
void lcd_write_com(uchar com)
{
	check_busy();
	wr=0;
	rs=0;
	P0=com;
	_nop_();
	en=1;
	_nop_();
	en=0;
}


/****
******Һ��д���ݺ���
****/
void lcd_write_date(uchar date)
{
	check_busy();
	wr=0; 		//д״̬
	rs=1;		//����ѡ���
	P0=date;
	_nop_();
	en=1;
	_nop_();
	en=0;
}

/****
******Һ���趨���꺯��
****** x:0-8
****** y:0-63
****/
void lcd_setxy(uchar x,uchar y)
{
	lcd_write_com(0xb8+x);	   //0xb8Ϊҳ������ҳ��
	lcd_write_com(0x40+y);	   //ox40Ϊ�У���������
}

/****
******Һ��дһ���ַ�����
****** x:0-4
****** y:0-15
****/
void lcd_ch(uchar x,uchar y,uchar *ch)
{
	uchar i,j;
	if(y<8)
	{
		cs1=0;
		cs2=1;
	}
	else 
	{
		cs1=1;
		cs2=0;
		y-=8;
	}
	for(i=0;i<2;i++)
	{
	   lcd_setxy(x*2+i,y*8);
	   {
			for(j=0;j<8;j++)
			{
				lcd_write_date(ch[i*8+j]);	
			}
	   }
	}
	cs1=0;
	cs2=0;
}


/****
******Һ��дһ�����ֺ���
****** x:0-3
****** y:0-7
****/
void lcd_hanzi(uchar x,uchar y,uchar *ch)
{
	uchar i,j;
	if(y<4)
	{
		cs1=0;
		cs2=1;
	}
	else 
	{
		cs1=1;
		cs2=0;
		y-=4;
	}
	for(i=0;i<2;i++)
	{
		lcd_setxy(x*2+i,y*16);
		for(j=0;j<16;j++)
		{
			lcd_write_date(ch[i*16+j]);	
		}	
	}
	cs1=0;
	cs2=0;
}

/****
******Һ��дһ�к��ֺ���
****** x:0-3
****** y:0-7
****** n:�ַ���Ŀ
****/
void lcd_hanzi_str(uchar x,uchar y,uchar *date,uchar n)
{
	uchar i;
	for(i=0;i<n;i++)
	{
		lcd_hanzi(x,y,date+32*i);
		y++;	
	}
}

/****
******Һ��дһ���ַ�������
****** x:0-3
****** y:0-7
****** n:�ַ���Ŀ
****/
void lcd_ch_str(uchar x,uchar y,uchar *date,uchar n)
{
	uchar i;
	for(i=0;i<n;i++)
	{
		lcd_ch(x,y,date+16*i);
		y++;	
	}
}

/****
******Һ����ʼ������
****/
void lcd_init()
{
	 lcd_write_com(0x3f);
	 lcd_write_com(0xb8);
	 lcd_write_com(0x40);
}

/****
******Һ�������Ļ����
****/
void lcd_clear_scr()
{
	uchar i,j;
	cs1=0;
	cs2=1;
	for(i=0;i<8;i++)
	{
		lcd_setxy(i,0);
		for(j=0;j<64;j++)
		{
			lcd_write_date(0);	
		}	
	}

	cs1=1;
	cs2=0;
	for(i=0;i<8;i++)
	{
		lcd_setxy(i,0);
		for(j=0;j<64;j++)
		{
			lcd_write_date(0);	
		}	
	}
}

