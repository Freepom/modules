#include"IIC.h"

/////////24C08读写驱动程序////////////////////
void  delay1_IIC(unsigned char x)
{  unsigned int i;
  for(i=0;i<x;i++)
  ;
  ;
 }
void flash()
{  
	;  
	; 
}
void x24c08_init()  //24c08初始化子程序
 {
 	scl=1; 
 	flash(); 
 	sda=1; 
 	flash();
 }
void start()        //启动I2C总线
{
	sda=1; 
	flash(); 
	scl=1; 
	flash(); 
	sda=0; 
	flash(); 
	scl=0; 
	flash();
}
void stop()         //停止I2C总线
{
	sda=0; 
	flash(); 
	scl=1; 
	flash(); 
	sda=1; 
	flash();
}
void writex(unsigned char j)  //写一个字节
{  
	unsigned char i,temp;
   	temp=j;
   for (i=0;i<8;i++)
   {
   	temp=temp<<1;
   	scl=0; 
   	flash(); 
   	sda=CY; 
   	flash(); 
   	scl=1; 
   	flash();
   }
   scl=0; 
   flash(); 
   sda=1; 
   flash();
}
unsigned char readx()   //读一个字节
{
   unsigned char i,j,k=0;
   scl=0; flash(); sda=1;
   for (i=0;i<8;i++)
   {  
   	flash(); 
   	scl=1; 
   	flash();
      if (sda==1) 
      	j=1;
      else 
      	j=0;
      k=(k<<1)|j;
	  scl=0;}
   	flash(); 
   	return(k);
}
void clock()         //I2C总线时钟
{
   unsigned char i=0;
   scl=1; 
   flash();
   while ((sda==1)&&(i<255))
   i++;
   scl=0; 
   flash();
}
////////从24c02的地址address中读取一个字节数据/////
unsigned char x24c08_read(unsigned char address)
{
   unsigned char i;
   start(); 
   writex(0xa0);
   clock(); 
   writex(address);
   clock(); 
   start();
   writex(0xa1); 
   clock();
   i=readx(); 
   stop();
    delay1_IIC(10);
   return(i);
}
//////向24c02的address地址中写入一字节数据info/////
void x24c08_write(unsigned char address,unsigned char info)
{
//   EA=0;
   start(); 
   writex(0xa0);
   clock(); 
   writex(address);
   clock(); 
   writex(info);
   clock(); 
   stop();
//   EA=1;
    delay1_IIC(50);
}