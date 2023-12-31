/**
 * Copyright 2022-2023 AhDun. All rights reserved.
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
/**
 *
 * @file osLink.c
 *
 * @brief 链接(衔接)文件
 *
 * @note 
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

/**
 *
 * @name osLinkTaskStackInit
 *
 * @brief 任务栈初始化
 *
 * @param uint32_t tta(任务传参) ,uint32_t *tsa(任务开始地址),uint32_t *eca(任务结束回调地址),uint32_t *tsas(任务栈地址)
 *
 * @retval none
 *
 * @note none
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
	MOV    R2,#0x00//将0x00值加载到R2寄存器中
	PUSH   {R2}//R12(0x00)
	PUSH   {R2}//R3(0x00)
	PUSH   {R2}//R2(0x00)
	PUSH   {R2}//R1(0x00)
	PUSH   {R0}//R0(0x00)


	#if (osFPU_Config > 0)//启用了FPU
	SUB   SP,    SP,#0x40//SP寄存器中的值减去0x40

	#endif

	LDR		R5,	=LR_INIT_VALUE
	PUSH   {R5}//R11
	MOV   R5,   #0x00//将0x00传给R5寄存器
	PUSH   {R5}//R4
	PUSH   {R5}//R5
	PUSH   {R5}//R6
	PUSH   {R5}//R7
	PUSH   {R5}//R8
	PUSH   {R5}//R9
	PUSH   {R5}//R10
	PUSH   {R5}//R11


	STR	  SP,	[R3]
	MOV   SP,   R4//将R4寄存器中的值加载到SP寄存器中，上半部分程序备份的SP值
	POP{R4-R5}

	BX	  LR
}
/**
 *
 * @name osLinkUseEnable
 *
 * @brief 启用进程栈
 *
 * @param uint32_t *tsas(任务栈地址)
 *
 * @retval none
 *
 * @note none
 *
 */
__asm void osLinkUseEnable(void)
{
//	#if (osTaskUseStack_Config > 0)
//	MOV	R1,	  SP
//	MSR   PSP,  R1//通过MSR命令将R0寄存器中的内容写到PSP（进程栈）寄存器中
//	LDR	R0,	  =osTaskGetRunTaskHandle()
//	LDR	R0,	  [R0]
//	LDR	R0,	  [R0]
//	MSR   MSP,  R0//通过MSR命令将R0寄存器中的内容写到PSP（进程栈）寄存器中
//	/*使能进程栈{*/
//	MRS	R0,		CONTROL//通过MRS命令读取控制寄存器到R0寄存器
//	ORR	R0,		R0,#0x02//R0寄存器与0x02进行或运算，使的bit1位 置1
//	MSR	CONTROL,R0//再通过MSR命令将R0寄存器中的内容写回控制寄存器中
//	/*}*/
//	#endif
	#if (osTaskUseStack_Config > 0)
	MOV	R1,	  SP
	MSR PSP,  R1//通过MSR命令将R0寄存器中的内容写到PSP（进程栈）寄存器中
	SUB	R1,	  #0x64
	MSR MSP,  R1//通过MSR命令将R0寄存器中的内容写到PSP（进程栈）寄存器中
	/*使能进程栈{*/
	MRS	R0,		CONTROL//通过MRS命令读取控制寄存器到R0寄存器
	ORR	R0,		R0,#0x02//R0寄存器与0x02进行或运算，使的bit1位 置1
	MSR	CONTROL,R0//再通过MSR命令将R0寄存器中的内容写回控制寄存器中
	/*}*/
	#endif
	BX    LR//退出函数，跳转到BX寄存器中所存的地址
	NOP
}


/**
 *
 * @name HardFault_Handler
 *
 * @brief 任务错误入口
 *
 * @param none
 *
 * @retval none
 *
 * @note none
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
/**
 *
 * @name SysTick_Handler
 *
 * @brief 系统时钟入口
 *
 * @param none
 *
 * @retval none
 *
 * @note none
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
/**
 *
 * @name PendSV_Handler
 *
 * @brief 启动第一个任务
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
#if (osTaskUseStack_Config > 0)
__asm void PendSV_Handler(void)
{
	PRESERVE8

	extern osTaskGetRunTaskHandle()
	extern osTaskGetNextTaskHandle()
	#if (osPerf_Config > 0)
	extern OSRecord
	#endif

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
	

//	CPSIE   I

//	BL.W	osTaskNext

//	CPSID   I			//禁用所有中断


	#if (osPerf_Config > 0)
//	OSRecord.TSC += 1;
	LDR	R0, = OSRecord
	LDR R1,	[R0]
	ADD	R1, #0x01
	STR	R1,	[R0]
	#endif

	LDR   R0,	=osTaskGetNextTaskHandle()
	LDR	  R1,	=osTaskGetRunTaskHandle()
	LDR	  R0,	[R0]
	STR	  R0,	[R1]
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
	extern osTaskGetNextTaskHandle()
	#if (osPerf_Config > 0)
	extern OSRecord
	#endif

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

	#if (osPerf_Config > 0)
//	OSRecord.TSC += 1;
	LDR	R0, = OSRecord
	LDR R1,	[R0]
	ADD	R1, #0x01
	STR	R1,	[R0]
	#endif

	LDR   R0,	=osTaskGetNextTaskHandle()
	LDR	  R1,	=osTaskGetRunTaskHandle()
	LDR	  R0,	[R0]
	STR	  R0,	[R1]
	LDR   R1,   [R0]	

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



OsErrorValue osTaskErrorHardFault(uint32_t pc,uint32_t psp)
{
	#if (osTaskRunError_Config > 0)
	uint8_t Count = 1;
	osTaskEnterIRQ();
	while(Count--){
		#if (osTaskName_Config > 0)
		print("\n\n\n名称为%s的任务发生“硬件错误”异常!!!\n",osTaskGetRunTaskHandle() -> Name);
		#endif
		print("任务优先级:%d\n",osTaskGetRunTaskHandle() -> Level);
		print("任务当前使用量:%d%%\n",osTaskGetRunTaskHandle() -> OccupyRatio);
		print("任务延时剩余时间:%d%ms\n任务单次最大运行时长:%dms\n",osTaskGetRunTaskHandle() -> Delay,osTaskGetRunTaskHandle() -> Wheel);
		print("任务最一近状态:",0,0);
		switch(osTaskGetRunTaskHandle() -> Config){
			case Task_State_Up_DT:print("延时挂起\n");break;
			case Task_State_Up_SI:print("信号挂起\n");break;
			case Task_State_Up_PT:print("邮件挂起\n");break;
			case Task_State_DI:print("禁用态\n");break;
			case Task_State_ST:print("终止态\n");break;
			case Task_State_RB:print("重启态\n");break;
			case Task_State_OP:print("运行态\n");break;
			case Task_State_RE:print("就绪态\n");break;
		}
		print("任务邮箱状态:");
		if(osTaskGetRunTaskHandle() -> Arg1 == NULL){
			print("空的\n");
		}
		else{
			print("非空\n");
		}
		print("任务栈总大小:%d字节\n任务栈剩余:%d字节\n",(uint32_t)osTaskGetRunTaskHandle() -> Length - (uint32_t)osTaskGetRunTaskHandle() -  sizeof(_TaskHandle),psp - ((uint32_t)osTaskGetRunTaskHandle() +  sizeof(_TaskHandle)));
		print("任务异常处:%X\n",pc);
		print("内存总量:%d字节\n内存余量:%d字节",osMemoryGetAllValue(),osMemoryGetFreeValue());
	}
	#endif
	#if (osTaskErrorSet == 1)
	osTaskSet(NULL,Task_Set_Reboot);
	#elif(osTaskErrorSet == 0)
	osTaskSet(NULL,Task_Set_Pause);
	#endif
	osTaskExitIRQ();
	return (OK);
}
/**
 *
 * @name osTaskSpeedTest
 *
 * @brief 任务切换速度测试
 *
 * @param none	
 *
 * @retval -1:创建错误，0: 创建成功
 *
 * @note none
 *
 */
void Delay1ms()		//@24.000MHz
{
	unsigned long i;

//	_nop_();
//	_nop_();
//	_nop_();
	i = 5998UL;
	while (i) i--;
}

OsErrorValue osTaskSpeedTest(void)
{
	uint32_t t0,t1;
	osTaskGetRunTaskHandle() -> Config = Task_State_RE;
	t0 = SysTick->VAL;
	Delay1ms();
	t1 = SysTick->VAL;
	#if (osPerf_Config > 0)
	OSRecord.TSSU = (osCPU_Period*(t0 - t1)*8)/osCPU_Period_Times;
	#endif
	#if (osTaskLog_Config > 0)
	print("任务切换速度测试: t0 %d - t1 %d = %d个时钟周期(%fus)\n",t0,t1,(t0 - t1)*8,(osCPU_Period*(t0 - t1)*8)/osCPU_Period_Times);
	#endif
	return (OK);
}
OsErrorValue osTaskMonitor(void)

{
	_TaskHandle* TaskHandleListBuf = osTaskGetTaskHandleListHead();;
	do{
		print("任务<%s>占用时长:%dms | 任务优先级:%d | 任务状态:",TaskHandleListBuf -> Name,TaskHandleListBuf -> OccupyRatio,TaskHandleListBuf -> Level);
		if(TaskHandleListBuf != osTaskGetRunTaskHandle()){
			switch(TaskHandleListBuf -> Config){
				case Task_State_Up_DT:print("延时挂起\n");break;
				case Task_State_Up_SI:print("信号挂起\n");break;
				case Task_State_Up_PT:print("邮件挂起\n");break;
				case Task_State_DI:print("禁用态\n");break;
				case Task_State_ST:print("终止态\n");break;
				case Task_State_RB:print("重启态\n");break;
				case Task_State_OP:print("运行态\n");break;
				case Task_State_RE:print("就绪态\n");break;
			}
		}
		else{
			print("正在运行\n");
		}
		TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
	}while(TaskHandleListBuf != osTaskGetTaskHandleListHead());

	
	print("CPU总使用量:%d%% = 任务 %d%% + 中断%d%% + 调度%d%%\n",OSRecord.CTO + OSRecord.CISRO + OSRecord.CSO,OSRecord.CTO,OSRecord.CISRO,OSRecord.CSO);

	print("任务调度次数:%d | 预计耗时:%fus(%fms)\n",OSRecord.TSCb,OSRecord.TSCb*2.0,(OSRecord.TSCb*OSRecord.TSSU) / 1000);

	print("内存 总量:%d字节 | 余量:%d字节 | 可分配:%d字节 | 块数:%d\n",osMemoryGetAllValue(),osMemoryGetFreeValue(),osMemoryGetPassValue(),osMemorySum());
	print("系统已运行: %d天 %d小时 %d分钟 %d秒\n",osClockGetOsRTCD(),osClockGetOsRTCH(),osClockGetOsRTCM(),osClockGetOsRTCS());
	
	return (OK);
}




/**
 *
 * @name pchar
 *
 * @brief 输出接口
 *
 * @param ch	字符
 *
 * @retval none
 *
 * @note 该函数可以用于重定向
 *
 */
int pchar(const char ch)
{
	USART_SendData(USART1,ch);//发送到串口
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return (ch);
}

/**
 *
 * @name print
 *
 * @brief print函数入口
 *
 * @param c 控制字符串
 *			  ... 其他传参
 *
 * @retval none
 *
 * @note none
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
/**
 *
 * @name sprint
 *
 * @brief sprint函数入口
 *
 * @param s 输出地址
 *  		  c 控制字符串
 *			  ... 其他传参
 *
 * @retval none
 *
 * @note none
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



