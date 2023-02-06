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
 * @�ļ�����: AhDun (mail: ahdunxx@163.com)
 *
 * @ע    ��: ��
 *
 */


#ifndef __osSignalH_
#define __osSignalH_


#include "main.h"
#include "osConfig.h"

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


//�ź�������{
typedef		uint32_t		_TaskInfo;
typedef struct
{
	_NextAddr  DownAddr;//��һ����ĵ�ַ
	_TaskInfo*	TaskInfo;//������
}_SignalToken;
//}

//�ź���{
typedef     uint8_t     _SignalValue;
typedef     uint8_t     _SignalType;
typedef struct
{
    _SignalValue 	 Value;//�ź�ֵ
    _SignalType   	 Type;//�źŵ�����
	_NextAddr		 NextAddr;//�ź���������ͷ
}_Signal;
//}




#if (osSignalAutoApply_Enable > 0)//�������ź����Զ�����

/*
 *
 * @��������: osSignalLogin
 *
 * @��������: �ź���ע��
 *
 * @�������: _Signal* ST(�ź����ṹ��)
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
_Signal* osSignalLogin(_SignalType SP);
#else
osErrorValue osSignalLogin(_Signal* ST,_SignalType SP);
#endif

osErrorValue osSignalUseWait(_Signal* ST);
osErrorValue osSignalFree(_Signal* ST);


#endif
