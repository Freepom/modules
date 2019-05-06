#ifndef	_eerom_H
#define	_eerom_H

#include<stc15w.h> 
#include "intrins.h"

#define u8 unsigned char
#define u16 unsigned int

#define STC15W408AS

// #ifdef (STC15W401AS || STC15W402AS || STC15W408AS || STC15W408S)
// #ifdef (STC15W408AS) 
    #define MAXSECTORCOUNTS 10
// #elseif (STC15W404AS || STC15W404S)
//     #define MAXSECTORCOUNTS 18
// #elif (STC15W410AS)
//     #define MAXSECTORCOUNTS 6
// #elif (STC15W412AS)
//     #define MAXSECTORCOUNTS 2
// #endif
/*Declare SFR associated with the IAP */
sfr IAP_DATA    =   0xC2;           //Flash data register
sfr IAP_ADDRH   =   0xC3;           //Flash address HIGH
sfr IAP_ADDRL   =   0xC4;           //Flash address LOW
sfr IAP_CMD     =   0xC5;           //Flash command register
sfr IAP_TRIG    =   0xC6;           //Flash command trigger
sfr IAP_CONTR   =   0xC7;           //Flash control register

/*Define ISP/IAP/EEPROM command*/
#define CMD_IDLE    0               //Stand-By
#define CMD_READ    1               //Byte-Read
#define CMD_PROGRAM 2               //Byte-Program
#define CMD_ERASE   3               //Sector-Erase

/*Define ISP/IAP/EEPROM operation const for IAP_CONTR*/
#define ENABLE_IAP 0x80           //if SYSCLK<30MHz
//#define ENABLE_IAP 0x81           //if SYSCLK<24MHz
//#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
//#define ENABLE_IAP 0x83           //if SYSCLK<12MHz
// #define ENABLE_IAP 0x84           //if SYSCLK<6MHz
//#define ENABLE_IAP 0x85           //if SYSCLK<3MHz
//#define ENABLE_IAP 0x86           //if SYSCLK<2MHz
//#define ENABLE_IAP 0x87           //if SYSCLK<1MHz

void writeData2OneSector(unsigned int sectorCount, unsigned char *buffer, unsigned int bufferLen);
void readDataFromOneSector(unsigned int sectorCount, unsigned char *buffer, unsigned int bufferLen);
#endif
