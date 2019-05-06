#ifndef _ReadKey_H
#define _ReadKey_H
#include <stdbool.h>

#define baseTime 10		//KeyValueChange()���õĻ�׼ʱ��

typedef struct{
	bool enReleaseKey;	//ʹ�ܵ�����Ч����
	bool enDoubleKey;		//ʹ��˫����Ч����
	bool enLongKey;			//ʹ�ܳ�����Ч����
	bool enCyclicKey;		//ʹ�ܰ�����Ч�������Դ�������
	
	bool stReleaseKey;	//����״̬
	bool stDoubleKey;		//˫��״̬
	bool stLongKey;			//����״̬
	bool stCyclicKey;		//������Ч�������Դ�������״̬
	
	bool isDown;				//��������=true����������=false
	unsigned int downTime; //��������ʱ��
	unsigned int upTime; 	 //��������ʱ��
	
	unsigned char oldValue; //��һ�ΰ���
	unsigned char newValue; //��ǰ����
	
}KeyParam_ts;
typedef struct{
	bool haveKey;				 //�������°���
	unsigned char value; //������ֵ
}KeyParamExt_ts;
/**
 * --------��������ת��
 * @since 2018-7-25
 * @Param1 PreKeyValue����Ҫת��ʵ�ֹ��ܵİ�����ֵ
 * @Addition
 * 		���Բ���������Ч��������Ч������ѭ����Ч��˫����Ч����
 *		������Ч������ѭ����Ч��˫����Ч������Ӧʱ���ܸú����ĵ���
 *		��׼ʱ���йأ�������׼ʱ��Ϊ10ms����֪Ϥ��
 * @Return 
 *		KeyParamExt_ts��haveKey=true�ſ��Դ�������valueȡ�ü�ֵ
 */
KeyParamExt_ts *KeyValueChange(unsigned char PreKeyValue);
/**
 * --------ʹ��˫����Ч����
 * @since 2018-7-25
 * @Param1 void
 * @Addition	Keys.upTime����׼ʱ��10ms
 *						ʹ�÷�����.c�ļ�ͷ
 * @Return 
 *
 */
void 	EnableDoubleKey(void);
bool getDoubleKeySt(void);
void clearDoubleKey(void);
/**
 * --------ʹ�ܳ�����Ч���ܣ�������Ч
 * @since 2018-7-25
 * @Param1 void
 * @Addition	Keys.downTime����׼ʱ��10ms
 *						ʹ�÷�����.c�ļ�ͷ
 * @Return 
 *
 */
void 	EnableLongKey(unsigned int Xms);
bool getLongKeySt(void);
void clearLongKey(void);
/**
 * --------ʹ��ѭ��������Ч���ܣ�ѭ����Ч
 * @since 2018-7-25
 * @Param1 void
 * @Addition	Keys.downTime����׼ʱ��10ms
 *						ʹ�÷�����.c�ļ�ͷ
 * @Return 
 *
 */
void 	EnableCyclicKey(unsigned int Xms);
bool getCyclicKeySt(void);
void clearCyclicKey(void);
/**
 * --------ʹ�ܵ�����Ч����
 * @since 2018-7-25
 * @Param1 void
 * @Addition	
 *						ʹ�÷�����.c�ļ�ͷ
 * @Return 
 *
 */
void 	EnableReleaseKey(void);
bool getReleaseKeySt(void);
void clearReleaseKey(void);
#endif
