/**
 * Copyright 2022-2023 AhDun. All rights reserved.
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
/**
 *
 * @file .h
 *
 * @brief ��
 *
 * @note none
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

/**
 *
 * @name osSignalLogin
 *
 * @brief �ź���ע��
 *
 * @param _SignalHandle* ST(�ź����ṹ��)
 *
 * @retval none
 *
 * @note none
 *
 */
_SignalHandle* osSignalLogin(_SignalType SP);
#else
OsErrorValue osSignalLogin(_SignalHandle* ST,_SignalType SP);
#endif
/**
 *
 * @name osSignalUseWait
 *
 * @brief �ź����ȴ�ʽռ��
 *
 * @param ST	�ź������
 *
 * @retval 0:ռ�óɹ�  -1:ռ��ʧ��
 *
 * @note none
 *
 */
OsErrorValue osSignalUseWait(_SignalHandle* ST);
/**
 *
 * @name osSignalUse
 *
 * @brief �ź����ǵȴ�ʽռ��
 *
 * @param ST	�ź������
 *
 * @retval 0:ռ�óɹ�  -1:ռ��ʧ��
 *
 * @note none
 *
 */
OsErrorValue osSignalUse(_SignalHandle* ST);
/**
 *
 * @name osSignalFree
 *
 * @brief �ź����ͷ�
 *
 * @param  ST	�ź������
 *
 * @retval 0:�ͷųɹ�  -1:�ͷ�ʧ��
 *
 * @note none
 *
 */
OsErrorValue osSignalFree(_SignalHandle* ST);


OsErrorValue osSignalSetGroup(_SignalHandle* ST,uint8_t Bits,uint8_t SetBit,uint8_t SetValue);



#endif

#endif
