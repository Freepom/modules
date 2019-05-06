#include"NRF2401.h"

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

void REG_write(u8 address,u8 command)	//д���üĴ���
{
	CSN=0;		//ѡ������ģ��
	SPI(0x20+address);	//��ַ
	SPI(command);		//����
	CSN=1;		//ֹͣ����

}

void FIFO_read(u8 DATA_IN[])		//��ȡ�������ݻ�����
{
	CSN=0;
	SPI(0x61);	//��ȡ����
	DATA_IN[0]=SPI(0);	//��ȡ����
	DATA_IN[1]=SPI(0);
	DATA_IN[2]=SPI(0);
	DATA_IN[3]=SPI(0);
	DATA_IN[4]=SPI(0);
	DATA_IN[5]=SPI(0);
	CSN=1;
}
void FIFO_write(u8 DATA_OUT[])
{
	CSN=0;
	SPI(0xa0);
	SPI(DATA_OUT[0]);
	SPI(DATA_OUT[1]);
	SPI(DATA_OUT[2]);
	SPI(DATA_OUT[3]);
	SPI(DATA_OUT[4]);
	SPI(DATA_OUT[5]);
	CSN=1;
}
void RX_mode()					//������ģ������Ϊ����ģʽ
{
	CE=0;		//�ȹر�ģ�飬����д����Ĵ���
	SCK=0;
	REG_write(0x00,0x7b); //CRC,8 bit,Power on,RX
	REG_write(0x01,0x00); //�������Զ�Ӧ��
	REG_write(0x02,0x01); //ʹ��P0�ŵ�ͨ�ţ�ʹ��Ĭ�ϵ�ַ
	REG_write(0x04,0x00); //�������Զ�Ӧ��
	REG_write(0x05,64); //ʹ�õ�64Ƶ�����ܼ�128Ƶ�������Զ���
	REG_write(0x06,0x07); //1Mbps,0dBm
	REG_write(0x11,6);//ÿ���ź�6�ֽ�����
	CE=1; 
}

void TX_mode()			//����Ϊ����ģʽ
{
	CE=0;
	SCK=0;
	REG_write(0x00,0x0a); //CRC,8 bit,Power on,TX
	REG_write(0x01,0x00); //unable ACK
	REG_write(0x02,0x01); //enable P0
	REG_write(0x04,0x00); //unable ACK
	REG_write(0x05,0x40); //ʹ�õ�64ͨ�������Զ���
	REG_write(0x06,0x07); //1Mbps,0dBm
	REG_write(0x11,0x06);//DATA 6 bytes
	CE=1;
}

