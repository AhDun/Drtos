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
 * @�ļ�����: osMemory.h
 *
 * @�ļ�����: ��
 *
 * @ע   ��: ��
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
/*
 *
 * @��������: osMemorySwitch
 *
 * @��������: �ڴ���л�
 *
 * @�������: a �ڴ���Ϣ���
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
#define osMemoryInstall(a) MemoryInfoHandle = a
/*
 *
 * @��������: osMemoryInit
 *
 * @��������: �ڴ��ʼ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
_MemoryInfo*  osMemoryInit(_MemoryInfo* MemoryInfo);
/*
 *
 * @��������: osMemoryMalloc
 *
 * @��������: �ڴ�����
 *
 * @�������: MemSize	���볤��
 *
 * @�� �� ֵ: ���뷵�ص��ڴ��ַ
 *
 * @ע    ��: ��
 *
 */
void* osMemoryMalloc(uint32_t MemSize);
/*
 *
 * @��������: osMemoryReset
 *
 * @��������: �ڴ�鸴λ
 *
 * @�������: Addr	�ڴ���ַ
			 Data	��λ����
 *
 * @�� �� ֵ: ��Addr����������ͬ���ڴ���ַ
 *
 * @ע    ��: ��
 *
 */
void* osMemoryReset(void* Addr,uint8_t Data);
/*
 *
 * @��������: osMemoryFree
 *
 * @��������: �ͷ��ڴ�
 *
 * @�������: 0
 *
 * @�� �� ֵ: 
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osMemoryFree(void* Addr);
/*
 *
 * @��������: osMemoryGetFreeValue
 *
 * @��������: ��ȡʣ���ڴ�ĳ���
 *
 * @�������: ��
 *
 * @�� �� ֵ: ʣ���ڴ�ĳ���
 *
 * @ע    ��: ��
 *
 */
uint32_t osMemoryGetFreeValue(void);
/*
 *
 * @��������: osMemoryGetPassValue
 *
 * @��������: ��ȡ�������ڴ�ĳ���
 *
 * @�������: ��
 *
 * @�� �� ֵ: �������ڴ�ĳ���
 *
 * @ע    ��: ��
 *
 */
uint32_t osMemoryGetPassValue(void);
/*
 *
 * @��������: osMemoryGetAllValue
 *
 * @��������: ��ȡ���ڴ泤��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ���ڴ泤��
 *
 * @ע    ��: ��
 *
 */
uint32_t osMemoryGetAllValue(void);
/*
 *
 * @��������: osMemorySum
 *
 * @��������: �������ڴ��У��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osMemorySum(void);
/*
 *
 * @��������: osMemoryGetAllValue
 *
 * @��������: ��ȡ���ڴ泤��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ���ڴ泤��
 *
 * @ע    ��: ��
 *
 */
_MemoryInfoStatic* osMemoryInitStatic(_MemoryInfoStatic* MemoryInfoStatic);
/*
 *
 * @��������: osMemorySwitchoverStatic
 *
 * @��������: ��̬�ڴ��л�
 *
 * @�������: ��
 *
 * @�� �� ֵ: ���ڴ泤��
 *
 * @ע    ��: ��
 *
 */
#define osMemoryInstallStatic(a) MemoryInfoStaticHandle = a;
/*
 *
 * @��������: osMemoryMallocStatic
 *
 * @��������: ���뾲̬�ڴ�
 *
 * @�������: MemSize ҪҪ������ֽ���
 *
 * @�� �� ֵ: ���뵽���õ��ڴ��ַ
 *
 * @ע    ��: ��
 *
 */
void* osMemoryMallocStatic(int32_t MemSize);
/*
 *
 * @��������: osMemoryFreeStatic
 *
 * @��������: ��̬�ڴ��ͷ�
 *
 * @�������: ��
 *
 * @�� �� ֵ: ���ڴ泤��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osMemoryFreeStatic(void* Addr);
/*
 *
 * @��������: osMemoryStaticGetPassValue
 *
 * @��������: ��ȡ��̬�ڴ�������ֽ���
 *
 * @�������: ��
 *
 * @�� �� ֵ: ���ڴ泤��
 *
 * @ע    ��: ��
 *
 */
uint32_t osMemoryStaticGetPassValue(void);
/*
 *
 * @��������: osMemoryStaticGetAllValue
 *
 * @��������: ��ȡ��̬�ڴ������ֽ���
 *
 * @�������: ��
 *
 * @�� �� ֵ: ���ڴ泤��
 *
 * @ע    ��: ��
 *
 */
uint32_t osMemoryStaticGetAllValue(void);

#endif



