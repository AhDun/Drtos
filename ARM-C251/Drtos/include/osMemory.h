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
 * @file osMemory.h
 *
 * @brief ��
 *
 * @note none
 *
 */
#ifndef _osMemory_H_
#define _osMemory_H_



//
#include "print.h"
#include "osConfig.h"




//�ڴ���־{
#define Memory_Occupy 					0x01 //���ڴ��ռ����
#define Memory_Free   					0x02 //���ڴ�����ͷ�
//}

#define MemoryStructLength				sizeof(MemoryStruct)

typedef uint8_t	_MemoryUnit;//

//�ڴ���Ϣ��{
typedef _MemoryUnit 	_MemoryPoolAddr;
typedef uint32_t 		_MemoryPoolLength;
typedef _MemoryUnit 	_MemoryNextAddr;
typedef  struct
{ 
	_MemoryPoolAddr*			HeadAddr;//�ڴ�ͷ��ַ
	_MemoryNextAddr*			NextAddr;//�ڴ�ɷ���ĵ�ַ
	const _MemoryPoolAddr*		TailAddr;//�ڴ�β��ַ

}_MemoryInfo;
typedef	_MemoryInfo*	_MemoryInfoHandle;
extern _MemoryInfoHandle	MemoryInfoHandle;
//}
//�ṹ�ڴ���Ϣ��{
#if (osMemoryStatic_Config > 0)
typedef  struct
{ 
	uint32_t*			HeadAddr;//�ڴ�ͷ��ַ
	const uint32_t*		TailAddr;//�ڴ�β��ַ
	const uint8_t		Byte;
	const uint8_t		Size;

}_MemoryInfoStatic;
typedef	_MemoryInfoStatic*	_MemoryInfoStaticHandle;
extern _MemoryInfoStaticHandle	MemoryInfoStaticHandle;
#endif
//}


#if (osMemorySequence_Config == 0)
//�ڴ��ṹ{
typedef uint8_t 	_MemoryFlag;
typedef uint16_t 	_MemoryLength;

typedef  struct
{ 
	_MemoryLength	MemoryLength;//�ڴ泤��
	_MemoryFlag 	MemoryFlag;//�ڴ��־

}MemoryStruct;
#endif
//}
/**
 *
 * @name osMemorySwitch
 *
 * @brief �ڴ���л�
 *
 * @param a �ڴ���Ϣ���
 *
 * @retval none
 *
 * @note none
 *
 */
#define osMemoryInstall(a) MemoryInfoHandle = a
/**
 *
 * @name osMemoryInit
 *
 * @brief �ڴ��ʼ��
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
_MemoryInfo*  osMemoryInit(_MemoryInfo* MemoryInfo);
/**
 *
 * @name osMemoryMalloc
 *
 * @brief �ڴ�����
 *
 * @param MemSize	���볤��
 *
 * @retval ���뷵�ص��ڴ��ַ
 *
 * @note none
 *
 */
void* osMemoryMalloc(uint32_t MemSize);
/**
 *
 * @name osMemoryReset
 *
 * @brief �ڴ�鸴λ
 *
 * @param Addr	�ڴ���ַ
			 Data	��λ����
 *
 * @retval ��Addr����������ͬ���ڴ���ַ
 *
 * @note none
 *
 */
void* osMemoryReset(void* Addr,uint8_t Data);
/**
 *
 * @name osMemoryFree
 *
 * @brief �ͷ��ڴ�
 *
 * @param 0
 *
 * @retval 
 *
 * @note none
 *
 */
OsErrorValue osMemoryFree(void* Addr);
/**
 *
 * @name osMemoryGetFreeValue
 *
 * @brief ��ȡʣ���ڴ�ĳ���
 *
 * @param none
 *
 * @retval ʣ���ڴ�ĳ���
 *
 * @note none
 *
 */
uint32_t osMemoryGetFreeValue(void);
/**
 *
 * @name osMemoryGetPassValue
 *
 * @brief ��ȡ�������ڴ�ĳ���
 *
 * @param none
 *
 * @retval �������ڴ�ĳ���
 *
 * @note none
 *
 */
uint32_t osMemoryGetPassValue(void);
/**
 *
 * @name osMemoryGetAllValue
 *
 * @brief ��ȡ���ڴ泤��
 *
 * @param none
 *
 * @retval ���ڴ泤��
 *
 * @note none
 *
 */
uint32_t osMemoryGetAllValue(void);
/**
 *
 * @name osMemorySum
 *
 * @brief �������ڴ��У��
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
OsErrorValue osMemorySum(void);
/**
 *
 * @name osMemoryGetAllValue
 *
 * @brief ��ȡ���ڴ泤��
 *
 * @param none
 *
 * @retval ���ڴ泤��
 *
 * @note none
 *
 */
_MemoryInfoStatic* osMemoryInitStatic(_MemoryInfoStatic* MemoryInfoStatic);
/**
 *
 * @name osMemorySwitchoverStatic
 *
 * @brief ��̬�ڴ��л�
 *
 * @param none
 *
 * @retval ���ڴ泤��
 *
 * @note none
 *
 */
#define osMemoryInstallStatic(a) MemoryInfoStaticHandle = a;
/**
 *
 * @name osMemoryMallocStatic
 *
 * @brief ���뾲̬�ڴ�
 *
 * @param MemSize ҪҪ������ֽ���
 *
 * @retval ���뵽���õ��ڴ��ַ
 *
 * @note none
 *
 */
void* osMemoryMallocStatic(int32_t MemSize);
/**
 *
 * @name osMemoryFreeStatic
 *
 * @brief ��̬�ڴ��ͷ�
 *
 * @param none
 *
 * @retval ���ڴ泤��
 *
 * @note none
 *
 */
OsErrorValue osMemoryFreeStatic(void* Addr);
/**
 *
 * @name osMemoryStaticGetPassValue
 *
 * @brief ��ȡ��̬�ڴ�������ֽ���
 *
 * @param none
 *
 * @retval ���ڴ泤��
 *
 * @note none
 *
 */
uint32_t osMemoryStaticGetPassValue(void);
/**
 *
 * @name osMemoryStaticGetAllValue
 *
 * @brief ��ȡ��̬�ڴ������ֽ���
 *
 * @param none
 *
 * @retval ���ڴ泤��
 *
 * @note none
 *
 */
uint32_t osMemoryStaticGetAllValue(void);

#endif



