/*****************************************************/
//   红外编码发送
//作者：林其平  QQ：578218949
//版本：V00
//日期：2017年08月06日 完成
//备注：利用定时器2模拟输出占空比可调PWM
/*****************************************************/
#ifndef _T2CLK_PWM_H_
#define _T2CLK_PWM_H_

#define 	FOSC    11092500L
#define     	PWM_Frq        (38000UL)	//输出PWM频率
#define     	PWM_DUTY        FOSC/(PWM_Frq)//  总周期，
#define     	PWM_HIGH_MIN    32              //限制PWM输出的最小占空比。用户请勿修改。
#define     	PWM_HIGH_MAX    (PWM_DUTY-PWM_HIGH_MIN) //限制PWM输出的最大占空比。用户请勿修改。
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