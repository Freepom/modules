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

void	ReadR_KeyValue()//����2ms��ʱ��ִ�У�20msִ��һ��
{
//	if(!Flg_SisResetOK)	//ϵͳδ��ʼ����ɣ��˳�
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
		if(R_OldKeyValue)//��ǰ��ֵ��Ϊ0
			{
			Flg_KeyPress=1;//��������	
			if(R_KeyPressTm == 0)//����ʱ�䵽
				{
				if(Flg_EnableLongKey)//������ʹ������Ч����
					{					
					Flg_LongKey=1;//��Ӧ������
					Flg_EnableLongKey=0;
					Flg_EnableRelease=0;//��Ӧ��������ȡ�������ͷŹ���
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
			else//������ֵΪ0
				{
				
				Flg_EnableLongKey=0;
		
				}
		}
		else
			{
			Flg_EnableLongKey=0;

			if(R_OldKeyValue)//��һ�β�����Ч����
				{
				Flg_KeyPress=1;//��������
				Flg_KeyRelease=0;
				Flg_EnableRelease=0;					
				if(FLG_EnableDoubleKey)//�Ƿ�����˫����
					{
					if(R_KeyDoubleTm)//�����˫�������޶�ʱ����
						{
						FLG_keyDouble=1;		//��Ӧ˫����
						R_CurKey=R_OldKeyValue;	//���¼�ֵ	
						Flg_HaveKey=1;		//��Ӧ������	
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
						R_CurKey=R_OldKeyValue;	//���¼�ֵ	
						Flg_HaveKey=1;
						FLG_keymark=0;
						R_KeyDelay=50;
						R_KeyPressTm=10;							
						}							
				}
				else//��������
					{
//					R_CurKey=R_OldKeyValue;	//���¼�ֵ	
					if(Flg_EnableRelease)//�Ƿ�ʹ�ܰ����ͷŹ���
						{
						if(Flg_KeyPress)//�����Ƿ��Ѿ�����
							{
							Flg_KeyRelease=1;//��Ӧ�����ͷŹ���
							Flg_EnableRelease=0;	
//							R_CurKey=R_OldKeyValue;
							Flg_HaveKey=1;						
							}	
						}
						else
							{
							R_CurKey=R_OldKeyValue;	
							}
					Flg_KeyPress=0;//�����ͷ�										
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
//���������������ӳ���
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