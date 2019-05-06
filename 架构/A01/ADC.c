#include"ADC.h"

/*----------------------------
Initial ADC sfr
----------------------------*/
void InitADC()
{
//    P1 = P1M0 = P1M1 = 0xff;        //Set all P1 as Open-Drain mode
    ADC_DATA = 0;                   //Clear previous result
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
	IE|=0x20;//b7: EA b6:ELVD b5:EADC b4:ES b3:ET1 b6:EX1 b1:ET0 b0:EX0	中断使能
	IP|=0x00;//b7: PPCA b6:PLVD b5:PADC b4:PS b3:PT1 b6:PX1 b1:PT0 b0:PX0 优先级    
    P1ASF = 0x1b;//0b00011110;                   //设置P1口为AD口
//    Delay(2);                       //ADC power-on and delay
}
/*----------------------------
Get ADC result
----------------------------*/
//unsigned char GetADCResult(unsigned char ch)
//{
//    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
////    _nop_();                        //Must wait before inquiry
////    _nop_();
////    _nop_();
////    _nop_();
//////    while (!(ADC_CONTR & ADC_FLAG));//Wait complete flag
////    ADC_CONTR &= ~ADC_FLAG;         //Close ADC
//
//    return ADC_DATA;                //Return ADC result
//}