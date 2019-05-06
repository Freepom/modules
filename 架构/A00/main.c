//#include<stc15w.h> 
#include"NRF2401.h"
#define u8 unsigned char
#define u16 unsigned int

#define FOSC 11059200L

#define T1MS (65536-FOSC/1000)      //1Tģʽ
//#define T1MS (65536-FOSC/12/1000) //12Tģʽ

sbit T2CLKO   = P3^0;               //��ʱ��2��ʱ�������

#define F38_4KHz (65536-FOSC/2/38400)    //1Tģʽ
//#define F38_4KHz (65536-FOSC/2/12/38400) //12Tģʽ
//-----------------��ѭ���ܹ��Ķ���-----------------------------------
u8	R_2ms=0;//2ms��ʱ
bit	Flg_2ms=0;
char	R_Jmp2msCnt=0;

char	R_MMode=0;
#define	D_Mode1	0
#define	D_Mode2	1
#define	D_Mode3	2
#define	D_Mode4	3
#define	D_Mode5	4
#define	D_Mode6	5

//----------------------------------------------------------
/**********************************************************************************/
//----����ɨ�衢������⡢��������Ķ���-----------------------------------
sbit key_onoff	 = P5^5;
sbit key_add	 = P5^4;
sbit key_sub	 = P2^0;
sbit key_slt	 = P2^4; 
#define	nokey		0
#define	addkey		1
#define	subkey		2
#define	onoffkey	3
#define	sltkey		4

u8	KeyDly		=0;
u8	KeyMarkDly	=0;
bit	FLG_keymark	=0;
char	KeyValue	=0;
char	R_curkey	=0;
char	R_keybuf	=0;
//----------------------------------------------------------
//*************�ֱ���5���ӻ���Ӧ�Ĺ̶�ͨ��Ƶ��
u8 R_CHtab[5]={0x40,0x45,0x48,0x4a,0x4f};	//Ƶ��
//**********************�û���+��ַ��+data1+data2+data3���ֱ��Ӧ5���ӻ�		  
u8 R_SendData_Tab[5][6]={{0xf1,0xe0,10,0,0,0},{0xf2,0xe0,60,0,0,0},
			 {0xf4,0xe0,110,0,0,0},{0xf8,0xe0,160,0,0,0},
			 {0xfa,0xe0,210,0,0,0}};	//ÿ��Ƶ������������
#define	D_RFChance1	0
#define	D_RFChance2	1
#define	D_RFChance3	2
#define	D_RFChance4	3
#define	D_RFChance5	4
//sfr P1M0=0x91;	//IO�ڿ��ƼĴ���
//
//sfr ADC_CONTR=0xc5;	//ADC���ƼĴ���
//sfr ADC_DATA=0xc6;
//sfr ADC_LOW2=0xbe;
//
//sfr AUXR=0x8e;

//sbit	led=P5^5;
sbit	led=P1^5;
u8 ad[4];	//4����λ����ADֵ
u8 tx[6];	//6����������
u8 w;

void initial()
{

   	 AUXR |= 0x80;                   //��ʱ��0Ϊ1Tģʽ
// 	 AUXR &= 0x7f;                   //��ʱ��0Ϊ12Tģʽ

    	TMOD = 0x00;                    //���ö�ʱ��Ϊģʽ0(16λ�Զ���װ��)
	TL0 = 0x9A;		//���ö�ʱ��ֵ
	TH0 = 0xFA;		//���ö�ʱ��ֵ125us    
    	TR0 = 1;                        //��ʱ��0��ʼ��ʱ
    	ET0 = 1;                        //ʹ�ܶ�ʱ��0�ж�
    	
    	AUXR |= 0x04;                   //��ʱ��2Ϊ1Tģʽ
//  	AUXR &= ~0x04;                  //��ʱ��2Ϊ12Tģʽ

    	AUXR &= ~0x08;                  //T2_C/T=0, ���ڲ�ʱ�ӽ���ʱ�����
//  	AUXR |= 0x08;                   //T2_C/T=1, ��T2(P3.1)���ŵ��ⲿʱ�ӽ���ʱ�����

    	T2L = F38_4KHz;                 //��ʼ����ʱֵ
    	T2H = F38_4KHz >> 8;
    
    	AUXR |= 0x10;                   //��ʱ��2��ʼ��ʱ
    	INT_CLKO = 0x04;                //ʹ�ܶ�ʱ��2��ʱ���������
    
    	EA = 1;    
}

void	DealKey();
void	ReadKeyValue();
void	KeyScan();
void	Timer20msCnt();
//void	RF_CH_Change(unsigned char	RF_CH);

main()
{
	initial();	//��ʱ����ʼ��
	TX_mode();	//����ģ���ʼ��

	while(1)
	{	     
	
	DealKey();	//��������
	if(Flg_2ms)	//2�����ʱ����
		{
		Flg_2ms=0;
		if(++R_Jmp2msCnt == 10)R_Jmp2msCnt=0;
		switch(R_Jmp2msCnt)	//2�����ʱ����
			{
			case	0:
					ReadKeyValue();	//����ת��
				break;
			case	1:
				
				break;
			case	2:
				
				break;												
			case	3:
				
				break;
			case	4:
				
				break;
			case	5:
				
				break;
			case	6:
				
				break;
			case	7:
				
				break;
			case	8:
				
				break;	
			case	9:
					Timer20msCnt();	//20�����ʱ
				break;
			default:
				break;																
			}
		}	
	}
}

void et0()interrupt 1
{
	static	char	temper=0,R_2msCnt=0;
	temper++;
	R_2msCnt++;
	
	if(R_2msCnt == 16)
		{
		R_2msCnt=0;
		Flg_2ms=1;	
		}
	KeyScan();	//����ɨ��
	
}

void	Timer20msCnt()
{
	static char	R_500msCnt=0,ii;	
	static char	R_CHtmp=0;		
	R_500msCnt++;
	
//----------��ʱ20ms------------------------------------		
	{
	R_CHtmp++;
	if(R_CHtmp == 5)R_CHtmp=0;
//		RF_CH_Change(R_CHtmp);	
	FIFO_write(R_SendData_Tab[R_CHtmp]);	//��������ÿ��Ƶ�������ڣ�20*5ms
//	for(ii==1;ii<5;ii++)
//		{
//		R_SendData_Tab[R_CHtmp][2]=0;	
//		}
	}
//----------��ʱ20ms---END---------------------------------	

//----------��ʱ500ms------------------------------------	
	if( (R_500msCnt == 25) || (R_500msCnt == 0) )
		{
//----------�˶�Ϊ500ms------------------------------------			
		}
//----------��ʱ500ms--END----------------------------------

//----------��ʱ1s------------------------------------				
	if(R_500msCnt == 50)
		{
		R_500msCnt=0;
//----------�˶�Ϊ1s------------------------------------			

		led=!led;		
//		if(led)R_SendData_Tab[R_CHtmp][1]=255;
//			else
//				R_SendData_Tab[R_CHtmp][1]=0;	
	
				
		}		
//----------��ʱ1s---END---------------------------------				
			
}
void	DealKey()//������ѭ����ִ��
{
	char	R_BottomMode=0;
	static	char	n=0;
	if(R_curkey != 0)
		{
		 R_BottomMode = R_curkey;
		 R_curkey=0;

		 switch(R_BottomMode)
			{
			case addkey:	  	
//					led=!led;		
//					if(led)R_SendData_Tab[D_RFChance1][1]=255;
//						else
//							R_SendData_Tab[D_RFChance1][1]=0;
				break;
			case subkey:	  	
				  
				break;
			case onoffkey:		
					led=!led;		
					
					if(n==5)n=0;		
					if(led)R_SendData_Tab[D_RFChance1+n][2]=255,n++;
						else
							R_SendData_Tab[D_RFChance1+n][2]=5;
				break;
			case sltkey:	  
				
				break;
			 default:;		           
			 	 break;
			}			
		}
	}
void	ReadKeyValue()//����2ms��ʱ��ִ�У�20msִ��һ��
{
	if((KeyDly++ >= 2))
		{ 
		 R_keybuf=0;
		 FLG_keymark=0;
		 KeyDly=0;
		 KeyValue=0;
		 KeyMarkDly=0;
		}
	if(KeyValue != 0)
		{ 
		KeyDly=0;
		if(KeyValue == R_keybuf)
			{
				KeyMarkDly++;
				if(FLG_keymark==0)
					{
					if(KeyMarkDly >= 50)
						{
						KeyMarkDly=0;
						FLG_keymark=1;
						R_keybuf=R_curkey=KeyValue;	
						KeyValue=0;						
						}
						else
							{
							KeyValue=0;
							}
					}
					else
						{
					 	if(KeyMarkDly >= 25)
							{
							KeyMarkDly=0;
							FLG_keymark=1;
							R_keybuf=R_curkey=KeyValue;	
							KeyValue=0;				
							}
						else
							{
							KeyValue=0;
							}						
						}		
			 }
			else//��������
				{
				R_keybuf=R_curkey=KeyValue;
				KeyValue=0;
				FLG_keymark=0;
				KeyMarkDly=0;	
				}		
			}
		else //�ް�������
			{
				//R_keybuf=0;
			 //FLG_keymark=0;
			 //KeyDly=0;
			 //KeyValue=0;
			 //KeyMarkDly=0;
			}
	}
	
void	KeyScan()//�����жϺ�����ִ��125usִ��һ��
{
	KeyValue=0;
	if(!key_add)
		{
			KeyValue=addkey;		
		}
	if(!key_sub)
		{

			KeyValue=subkey;	
		}
	if(!key_slt)
		{
			KeyValue=sltkey;	
		}
	if(!key_onoff)
		{
			KeyValue=onoffkey;	
		}
	}
//void	RF_CH_Change(unsigned char	RF_CH)
//{
//	CE=0;
//	SCK=0;
////	REG_write(0x00,0x0a); //CRC,8 bit,Power on,TX
////	REG_write(0x01,0x00); //unable ACK
////	REG_write(0x02,0x01); //enable P0
////	REG_write(0x04,0x00); //unable ACK
//	REG_write(0x05,R_CHtab[RF_CH]); //���Զ���
////	REG_write(0x06,0x07); //1Mbps,0dBm
////	REG_write(0x11,0x06);//DATA 6 bytes	
//	CE=1;		
//}
	