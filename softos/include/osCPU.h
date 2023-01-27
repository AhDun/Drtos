/*
                                                  FILE-START
*/

#ifndef __osCPU_H_
#define __osCPU_H_

/*

 *@文件名称: osCPU.h

 *@文件内容: 

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注    释: 

*/

/*
                                                  <引用文件区>
*/

#include "main.h"

/*
                                                  <宏定义区>
*/

#define xPSR_INIT_VALUE 0x01000000//xPSR寄存器初始化变量
#if (osFPU_Enable > 0) //启用了FPU
#define LR_INIT_VALUE 0xFFFFFFED//xPSR寄存器初始化变量
#else
#define LR_INIT_VALUE 0xFFFFFFFD//xPSR寄存器初始化变量
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
                                                  <数据声明区>
*/
typedef  u8  _CPU_Occupy;//CPU总占用量

typedef struct
{
    _CPU_Occupy CO;//CPU总占用量

}CPUState;//CPU状况

/*
                                                  <数据声明区>
*/

extern CPUState CPUS;//CPU状况

/*
                                                  <函数声明区>
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
