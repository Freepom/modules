/**************************************************************
24bit HX711参考驱动程序（C） 优质人生 2010/11
在C中调用: extern unsigned long ReadAD(void);
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
ADSK=0; //使能AD（PD_SCK 置低）
Count=0;
while(ADDO); //AD转换未结束则等待，否则开始读取
for (i=0;i<24;i++)
{
ADSK=1; //PD_SCK 置高（发送脉冲）
Count=Count<<1; //下降沿来时变量Count左移一位，右侧补零
ADSK=0; //PD_SCK 置低
if(ADDO) Count++;
}
ADSK=1;
Count=Count^0x800000;//第25个脉冲下降沿来时，转换数据
ADSK=0;
return(Count);
}
