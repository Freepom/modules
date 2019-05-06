/**************************************************************
24bit HX711�ο���������C�� �������� 2010/11
��C�е���: extern unsigned long ReadAD(void);
.
.
unsigned long data;
data=ReadAD();
.
.
-------------------------------------------------------------*/
#include<reg52.h>
#include"HX711.h"
sbit ADDO = P1^5;
sbit ADSK = P0^0;
unsigned long ReadCount(void)
{
unsigned long Count;
unsigned char i;
ADSK=0; //ʹ��AD��PD_SCK �õͣ�
Count=0;
while(ADDO); //ADת��δ������ȴ�������ʼ��ȡ
for (i=0;i<24;i++)
{
ADSK=1; //PD_SCK �øߣ��������壩
Count=Count<<1; //�½�����ʱ����Count����һλ���Ҳಹ��
ADSK=0; //PD_SCK �õ�
if(ADDO) Count++;
}
ADSK=1;
Count=Count^0x800000;//��25�������½�����ʱ��ת������
ADSK=0;
return(Count);
}
