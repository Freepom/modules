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
//备注：软件模拟SPI
//			
//		
//		
//		
//--------------------------------------------------------
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
//------------------------------------------------
//
//
//备注：写命令操作
//			
//		
//		
//		
//--------------------------------------------------------
void REG_write(u8 address,u8 command)	//写配置寄存器
{
	CSN=0;		//选中无线模块
	SPI(0x20+address);	//地址
	SPI(command);		//命令
	CSN=1;		//停止操作

}
//------------------------------------------------
//
//
//备注：写命令操作
//			
//		
//		
//		
//--------------------------------------------------------
u8 REG_Read(u8 address)	//写配置寄存器
{
	u8	Reg_value=0;
	CSN=0;		//选中无线模块
	SPI(address);	//地址
	Reg_value=SPI(0);		//命令,读取寄存器值
	CSN=1;		//停止操作
	
	return(Reg_value);

}
//------------------------------------------------
//
//
//备注：数据读取完之后，必须将NRF的中断寄存器清零，等待
//			下一次的中断响应
//		CE=0;
//		REG_write(0x07,0x40);	//清除无线模块中断信号
//		CE=1;
//--------------------------------------------------------
void FIFO_read(u8 DATA_IN[])		//读取接收数据缓冲区
{
	char i;
	CSN=0;
	SPI(0x61);	//读取命令
	for(i=0;i<RX_DATA_WITDH;i++)
	{
	DATA_IN[i]=SPI(0);	
	}
//	DATA_IN[0]=SPI(0);	//读取数据
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
//备注：将需要发送的数据放在数组DATA_OUT[]中，再执行
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
void RX_mode()					//将无线模块配置为接收模式
{
	CE=0;		//先关闭模块，才能写命令寄存器
	SCK=0;
//	REG_write(0xe1,0xff);
	REG_write(0x00,0xff); //CRC,8 bit,Power on,RX  0x3b
	REG_write(0x01,0x00); //不允许自动应答
	REG_write(0x02,0x01); //使用P0信道通信，使用默认地址
	REG_write(0x04,0x00); //不允许自动应答
	REG_write(0x05,0x40); //使用第64频道，总计128频道，可自定义
	REG_write(0x06,0x07); //1Mbps,0dBm
	REG_write(0x11,RX_DATA_WITDH);//每次信号6字节数据
	CE=1;
}

void TX_mode()			//设置为发射模式
{
	CE=0;
	SCK=0;
	REG_write(0xc1,0xff);
	REG_write(0x00,0xfe); //CRC,8 bit,Power on,TX
	REG_write(0x01,0x00); //unable ACK
	REG_write(0x02,0x01); //enable P0
	REG_write(0x04,0x00); //unable ACK
	REG_write(0x05,0x40); //使用第64通道，可自定义
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
	REG_write(0x05,ModelID_Tab[R_FrqCh]); //使用第64通道，可自定义
	CE=1;	
}
//-------------------------------------------
/*---------------NRF数据处理子程序------------
//--------------------------------------------
/输入：
/输出：
/备注：主循环中调用
/
*/
//-------------------------------------------
void	ClearData_NRF(bit Flg_Sta)//Flg_Sta=1接收数据缓存清零，Flg_Sta=0发送数据缓存清零
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