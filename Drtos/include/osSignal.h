/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
 */
/*
 *
 * @�ļ�����: .h
 *
 * @�ļ�����: ��
 *
 * @ע    ��: ��
 *
 */


#ifndef __osSignal_H_
#define __osSignal_H_



#include "main.h"
#include "osConfig.h"


#if (osSignal_Config > 0)

//�ź�������{

//}


//�ź�������{
typedef		uint32_t		_TaskInfo;
typedef struct
{
	_NextAddr  DownAddr;//��һ����ĵ�ַ
	_TaskInfo*	TaskInfo;//������
}_SignalToken;
//}

//�ź������{
typedef     uint32_t    _SignalValue;
typedef     uint8_t     _SignalType;
typedef struct
{
    _SignalType   	 Type;//�źŵ�����
	_NextAddr		 NextAddr;//�ź���������ͷ
}_SignalHandle;
typedef struct
{
    _SignalType   	 Type;//�źŵ�����
	_NextAddr		 NextAddr;//�ź���������ͷ
	_SignalValue 	 Value;//�ź�ֵ
}_SignalHandleValue;

//}




#if (osSignalAutoApply_Config > 0)//�������ź����Զ�����

/*
 *
 * @��������: osSignalLogin
 *
 * @��������: �ź���ע��
 *
 * @�������: _SignalHandle* ST(�ź����ṹ��)
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
_SignalHandle* osSignalLogin(_SignalType SP);
#else
OsErrorValue osSignalLogin(_SignalHandle* ST,_SignalType SP);
#endif
/*
 *
 * @��������: osSignalUseWait
 *
 * @��������: �ź����ȴ�ʽռ��
 *
 * @�������: ST	�ź������
 *
 * @�� �� ֵ: 0:ռ�óɹ�  -1:ռ��ʧ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osSignalUseWait(_SignalHandle* ST);
/*
 *
 * @��������: osSignalUse
 *
 * @��������: �ź����ǵȴ�ʽռ��
 *
 * @�������: ST	�ź������
 *
 * @�� �� ֵ: 0:ռ�óɹ�  -1:ռ��ʧ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osSignalUse(_SignalHandle* ST);
/*
 *
 * @��������: osSignalFree
 *
 * @��������: �ź����ͷ�
 *
 * @�������:  ST	�ź������
 *
 * @�� �� ֵ: 0:�ͷųɹ�  -1:�ͷ�ʧ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osSignalFree(_SignalHandle* ST);


OsErrorValue osSignalSetGroup(_SignalHandle* ST,uint8_t Bits,uint8_t SetBit,uint8_t SetValue);



#endif

#endif
