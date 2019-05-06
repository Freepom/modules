
#include<stc15w.h>
#define u8 unsigned char
#define u16 unsigned int

sbit MDO=P1^4;
sbit MDI=P1^3;
sbit SCK=P1^5;
sbit CE=P5^4;
sbit IRQ=P3^2;
sbit CSN=P1^2;

//sbit MDO=P2^1;
//sbit MDI=P2^2;
//sbit SCK=P2^3;
//sbit CE=P2^5;
//sbit IRQ=P2^0;
//sbit CSN=P2^4;

/*******************************************************/
#define TX_ADDR_WITDH 5	//���͵�ַ�������Ϊ5���ֽ�
#define RX_ADDR_WITDH 5	//���յ�ַ�������Ϊ5���ֽ�
#define TX_DATA_WITDH 16//�������ݿ��1���ֽ�
#define RX_DATA_WITDH 16//�������ݿ��1���ֽ�

extern u8 RxNRF_Tab[RX_DATA_WITDH],TxNRF_Tab[TX_DATA_WITDH];
extern u8 code ModelID_Tab[];

u8 SPI(u8 byte);
void REG_write(u8 address,u8 command);
u8 REG_Read(u8 address);	//д���üĴ���
void FIFO_read(u8 DATA_IN[]);
void FIFO_write(u8 DATA_OUT[]);
void RX_mode();
void TX_mode();
void SetMode_NRF(bit Flg_Sta);//Tx:Flg_Sta=0 Rx:Flg_Sta=1
void SetFrqCh_NRF(u8 R_FrqCh);
void ClearData_NRF(bit Flg_Sta);//Flg_Sta=1�������ݻ������㣬Flg_Sta=0�������ݻ�������