/*
                                                  FILE-START
*/
/*

 *@�ļ�����: .h

 *@�ļ�����: ��

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע    ��: ��

*/
/*
                                                  ���ظ������������
*/
#ifndef __osSignalH_
#define __osSignalH_

/*
                                                  <�����ļ���>
*/
#include "main.h"
#include "osMain.h"
//#include "osTask.h"
/*
                                                  <�궨����>
*/
#define osSignal_Enable //���ö��� ��������������ֶ����ã������Զ�����ļ����Զ���������

#define Signal_Mutual       0x01u//�����ź���
//ʲô�ǻ����ź���?
//
#define Signal_Binary       0x02u//��ֵ�ź���
//ʲô�Ƕ�ֵ�ź���?

#define Signal_Count        0x03u//�����ź���
//ʲô�ǻ����ź���?
#define Signal_Logout		0x04u//��Ч�ź���


#define osSignalMutual_Enable //���û����ź���
#define osSignalBinary_Enable //���ö�ֵ�ź���
#define osSignalCount_Enable  //���ü����ź���


/*
                                                  �������ͱ���������
*/
typedef     u32      _SemaphoreValue;
typedef     u8       _SemaphoreType;
typedef		u8 		 _Occupy_TaskID;
typedef		u32		 _SignalPost;
/*
                                                  �ṹʽ�������ͱ���������
*/
typedef struct
{
    _SemaphoreValue 	 SV;//�ź�ֵ
    _SemaphoreType   	ST;//�źŵ�����
	_SignalPost*		 SP;
}SemaphoreTable;//�ź���

/*
                                                  <����������>
*/
/*
                                                  <����������>
*/
#if (osSignalAutoApply_Enable > 0)//�������ź����Զ�����
extern SemaphoreTable* osSignalLogin(_SemaphoreType SP);
#else
extern osErrorValue osSignalLogin(SemaphoreTable* ST,_SemaphoreType SP);
#endif
extern osErrorValue osSignalApply_Wait(SemaphoreTable* ST);
extern osErrorValue osSignalFree(SemaphoreTable* ST);

/*
                                                  FILE-END
*/
#endif
