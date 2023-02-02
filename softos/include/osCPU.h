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


/*
                                                  <数据声明区>
*/


/*
                                                  <数据声明区>
*/



/*
                                                  <函数声明区>
*/

__asm void Jump(uint32_t* addr);


void INTX_DISABLE(void);

void INTX_ENABLE(void);

__asm  void osTASK_Stack_Init(uint32_t* tpp,uint32_t* tsa,uint32_t* eca,uint32_t* tsas);

__asm void osTASK_START(uint32_t* tsas);

__asm void CPU_PendSV(void);

void CPU_PendSV_STATE(void);

__asm void CPU_SVC(void);





#endif


/*
                                                  FILE-END
*/
