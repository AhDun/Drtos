/*
                                                  FILE-START
*/
/*

 *@文件名称: osCPU.c

 *@文件内容: 系统"CPU内核操作"文件

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注    释: 

*/

/*
                                                  <引用文件区>
*/
#include "osMain.h"
#include "osCPU.h"

CPUState CPUS;//CPU状况

/*
                                                  变量初始化区
*/

/*
                                                  <函数区>
*/

const u32 NVIC_PendSV = 0xE000ED04;//PendSV
const u32 NVIC_PendSV_SET = 0x10000000;

/*

 *@函数名称: osTASK_START

 *@函数版本: 1.0.0

 *@函数功能: 任务启动

 *@输入参数: u32 tta(任务传参) ,u32 *tsa(任务开始地址),u32 *eca(任务结束回调地址),u32 *tsas(任务栈地址)

 *@返 回 值: 无

 *@注    释: 无

*/

__asm void osTASK_Stack_Init(u32* tpp,u32* tsa,u32* eca,u32* tsas)
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

 *@函数名称: osTASK_FIRST_START

 *@函数版本: 1.0.0

 *@函数功能: 启动第一个任务

 *@输入参数: u32 *tsas(任务栈地址)

 *@返 回 值: 无

 *@注   释: 无

*/
__asm void osTASK_FIRST_START(u32* tsas)
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

 *@函数名称: FPU_STACK_ENABLE

 *@函数版本: 1.0.0

 *@函数功能: 使能FPU压栈

 *@输入参数: 无

 *@返 回 值: 无

 *@注   释: 无

*/
__asm  void FPU_STACK_ENABLE(void)
{
    MRS		R0,		CONTROL	   	//通过MRS命令读取控制寄存器到R0寄存器
	ORR		R0,		R0,#0x04   	//R0寄存器与0x04进行或运算，使的bit2位 置1
	MSR		CONTROL,R0			//再通过MSR命令将R0寄存器中的内容写回控制寄存器中
	BX		LR					//退出函数，跳转到BX寄存器中所存的地址
}

__asm int Read_PSP(void)
{
	MRS	  	R0,		PSP		//通过MRS命令将PSP（进程栈）寄存器中的内容读到R1寄存器中
	BX		LR
}
__asm int Read_PC(void)
{
	MRS	  	R1,		PSP		//通过MRS命令将PSP（进程栈）寄存器中的内容读到R1寄存器中
	LDR		R0,		[R1,#0x14]
	BX		LR
}

__asm void PendSV_Handler(void)
{
	PRESERVE8

	extern RunTask_TIT
	extern osTaskNext

	CPSID   I			//禁用所有中断
 
	MRS	  R1,	PSP		//通过MRS命令将PSP（进程栈）寄存器中的内容读到R1寄存器中
#if (osFPU_Enable > 0) //启用了FPU
    TST		LR, #0x10
    IT		EQ
    VSTMDBEQ R1!,{S16-S31}
#endif

    STMDB R1!,	{R4-R11,LR}	//压栈R4-R11

	LDR   R0,	=RunTask_TIT
	LDR	  R0,	[R0]
    STR   R1,   [R0]	
	

	CPSIE   I
	LDR 	R0,		=osTaskNext
	BLX 	R0
	CPSID   I			//禁用所有中断

	LDR   R0,	=RunTask_TIT
	LDR	  R0,	[R0]
	LDR   R1,   [R0]	//以R0寄存器中的值做指针取值到R0寄存器中

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
}

//__asm void CPU_PendSV(void)
//{
//	PRESERVE8

//	extern NVIC_PendSV
//	extern NVIC_PendSV_SET

//	PUSH    {R0,R1,LR}
//	CPSID   I						//禁用所有中断
//    LDR     R0,     =NVIC_PendSV 	//将PendSV寄存器的地址加载到R0寄存器中
//    LDR     R1,     =NVIC_PendSV_SET//将PendSV寄存器内核悬起使能值加载到R1寄存器中
//    STR     R1, [R0]				//将PendSV寄存器内核悬起使能写入R0寄存器所指向的地址
//    CPSIE   I						//使能所有中断
//	POP     {R0,R1,PC}
//	NOP
////    BX      LR						//跳转到LR寄存器中所指向的值
//}
/*
                                                  FILE-END
*/

