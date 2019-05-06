#include"NRF2401.h"

u8 SPI(u8 byte)		//以下为无线模块的控制程序，比较复杂。SPI模拟程序
{
	u8 i;
	for(i=0;i<8;i++)
	{
		MDI=(byte&0x80);//单片机输出最高位数据
		SCK=1;		//时钟信号的上升沿后无线模块读取新数据
		byte<<=1;	//数据左移
		byte|=MDO;	//单片机读取数据
		SCK=0;		//时钟信号的下降沿后无线模块输出新数据
	}
	return byte;
}

void REG_write(u8 address,u8 command)	//写配置寄存器
{
	CSN=0;		//选中无线模块
	SPI(0x20+address);	//地址
	SPI(command);		//命令
	CSN=1;		//停止操作

}

void FIFO_read(u8 DATA_IN[])		//读取接收数据缓冲区
{
	CSN=0;
	SPI(0x61);	//读取命令
	DATA_IN[0]=SPI(0);	//读取数据
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
void RX_mode()					//将无线模块配置为接收模式
{
	CE=0;		//先关闭模块，才能写命令寄存器
	SCK=0;
	REG_write(0x00,0x7b); //CRC,8 bit,Power on,RX
	REG_write(0x01,0x00); //不允许自动应答
	REG_write(0x02,0x01); //使用P0信道通信，使用默认地址
	REG_write(0x04,0x00); //不允许自动应答
	REG_write(0x05,64); //使用第64频道，总计128频道，可自定义
	REG_write(0x06,0x07); //1Mbps,0dBm
	REG_write(0x11,6);//每次信号6字节数据
	CE=1; 
}

void TX_mode()			//设置为发射模式
{
	CE=0;
	SCK=0;
	REG_write(0x00,0x0a); //CRC,8 bit,Power on,TX
	REG_write(0x01,0x00); //unable ACK
	REG_write(0x02,0x01); //enable P0
	REG_write(0x04,0x00); //unable ACK
	REG_write(0x05,0x40); //使用第64通道，可自定义
	REG_write(0x06,0x07); //1Mbps,0dBm
	REG_write(0x11,0x06);//DATA 6 bytes
	CE=1;
}

