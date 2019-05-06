#include "stc15w.h"
#include "T2CLK_PWM.h"

sbit    P_PWM = P3^0;       //����PWM������š�

//unsigned int     pwm;                //����PWM����ߵ�ƽ��ʱ��ı������û�����PWM�ı�����
unsigned int     PWM_high,PWM_low;   //�м�������û������޸ġ�

void InitPWM()
{
//---------------------------------------------------T2CLKģ�����PWM����
    P_PWM = 0;
    P3M1 &= ~1; //P3.0 ����Ϊ�������
    P3M0 |=  1;

    AUXR &= ~(1<<4);    //ֹͣ����
    IE2  |=  (1<<2);    //�����ж�
    AUXR |=  (1<<2);    //1T
    AUXR &= ~(1<<3);    //��ʱ

    INT_CLKO |=  0x04;  //���ʱ��

    TH2 = 0;
    TL2 = 0;
//    AUXR |=  (1<<4);    //��ʼ����
    
    EA = 1;
}
/**************** ����PWM��װֵ���� *******************/
void    LoadPWM(unsigned int i)
{
    unsigned int j;

    if(i > PWM_HIGH_MAX)        i = PWM_HIGH_MAX;   //���д��������ռ�ձ����ݣ���ǿ��Ϊ���ռ�ձȡ�
    if(i < PWM_HIGH_MIN)        i = PWM_HIGH_MIN;   //���д��С����Сռ�ձ����ݣ���ǿ��Ϊ��Сռ�ձȡ�
    j = 65536UL - PWM_DUTY + i; //����PWM�͵�ƽʱ��
    i = 65536UL - i;            //����PWM�ߵ�ƽʱ��
    EA = 0;
    PWM_high = i;   //װ��PWM�ߵ�ƽʱ��
    PWM_low  = j;   //װ��PWM�͵�ƽʱ��
    EA = 1;
}
/********************* Timer2�жϺ���************************/
void timer2_int (void) interrupt 12
{
    if(P_PWM)
    {
        TH2 = (u8)(PWM_low >> 8);   //���������ߵ�ƽ����װ�ص͵�ƽʱ�䡣
        TL2 = (u8)PWM_low;
    }
    else
    {
        TH2 = (u8)(PWM_high >> 8);  //���������͵�ƽ����װ�ظߵ�ƽʱ�䡣
        TL2 = (u8)PWM_high;
    }
}