// Header:
// File Name: 
// Author:
// Date:
#include "PWM_software.h"

//LED控制IO口定义
sbit PIN_LED_1 = P1^4;
#define LED_1_ON() PIN_LED_1=1
#define LED_1_OFF() PIN_LED_1=0
sbit PIN_LED_2 = P1^5;
#define LED_2_ON() PIN_LED_2=1
#define LED_2_OFF() PIN_LED_2=0
sbit PIN_LED_3 = P1^6;
#define LED_3_ON() PIN_LED_3=1
#define LED_3_OFF() PIN_LED_3=0
sbit PIN_LED_4 = P5^4;
#define LED_4_ON() PIN_LED_4=1
#define LED_4_OFF() PIN_LED_4=0

unsigned int   xdata  PWM1_low=PWM_HIGH_MIN,PWM1Buffer_low=PWM_HIGH_MIN;
unsigned int   xdata  PWM2_low=PWM_HIGH_MIN,PWM2Buffer_low=PWM_HIGH_MIN;
unsigned int   xdata  PWM3_low=PWM_HIGH_MIN,PWM3Buffer_low=PWM_HIGH_MIN;
unsigned int   xdata  PWM4_low=PWM_HIGH_MIN,PWM4Buffer_low=PWM_HIGH_MIN;


void PWM_SW_Driver(void)
{
    static u16 pwmDutyCnt=0;
    
    if(pwmDutyCnt >= PWM_HIGH_MAX){
        pwmDutyCnt = 0;
        if(PWM1_low != PWM_HIGH_MIN)
        LED_1_ON();
        if(PWM2_low != PWM_HIGH_MIN)
        LED_2_ON();
        if(PWM3_low != PWM_HIGH_MIN)
        LED_3_ON();
        if(PWM4_low != PWM_HIGH_MIN)
        LED_4_ON();
    }
    if(pwmDutyCnt >= PWM1_low){
        if(PWM1_low != PWM_HIGH_MAX)
        LED_1_OFF();
    }
    if(pwmDutyCnt >= PWM2_low){
        if(PWM2_low != PWM_HIGH_MAX)
        LED_2_OFF();
    }    
    if(pwmDutyCnt >= PWM3_low){
        if(PWM3_low != PWM_HIGH_MAX)
        LED_3_OFF();
    }
    if(pwmDutyCnt >= PWM4_low){
        if(PWM4_low != PWM_HIGH_MAX)
        LED_4_OFF();
    }    
    pwmDutyCnt++;
}
//========================================================================
// 函数: void PWMn_SetHighReg(unsigned int high)
// 描述: 更新占空比数据。
// 参数: high:  占空比数据，即PWM输出高电平的PCA时钟脉冲个数。
// 返回: 无
// 版本: VER1.0
// 日期: 2013-5-15
// 备注: 
//========================================================================
void PWM_SW_SetDuty(u16 pwmChannel, u16 pwmWidth)
{

    if(pwmWidth > PWM_HIGH_MAX)  pwmWidth = PWM_HIGH_MAX; //如果写入大于最大占空比数据，强制为最大占空比。
    if(pwmWidth < PWM_HIGH_MIN)  pwmWidth = PWM_HIGH_MIN; //如果写入小于最小占空比数据，强制为最小占空比。

    switch (pwmChannel)
    {
        case 1:
            PWM1Buffer_low = pwmWidth;  //计算并保存PWM输出低电平的PCA时钟脉冲个数。
            break;
        case 2:
            PWM2Buffer_low = pwmWidth;  //计算并保存PWM输出低电平的PCA时钟脉冲个数。
            break;
        case 3:
            PWM3Buffer_low = pwmWidth;  //计算并保存PWM输出低电平的PCA时钟脉冲个数。
            break;
        case 4:
            PWM4Buffer_low = pwmWidth;  //计算并保存PWM输出低电平的PCA时钟脉冲个数。
            break;
        case 0xff:
            PWM1Buffer_low = pwmWidth;  //计算并保存PWM输出低电平的PCA时钟脉冲个数。
            PWM2Buffer_low = pwmWidth;  //计算并保存PWM输出低电平的PCA时钟脉冲个数。
            PWM3Buffer_low = pwmWidth;  //计算并保存PWM输出低电平的PCA时钟脉冲个数。
            PWM4Buffer_low = pwmWidth;  //计算并保存PWM输出低电平的PCA时钟脉冲个数。
            break;
    
        default:
            break;
    }
}
void PWM_SW_TimeToUpdateDuty(void)
{
    if(PWM1_low < PWM1Buffer_low){
        PWM1_low++;
    }else if(PWM1_low > PWM1Buffer_low){
        PWM1_low--;
    }
    
    if(PWM2_low < PWM2Buffer_low){
        PWM2_low++;
    }else if(PWM2_low > PWM2Buffer_low){
        PWM2_low--;
    }
    if(PWM3_low < PWM3Buffer_low){
        PWM3_low++;
    }else if(PWM3_low > PWM3Buffer_low){
        PWM3_low--;
    }
    
    if(PWM4_low < PWM4Buffer_low){
        PWM4_low++;
    }else if(PWM4_low > PWM4Buffer_low){
        PWM4_low--;
    }
}
void PWM_SW_OFFALL(void)
{
    PWM_SW_SetDuty(0xff,0);
}
void PWM_SW_ONALL(void)
{
    PWM_SW_SetDuty(0xff,90);
}
void LED_running(void)
{
	static char cnt=0;
	LED_1_OFF();
	LED_2_OFF();
	LED_3_OFF();
	LED_4_OFF();

	switch (cnt)
	{
		case 0:
			LED_1_ON();
			break;
		case 1:
			LED_2_ON();
			break;
		case 2:
			LED_3_ON();
			break;
		case 3:
			LED_4_ON();
			break;
	
		default:
			break;
	}
	cnt++;
	if(cnt == 4){
		cnt = 0;
	}
}
//========================================================================
// 函数: void   PCA_Init(void)
// 描述: PCA初始化程序.
// 参数: none
// 返回: none.
// 版本: V1.0, 2013-11-22
//========================================================================
void PWM_SW_Init(void)
{
    // GPIO_InitTypeDef GPIOinitStruct;

    // //刹车灯p2.1，蜂鸣器p2.2，充电控制p2.5，电机控制输出p2.6
    // GPIOinitStruct.Mode = GPIO_OUT_PP;  //推挽输出
    // GPIOinitStruct.Pin = GPIO_Pin_2;
    // GPIO_Inilize(GPIO_P3,&GPIOinitStruct);
    // GPIOinitStruct.Mode = GPIO_OUT_PP;  //推挽输出
    // GPIOinitStruct.Pin = GPIO_Pin_1;
    // GPIO_Inilize(GPIO_P1,&GPIOinitStruct);

    PWM_SW_OFFALL();
	LED_1_OFF();
	LED_2_OFF();
	LED_3_OFF();
	LED_4_OFF();    
}

