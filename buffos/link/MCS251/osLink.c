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


__asm void osLinkJump(uint32_t* addr)
{
	PUSH {R0}
	POP	{PC}
}

__asm void osLinkISRDisable(void)
{

	CPSID   I	//禁用所有中断
	BX      LR	//退出函数，跳转到BX寄存器中所存的地址
}

__asm void osLinkISREnable(void)
{

	CPSIE   I	//禁用所有中断
	BX      LR  //退出函数，跳转到BX寄存器中所存的地址
}

/*
 *
 * @函数名称: osLinkTaskStackInit
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
__asm void osLinkTaskStackInit(uint32_t* tpp,uint32_t* tsa,uint32_t* eca,uint32_t* tsas)
						  //R0      ,R1      ,R2      ,R3
						  //C编译器函数各个传参对应的寄存器
{	
	PUSH{R4-R5}

	MOV   R4,   SP//将SP寄存器备份到R4寄存器中
	LDR   SP,   [R3]//以R3寄存器中的值做为指针，取值到SP寄存器中
		
	#if (osFPU_Config > 0)//启用了FPU
	MOV   R5,   #0x00//将0x00传给R5寄存器
	PUSH  {R5}//FPSCR
	SUB   SP,    SP,#0x40//SP寄存器中的值减去0x40

	#endif

	LDR    R5,   =xPSR_INIT_VALUE //xPSR寄存器初始化变量加载到R5寄存器中
	//|指令|寄存器|弹栈时所在的寄存器  
	PUSH   {R5}//xPSR(xPSR_INIT_VALUE)
	PUSH   {R1}//PC(任务开始地址)
	PUSH   {R2}//LR(任务结束回调地址)
	#if (osTaskInitRegister_Config > 0)
	MOV    R2,#0x00//将0x00值加载到R2寄存器中
	PUSH   {R2}//R12(0x00)
	PUSH   {R2}//R3(0x00)
	PUSH   {R2}//R2(0x00)
	PUSH   {R2}//R1(0x00)
	#else
	SUB		SP,SP,#0x18
	#endif
	PUSH   {R0}//R0(0x00)


	#if (osFPU_Config > 0)//启用了FPU
	SUB   SP,    SP,#0x40//SP寄存器中的值减去0x40

	#endif

	LDR		R5,	=LR_INIT_VALUE
	PUSH   {R5}//R11
	#if (osTaskInitRegister_Config > 0)
	MOV   	R5,   #0x00//将0x00传给R5寄存器
	PUSH   {R5}//R4
	PUSH   {R5}//R5
	PUSH   {R5}//R6
	PUSH   {R5}//R7
	PUSH   {R5}//R8
	PUSH   {R5}//R9
	PUSH   {R5}//R10
	PUSH   {R5}//R11
	#else
	SUB		SP,SP,#0x40
	#endif


	STR	  SP,	[R3]
	MOV   SP,   R4//将R4寄存器中的值加载到SP寄存器中，上半部分程序备份的SP值

	POP{R4-R5}
	BX	  LR
}
/*
 *
 * @函数名称: osLinkUseEnable
 *
 * @函数功能: 启用进程栈
 *
 * @输入参数: uint32_t *tsas(任务栈地址)
 *
 * @返 回 值: 无
 *
 * @注   释: 无
 *
 */
__asm void osLinkUseEnable(void)
{
#if (osTaskUseStack_Config > 0)
  MOV	R1,	  SP
  MSR   PSP,  R1//通过MSR命令将R0寄存器中的内容写到PSP（进程栈）寄存器中
  LDR	R0,	  =osTaskGetRunTaskHandle()
  LDR	R0,	  [R0]
  LDR	R0,	  [R0]
  MSR   MSP,  R0//通过MSR命令将R0寄存器中的内容写到PSP（进程栈）寄存器中
 /*使能进程栈{*/
  MRS	R0,		CONTROL//通过MRS命令读取控制寄存器到R0寄存器
  ORR	R0,		R0,#0x02//R0寄存器与0x02进行或运算，使的bit1位 置1
  MSR	CONTROL,R0//再通过MSR命令将R0寄存器中的内容写回控制寄存器中
  /*}*/
#endif
  BX    LR//退出函数，跳转到BX寄存器中所存的地址
  NOP
}


/*
 *
 * @函数名称: HardFault_Handler
 *
 * @函数功能: 任务错误入口
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
 * @函数功能: 系统时钟入口
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
#if (osTaskUseStack_Config > 0)
__asm void PendSV_Handler(void)
{
	PRESERVE8

	extern osTaskGetRunTaskHandle()
	extern osTaskNext

	CPSID   I			//禁用所有中断
 
	MRS	  R1,	PSP		//通过MRS命令将PSP（进程栈）寄存器中的内容读到R1寄存器中
#if (osFPU_Config > 0) //启用了FPU
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
#if (osFPU_Config > 0) //启用了FPU
	TST		LR, #0x10
    IT		EQ
    VLDMIAEQ R1!,{S16-S31}
#endif

	MSR   PSP,  R1		//通过MSR命令将R0寄存器中的内容写到PSP（进程栈）寄存器中

	CPSIE   I			//启用所有中断
    BX	  LR
	NOP
#if (osFPU_Config > 0) //启用了FPU
	NOP
#endif
}
#else
__asm void PendSV_Handler(void)
{
	PRESERVE8

	extern osTaskGetRunTaskHandle()
	extern osTaskNext

	CPSID   I			//禁用所有中断
 
#if (osFPU_Config > 0) //启用了FPU
    TST		LR, #0x10
    IT		EQ
    VSTMDBEQ SP!,{S16-S31}
#endif

    STMDB SP!,	{R4-R11,LR}	//压栈R4-R11

	LDR   R0,	=osTaskGetRunTaskHandle()
	LDR	  R0,	[R0]
    STR   SP,   [R0]	
	

	CPSIE   I

	BL.W	osTaskNext

	CPSID   I			//禁用所有中断

	LDR   R0,	=osTaskGetRunTaskHandle()
	LDR	  R0,	[R0]
	LDR   SP,   [R0]	

	LDMIA SP! ,{R4-R11,LR}	//弹栈R4-R11
#if (osFPU_Config > 0) //启用了FPU
	TST		LR, #0x10
    IT		EQ
    VLDMIAEQ SP!,{S16-S31}
#endif

	CPSIE   I			//启用所有中断
    BX	  LR
	NOP
	NOP
#if (osFPU_Config > 0) //启用了FPU
	NOP
#endif
}
#endif

/*
 *
 * @函数名称: print
 *
 * @函数功能: print函数入口
 *
 * @输入参数: c 控制字符串
 *			  ... 其他传参
 *
 * @返 回 值: 无
 *
 * @注   释: 无
 *
 */


__asm void print(const char* c,...)
{
	PRESERVE8
	extern  xprint
	
	PUSH	{R3}//将传参压入栈中
	PUSH	{R2}//将传参压入栈中
	PUSH	{R1}//将传参压入栈中
    MOV		R1,R0//将控制字符串指针传入R1,相当传入xprint函数的con参数 (控制字符串指针)
	MOV		R2,SP//将栈指针传入R2,相当传入xprint函数的sp参数 (栈指针)
    MOV		R0,#0x00//将0x00传入R0,相当传入xprint函数的s参数 (回写地址)
	PUSH 	{LR}//压入返回地址

	BL.W	xprint//调用xprint函数
					
	POP  	{LR}//弹出返回地址
	ADD		SP,#0x0C//释放栈
	BX		LR//根据LR寄存器中的地址,返回上一个函数
}
/*
 *
 * @函数名称: sprint
 *
 * @函数功能: sprint函数入口
 *
 * @输入参数: s 输出地址
 *  		  c 控制字符串
 *			  ... 其他传参
 *
 * @返 回 值: 无
 *
 * @注   释: 无
 *
 */

__asm void sprint(char* s,const char* c,...)
{
	PRESERVE8
	extern  xprint
	
	PUSH	{R3}//将传参压入栈中
	PUSH	{R2}//将传参压入栈中
	PUSH	{R0}//将输出地址压入栈中
	ADD		R2,SP,#0x04//将栈指针传入R2,相当传入xprint函数的sp参数 (栈指针)
	MOV		R0,SP//将栈指针传入R0,相当传入xprint函数的s参数 (回写地址)
	PUSH 	{LR}//压入返回地址

	BL.W	xprint//调用xprint函数
					
	POP  	{LR}//弹出返回地址
	ADD		SP,#0x0C//释放栈
	BX		LR//根据LR寄存器中的地址,返回上一个函数
}



