#ifndef _ReadKey_H
#define _ReadKey_H

//u8	R_KeyDelay		=0;
//u8	KeyMarkDly	=0;
extern bit FLG_keymark;
extern bit FLG_keyDouble;
extern bit FLG_EnableDoubleKey;
extern bit Flg_LongKey;
extern bit Flg_EnableLongKey;

extern bit Flg_EnableRelease;
extern bit Flg_KeyRelease;
extern bit Flg_KeyPress;

extern bit Flg_HaveKey;
extern unsigned char R_KeyDoubleTm;
extern unsigned int R_KeyPressTm;
extern unsigned char R_KeyValue;
//u8	R_OldKeyValue	=0;
extern unsigned char R_CurKey;
//u8	R_KeyBuffer	=0;

#define DefineDoubleKey 0
#define DefineLongKeyS  0

void	ReadR_KeyValue();

#ifdef DefineDoubleKey
void 	EnableDoubleKey();
#endif
#ifdef DefineLongKeyS
void 	EnableLongKeyS(unsigned char XS);
#endif



#endif