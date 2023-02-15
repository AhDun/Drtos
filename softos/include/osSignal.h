/*
 * Copyright (c) 2022-2023 AhDun
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
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


#ifndef __osSignalH_
#define __osSignalH_


#include "main.h"
#include "osConfig.h"

#define osSignal_Config //���ö��� ��������������ֶ����ã������Զ�����ļ����Զ���������
//�ź�������{
#define Signal_Mutual       0x01u//�����ź���
#define Signal_Binary       0x02u//��ֵ�ź���
#define Signal_Count        0x03u//�����ź���
//}

#define 	osSignalMemoryMalloc	osMemoryMalloc
#define 	osSignalMemoryFree		osMemoryFree


//�ź�������{
typedef		uint32_t		_TaskInfo;
typedef struct
{
	_NextAddr  DownAddr;//��һ����ĵ�ַ
	_TaskInfo*	TaskInfo;//������
}_SignalToken;
//}

//�ź������{
typedef     uint8_t     _SignalValue;
typedef     uint8_t     _SignalType;
typedef struct
{
    _SignalValue 	 Value;//�ź�ֵ
    _SignalType   	 Type;//�źŵ�����
	_NextAddr		 NextAddr;//�ź���������ͷ
}_SignalHandle;
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


#endif
