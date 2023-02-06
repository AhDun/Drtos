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



#define osMemory_Enable //�����ڴ� ��������������ֶ����ã������Զ�����ļ����Զ���������


//�ڴ���־{
#define Memory_Occupy 					0x01 //���ڴ��ռ����
#define Memory_Free   					0x02 //���ڴ�����ͷ�
//}

//�ڴ�����{
#define MemTank_Max 					16 * 1024 //�ڴ�ش�С����


#define MemoryProtect_Enable 			0 // �ڴ汣������ 	1:�������� 0:�رձ���	
										//���ñ��������ڴ����ͷ��ڴ����õ�ʱ����������
										//�ڴ汣��Ҳ��һ����֤�ڴ��һ�����ᷢ������!!!,ֻ�ή���ڴ淢������ĸ���

#define osMemoryInitReset_Enable 		0 //��ʼ���ڴ�ʱ��λ�ڴ� 1:���� 0:�ر�

#define osMemorySequence_Enable 		0 //�ڴ�˳�����   1������ 0������


#if (osMemorySequence_Enable == 0)

#define osMemoryFreeReset_Enable 		0 //�ͷ��ڴ�ʱ��λ�ڴ� 1:���� 0:�ر�

#define osMemoryFreeTest_Enable 		1 //�ͷ��ڴ�ʱ����ڴ� 1:���� 0:�ر�

#define osMemoryPart_Enable				1 //��ָ�  1:���� 0:�ر�

#define osMemoryMerge_Enable			1 //��ϲ�  1:���� 0:�ر�

#endif

#define osMemoryDebug_Enable 			1 //Debug���� 1:����Debug��� 0:�ر�Debug���

#define osMemoryErrorDebug osDebugError//DeBug�������



//}





typedef uint8_t	_MemoryUnit;//

//�ڴ���Ϣ��{
typedef _MemoryUnit 	_MemoryPoolAddr;
typedef uint32_t 		_MemoryPoolLength;
typedef _MemoryUnit 	_MemoryNextAddr;
typedef  struct
{ 
	_MemoryPoolAddr*			HeadAddr;//�ڴ�ͷ��ַ
	const _MemoryPoolAddr*		TailAddr;//�ڴ�β��ַ
	_MemoryNextAddr*			NextAddr;//�ڴ�

}_MemoryInfo;
//}
typedef	_MemoryInfo*	_MemoryInfoHandle;
#if (osMemorySequence_Enable == 0)
//�ڴ��ṹ{
typedef uint8_t 	_MemoryFlag;
typedef uint16_t 	_MemoryLength;

typedef  struct
{ 
	_MemoryFlag 	MemoryFlag;//�ڴ��־
	_MemoryLength	MemoryLength;//�ڴ泤��

}MemoryStruct;
#endif
//}


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
osErrorValue  osMemoryInit(void);
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
 * @�������: addr	�ڴ���ַ
			 data	��λ����
 *
 * @�� �� ֵ: ��addr����������ͬ���ڴ���ַ
 *
 * @ע    ��: ��
 *
 */
void* osMemoryReset(void* addr,uint8_t data);
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
osErrorValue osMemoryFree(void* addr);
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
osErrorValue osMemorySum(void);



#endif



