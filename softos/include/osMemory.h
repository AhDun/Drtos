/*
                                                  FILE-START
*/
/*

 *@�ļ�����: osMemory.h

 *@�ļ�����: ��

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@ע   ��: ��

*/
#ifndef _osMemory_H_
#define _osMemory_H_


/*
                                                  <�����ļ���>
*/
//
#include "print.h"
#include "osConfig.h"
/*
                                                  <�궨����>
*/


#define osMemory_Enable //�����ڴ� ��������������ֶ����ã������Զ�����ļ����Զ���������


//�ڴ���־{
#define Memory_Occupy 	0x01 //���ڴ��ռ����
#define Memory_Free   	0x02 //���ڴ�����ͷ�
//}

//�ڴ�����{
#define MemTank_Max 	16 * 1024 //�ڴ�ش�С����


#define MemoryProtect_Enable 0 // �ڴ汣������ 	1:�������� 0:�رձ���	
								//���ñ��������ڴ����ͷ��ڴ����õ�ʱ����������
								//�ڴ汣��Ҳ��һ����֤�ڴ��һ�����ᷢ������!!!,ֻ�ή���ڴ淢������ĸ���

#define osMemoryInitReset_Enable 1 //��ʼ���ڴ�ʱ��λ�ڴ� 1:���� 0:�ر�

#define osMemoryFreeReset_Enable 1 //�ͷ��ڴ�ʱ��λ�ڴ� 1:���� 0:�ر�

#define osMemoryErrorDebug osDebugError//DeBug�������

#define osMemoryDebug_Enable 1 //Debug���� 1:����Debug��� 0:�ر�Debug���

#define osMemorySequence_Enable 0 //�ڴ�˳�����   1������ 0������

//}


/*
                                                  <����������>
*/


typedef uint8_t	_MemoryUnit;//

//�ڴ���Ϣ��{
typedef _MemoryUnit 	_MemoryPoolAddr;
typedef uint32_t 		_MemoryPoolLength;
typedef _MemoryUnit 	_MemoryNextAddr;
typedef  struct
{ 
	_MemoryPoolAddr*			HeadAddr;//�ڴ�ͷ��ַ
	const _MemoryPoolAddr*			TailAddr;//�ڴ�β��ַ
	_MemoryNextAddr*			NextAddr;//�ڴ�

}_MemoryInfo;
//}
typedef	_MemoryInfo*	_MemoryInfoHandle;

//�ڴ��ṹ{
typedef uint8_t 	_MemoryFlag;
typedef uint16_t 	_MemoryLength;

typedef  struct
{ 
	_MemoryFlag 	MemoryFlag;//�ڴ��־
	_MemoryLength	MemoryLength;//�ڴ泤��

}MemoryStruct;
//}

/*
                                                  <����������>
*/
/*

 *@��������: osMemoryInit

 *@�����汾: 1.0.0

 *@��������: �ڴ��ʼ��

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
osErrorValue  osMemoryInit(void);
/*

 *@��������: osMemoryMalloc

 *@�����汾: 1.0.0

 *@��������: �ڴ�����

 *@�������: MemSize	���볤��

 *@�� �� ֵ: ���뷵�ص��ڴ��ַ

 *@ע    ��: ��

*/
void* osMemoryMalloc(uint32_t MemSize);
/*

 *@��������: osMemoryReset

 *@�����汾: 1.0.0

 *@��������: �ڴ�鸴λ

 *@�������: addr	�ڴ���ַ
			 data	��λ����

 *@�� �� ֵ: ��addr����������ͬ���ڴ���ַ

 *@ע    ��: ��

*/
void* osMemoryReset(void* addr,uint8_t data);
/*

 *@��������: osMemoryFree

 *@�����汾: 1.0.0

 *@��������: �ͷ��ڴ�

 *@�������: 0

 *@�� �� ֵ: 

 *@ע    ��: ��

*/
osErrorValue osMemoryFree(void* addr);
/*

 *@��������: osMemoryGetFreeValue

 *@�����汾: 1.0.0

 *@��������: ��ȡʣ���ڴ�ĳ���

 *@�������: ��

 *@�� �� ֵ: ʣ���ڴ�ĳ���

 *@ע    ��: ��

*/
uint32_t osMemoryGetFreeValue(void);
/*

 *@��������: osMemoryGetPassValue

 *@�����汾: 1.0.0

 *@��������: ��ȡ�������ڴ�ĳ���

 *@�������: ��

 *@�� �� ֵ: �������ڴ�ĳ���

 *@ע    ��: ��

*/
uint32_t osMemoryGetPassValue(void);
/*

 *@��������: osMemoryGetAllValue

 *@�����汾: 1.0.0

 *@��������: ��ȡ���ڴ泤��

 *@�������: ��

 *@�� �� ֵ: ���ڴ泤��

 *@ע    ��: ��

*/
uint32_t osMemoryGetAllValue(void);
/*

 *@��������: osMemorySum

 *@�����汾: 1.0.0

 *@��������: �������ڴ��У��

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
osErrorValue osMemorySum(void);



#endif
/*
                                                  FILE-END
*/


