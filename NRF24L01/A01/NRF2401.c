#include"NRF2401.h"

u8 RxNRF_Tab[RX_DATA_WITDH],TxNRF_Tab[TX_DATA_WITDH];
u8 code ModelID_Tab[]={//36*3
	0x40,0x0d,0x43, 0x03,0x08,0x05, 0x06,0x0a,0x46, 0x09,0x04,0x0b, 0x4a,0x01,0x0e, 
	0x0f,0x1c,0x52, 0x32,0x17,0x14, 0x15,0x19,0x55, 0x18,0x13,0x1a, 0x59,0x10,0x1d,
	0x1e,0x2b,0x61, 0x21,0x26,0x23, 0x24,0x28,0x64, 0x27,0x22,0x29, 0x68,0x1f,0x2c,
	0x2d,0x3a,0x71, 0x30,0x35,0x32, 0x33,0x37,0x74, 0x36,0x31,0x38, 0x77,0x2e,0x3b, 
	0x03,0x49,0x3e, 0x3f,0x44,0x41, 0x42,0x07,0x02, 0x45,0x00,0x47, 0x48,0x3d,0x0c,
	0x12,0x58,0x4d, 0x4e,0x53,0x50, 0x51,0x16,0x11, 0x54,0x4f,0x56, 0x57,0x4c,0x1b,
	0x21,0x67,0x5c, 0x5d,0x62,0x5f, 0x60,0x25,0x20, 0x63,0x5e,0x65, 0x66,0x5b,0x2a, 
	0x30,0x6b,0x6c, 0x6d,0x72,0x6f, 0x71,0x34,0x2f, 0x73,0x6e,0x75, 0x6a,0x76,0x39,
	0x78,0x7c,0x7a, 0x7b,0x7d,0x79, 0x70,0x16,0x7d, 0x10,0x26,0x4d, 0x20,0x56,0x7d,
	};
//------------------------------------------------
//
//
//��ע�����ģ��SPI
//			
//		
//		
//		
//--------------------------------------------------------
u8 SPI(u8 byte)		//����Ϊ����ģ��Ŀ��Ƴ��򣬱Ƚϸ��ӡ�SPIģ�����
{
	u8 i;
	for(i=0;i<8;i++)
	{
		MDI=(byte&0x80);//��Ƭ��������λ����
		SCK=1;		//ʱ���źŵ������غ�����ģ���ȡ������
		byte<<=1;	//��������
		byte|=MDO;	//��Ƭ����ȡ����
		SCK=0;		//ʱ���źŵ��½��غ�����ģ�����������
	}
	return byte;
}
//------------------------------------------------
//
//
//��ע��д�������
//			
//		
//		
//		
//--------------------------------------------------------
void REG_write(u8 address,u8 command)	//д���üĴ���
{
	CSN=0;		//ѡ������ģ��
	SPI(0x20+address);	//��ַ
	SPI(command);		//����
	CSN=1;		//ֹͣ����

}
//------------------------------------------------
//
//
//��ע��д�������
//			
//		
//		
//		
//--------------------------------------------------------
u8 REG_Read(u8 address)	//д���üĴ���
{
	u8	Reg_value=0;
	CSN=0;		//ѡ������ģ��
	SPI(address);	//��ַ
	Reg_value=SPI(0);		//����,��ȡ�Ĵ���ֵ
	CSN=1;		//ֹͣ����
	
	return(Reg_value);

}
//------------------------------------------------
//
//
//��ע�����ݶ�ȡ��֮�󣬱��뽫NRF���жϼĴ������㣬�ȴ�
//			��һ�ε��ж���Ӧ
//		CE=0;
//		REG_write(0x07,0x40);	//�������ģ���ж��ź�
//		CE=1;
//--------------------------------------------------------
void FIFO_read(u8 DATA_IN[])		//��ȡ�������ݻ�����
{
	char i;
	CSN=0;
	SPI(0x61);	//��ȡ����
	for(i=0;i<RX_DATA_WITDH;i++)
	{
	DATA_IN[i]=SPI(0);	
	}
//	DATA_IN[0]=SPI(0);	//��ȡ����
//	DATA_IN[1]=SPI(0);
//	DATA_IN[2]=SPI(0);
//	DATA_IN[3]=SPI(0);
//	DATA_IN[4]=SPI(0);
//	DATA_IN[5]=SPI(0);
	CSN=1;
}
//------------------------------------------------
//
//
//��ע������Ҫ���͵����ݷ�������DATA_OUT[]�У���ִ��
//			FIFO_write(u8 DATA_OUT[])
//		
//		
//		
//--------------------------------------------------------
void FIFO_write(u8 DATA_OUT[])
{
	char i;
	CSN=0;
	SPI(0xa0);
	for(i=0;i<TX_DATA_WITDH;i++)
	{
	SPI(DATA_OUT[i]);	
	}
	
//	SPI(DATA_OUT[1]);
//	SPI(DATA_OUT[2]);
//	SPI(DATA_OUT[3]);
//	SPI(DATA_OUT[4]);
//	SPI(DATA_OUT[5]);
	CSN=1;
}
void RX_mode()					//������ģ������Ϊ����ģʽ
{
	CE=0;		//�ȹر�ģ�飬����д����Ĵ���
	SCK=0;
//	REG_write(0xe1,0xff);
	REG_write(0x00,0xff); //CRC,8 bit,Power on,RX  0x3b
	REG_write(0x01,0x00); //�������Զ�Ӧ��
	REG_write(0x02,0x01); //ʹ��P0�ŵ�ͨ�ţ�ʹ��Ĭ�ϵ�ַ
	REG_write(0x04,0x00); //�������Զ�Ӧ��
	REG_write(0x05,0x40); //ʹ�õ�64Ƶ�����ܼ�128Ƶ�������Զ���
	REG_write(0x06,0x07); //1Mbps,0dBm
	REG_write(0x11,RX_DATA_WITDH);//ÿ���ź�6�ֽ�����
	CE=1;
}

void TX_mode()			//����Ϊ����ģʽ
{
	CE=0;
	SCK=0;
	REG_write(0xc1,0xff);
	REG_write(0x00,0xfe); //CRC,8 bit,Power on,TX
	REG_write(0x01,0x00); //unable ACK
	REG_write(0x02,0x01); //enable P0
	REG_write(0x04,0x00); //unable ACK
	REG_write(0x05,0x40); //ʹ�õ�64ͨ�������Զ���
	REG_write(0x06,0x07); //1Mbps,0dBm
	REG_write(0x11,TX_DATA_WITDH);//DATA 6 bytes
	CE=1;
}
void SetMode_NRF(bit Flg_Sta)//Tx:Flg_Sta=0 Rx:Flg_Sta=1
{
	if(Flg_Sta)
		{
		RX_mode();
		}
		
		else
			{
			TX_mode();	
			}
}
void SetFrqCh_NRF(u8 R_FrqCh)
{
	CE=0;
	SCK=0;
	REG_write(0x05,ModelID_Tab[R_FrqCh]); //ʹ�õ�64ͨ�������Զ���
	CE=1;	
}
//-------------------------------------------
/*---------------NRF���ݴ����ӳ���------------
//--------------------------------------------
/���룺
/�����
/��ע����ѭ���е���
/
*/
//-------------------------------------------
void	ClearData_NRF(bit Flg_Sta)//Flg_Sta=1�������ݻ������㣬Flg_Sta=0�������ݻ�������
{
	u8 i;
	if(Flg_Sta)
		{
		for(i=0;i<RX_DATA_WITDH;i++)
			{		
			RxNRF_Tab[i]=0;		
			}	
		}
		else
			{
			for(i=0;i<TX_DATA_WITDH;i++)
				{		
				TxNRF_Tab[i]=0;		
				}	
			}
	
}