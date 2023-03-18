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
#ifndef __osConfig_H_
#define __osConfig_H_
/*
 *
 * @文件名称: osConfig.h
 *
 * @文件内容: 系统配置
 *
 * @注    释: 
 *
 */




#include "main.h"
#include "SysTick.h"
#include "usart.h"
#include "Str.h"
#include "print.h"
#include "LinkList.h"




//系统信息{
#define osVersionNumber        110 //系统版本号
#define osVersionNumberS       "v1.1.0" //系统版本号名
#define osName                 "buffos" //系统名称
#define osNameVersionNumberS   "buffos v1.1.0" //系统名称 + 系统版本号名
#define osCompileDate		  	__DATE__//系统编译日期
#define osCompileTime 		 	__TIME__//系统编译时间
#define osCPU_Name				"STM32F407ZG"//CPU名称
#define osCPU_Freq				168u//CPU主频
#define osCPU_Period			5.95f//CPU时钟周期
#define osCPU_Period_Times		1000//CPU时钟周期的单位到
#define osCPU_Bit				sizeof(void*)*8//CPU位数
//}


//硬件驱动{

/*
 *
 * @函数名称: osClock_Init
 *
 * @函数功能: 系统时钟初始化
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osClock_Init() 		 SysTick_us_Init(osCPU_Freq,osClockTimePeriod)//
/*
 *
 * @函数名称: osDebug_Init
 *
 * @函数功能: 系统Debug初始化
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osDebug_Init() 		 USART1_Init(115200)//
/*
 *
 * @函数名称: osIRQ_Init
 *
 * @函数功能: 系统中断初始化
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osIRQ_Init()  		 do{\
								NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);\
								NVIC_SetPriority (SysTick_IRQn, 0x04|0x02|0x01);\
								NVIC_SetPriority (PendSV_IRQn, 0x08|0x04|0x02|0x01);\
							 }while(0);
/*
 *
 * @函数名称: osClockPause
 *
 * @函数功能: 系统时钟暂停
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/

#define osClockPause()   	do{\
									SysTick->CTRL &= ~(0x02) ;\
								}while(0);//暂停系统
/*
 *
 * @函数名称: osClockRecover
 *
 * @函数功能: 系统时钟恢复
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osClockRecover() 	do{\
									SysTick->CTRL |= (0x02) ;\
								}while(0);//恢复系统

//}


//函数差异化{
#define osTaskTimeUs(a) 	SysTick_us(us)//微秒级延时
//}

/*
 *
 * @函数名称: osInfoDebug
 *
 * @函数功能: 系统信息打印
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osInfoDebug()  		do{\
							print("系统名称: %s\n",osName);\
							print("系统版本号: %s\n",osVersionNumberS);\
							print("系统编译日期: %s\n",osCompileDate);\
							print("系统编译时间: %s\n",osCompileTime);\
							print("CPU名称: %s\n",osCPU_Name);\
							print("CPU主频: %dMHz\n",osCPU_Freq);\
							print("CPU位数: %d\n",osCPU_Bit);\
							osTaskSpeedTest();\
							}while(0);//系统信息
/*
 *
 * @函数名称: osInit
 *
 * @函数功能: 系统初始化
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osInit()    do{\
						osIRQ_Init();\
						osDebug_Init();\
						osMemoryInit(&Memory_CCRAM);\
						osTaskInit();\
						osClockInit();\
						osInfoDebug();\
						osTaskSIRQInit();\
						osSTimeInit();\
					}while(0);//系统初始化






//Debug配置{
#define osDebugError 		print	//错误Debug输出方法
#define osDebugInfo 		print	//信息Debug输出方法
#define osDebugWarning 		print	//警告Debug输出方法

#define osDebugClass_Error			1	
#define osDebugClass_Warning		2
#define osDebugClass_Info			3

//}

//log配置{
#define osLogClass_Fatal			1 // 严重级
#define osLogClass_Error			2 // 错误级
#define osLogClass_Warn				3 // 警告级
#define osLogClass_Info				4 // 信息级
#define osLogClass_Debug			5 // 调试级

#define osLogClassFatalOutput	print			
#define osLogClassErrorOutput	print			
#define osLogClassWarnOutput	print				
#define osLogClassInfoOutput	print				
#define osLogClassDebugOutput	print			
	
//}

//任务配置{
#define osTaskLog_Config 1 //Debug配置 1:开启Log输出 0:关闭Log输出
#define osCriticalToProtect_Config   1  //临界保护  1：启用 0：禁用
#define osTaskName_Config			1// 任务的名称 1：启用 0：禁用
#define osTaskUseStack_Config 1//启用进程栈  1：启用 0：禁用
#if (__FPU_USED == 1)
#define osFPU_Config                    1//启用FPU硬件   1：启用 0：禁用
		/*启用后会进行了对FPU压栈操作，同时也需要在编译器中开启浮点硬件才可以支持
		  如果你的编译器或MCU不支持浮点硬件，请禁用！
		*/
#else
#define osFPU_Config                    0//启用FPU硬件   1：启用 0：禁用
#endif

#define osTaskNewR_Config				1//加载任务时新寄存器   1：启用 0：禁用
										/*可以通过关闭加载任务时新寄存器，加快新任务的启动速度，但是可能会影响任务的稳定性*/

#define TaskTimeWheelDefault        	100u//默认轮片时间(单位ms)
#define Default_Stack_Size             1000u//默认栈大小
//}
//主任务配置{
#define MainName_Config 			"Main"//任务名称
#define MainStackSize_Config 		400	
#define MainTimeWheel_Config 		TaskTimeWheelDefault
#define MainPriorityLevel_Config 	0
#define MainPass_Config 			(void*)0
#define MainSet_Config 				Task_Set_Default
//}
//软中断配置{
#define SIRQName_Config 			"SIRQ"
#define SIRQStackSize_Config 		400
#define SIRQTimeWheel_Config 		TaskTimeWheelDefault
#define SIRQPriorityLevel_Config 	-127
#define SIRQPass_Config 			(void*)0
#define SIRQSet_Config 				Task_Set_Default
#define SIRQ_Config					1 //软中断配置  0:禁用  1:启用
//}
//软定时器配置{
#define STimeName_Config 			"STime"
#define STimeStackSize_Config 		400
#define STimeTimeWheel_Config 		TaskTimeWheelDefault
#define STimePriorityLevel_Config 	-126
#define STimePass_Config 			(void*)0
#define STimeSet_Config 			Task_Set_Default
#define STime_Config				1 //软定时器配置  0:禁用  1:启用
//}





//错误配置{
#define osTaskRunError_Config 1 //任务运行时发生致命错误 1:开启Log输出 0:关闭Log输出
#define	osTaskErrorSet					0//任务运行时发生致命错误后处理 1：重启这个任务 0：暂停这个任务
typedef int32_t OsErrorValue;//函数错误返回值
//}


//统计配置{
#define osPerformanceStatistics_Config 1//任务统计  1：启用 0：禁用
#define os_TotalSystemRunningTime_Config 1//记录系统运行时长  1：启用 0：禁用
#define TaskOccupyRatioSamplingTime 		1000 //任务统计时间，单位ms
#define osSpeedTest_Config 				1//启动时测试任务切换速度 1：启用 0：禁用
#define osTaskArg_Config 		1//启用任务传参 1：启用 0：禁用
//}


//时钟配置{

#define osClockTimePeriod 					1000 //系统时间周期，单位us
#define osClockTimePeriodStandard			1000 //系统时间基准周期，单位us

//}

//信号量配置{
#define osSignalAutoApply_Config		1//信号量自动分配   1：启用 0：禁用
		/*启用后会为信号量自动分配内存*/
#define osSignalMutual_Config //启用互斥信号量
#define osSignalBinary_Config //启用二值信号量
#define osSignalCount_Config  //启用计数信号量
#define osSignalLog_Config 1 //信号量错误DeBug  1:开启Log输出 0:关闭Log输出
#define osSignalMemoryMalloc	osMemoryMalloc	//内存申请方法
#define osSignalMemoryFree		osMemoryFree	//内存释放方法

//}

//邮箱配置{
#define osPost_Config	1 	 //启用邮箱 1：启用 0：禁用
#define osPostHead		1	 //读邮件方式  1:队列式  0:栈式
#define osPostLog_Config 1 //邮箱错误DeBug  1:开启Log输出 0:关闭Log输出
#define osPostMemoryMalloc		osMemoryMalloc	//内存申请方法
#define osPostMemoryFree		osMemoryFree	//内存释放方法
//}

//内存配置{
#define MemTank_Max 					16 * 1024 //内存池大小配置

#define MemoryProtect_Config 			0 // 内存保护配置 	1:开启保护 0:关闭保护	
										//启用保护申请内存与释放内存所用的时长将会增加
										//内存保护也不一定保证内存块一定不会发生错误!!!,只会降低内存发生错误的概率

#define osMemoryInitReset_Config 		0 //初始化内存时复位内存 1:开启 0:关闭
#define osMemorySequence_Config 		0 //内存顺序分配   1：启用 0：禁用

#if (osMemorySequence_Config == 0)

#define osMemoryFreeReset_Config 		0 //释放内存时复位内存 1:开启 0:关闭
#define osMemoryFreeTest_Config 		1 //释放内存时检查内存 1:开启 0:关闭
#define osMemoryPart_Config				1 //块分割  1:开启 0:关闭
#define osMemoryMerge_Config			1 //块合并  1:开启 0:关闭

#endif

#define osMemoryDebug_Config 			1 //Debug配置 1:开启Log输出 0:关闭Log输出
#define osMemoryErrorDebug osDebugError	//DeBug输出方法
//}





#include "osLink.h"
#include "osSignal.h"
#include "osPost.h"
#include "osTask.h"
#include "osTime.h"
#include "osMemory.h"
#include "osPost.h"
#include "osTool.h"

#endif


