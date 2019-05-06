#ifndef _MAIN_H
#define _MAIN_H



#define u8 unsigned char
#define u16 unsigned int

#define	D_MMode_Main		0
#define	D_MMode_TimerDisp	1
#define	D_MMode_Set		2
#define	D_MMode_SetAlarm	3
#define	D_MMode_SetTimer	4
#define	D_MMode_SetPan		5


#define	ToBakMode(n) {if(n==1)\
			{R_SetQuit=1;R_ModeBak=R_MainMode;}\
			else\
			{R_SetQuit=2;R_ModeBak=R_SetMode;}\
			}

extern bit Flg_500MsFlash;
extern u8 R_MainMode;
extern u8 R_AudioAD;	
extern u8 R_PanLight;
extern bit Flg_HaveAudio; 
extern u16 R_T1ExtCnt; 
extern u16 idata R_SpeedCnt;
//----------------------------------------------------------
#endif
