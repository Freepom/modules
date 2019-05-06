#include "stc15w.h"
#include "T2CLK_PWM.h"

sbit    P_PWM = P3^0;       //定义PWM输出引脚。

//unsigned int     pwm;                //定义PWM输出高电平的时间的变量。用户操作PWM的变量。
unsigned int     PWM_high,PWM_low;   //中间变量，用户请勿修改。

void InitPWM()
{
//---------------------------------------------------T2CLK模拟输出PWM配置
    P_PWM = 0;
    P3M1 &= ~1; //P3.0 设置为推挽输出
    P3M0 |=  1;

    AUXR &= ~(1<<4);    //停止计数
    IE2  |=  (1<<2);    //允许中断
    AUXR |=  (1<<2);    //1T
    AUXR &= ~(1<<3);    //定时

    INT_CLKO |=  0x04;  //输出时钟

    TH2 = 0;
    TL2 = 0;
//    AUXR |=  (1<<4);    //开始运行
    
    EA = 1;
}
/**************** 计算PWM重装值函数 *******************/
void    LoadPWM(unsigned int i)
{
    unsigned int j;

    if(i > PWM_HIGH_MAX)        i = PWM_HIGH_MAX;   //如果写入大于最大占空比数据，则强制为最大占空比。
    if(i < PWM_HIGH_MIN)        i = PWM_HIGH_MIN;   //如果写入小于最小占空比数据，则强制为最小占空比。
    j = 65536UL - PWM_DUTY + i; //计算PWM低电平时间
    i = 65536UL - i;            //计算PWM高电平时间
    EA = 0;
    PWM_high = i;   //装载PWM高电平时间
    PWM_low  = j;   //装载PWM低电平时间
    EA = 1;
}
/********************* Timer2中断函数************************/
void timer2_int (void) interrupt 12
{
    if(P_PWM)
    {
        TH2 = (u8)(PWM_low >> 8);   //如果是输出高电平，则装载低电平时间。
        TL2 = (u8)PWM_low;
    }
    else
    {
        TH2 = (u8)(PWM_high >> 8);  //如果是输出低电平，则装载高电平时间。
        TL2 = (u8)PWM_high;
    }
}