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
#ifndef __osConfig_H_
#define __osConfig_H_
/**
 *
 * @file osConfig.h
 *
 * @brief 系统配置
 *
 * @note 
 *
 */




#include "main.h"
#include "usart.h"
#include "Str.h"
#include "print.h"
#include "LinkList.h"




//系统信息{
#define osMaximumTask 	     	64 //系统最大任务量
#define osVersionNumber        110 //系统版本号
#define osVersionNumberS       "v1.1.0" //系统版本号名
#define osName                 "Drtos" //系统名称
#define osNameVersionNumberS   "Drtos v1.1.0" //系统名称 + 系统版本号名
#define osCompileDate		  	__DATE__//系统编译日期
#define osCompileTime 		 	__TIME__//系统编译时间
#define osCPU_Name				"STM32F407ZG"//CPU名称
#define osCPU_Freq				168u//CPU主频
#define osCPU_Bit				sizeof(void*)
//}


//硬件驱动{
#define osClock_Init() 		 

#define osDebug_Init() 		 

#define osIRQ_Init()  		 do{}while(0);//系统中断初始化函数


#define osClockPause()   	do{}while(0);//暂停系统

#define osClockRecover() 	do{}while(0);//恢复系统

//}


//函数差异化{
#define osTaskTimeUs(a) 	SysTick_us(us)//微秒级延时

#define osInfoDebug()  		do{\
							print("系统名称: %s\n",osName);\
							print("系统版本号: %s\n",osVersionNumberS);\
							print("系统最大任务量: %d\n",osMaximumTask);\
							print("系统编译日期: %s\n",osCompileDate);\
							print("系统编译时间: %s\n",osCompileTime);\
							print("CPU名称: %s\n",osCPU_Name);\
							print("CPU主频: %dMHz\n",osCPU_Freq);\
							}while(0);//系统信息

#define osInit()    do{\
						osIRQ_Init();\
						osDebug_Init();\
						osMemoryInit();\
						osTaskInit();\
						osClockInit();\
						osInfoDebug();\
						osTaskSpeedTest();\
					}while(0);//系统初始化


#define osDebugError 		print
#define osDebugInfo 		print
#define osDebugWarning 		print

//}

//功能配置{
#define osCriticalToProtect_Enable   1  //临界保护  1：启用 0：禁用

#define osPerformanceStatistics_Enable 1//任务统计  1：启用 0：禁用

#define os_TotalSystemRunningTime_Enable 1//记录系统运行时长  1：启用 0：禁用

#if (__FPU_USED == 1)
#define osFPU_Enable                    1//启用FPU硬件   1：启用 0：禁用
		/*启用后会进行了对FPU压栈操作，同时也需要在编译器中开启浮点硬件才可以支持
		  如果你的编译器或MCU不支持浮点硬件，请禁用！
		*/
#else
#define osFPU_Enable                    0//启用FPU硬件   1：启用 0：禁用
#endif

#define osSignalAutoApply_Enable		1//信号量自动分配   1：启用 0：禁用
		/*启用后会为信号量自动分配内存*/

#define osTaskNewR_Enable				1//加载任务时新寄存器   1：启用 0：禁用
										/*可以通过关闭加载任务时新寄存器，加快新任务的启动速度，但是可能会影响任务的稳定性*/

#define osSpeedTest_Enable 				1//启动时测试任务切换速度 1：启用 0：禁用

#define osClockTimePeriod 					1000 //系统时间周期，单位us

#define osClockTimePeriodStandard			1000 //系统时间基准周期，单位us

#define	SIRQListLength						10

#define	osTaskErrorSet					0//任务运行时发生致命错误后处理 1：重启这个任务 0：暂停这个任务


#define osTaskParameterPass_Enable 		1//启动时测试任务切换速度 1：启用 0：禁用

//}


typedef int32_t osErrorValue;//函数错误返回值


#include "osLink.h"
#include "osSignal.h"
#include "osPost.h"
#include "osTask.h"
#include "osClock.h"
#include "osMemory.h"
#include "osPost.h"

#endif


