#ifndef _ADC_H
#define _ADC_H

#include "stc15w.h"
#include "intrins.h"
/* ADC Register */
//				//7       6      5       4         3      2    1    0   Reset Value
//sfr ADC_CONTR = 0xc5;		//ADC_POWER SPEED1 SPEED0 ADC_FLAG ADC_START CHS2 CHS1 CHS0 0000,0000	//AD 转换控制寄存器 
//sfr ADC_DATA  = 0xc6;		//ADCV.9 ADCV.8 ADCV.7 ADCV.6 ADCV.5 ADCV.4 ADCV.3 ADCV.2 0000,0000	//A/D 转换结果高8位 
//sfr ADC_LOW2   = 0xbe;											
//sfr ADC_CONTR  = 0xBC;	//直接用MOV操作，不要用与或

sfr ADC_CONTR   =   0xBC;           //ADC控制寄存器
sfr ADC_DATA     =   0xBD;           //ADC高8位结果
sfr ADC_LOW2    =   0xBE;           //ADC低2位结果
/*Define ADC operation const for ADC_CONTR*/
#define ADC_POWER   0x80            //ADC power control bit
#define ADC_FLAG    0x10            //ADC complete flag
#define ADC_START   0x08            //ADC start control bit
#define ADC_SPEEDLL 0x00            //420 clocks
#define ADC_SPEEDL  0x20            //280 clocks
#define ADC_SPEEDH  0x40            //140 clocks
#define ADC_SPEEDHH 0x60            //70 clocks

extern unsigned char R_ADData0,R_ADData1,R_ADData2,R_ADData3;
extern unsigned char R_ADData4,R_ADData5,R_ADData6,R_ADData7;

#define D_EnADC0 0x00	//该IO口作ADC检测设置为 0x01,否则为 0x00
#define D_EnADC1 0x00	//该IO口作ADC检测设置为 0x02,否则为 0x00
#define D_EnADC2 0x04	//该IO口作ADC检测设置为 0x04,否则为 0x00
#define D_EnADC3 0x08	//该IO口作ADC检测设置为 0x08,否则为 0x00
#define D_EnADC4 0x00	//该IO口作ADC检测设置为 0x10,否则为 0x00
#define D_EnADC5 0x00	//该IO口作ADC检测设置为 0x20,否则为 0x00
#define D_EnADC6 0x00	//该IO口作ADC检测设置为 0x40,否则为 0x00
#define D_EnADC7 0x00	//该IO口作ADC检测设置为 0x80,否则为 0x00

void InitADC();
void ChangeADCchannel();
void GetADCresult();

#endif