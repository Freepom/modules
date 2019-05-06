//////    ���������е���Multiple_Read_HMC5883();      //�����������ݣ��洢��BUF��
///////////////////////���������ͬʱ��double angle;
///////////////////////////////////////����Ϊȫ�ֱ���
///////////////////////   ��ʼ������Init_HMC5883();

#include  <REG51.H>	
#include  <math.h>    //Keil library
#include  <INTRINS.H> 
#include  "HMC5883.h" 
#define	SlaveAddress   0x3C	  //��������5883��IIC�����еĴӵ�ַ

sbit	SCL=P1^0;      //IICʱ�����Ŷ���
sbit	SDA=P1^1;      //IIC�������Ŷ���
double angle;
BYTE BUF[8];			//�������ݻ�����

/**************************************
��ʱ5΢��(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺�����ע��ʱ�ӹ���ʱ��Ҫ�޸�
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5us()
{
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
}

/**************************************
��ʱ5����(STC90C52RC@12M)
��ͬ�Ĺ�������,��Ҫ�����˺���
������1T��MCUʱ,���������ʱ����
**************************************/
void Delay5ms()
{
    WORD n = 560;

    while (n--);
}

/**************************************
��ʼ�ź�
**************************************/
void HMC5883_Start()
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 0;                    //�����½���
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
}

/**************************************
ֹͣ�ź�
**************************************/
void HMC5883_Stop()
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 1;                    //����������
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void HMC5883_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
bit HMC5883_RecvACK()
{
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ

    return CY;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void HMC5883_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    HMC5883_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
BYTE HMC5883_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    return dat;
}

//***************************************************

void Single_Write_HMC5883(uchar REG_Address,uchar REG_data)
{
    HMC5883_Start();                  //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    HMC5883_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf 
    HMC5883_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf
    HMC5883_Stop();                   //����ֹͣ�ź�
}
 /*
//********���ֽڶ�ȡ�ڲ��Ĵ���*************************
uchar Single_Read_HMC5883(uchar REG_Address)
{  uchar REG_data;
    HMC5883_Start();                          //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    HMC5883_SendByte(REG_Address);                   //���ʹ洢��Ԫ��ַ����0��ʼ	
    HMC5883_Start();                          //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data=HMC5883_RecvByte();              //�����Ĵ�������
	HMC5883_SendACK(1);   
	HMC5883_Stop();                           //ֹͣ�ź�
    return REG_data; 
}
*/
//******************************************************
//
//��������HMC5883�ڲ��Ƕ����ݣ���ַ��Χ0x3~0x5
//
//******************************************************
void Multiple_read_HMC5883(void)
{   uchar i;
   int x,y,z;
//   double angle;
    HMC5883_Start();                          //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    HMC5883_SendByte(0x03);                   //���ʹ洢��Ԫ��ַ����0x3��ʼ	
    HMC5883_Start();                          //��ʼ�ź�
    HMC5883_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
	 for (i=0; i<7; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = HMC5883_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 6)
        {
           HMC5883_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
          HMC5883_SendACK(0);                //��ӦACK
       }
   }
    HMC5883_Stop();                          //ֹͣ�ź�
    Delay5ms();
	x = BUF[0] << 8 | BUF[1]; 
    y = BUF[4] << 8 | BUF[5]; 
	z = BUF[2] << 8 | BUF[3]; 
    angle= atan2((double)y,(double)x) * (180 / 3.14159265) + 180; // angle in degrees
}

//��ʼ��HMC5883��������Ҫ��ο�pdf�����޸�****
void Init_HMC5883()
{
     Single_Write_HMC5883(0x02,0x00);  //
	 Single_Write_HMC5883(0x01,0xE0);  //
}

// uchar code lcd_mun_to_char[16]={"0123456789ABCDEF"};     	                      //����
//
////*********************************************************
//void conversion(uint temp_data)  
//{  
//    HMC5883_tab[4]=temp_data/10000 ;
//	HMC5883_tab[3]=temp_data%10000/1000 ;
//	HMC5883_tab[2]=temp_data%1000/100 ;
//	HMC5883_tab[1]=temp_data%100/10 ;
//	HMC5883_tab[0]=temp_data%10 ;	
//}