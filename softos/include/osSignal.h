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
typedef     u32     _SemaphoreValue;
typedef     u8      _SemaphoreType;
typedef		u32		_SignalPost;
typedef		u32		_TaskInfo;
/*
                                                  �ṹʽ�������ͱ���������
*/
typedef struct
{
	_NextAddr*  DownAddr;//��һ����ĵ�ַ
	_TaskInfo*	TaskInfo;
}SemaphoreToken;//�ź�������

typedef struct
{
    _SemaphoreValue 	 SV;//�ź�ֵ
    _SemaphoreType   	 ST;//�źŵ�����
	SemaphoreToken*		 SP;//�ź���������ͷ
}SemaphoreTable;//�ź���

/*
                                                  <����������>
*/
/*
                                                  <����������>
*/
#if (osSignalAutoApply_Enable > 0)//�������ź����Զ�����

/*

 *@��������: osSignalLogin

 *@�����汾: 1.0.0

 *@��������: �ź���ע��

 *@�������: SemaphoreTable* ST(�ź����ṹ��)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
SemaphoreTable* osSignalLogin(_SemaphoreType SP);
#else
osErrorValue osSignalLogin(SemaphoreTable* ST,_SemaphoreType SP);
#endif

osErrorValue osSignalUseWait(SemaphoreTable* ST);
osErrorValue osSignalFree(SemaphoreTable* ST);

/*
                                                  FILE-END
*/
#endif
