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


/*
                                                  <����������>
*/


/*
                                                  <����������>
*/



/*
                                                  <����������>
*/


void INTX_DISABLE(void);

void INTX_ENABLE(void);

__asm  void osTASK_Stack_Init(u32* tpp,u32* tsa,u32* eca,u32* tsas);

__asm void osTASK_START(u32* tsas);

__asm void CPU_PendSV(void);

void CPU_PendSV_STATE(void);

__asm void CPU_SVC(void);





#endif


/*
                                                  FILE-END
*/
