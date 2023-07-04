/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
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
#include "Str.h"
#include "print.h"
#include "LinkList.h"




//系统信息{
#define osVersionNumber        110 //系统版本号
#define osVersionNumberS       "v1.1.0" //系统版本号名
#define osName                 "Drtos" //系统名称
#define osNameAndVersion  		"Drtos v1.1.0" //系统名称 + 系统版本号名
#define osCompileDate		  	__DATE__//系统编译日期
#define osCompileTime 		 	__TIME__//系统编译时间
#define osCPU_Name				"STC32G12K128"//CPU名称
#define osCPU_Freq				22u//CPU主频
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
#define osClock_Init() 		 1
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
#define osDebug_Init() 		 
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
								EA = 1;\
								EX0 = 1;\
								PX0H = 1;\
								PX0 = 1;\
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
#define osTaskTimeUs(a) 	//微秒级延时
//}

/*
 *
 * @函数名称: osInfoPrint
 *
 * @函数功能: 系统信息打印
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osInfoPrint()  		do{\
							print("系统名称: %s\n",osName);\
							print("系统版本号: %s\n",osVersionNumberS);\
							print("系统编译日期: %s\n",osCompileDate);\
							print("系统编译时间: %s\n",osCompileTime);\
							print("CPU名称: %s\n",osCPU_Name);\
							print("CPU主频: %dMHz\n",osCPU_Freq);\
							print("CPU位数: %d\n",osCPU_Bit);\
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
						osMemoryInstall(osMemoryInit(&Memory_CCRAM));\
						osTaskInit();\
						osClockInit();\
						osInfoPrint();\
						osTaskSIRQInit();\
						osSTimerInit();\
					}while(0);


//}

//log配置{
#define osLogF(a,...)				print("[Fatal] %s - %M",a,##__VA_ARGS__)// 严重级
#define osLogE(a,...)				print("[Error] %s - %M",a,##__VA_ARGS__)// 错误级
#define osLogW(a,...)				print("[Warn] %s - %M",a,##__VA_ARGS__)// 警告级
#define osLogI(a,...)				print("[Info] %s - %M",a,##__VA_ARGS__)// 信息级
#define osLogD(a,...)				print("[Debug] %s - %M",a,##__VA_ARGS__)// 调试级
	
//}

//任务配置{
#define osTaskLog_Config 1 //Debug配置 1:开启Log输出 0:关闭Log输出
#define osCriticalToProtect_Config   1  //临界保护  1：启用 0：禁用
#define osTaskName_Config			1// 任务的名称 1：启用 0：禁用
#define osTaskUseStack_Config 0//启用进程栈  1：启用 0：禁用
#define osFPU_Config                    0//启用FPU硬件   1：启用 0：禁用

#define osTaskNewR_Config				1//加载任务时新寄存器   1：启用 0：禁用
										/*可以通过关闭加载任务时新寄存器，加快新任务的启动速度，但是可能会影响任务的稳定性*/

#define TaskTimeWheelDefault        	100u//默认轮片时间(单位ms)
#define Default_Stack_Size             1000u//默认栈大小
#define osTaskArg_Config 			1 //启用任务传参 1：启用 0：禁用

#define osTaskStackDir_Config		CPUStackDir //		任务栈生长方向  1:递减 0:递增

#if( osFPU_Config > 0)
#define osTaskMinimumStackSize		80*4 //如果启用了浮点硬件，至少任务栈大小应大于80*4字节
#else
#define osTaskMinimumStackSize		50*4 //如果没有启用了浮点硬件，至少任务栈大小也应大于50*4字节
#endif

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
#define osPerf_Config 				1//任务统计  1：启用 0：禁用
#define osRunTime_Config 			1	//记录系统运行时长  1：启用 0：禁用
#define osTaskRunTime_Config 		1000 //任务统计时间，单位ms

//}


//时钟配置{

#define osClockTimePeriod 					1000 //系统时间周期，单位us
#define osClockTimePeriodStandard			1000 //系统时间基准周期，单位us

//}

//信号量配置{
#define osSignalAutoApply_Config		1//信号量自动内存分配   1：启用 0：禁用

#define Signal_Mutual       0x01u//互斥信号量
#define Signal_Binary       0x02u//二值信号量
#define Signal_Count        0x04u//计数信号量
#define Signal_AndGroup		0x08u//与组
#define Signal_OrGroup		0x10u//或组

#define osSignal_Config			Signal_Mutual | Signal_Binary | Signal_Count | Signal_AndGroup | Signal_OrGroup
							/*通过或配置*/

#define osSignalLog_Config		 1 //信号量错误DeBug  1:开启Log输出 0:关闭Log输出
#define osSignalMemoryMalloc	osMemoryMalloc	//内存申请方法
#define osSignalMemoryFree		osMemoryFree	//内存释放方法

//}

//邮箱配置{
#define osPost_Config			1 	 //启用邮箱 1：启用 0：禁用
#define osPostHead_Config		1	 //读邮件方式  1:队列式  0:栈式
#define osPostLog_Config 		1 	//邮箱错误DeBug  1:开启Log输出 0:关闭Log输出
#define osPostMemoryMalloc		osMemoryMallocStatic	//内存申请方法
#define osPostMemoryFree		osMemoryFreeStatic	//内存释放方法
//}

//内存配置{
#define MemTank_Max 					2 * 1024 //内存池大小配置

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

#define	osMemoryStatic_Config			1 //静态内存 1:开启 0: 关闭

#define osMemoryLog_Config 				1 //Debug配置 1:开启Log输出 0:关闭Log输出

//}






#include "osSignal.h"
#include "osPost.h"
#include "osTask.h"
#include "osTime.h"
#include "osMemory.h"
#include "osPost.h"
#include "osLink.h"

#endif


