#include "eerom.h"

/*----------------------------
Disable ISP/IAP/EEPROM function
Make MCU in a safe state
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //Close IAP function
    IAP_CMD = 0;                    //Clear command to standby
    IAP_TRIG = 0;                   //Clear trigger register
    IAP_ADDRH = 0x80;               //Data ptr point to non-EEPROM area
    IAP_ADDRL = 0;                  //Clear IAP address to prevent misuse
}


/*----------------------------
Erase one sector area
Input: addr (ISP/IAP/EEPROM address)
Output:-
----------------------------*/
static void IapEraseSector(u16 addr)
{
    IAP_CONTR = ENABLE_IAP;         //Open IAP function, and set wait time
    IAP_CMD = CMD_ERASE;            //Set ISP/IAP/EEPROM ERASE command
    IAP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    IAP_TRIG = 0x5A;                //Send trigger command1 (0x46)
    IAP_TRIG = 0xA5;                //Send trigger command2 (0xb9)
    _nop_();                        //MCU will hold here until ISP/IAP/EEPROM operation complete
    _nop_(); 
    _nop_(); 
    IapIdle();
}
/**
 * @funtion: IAP写入一串数据
 * stc部分单片机有独立的eeprom
 * IAP操作
 * 每个扇区512Byte，
 * @params:sectorCount=>扇区标号
*/
void writeData2OneSector(unsigned int sectorCount, unsigned char *buffer, unsigned int bufferLen)
{
    unsigned int writeStartAddr;
    if(sectorCount < 1){
        sectorCount = 1;
    }

    if(sectorCount > MAXSECTORCOUNTS){
        sectorCount = MAXSECTORCOUNTS;
    }
    writeStartAddr = 512*(sectorCount - 1);
    IapEraseSector(writeStartAddr);

    IAP_CONTR = ENABLE_IAP;         //Open IAP function, and set wait time
    IAP_CMD = CMD_PROGRAM;          //Set ISP/IAP/EEPROM PROGRAM command
    while(bufferLen){
        IAP_ADDRL = writeStartAddr;               //Set ISP/IAP/EEPROM address low
        IAP_ADDRH = writeStartAddr >> 8;          //Set ISP/IAP/EEPROM address high
        IAP_DATA = *buffer;                 //Write ISP/IAP/EEPROM data
        IAP_TRIG = 0x5A;                //Send trigger command1 (0x46)
        IAP_TRIG = 0xA5;                //Send trigger command2 (0xb9)
        _nop_();                        //MCU will hold here until ISP/IAP/EEPROM operation complete
        _nop_(); 
        _nop_();

        writeStartAddr ++;
        buffer ++;
        bufferLen --;
    }
    IapIdle();
    
}
/**
 * @funtion: IAP读取一串数据
 * stc部分单片机有独立的eeprom
 * IAP操作
 * 每个扇区512Byte，
 * @params:sectorCount=>扇区标号
*/
void readDataFromOneSector(unsigned int sectorCount, unsigned char *buffer, unsigned int bufferLen)
{
    unsigned int readStartAddr;
    if(sectorCount < 1){
        sectorCount = 1;
    }

    if(sectorCount > MAXSECTORCOUNTS){
        sectorCount = MAXSECTORCOUNTS;
    }
    readStartAddr = 512*(sectorCount - 1);
    IAP_CONTR = ENABLE_IAP;         //Open IAP function, and set wait time
    IAP_CMD = CMD_READ;             //Set ISP/IAP/EEPROM READ command
    while(bufferLen){        
        IAP_ADDRL = readStartAddr;               //Set ISP/IAP/EEPROM address low
        IAP_ADDRH = readStartAddr >> 8;          //Set ISP/IAP/EEPROM address high
        IAP_TRIG = 0x5A;                //Send trigger command1 (0x46)
        IAP_TRIG = 0xA5;                //Send trigger command2 (0xb9)
        _nop_();                        //MCU will hold here until ISP/IAP/EEPROM operation complete
        _nop_(); 
        _nop_();
        *buffer = IAP_DATA;                 //Read ISP/IAP/EEPROM data

        readStartAddr ++;
        buffer ++;
        bufferLen --;    
    }
    
    IapIdle();                      //Close ISP/IAP/EEPROM function    
}