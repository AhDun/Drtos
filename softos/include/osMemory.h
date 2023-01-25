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


//�ڴ���־{
#define Memory_Occupy 	0x01 //���ڴ��ռ����
#define Memory_Free   	0x02 //���ڴ�����ͷ�
//}

//�ڴ�����{
#define MemTank_Max 	32 * 1024 //�ڴ�ش�С����


#define MemoryProtect_Enable 1 // �ڴ汣������ 	1:�������� 0:�رձ���	
								//���ñ��������ڴ����ͷ��ڴ����õ�ʱ����������
								//�ڴ汣��Ҳ��һ����֤�ڴ��һ�����ᷢ������!!!,ֻ�ή���ڴ淢������ĸ���

#define osMemoryErrorDebug print//DeBug�������

#define osMemoryDebug_Enable 1 //Debug���� 1:����Debug��� 0:�ر�Debug���


#define osMemorySequence_Enable 0 //�ڴ�˳�����   1������ 0������

#if (osMemorySequence_Enable == 0)
#define osMemoryMerge_Enable   1 //�ڴ��ϲ� 1������ 0������
#endif
//}



/*
                                                  <����������>
*/



typedef u8	_MemoryUnit;

extern _MemoryUnit*    MemoryNextAddr;//�ڴ��µ�ַ
extern _MemoryUnit 	MemoryPool[MemTank_Max];//�ڴ��

//�ڴ��ṹ{
typedef u8 	_MemoryFlag;
typedef u16 _MemoryLength;

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
void* osMemoryMalloc(u32 MemSize);
/*

 *@��������: osMemoryReset

 *@�����汾: 1.0.0

 *@��������: �ڴ�鸴λ

 *@�������: addr	�ڴ���ַ
			 data	��λ����

 *@�� �� ֵ: ��addr����������ͬ���ڴ���ַ

 *@ע    ��: ��

*/
void* osMemoryReset(void* addr,u8 data);
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
u32 osMemoryGetFreeValue(void);
/*

 *@��������: osMemoryGetPassValue

 *@�����汾: 1.0.0

 *@��������: ��ȡ�������ڴ�ĳ���

 *@�������: ��

 *@�� �� ֵ: �������ڴ�ĳ���

 *@ע    ��: ��

*/
u32 osMemoryGetPassValue(void);
/*

 *@��������: osMemoryGetAllValue

 *@�����汾: 1.0.0

 *@��������: ��ȡ���ڴ泤��

 *@�������: ��

 *@�� �� ֵ: ���ڴ泤��

 *@ע    ��: ��

*/
u32 osMemoryGetAllValue(void);
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


