#include"ReadKey.h"
unsigned char	R_KeyDelay	=0;
unsigned char	KeyMarkDly	=0;
unsigned char	R_KeyDoubleTm	=0;
unsigned int	R_KeyPressTm	=0;
unsigned char	R_KeyValue	=0;
unsigned char	R_OldKeyValue	=0;
unsigned char	R_CurKey	=0;
unsigned char	R_KeyBuffer	=0;

bit	FLG_keymark	=0;
bit	FLG_keyDouble	=0;
bit	FLG_EnableDoubleKey	=0;
bit	Flg_LongKey	=0;
bit	Flg_EnableLongKey	=0;

bit 	Flg_HaveKey;

void	ReadR_KeyValue()//放在2ms分时中执行，20ms执行一次
{
//	if(!Flg_SisResetOK)	//系统未初始化完成，退出
//		return;
	if(R_KeyDelay)
		{
		R_KeyDelay--;	
		}
	if(R_KeyDoubleTm)
		{
		R_KeyDoubleTm--;	
		}		
	if(R_KeyPressTm)
		{
		R_KeyPressTm--;	
		}		
		else
			{
			Flg_EnableLongKey=0;
			FLG_EnableDoubleKey=0;
			FLG_keymark=0;	
			FLG_EnableDoubleKey=0;				
			}		
	if(!R_KeyDelay)
		{ 
		 R_OldKeyValue=0;
		Flg_EnableLongKey=0;
		FLG_keymark=0;			 	 
		}
//	if(R_KeyValue)
		{
		R_OldKeyValue=R_KeyValue;	
		}
	if(R_OldKeyValue == R_CurKey)
		{
		if(R_OldKeyValue)//当前键值不为0
			{
			if(R_KeyPressTm == 0)//长按时间到
				{
				if(Flg_EnableLongKey)//长按键使能切有效按键
					{					
					Flg_LongKey=1;
					Flg_EnableLongKey=0;
					R_CurKey=R_OldKeyValue;
					Flg_HaveKey=1;		
					}
					else
						{
						FLG_keymark=1;
						R_CurKey=R_OldKeyValue;
						Flg_HaveKey=1;
						R_KeyPressTm=1;	
						}					
				}

			R_KeyDelay=50;				
			}
			else
				{
				R_CurKey=R_OldKeyValue;
				Flg_EnableLongKey=0;		
				}
		}
		else//第一次产生有效按键
			{
			Flg_EnableLongKey=0;
			if(R_OldKeyValue)
				{
				if(FLG_EnableDoubleKey)
					{
					if(R_KeyDoubleTm)
						{
						FLG_keyDouble=1;
						R_CurKey=R_OldKeyValue;
						Flg_HaveKey=1;	
						R_KeyDelay=50;
						R_KeyPressTm=10;						
						}
						else
							{
							FLG_keyDouble=0;	
							}	
					}
					else
						{
						R_CurKey=R_OldKeyValue;
						Flg_HaveKey=1;
						FLG_keymark=0;
						R_KeyDelay=50;
						R_KeyPressTm=10;							
						}							
				}
				else
					{
					R_CurKey=R_OldKeyValue;							
					}
				

			}

}

void EnableDoubleKey()
{
	if(FLG_EnableDoubleKey==0)
		{
		FLG_EnableDoubleKey=1;
//		FLG_keyDouble=1;
		R_KeyDoubleTm=100;
		}	
}
//-----------------------------------------
//
//按键长按键处理子程序
//
//-----------------------------------------
void EnableLongKeyS(unsigned char XS)
{
	if(Flg_EnableLongKey==0)
		{
		Flg_EnableLongKey=1;
//		Flg_LongKey=1;
		R_KeyPressTm=XS*1000/20;
		}	
}