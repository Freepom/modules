
#include "main.h"
#include <string.h>
#include <stddef.h>
#include "GPIO.h"

/***************************用户宏定义*******************************************************/

#define     PWM_DUTY_250Hz        128 
#define     PWM_DUTY        PWM_DUTY_250Hz        //定义PWM的周期，数值为PCA所选择的时钟脉冲个数。
#define     PWM_HIGH_MIN    0          //限制PWM输出的最小占空比, 避免中断里重装参数时间不够。
#define     PWM_HIGH_MAX    (PWM_DUTY - PWM_HIGH_MIN)       //限制PWM输出的最大占空比。


void PWM_SW_Init(void);
void PWM_SW_SetDuty(u16 pwmChannel, u16 pwm);
void PWM_SW_Driver(void);
void PWM_SW_TimeToUpdateDuty(void);
void PWM_SW_OFFALL(void);
void PWM_SW_ONALL(void);
