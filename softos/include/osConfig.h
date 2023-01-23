/*
                                                  FILE-START
*/
#ifndef __osConfig_H_
#define __osConfig_H_
/*

 *@文件名称: osConfig.h

 *@文件内容: 系统配置

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

//系统信息{
#define osMaximumTask 	     	64 //系统最大任务量
#define osVersionNumber        100 //系统版本号
#define osVersionNumberS       "v1.0.0" //系统版本号名
#define osName                 "softos" //系统名称
#define osNameVersionNumberS   "softos v1.0.0 Bate" //系统名称 + 系统版本号名
#define osCompileDate		  	__DATE__//系统编译日期
#define osCompileTime 		 	__TIME__//系统编译时间
#define osCPU_Name				"STM32F407ZG"//CPU名称
#define osCPU_Freq				168u//CPU主频
//}


//硬件驱动{
#define osClock_Init() 		 SysTick_us_Init(osCPU_Freq,osClockTimePeriod)//系统时钟初始化函数

#define osDebug_Init() 		 USART1_Init(115200)//系统串口初始化函数

#define osIRQ_Init()  		 do{\
								NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);\
								NVIC_SetPriority (SysTick_IRQn, 0x04|0x02|0x01);\
								NVIC_SetPriority (PendSV_IRQn, 0x08|0x04|0x02|0x01);\
							 }while(0);//系统中断初始化函数


#define osClockPause()   	do{\
									SysTick->CTRL &= ~(0x02) ;\
								}while(0);//暂停系统

#define osClockRecover() 	do{\
									SysTick->CTRL |= (0x02) ;\
								}while(0);//恢复系统

//}


//函数差异化{
#define osTaskTimeUs(a) 	SysTick_us(us)//微秒级延时

//}

//功能配置{
#define osCriticalToProtect_Enable   1  //临界保护  1：启用 0：禁用

#define osPerformanceStatistics_Enable 1//任务统计  1：启用 0：禁用

#define os_TotalSystemRunningTime_Enable 1//系统运行时长  1：启用 0：禁用

#if (__FPU_USED == 1)
#define osFPU_Enable                    1//启用FPU硬件   1：启用 0：禁用
		/*启用后会进行了对FPU压栈操作，同时也需要在编译器中开启浮点硬件才可以支持
		  如果你的编译器或MCU不支持浮点硬件，请禁用！
		*/
#else
#define osFPU_Enable                    0//启用FPU硬件   1：启用 0：禁用
#endif

#define osTaskAutoStack_Enable			1//任务栈自动分配   1：启用 0：禁用
		/*启用后会为任务栈自动分配内存*/

#define osSignalAutoApply_Enable		1//信号量自动分配   1：启用 0：禁用
		/*启用后会为信号量自动分配内存*/

#define osTaskNewR_Enable				1//加载任务时新寄存器   1：启用 0：禁用
		/*可以通过关闭加载任务时新寄存器，加快新任务的启动速度，但是可能会影响任务的稳定性*/

#define osTaskUsePrint 					0//打印各任务使用情况 1：启用 0：禁用


#define osTaskUsePrintClock 			1//时钟中断打印各任务使用情况 1：启用 0：禁用


#define osClockTimePeriod 					1000 //系统时间周期，单位us

#define osClockTimePeriodStandard			1000 //系统时间基准周期，单位us

//}

/*
                                                  <数据声明区>
*/
/*
                                                  <函数声明区>
*/
#endif
/*
                                                  FILE-END
*/

