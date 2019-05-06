#include"ADC.h"

unsigned char R_ADData0,R_ADData1,R_ADData2,R_ADData3;
unsigned char R_ADData4,R_ADData5,R_ADData6,R_ADData7;
unsigned char R_ADCChannel;
bit Flg_ToRunADC;
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
    P1ASF = D_EnADC0|D_EnADC1|D_EnADC2|D_EnADC3|D_EnADC4|D_EnADC5|D_EnADC6|D_EnADC7;//

}
/*----------------------------
Get ADC result
----------------------------*/
void GetADCresult()
{

	switch(R_ADCChannel)
	{
	case 7:
		R_ADData7=ADC_DATA;
			
		break;		
	case 6:
		R_ADData6=ADC_DATA;
			
		break;
	case 5:
		R_ADData5=ADC_DATA;
		
		break;
	case 4:
		R_ADData4=ADC_DATA;
				
		break;
	case 3:
		R_ADData3=ADC_DATA;
				
		break;
	case 2:
		R_ADData2=ADC_DATA;
				
		break;
	case 1:
		R_ADData1=ADC_DATA;
				
		break;
	case 0:
		R_ADData0=ADC_DATA;
				
		break;	
	default:		
		break;
											
	}			
}
//-------------------------------------------
/*---------------开启ADc检测---------------------
//--------------------------------------------
/输入：
/输出：
/备注：放在定时器中断中执行，自动循环打开每路ADC
/	通过ADC中断的方式查询AD值
*/
//-------------------------------------------
void ChangeADCchannel()
{
//	if(Flg_ToRunADC==0)
//		{
//		return;	
//		}
//	Flg_ToRunADC=0; 	
	R_ADCChannel++;
	if(R_ADCChannel==4)R_ADCChannel=2;
	switch(R_ADCChannel)
	{
	case 7:
		#if D_EnADC7
		ADC_CONTR = ADC_POWER | ADC_SPEEDLL | R_ADCChannel | ADC_START;
		#endif
		break;		
	case 6:
		#if D_EnADC6
		ADC_CONTR = ADC_POWER | ADC_SPEEDLL | R_ADCChannel | ADC_START;
		#endif
		break;	
	case 5:
		#if D_EnADC5
		ADC_CONTR = ADC_POWER | ADC_SPEEDLL | R_ADCChannel | ADC_START;
		#endif
		break;	
	case 4:
		#if D_EnADC4
		ADC_CONTR = ADC_POWER | ADC_SPEEDLL | R_ADCChannel | ADC_START;
		#endif
		break;	
	case 3:
		#if D_EnADC3
		ADC_CONTR = ADC_POWER | ADC_SPEEDLL | R_ADCChannel | ADC_START;
		#endif
		break;	
	case 2:
		#if D_EnADC2
		ADC_CONTR = ADC_POWER | ADC_SPEEDLL | R_ADCChannel | ADC_START;
		#endif
		break;	
	case 1:
		#if D_EnADC1
		ADC_CONTR = ADC_POWER | ADC_SPEEDLL | R_ADCChannel | ADC_START;
		#endif
		break;	
	case 0:
		#if D_EnADC0
		ADC_CONTR = ADC_POWER | ADC_SPEEDLL | R_ADCChannel | ADC_START;
		#endif
		break;		
	default:		
		break;
											
	}		

		
}
/*----------------------------
ADC中断服务程序
----------------------------*/
void adc_isr() interrupt 5 using 1
{
    ADC_CONTR &= !ADC_FLAG;         //清除ADC中断标志
    GetADCresult();
    Flg_ToRunADC=1;
}