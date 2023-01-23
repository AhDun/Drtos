/*
                                                  FILE-START
*/

#ifndef __osCPU_H_
#define __osCPU_H_

/*

 *@�ļ�����: osCPU.h

 *@�ļ�����: 

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע    ��: 

*/

/*
                                                  <�����ļ���>
*/

#include "main.h"

/*
                                                  <�궨����>
*/

#define xPSR_INIT_VALUE 0x01000000//xPSR�Ĵ�����ʼ������
#if (osFPU_Enable > 0) //������FPU
#define LR_INIT_VALUE 0xFFFFFFED//xPSR�Ĵ�����ʼ������
#else
#define LR_INIT_VALUE 0xFFFFFFFD//xPSR�Ĵ�����ʼ������
#endif

#define CPU_xPSR 	0x04u
#define CPU_PC 		0x04u
#define CPU_LR 		0x04u
#define CPU_R12 	0x04u
#define CPU_R3 		0x04u
#define CPU_R2 		0x04u
#define CPU_R1		0x04u
#define CPU_R0 		0x04u


/*
                                                  <����������>
*/
typedef  u8  _CPU_Occupy;//CPU��ռ����

typedef struct
{
    _CPU_Occupy CO;//CPU��ռ����

}CPUState;//CPU״��

/*
                                                  <����������>
*/

extern CPUState CPUS;//CPU״��

/*
                                                  <����������>
*/


extern   void INTX_DISABLE(void);

extern   void INTX_ENABLE(void);

extern __asm  void osTASK_Stack_Init(u32* tpp,u32* tsa,u32* eca,u32* tsas);

extern __asm void osTASK_START(u32* tsas);

extern  __asm void CPU_PendSV(void);

extern  void CPU_PendSV_STATE(void);

extern __asm void CPU_SVC(void);

extern __asm  void FPU_STACK_ENABLE(void);

extern __asm int Read_PSP(void);

extern __asm int Read_PC(void);


#endif


/*
                                                  FILE-END
*/
