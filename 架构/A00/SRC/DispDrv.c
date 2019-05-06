#include"display.H" 
unsigned char code Digit_Tab[]={DT_0,DT_1,DT_2,DT_3,DT_4,DT_5,DT_6,DT_7,DT_8,\
                                DT_9,DT_A,DT_C,DT_d,DT_E,DT_F,DT_NO};// 显示段码值0~9
                                
unsigned char code Mode_Tab[]={0x00,A_SEG,F_SEG,E_SEG,D_SEG,B_SEG,H_SEG,C_SEG,G_SEG};                                
//---------------------------------------------
//-----------------------------------------------------------
//显示2
//显示
bit Flg_DispOK;
unsigned char 	R_DBUF1,R_DBUF2,R_DBUF3,R_DBUF4,R_DBUF5;//,R_DBUF6=0;
unsigned char 	bdata  R_DBUFX;
sbit 	Flg_SegA=R_DBUFX^0;
sbit 	Flg_SegB=R_DBUFX^1;
sbit 	Flg_SegC=R_DBUFX^2;
sbit 	Flg_SegD=R_DBUFX^3;
sbit 	Flg_SegE=R_DBUFX^4;
sbit 	Flg_SegF=R_DBUFX^5;
sbit 	Flg_SegG=R_DBUFX^6;
sbit 	Flg_SegH=R_DBUFX^7;
//SEG口
#define SEG P1
sbit	PIN_SEGA = P2^7;   //P1^5;   P1^2; 
sbit	PIN_SEGB = P1^3;   //P1^0;   P1^7; 
sbit	PIN_SEGC = P1^6;   //P1^1;   P1^6; 
sbit	PIN_SEGD = P5^4;   //P1^2;   P1^5; 
sbit	PIN_SEGE = P1^7;   //P1^3;   P1^4; 
sbit	PIN_SEGF = P1^0;   //P1^4;   P1^3; 
sbit	PIN_SEGG = P1^5;   //P1^6;   P1^1; 
sbit	PIN_SEGDP = P5^5;  // P1^7;   P1^0;					                             
//COM口
sbit	PIN_COM1 = P2^6;
sbit	PIN_COM2 = P1^1;
sbit	PIN_COM3 = P1^2;
sbit	PIN_COM4 = P1^4;
sbit	PIN_COM5 = P2^2;
	
//void Init_Disp()
//{
//	PinPP(0,0);
//	PinPP(0,1);
//	PinPP(0,2);
//	PinPP(0,3);
//	PinPP(0,4);
//	PinPP(0,5);
//	PinPP(0,6);
//	PinPP(0,7);
//	PinPP(1,0);
//	PinPP(1,1);
//	
//}
void DispDrv()
{
	static u8 R_SegCnt,R_ComCnt;
//	PIN_COM1=1;
//	PIN_SEGA=0;
//	PIN_SEGB=0;
//	PIN_SEGC=0;
//	PIN_SEGD=0;
//	PIN_SEGE=0;
//	PIN_SEGF=0;
//	PIN_SEGG=0;
//	PIN_SEGDP=0;

	P1M0&=0x00;//00000011B
	P1M1|=0xff;//00000011B
	P2M0&=~0xc4;//00000011B
	P2M1|=0xc4;//11000100B	
	P5M0&=~0x30;//00000011B
	P5M1|=0x30;//00110000B	
	PIN_COM1=1;
	PIN_COM2=1;
	PIN_COM3=1;
	PIN_COM4=1;	
	PIN_COM5=1;
	PIN_SEGA=0;
	PIN_SEGA=0;
	PIN_SEGB=0;
	PIN_SEGC=0;
	PIN_SEGD=0;	
	PIN_SEGE=0;
	PIN_SEGF=0;
	PIN_SEGG=0;
	PIN_SEGDP=0;
	if(Flg_DispOK==0)
		{
		return;	
		}
//	R_DBUFX=A_SEG|B_SEG|E_SEG;
	R_SegCnt++;
	if(R_SegCnt==8)
		{
		R_SegCnt=0;
		R_ComCnt++;
		if(R_ComCnt==5)
			{
			R_ComCnt=0;	
			}	
		}
	switch(R_ComCnt)
	{
		case 0:			
			R_DBUFX=R_DBUF1;//Digit_Tab[R_data];					
			break;
		case 1:
			R_DBUFX=R_DBUF2;			
			break;	
		case 2:
			R_DBUFX=R_DBUF3;			
			break;	
		case 3:
			R_DBUFX=R_DBUF4;			
			break;	
		case 4:
			R_DBUFX=R_DBUF5;			
			break;							
		default:
			break;				
	}		
	switch(R_SegCnt)
	{
		case 0:
			if(Flg_SegA)
				{
				PIN_SEGA=1;
				}
				else
					{
					PIN_SEGA=0;	
					}
								
			break;
		case 1:
			if(Flg_SegB)
				{
				PIN_SEGB=1;
				}
				else
					{
					PIN_SEGB=0;	
					}
								
			break;
		case 2:
			if(Flg_SegC)
				{
				PIN_SEGC=1;
				}
				else
					{
					PIN_SEGC=0;	
					}
								
			break;
		case 3:
			if(Flg_SegD)
				{
				PIN_SEGD=1;
				}
				else
					{
					PIN_SEGD=0;	
					}
								
			break;	
		case 4:
			if(Flg_SegE)
				{
				PIN_SEGE=1;
				}
				else
					{
					PIN_SEGE=0;	
					}
								
			break;
		case 5:
			if(Flg_SegF)
				{
				PIN_SEGF=1;
				}
				else
					{
					PIN_SEGF=0;	
					}
								
			break;
		case 6:
			if(Flg_SegG)
				{
				PIN_SEGG=1;
				}
				else
					{
					PIN_SEGG=0;	
					}
								
			break;
		case 7:
			if(Flg_SegH)
				{
				PIN_SEGDP=1;
				}
				else
					{
					PIN_SEGDP=0;	
					}
			break;	
		default:
			break;													
	}
	switch(R_ComCnt)
	{
		case 0:			
			PIN_COM1=0;					
			break;
		case 1:
			PIN_COM2=0;			
			break;	
		case 2:
			PIN_COM3=0;			
			break;	
		case 3:
			PIN_COM4=0;			
			break;	
		case 4:
			PIN_COM5=0;			
			break;							
		default:
			break;				
	}
	P1M1&=0x00;//00000011B
	P1M0|=0xff;//00000011B
	P2M1&=~0xc4;//00000011B
	P2M0|=0xc4;//11000100B	
	P5M1&=~0x30;//00000011B
	P5M0|=0x30;//00110000B			
//	switch(R_ComCnt)
//	{
//		case 0:			
//			PIN_COM1=0;
//	P0M0|=0xff;//
//	P0M1&=0x00;
//	P1M0|=0x03;//00000011B
//	P1M1&=~0x03;//00000000B									
//			break;
//		case 1:
//			PIN_COM1=1;				
//			break;	
//		default:
//			break;				
//	}
		
}