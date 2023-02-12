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
 * @文件名称: osLink.c
 *
 * @文件内容: 链接(衔接)文件
 *
 * @注    释: 
 *
 */


#include "osConfig.h"
#include "osLink.h"

/*
                                                  变量初始化区
*/



//const uint32_t NVIC_PendSV = 0xE000ED04;//PendSV
//const uint32_t NVIC_PendSV_SET = 0x10000000;


__asm void Jump(uint32_t* addr)
{
	PUSH {R0}
	POP	{PC}
}

__asm void ISR_Disable(void)
{

	CPSID   I	//禁用所有中断
	BX      LR	//退出函数，跳转到BX寄存器中所存的地址
}

__asm void ISR_Enable(void)
{

	CPSIE   I	//禁用所有中断
	BX      LR  //退出函数，跳转到BX寄存器中所存的地址
}

/*
 *
 * @函数名称: osTASK_Stack_Init
 *
 * @函数功能: 任务栈初始化
 *
 * @输入参数: uint32_t tta(任务传参) ,uint32_t *tsa(任务开始地址),uint32_t *eca(任务结束回调地址),uint32_t *tsas(任务栈地址)
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
__asm void osTASK_Stack_Init(uint32_t* tpp,uint32_t* tsa,uint32_t* eca,uint32_t* tsas)
						  //R0      ,R1      ,R2      ,R3
						  //C编译器函数各个传参对应的寄存器
{	
	PUSH{R4-R5}

	MOV   R4,   SP		//将SP寄存器备份到R4寄存器中
	LDR   SP,   [R3]		//以R3寄存器中的值做为指针，取值到SP寄存器中
		
	#if (osFPU_Enable > 0) //启用了FPU
	MOV   R5,   #0x00		//将0x00传给R5寄存器
	PUSH  {R5}			//FPSCR
	SUB   SP,    SP,#0x40	//SP寄存器中的值减去0x40

	#endif

	LDR    R5,   =xPSR_INIT_VALUE //xPSR寄存器初始化变量加载到R5寄存器中
	//|指令|寄存器|弹栈时所在的寄存器  
	PUSH   {R5}  					//xPSR(xPSR_INIT_VALUE)
	PUSH   {R1}  					//PC(任务开始地址)
	PUSH   {R2}  					//LR(任务结束回调地址)
	MOV    R2,#0x00				//将0x00值加载到R2寄存器中
	PUSH   {R2}  	//R12(0x00)
	PUSH   {R2}  	//R3(0x00)
	PUSH   {R2}	//R2(0x00)
	PUSH   {R2}	//R1(0x00)
	PUSH   {R0}	//R0(0x00)


	#if (osFPU_Enable > 0) //启用了FPU
	SUB   SP,    SP,#0x40	//SP寄存器中的值减去0x40

	#endif

	LDR		R5,	=LR_INIT_VALUE
	PUSH   {R5}//R11
	MOV   R5,   #0x00		//将0x00传给R5寄存器
	PUSH   {R5}//R4
	PUSH   {R5}//R5
	PUSH   {R5}//R6
	PUSH   {R5}//R7
	PUSH   {R5}//R8
	PUSH   {R5}//R9
	PUSH   {R5}//R10
	PUSH   {R5}//R11


	STR	  SP,	[R3]
	MOV   SP,   R4				//将R4寄存器中的值加载到SP寄存器中，上半部分程序备份的SP值
	POP{R4-R5}

	BX	  LR
}
/*
 *
 * @函数名称: osTASK_FIRST_START
 *
 * @函数功能: 启动第一个任务
 *
 * @输入参数: uint32_t *tsas(任务栈地址)
 *
 * @返 回 值: 无
 *
 * @注   释: 无
 *
 */
__asm void osTASK_START(uint32_t* tsas)
								//R0
								//C编译器函数各个传参对应的寄存器
{
  MOV	R1,	  SP
  MSR   PSP,  R1		//通过MSR命令将R0寄存器中的内容写到PSP（进程栈）寄存器中
  LDR   R0,     [R0]	//以R3寄存器中的值做为指针，取值到SP寄存器中
  MSR   MSP,  R0		//通过MSR命令将R0寄存器中的内容写到PSP（进程栈）寄存器中
 /*使能进程栈{*/
  MRS	R0,		CONTROL 	//通过MRS命令读取控制寄存器到R0寄存器
  ORR	R0,		R0,#0x02	//R0寄存器与0x02进行或运算，使的bit1位 置1
  MSR	CONTROL,R0			//再通过MSR命令将R0寄存器中的内容写回控制寄存器中
  /*}*/

  BX    LR	//退出函数，跳转到BX寄存器中所存的地址
}


/*
 *
 * @函数名称: HardFault_Handler
 *
 * @函数功能: 启动第一个任务
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注   释: 无
 *
 */
__asm void HardFault_Handler(void)
{
	extern osTaskErrorHardFault
	
	PUSH	{LR}

	MRS	  	R1,		PSP		//通过MRS命令将PSP（进程栈）寄存器中的内容读到R1寄存器中
	LDR		R0,		[R1,#0x14]
	MRS	  	R1,		PSP		//通过MRS命令将PSP（进程栈）寄存器中的内容读到R1寄存器中
	
	BL.W	osTaskErrorHardFault

	POP		{PC}
}
/*
 *
 * @函数名称: SysTick_Handler
 *
 * @函数功能: 启动第一个任务
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注   释: 无
 *
 */
__asm void SysTick_Handler(void)
{
	extern osClockTimePulse
	
	PUSH	{LR}

	BL.W	osClockTimePulse

	POP		{PC}

	NOP
}
/*
 *
 * @函数名称: PendSV_Handler
 *
 * @函数功能: 启动第一个任务
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注   释: 无
 *
 */
__asm void PendSV_Handler(void)
{
	PRESERVE8

	extern osTaskGetRunTaskHandle()
	extern osTaskNext

	CPSID   I			//禁用所有中断
 
	MRS	  R1,	PSP		//通过MRS命令将PSP（进程栈）寄存器中的内容读到R1寄存器中
#if (osFPU_Enable > 0) //启用了FPU
    TST		LR, #0x10
    IT		EQ
    VSTMDBEQ R1!,{S16-S31}
#endif

    STMDB R1!,	{R4-R11,LR}	//压栈R4-R11

	LDR   R0,	=osTaskGetRunTaskHandle()
	LDR	  R0,	[R0]
    STR   R1,   [R0]	
	

	CPSIE   I

	BL.W	osTaskNext

	CPSID   I			//禁用所有中断

	LDR   R0,	=osTaskGetRunTaskHandle()
	LDR	  R0,	[R0]
	LDR   R1,   [R0]	

	LDMIA R1! ,{R4-R11,LR}	//弹栈R4-R11
#if (osFPU_Enable > 0) //启用了FPU
	TST		LR, #0x10
    IT		EQ
    VLDMIAEQ R1!,{S16-S31}
#endif

	MSR   PSP,  R1		//通过MSR命令将R0寄存器中的内容写到PSP（进程栈）寄存器中

	CPSIE   I			//启用所有中断
    BX	  LR
	NOP
	NOP
#if (osFPU_Enable > 0) //启用了FPU
	NOP
#endif
}


__asm void print(const char* s,...)
{
	PRESERVE8
	extern  xprint
	
	PUSH	{R3}
	PUSH	{R2}
	PUSH	{R1}
	PUSH	{R0}
	MOV		R1,#0x00
	MOV		R0,SP
	PUSH 	{LR}

	BL.W	xprint
					
	POP  	{LR}
	POP		{R0}
	POP		{R1}
	POP		{R2}
	POP		{R3}
	BX		LR
}
__asm void sprint(char* s,const char* c,...)
{
	PRESERVE8
	extern  xprint

	PUSH	{R3}
	PUSH	{R2}
	PUSH	{R1}
	PUSH	{R0}
	MOV		R1,#0x01
	MOV		R0,SP
	PUSH 	{LR}

	BL.W	xprint		
					
	POP  	{LR}
	POP		{R0}
	POP		{R1}
	POP		{R2}
	POP		{R3}
	BX		LR
}



