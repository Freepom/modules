
#include "main.h"
#include <string.h>
#include <stddef.h>
#include "GPIO.h"

/***************************�û��궨��*******************************************************/

#define     PWM_DUTY_250Hz        128 
#define     PWM_DUTY        PWM_DUTY_250Hz        //����PWM�����ڣ���ֵΪPCA��ѡ���ʱ�����������
#define     PWM_HIGH_MIN    0          //����PWM�������Сռ�ձ�, �����ж�����װ����ʱ�䲻����
#define     PWM_HIGH_MAX    (PWM_DUTY - PWM_HIGH_MIN)       //����PWM��������ռ�ձȡ�


void PWM_SW_Init(void);
void PWM_SW_SetDuty(u16 pwmChannel, u16 pwm);
void PWM_SW_Driver(void);
void PWM_SW_TimeToUpdateDuty(void);
void PWM_SW_OFFALL(void);
void PWM_SW_ONALL(void);
