/*
                                                  FILE-START
*/
/*

 *@�ļ�����: osMemory.h

 *@�ļ�����: ��

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע   ��: ��

*/
#ifndef _osMemory_H_
#define _osMemory_H_


/*
                                                  <�����ļ���>
*/
//#include "osError.h"
#include "print.h"
#include "osMain.h"
/*
                                                  <�궨����>
*/


#define osMemory_Enable //�����ڴ� ��������������ֶ����ã������Զ�����ļ����Զ���������


//�ڴ��״̬{
#define Memory_Occupy 	0x01 //���ڴ��ռ����
#define Memory_Free   	0x02 //���ڴ�����ͷ�
//}

//�ڴ�����{
#define MemTank_Max 	1 * 11 //32KB//�ڴ�ش�С

#define osMemoryDebug(a) print("\nosMemory: %s\n",a)//DeBug�������
#define osMemoryDebug_Enable 1 //Debug���� 1:����Debug��� 0:�ر�Debug���
#define osMemoryMarginSizeOut(a) print("\nosMemory: ʣ���ڴ��С %d �ֽ�\n",a)//DeBug�������
#define osMemoryMarginSizeOut_Enable 1//���� 1:����Debug��� 0:�ر�Debug���
#define osMemorySequence_Enable 0 //�ڴ�˳�����   1������ 0������
#define osMemTankSur_Enable 	1 //�ڴ�������¼   1������ 0������
#if (osMemorySequence_Enable == 0)
#define osMemoryMerge_Enable   1 //�ڴ��ϲ� 1������ 0������
#endif
//}



/*
                                                  <����������>
*/

typedef u8 	_MemoryFlag;
typedef u16 _MemoryLength;

typedef u8	_MemoryUnit;

typedef u32 	MemTankSur;

extern _MemoryUnit*    MemoryNextAddr;//�ڴ��µ�ַ
extern _MemoryUnit 	MemoryPool[MemTank_Max];//�ڴ��

typedef  struct
{ 
	_MemoryFlag 	MemoryFlag;
	_MemoryLength	MemoryLength;

}MemoryStruct;


/*
                                                  <����������>
*/
osErrorValue  osMemoryInit(void);
void* osMemoryMalloc(u32 MemSize);
#if (osMemorySequence_Enable == 0)
osErrorValue osMemoryFree(u8* addr);
void* osMemoryExtend(u8* addr,u32 MemSize);
u32 osMemoryMaxMallocValue(void);
#endif
u32 osMemoryAllSize(void);
u32 osMemoryMarginSize(void);



#endif
/*
                                                  FILE-END
*/


