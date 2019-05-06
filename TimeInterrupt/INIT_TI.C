#include <REG51.H>
#include	"INIT_TI.H"
void InitUart()
{
    SCON = 0x5a;                    //8 bit data ,no parity bit
    TMOD = 0x20;                    //T1 as 8-bit auto reload
    TH1 = TL1 = -(FOSC/12/32/BAUD); //Set Uart baudrate
    TR1 = 1;                        //T1 start running
}
void inittimer()
{
	TMOD|=0x01;	
	TH0=0x0c;
	TL0=0xdf;
	TR0=1;
	ET0=1;
	EA=1;
}