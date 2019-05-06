// Header:
// File Name: 
// Author:
// Date:
// ʹ�þ�����
/*
		if(isTmFor10ms){
			isTmFor10ms = false;
			KeyIn = KeyValueChange(mKeyValue);
		}
			if(K1 == 0){

					mKeyValue =1;
			}	else if(K2 == 0){
			mKeyValue =2;
			}else if(K3 == 0){
			mKeyValue =3;
			}else if(K4 == 0){
			mKeyValue =4;
			}else{
			mKeyValue =0;
			}
			
			if(KeyIn->haveKey){
				KeyIn->haveKey = false;
				switch(KeyIn->value){
					case 1:
						EnableLongKey(100);	
						if(getLongKeySt() == true){
							clearLongKey();	
							lenth++;
						}			
					break;
					case 2:
						EnableDoubleKey();	
						if(getDoubleKeySt() == true){
							clearDoubleKey();				
							lenth++;
						}							
					break;
					case 3:
						EnableReleaseKey();	
						if(getReleaseKeySt() == true){
							clearReleaseKey();				
							lenth++;
						}							
					break;	
					case 4:
						EnableCyclicKey(100);	
						if(getCyclicKeySt() == true)
							{			
									lenth++;
						}							
					break;
					default:
						break;
				}
				
			}
*/
#include "ReadKey.h"

KeyParam_ts Keys;
KeyParamExt_ts KeysExt;
/**
 * --------��������ת��
 * @since 2018-7-25
 * @Param1 PreKeyValue����Ҫת��ʵ�ֹ��ܵİ�����ֵ
 * @Addition
 * 		���Բ���������Ч��������Ч������ѭ����Ч��˫����Ч����
 *		������Ч������ѭ����Ч��˫����Ч������Ӧʱ���ܸú����ĵ���
 *		��׼ʱ���йأ�������׼ʱ��:baseTime=10ms�����в�ͬ������.h�ļ����޸���֪Ϥ��
 * @Return 
 *		KeyParamExt_ts��haveKey=true�ſ��Դ�������valueȡ�ü�ֵ
 */
KeyParamExt_ts *KeyValueChange(unsigned char PreKeyValue){
	
	Keys.newValue = PreKeyValue;
	if(Keys.upTime){
		Keys.upTime--;
	}else{
		Keys.enDoubleKey = false;
	}
		
	if(Keys.newValue){
		if(Keys.downTime){
			Keys.downTime--;
		}		
		if(Keys.newValue == Keys.oldValue){//��ȣ���ʾ��������״̬��
//------------------------------������-----------------------------------					
			if(Keys.enLongKey){//���ʹ���˳�����Ч���ܣ����δ���
				if(Keys.downTime == 0){//�������ʱ�䵽
					if(Keys.stLongKey == false){//���δ����������
						KeysExt.haveKey = true;	//��������
					}
					Keys.stLongKey = true;
				}
			}
//------------------------------ѭ��������-----------------------------------					
			if(Keys.enCyclicKey){//���ʹ���˳���ѭ����Ч���ܣ�ѭ������
				if(Keys.downTime == 0){//�������ʱ�䵽
					KeysExt.haveKey = true;	//��������
					Keys.stCyclicKey = true;	//������ѭ��������
				}
			}	
			
		}else{//����ȣ���ʾ�°������£����˫����
//------------------------------˫������-----------------------------------					
			if(Keys.enDoubleKey){//���ʹ����˫����Ч����
				if(Keys.upTime){//����ڰ�������ʱ�䷶Χ��
					KeysExt.haveKey = true;	//��������
					Keys.stDoubleKey = true;	//������˫������
				}				
			}
		}
//------------------------------�������ܰ���-----------------------------------				
		if(Keys.isDown == false){//��һ�β�������
			KeysExt.haveKey = true;	//��������
		}
		//���°���
		Keys.oldValue = Keys.newValue;	
		Keys.stReleaseKey = false;	
		Keys.isDown = true;
	}else{//����δ���£����˫�����͵�����Ч����
//------------------------------���𰴼�-----------------------------------				
		if(Keys.enReleaseKey){//���ʹ���˵�����Ч����
			if(Keys.isDown){//��ʾ��������
				KeysExt.haveKey = true;	//��������
				Keys.stReleaseKey = true;	//�����˵��𰴼�
			}
		}else{
			//���°���
			Keys.oldValue = Keys.newValue;		
		}
		Keys.enCyclicKey = false;
		Keys.enLongKey = false;
		Keys.stLongKey = false;
		Keys.stCyclicKey = false;
		Keys.stDoubleKey = false;
		Keys.isDown = false;
	}
	

	KeysExt.value = Keys.oldValue;
	return &KeysExt;
}
/**
 * --------ʹ��˫����Ч����
 * @since 2018-7-25
 * @Param1 void
 * @Addition	Keys.upTime����׼ʱ��10ms
 *						ʹ�÷�����.c�ļ�ͷ
 * @Return 
 *
 */
void EnableDoubleKey(void)
{
	if(Keys.enDoubleKey==false)
		{
		Keys.enDoubleKey = true; 
		Keys.upTime= 500/baseTime;
		}	
}
bool getDoubleKeySt(void){
	return Keys.stDoubleKey;
}
void clearDoubleKey(void){
	Keys.enDoubleKey = false;
}
//-----------------------------------------
//
//���������������ӳ���
//
//-----------------------------------------
/**
 * --------ʹ�ܳ�����Ч���ܣ�������Ч
 * @since 2018-7-25
 * @Param1 void
 * @Addition	Keys.downTime����׼ʱ��10ms
 *						ʹ�÷�����.c�ļ�ͷ
 * @Return 
 *
 */
void EnableLongKey(unsigned int Xms)
{
	if(Keys.enLongKey==false)
		{
		Keys.enLongKey = true; 
		Keys.downTime=Xms/baseTime;
		}	
}
bool getLongKeySt(void){
	return Keys.stLongKey;
}
void clearLongKey(void){
	Keys.enLongKey = false;
}
//-----------------------------------------
//
//����ѭ��������Ч�����ӳ���
//
//-----------------------------------------
/**
 * --------ʹ��ѭ��������Ч���ܣ�ѭ����Ч
 * @since 2018-7-25
 * @Param1 void
 * @Addition	Keys.downTime����׼ʱ��10ms
 *						����Ҫ�����״���Ч�����������getCyclicKeySt()
 *						ʹ�÷�����.c�ļ�ͷ
 * @Return 
 *
 */
void EnableCyclicKey(unsigned int Xms)
{
		Keys.enCyclicKey = true; 
		Keys.downTime = Xms/baseTime;	
}
bool getCyclicKeySt(void){
	return Keys.stCyclicKey;
}
//void clearCyclicKey(void){
//	Keys.enCyclicKey = false;
//}

//-----------------------------------------
//
//����������Ч�����ӳ���
//
//-----------------------------------------
//-----------------------------------------
/**
 * --------ʹ�ܵ�����Ч����
 * @since 2018-7-25
 * @Param1 void
 * @Addition	
 *						ʹ�÷�����.c�ļ�ͷ
 * @Return 
 *
 */
void EnableReleaseKey(void)
{
		Keys.enReleaseKey = true; 
}
bool getReleaseKeySt(void){
	return Keys.stReleaseKey;
}
void clearReleaseKey(void){
	Keys.enReleaseKey = false;
}
