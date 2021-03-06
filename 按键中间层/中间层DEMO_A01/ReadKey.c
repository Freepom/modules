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

bit Flg_EnableRelease;
bit Flg_KeyRelease;
bit Flg_KeyPress;
bit Flg_KeyUp;

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
			Flg_KeyPress=1;//按键按下	
			if(R_KeyPressTm == 0)//长按时间到
				{
				if(Flg_EnableLongKey)//长按键使能切有效按键
					{					
					Flg_LongKey=1;//响应长按键
					Flg_EnableLongKey=0;
					Flg_EnableRelease=0;//响应长按键后，取消按键释放功能
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
			else//按键键值为0
				{
				
				Flg_EnableLongKey=0;
		
				}
		}
		else
			{
			Flg_EnableLongKey=0;

			if(R_OldKeyValue)//第一次产生有效按键
				{
				Flg_KeyPress=1;//按键按下
				Flg_KeyRelease=0;
				Flg_EnableRelease=0;					
				if(FLG_EnableDoubleKey)//是否开启了双击键
					{
					if(R_KeyDoubleTm)//如果再双击键的限定时间内
						{
						FLG_keyDouble=1;		//响应双击键
						R_CurKey=R_OldKeyValue;	//更新键值	
						Flg_HaveKey=1;		//响应按键键	
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
						R_CurKey=R_OldKeyValue;	//更新键值	
						Flg_HaveKey=1;
						FLG_keymark=0;
						R_KeyDelay=50;
						R_KeyPressTm=10;							
						}							
				}
				else//按键弹起
					{
//					R_CurKey=R_OldKeyValue;	//更新键值	
					if(Flg_EnableRelease)//是否使能按键释放功能
						{
						if(Flg_KeyPress)//按键是否已经按下
							{
							Flg_KeyRelease=1;//响应按键释放功能
							Flg_EnableRelease=0;	
//							R_CurKey=R_OldKeyValue;
							Flg_HaveKey=1;						
							}	
						}
						else
							{
							R_CurKey=R_OldKeyValue;	
							}
					Flg_KeyPress=0;//按键释放										
					}
				

			}

}
#if DefineDoubleKey
void EnableDoubleKey()
{
	if(FLG_EnableDoubleKey==0)
		{
		FLG_EnableDoubleKey=1;
//		FLG_keyDouble=1;
		R_KeyDoubleTm=100;
		}	
}
#endif
//-----------------------------------------
//
//按键长按键处理子程序
//
//-----------------------------------------
#if DefineLongKeyS
void EnableLongKeyS(unsigned char XS)
{
	if(Flg_EnableLongKey==0)
		{
		Flg_EnableLongKey=1;
//		Flg_LongKey=1;
		R_KeyPressTm=XS*1000/20;
		}	
}
#endif