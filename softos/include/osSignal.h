/*
                                                  FILE-START
*/
/*

 *@�ļ�����: .h

 *@�ļ�����: ��

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

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
#include "osConfig.h"
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

#define osSignalDebugError_Enable 1 //�ź�������DeBug  1:����Debug��� 0:�ر�Debug���

#define osSignalDebugError	osDebugError 


/*
                                                  �������ͱ���������
*/

/*
                                                  �ṹʽ�������ͱ���������
*/
//�ź�������{
typedef		uint32_t		_TaskInfo;
typedef struct
{
	_NextAddr  DownAddr;//��һ����ĵ�ַ
	_TaskInfo*	TaskInfo;//������
}SemaphoreToken;
//}

//�ź���{
typedef     uint8_t     _SemaphoreValue;
typedef     uint8_t      _SemaphoreType;
typedef struct
{
    _SemaphoreValue 	 SV;//�ź�ֵ
    _SemaphoreType   	 ST;//�źŵ�����
	_NextAddr		 	 SP;//�ź���������ͷ
}SemaphoreTable;
//}

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
