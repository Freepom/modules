typedef unsigned char BYTE;
typedef unsigned short WORD;

void Init_HMC5883(void); 
void  Single_Write_HMC5883(uchar REG_Address,uchar REG_data);   //单个写入数据
//uchar Single_Read_HMC5883(uchar REG_Address);                   //单个读取内部寄存器数据
void  Multiple_Read_HMC5883();                                  //连续的读取内部寄存器数据
//以下是模拟iic使用函数-------------
void Delay5us();
void Delay5ms();
void HMC5883_Start();
void HMC5883_Stop();
void HMC5883_SendACK(bit);
bit  HMC5883_RecvACK();
void HMC5883_SendByte(BYTE);
BYTE HMC5883_RecvByte();
void HMC5883_ReadPage();
void HMC5883_WritePage();