/*****************************************************/
//   ������뷢��
//���ߣ�����ƽ  QQ��578218949
//�汾��V00
//���ڣ�2017��08��06�� ���
//��ע�����ö�ʱ��2ģ�����ռ�ձȿɵ�PWM
/*****************************************************/
#ifndef _T2CLK_PWM_H_
#define _T2CLK_PWM_H_

#define 	FOSC    11092500L
#define     	PWM_Frq        (38000UL)	//���PWMƵ��
#define     	PWM_DUTY        FOSC/(PWM_Frq)//  �����ڣ�
#define     	PWM_HIGH_MIN    32              //����PWM�������Сռ�ձȡ��û������޸ġ�
#define     	PWM_HIGH_MAX    (PWM_DUTY-PWM_HIGH_MIN) //����PWM��������ռ�ձȡ��û������޸ġ�
//-----------------------------------PWM 
#define D_PWM100 PWM_DUTY*10/10
#define D_PWM80 PWM_DUTY*8/10
#define D_PWM70 PWM_DUTY*7/10
#define D_PWM60 PWM_DUTY*6/10
#define D_PWM50 PWM_DUTY*5/10
#define D_PWM40 PWM_DUTY*4/10
#define D_PWM30 PWM_DUTY*3/10
#define D_PWM20 PWM_DUTY*2/10

void 	InitPWM();
void    LoadPWM(unsigned int i);

#endif