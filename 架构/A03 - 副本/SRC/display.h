#ifndef	_display_H
#define	_display_H

#include "stc15w.h"
#include "main.h"

#define A_SEG 0x01// 0X01
#define B_SEG 0x02// 0X02
#define C_SEG 0x04// 0X04
#define D_SEG 0x08// 0X08      
#define E_SEG 0x10// 0X10     
#define F_SEG 0x20// 0X20    
#define G_SEG 0x40// 0X40    
#define H_SEG 0x80// 0X80    
//SEGC A_SEG+B_SEG+C_SEG+D_SEG+E_SEG+F_SEG+G_SEG+H_SEG
#define DT_0 	A_SEG+B_SEG+C_SEG+D_SEG+E_SEG+F_SEG+0+0
#define DT_1	 0+B_SEG+C_SEG+0+0+0+0+0
#define DT_2 	A_SEG+B_SEG+0+D_SEG+E_SEG+0+G_SEG+0
#define DT_3 	A_SEG+B_SEG+C_SEG+D_SEG+0+0+G_SEG+0
#define DT_4 	0+B_SEG+C_SEG+0+0+F_SEG+G_SEG+0
#define DT_5 	A_SEG+0+C_SEG+D_SEG+0+F_SEG+G_SEG+0
#define DT_6 	A_SEG+0+C_SEG+D_SEG+E_SEG+F_SEG+G_SEG+0
#define DT_7 	A_SEG+B_SEG+C_SEG+0+0+0+0+0
#define DT_8 	A_SEG+B_SEG+C_SEG+D_SEG+E_SEG+F_SEG+G_SEG+0
#define DT_9 	A_SEG+B_SEG+C_SEG+D_SEG+0+F_SEG+G_SEG+0
#define DT_A 	A_SEG+B_SEG+C_SEG+0+E_SEG+F_SEG+G_SEG+0   //0X77
#define DT_b 	0+0+C_SEG+D_SEG+E_SEG+F_SEG+G_SEG+0
#define DT_C 	A_SEG+0+0+D_SEG+E_SEG+F_SEG+0+0   //0X79
#define DT_d 	0+B_SEG+C_SEG+D_SEG+E_SEG+0+G_SEG+0
#define DT_E 	A_SEG+0+0+D_SEG+E_SEG+F_SEG+G_SEG+0
#define DT_F 	A_SEG+0+0+0+E_SEG+F_SEG+G_SEG+0   //0X71
#define DT_H 	B_SEG+0+C_SEG+0+E_SEG+F_SEG+G_SEG+0 
#define DT_L 	D_SEG+0+0+0+E_SEG+F_SEG+0+0 
#define DT_T 	D_SEG+0+0+0+E_SEG+F_SEG+G_SEG+0 
#define DT_O 	A_SEG+B_SEG+C_SEG+D_SEG+E_SEG+F_SEG+0+0   //0X3f
#define DT_P 	A_SEG+B_SEG+0+0+E_SEG+F_SEG+G_SEG+0   //0X3f
#define DT_R 	A_SEG+B_SEG+C_SEG+0+E_SEG+F_SEG+G_SEG+0
#define DT_n 	A_SEG+B_SEG+C_SEG+0+E_SEG+F_SEG+0+0   //0X54
#define DT_o 	0+0+C_SEG+D_SEG+E_SEG+0+G_SEG+0          //0X5C 
#define DT_XG 	0+0+0+0+0+0+G_SEG+0               //0X40
#define DT_LL 	0+0+C_SEG+0+0+F_SEG+G_SEG+0               //0X46
#define DT_L_L 	B_SEG+0+0+0+E_SEG+0+G_SEG+0
#define DT_G 	A_SEG+B_SEG+C_SEG+D_SEG+E_SEG+F_SEG+G_SEG+H_SEG              // 0X64
#define DT_NO 0 
#define DS_NO 15   //与数组中的位置对应

#define	nokey		0
#define	D_keyUp		1
#define	D_keyDown	2
#define	D_key3		3
#define	D_key4		4
#define	D_keyTimerSet	5
#define	D_keyRelease	6
	
	
extern unsigned char R_DBUF1,R_DBUF2,R_DBUF3,R_DBUF4,R_DBUF5;
extern unsigned char code Digit_Tab[];
extern unsigned char code Mode_Tab[];
extern bit Flg_DispOK;
//void Init_Disp();
void DispDrv();
void	KeyScan();
#endif