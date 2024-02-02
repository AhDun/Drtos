/*------------------------------------------------------------------------------------------------------------------------
 * 文件名称：System_Clock.c

 * 文件内容：系统时钟内核

 * 文件版本：1.0.0

 * 文件作者：阿顿

 * 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5 

 * 注    意：
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  加载头文件区
------------------------------------------------------------------------------------------------------------------------*/
#include "Inc_Basic.h"//基本库
#include "Timer.h"
#include "System_Clock.h"
#include "System_Control.h"
#include "System_Task.h"
#include "CPU.h"
/*------------------------------------------------------------------------------------------------------------------------
                                                  变量初始化区
------------------------------------------------------------------------------------------------------------------------*/
#ifdef EnableRunningTime
u16 xdata SystemTime = NULL;//系统时钟
u32 xdata RUNTime = NULL;//连续运行时间
#endif
u16 xdata Task0Time = NULL;//任务0最大挂起时长
u16 xdata ProTime = NULL;//任务保护时长
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：TaskDelayMs

 * 函数功能：硬件延时

 * 输入参数：TimeMs-时间，单位ms

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void TaskDelayMs(u16 TimeMs)
{
	TaskInfo[RunAppID].Pa1 = TimeMs;//将定时值加载到当前任务所对应的任务表中参数中，可用于倒计时
	/*检查任务切换锁是否为解锁状态，如果为解锁状态，则进入*/
	if(SnLock == UnLock)
	{
		TaskRPlanTaskId();//刷新下一个要运行的任务ID
	}
	TimerIRQTouchType = Task_Touch;//加载触发类型
	System_Timer_Touch;//触发系统定时器中断
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：HeavyLoadSystemTimer

 * 函数功能：重装系统定时器

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void HeavyLoadSystemTimer()
{
	TH0 = System_Timer_Reload >> 8;//初值(高8位)
	TL0 = System_Timer_Reload & 0x00FF;//初值(低8位)
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：SystemClock

 * 函数功能：系统时钟

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void SystemClock()
{
	u8 tms_F0;
	if(TimerIRQTouchType == NULL)
	{
		/*重装系统定时器*/
		HeavyLoadSystemTimer();
		/*----------------------------------进行系统时间处理---------------------------------------*/
		#ifdef EnableRunningTime
		SystemTime++;//系统时间增值
		RUNTime++;//运行时间增值
		#endif
		#ifdef EnableECF
		for(tms_F0 = NULL; tms_F0 <= TaskDMax ; tms_F0++)//使用for循环，进行扫描处理(定时任务计时)
		#else
		for(tms_F0 = NULL; tms_F0 <= TaskMax ; tms_F0++)//使用for循环，进行扫描处理(定时任务计时)
		#endif
		{
			/*当前任务的任务优先级与当前任务的任务参数同时大于0时，进行计时*/
			if(TaskInfo[tms_F0].Pa1 > NULL && TaskInfo[tms_F0].Py1 > NULL)
			{
				/*数值减一*/
				TaskInfo[tms_F0].Pa1--;
				/*当前任务的任务参数等于0时，开始运行该任务*/
				if(TaskInfo[tms_F0].Pa1 == NULL)
				{
					/*当前任务ID，注入到任务队列中*/
					TaskQueue_write(tms_F0,TaskInfo[tms_F0].Py1);
					/*当前任务中参数进行重装，以便下次计量*/
					TaskInfo[tms_F0].Pa1 = TaskInfo[tms_F0].Pa0;
				}
			}
		}
		/*----------------------------------进行任务处理---------------------------------------*/
		/*保护时长为零时，则进入*/
		if(ProTime == NULL)
		{
			/*任务运行时长大于零并且运行的任务ID大于零时,则进入*/
			if(AppRunTimer > NULL && RunAppID > NULL)//超时挂起
			{
				AppRunTimer--;//数值减一
				/*当时达到阈值时，则进入*/
				if(AppRunTimer == (0xFF - AppRunTimerMax))
				{
					/*Test Start*/
					//			Uart_Outs("应用:");//显示提示
					//			Uart_Outnum(RunAppID);
					//			Uart_Outs("  ");
					//			Uart_Outs("运行超时请注意!!\n");//显示提示
					/*END Test*/
					TaskInterruptQueue_write();//写入到中断型任务队列
					TaskRPlanTaskId();//加载下一次运行任务ID
					/*当加载到下一次运行任务ID与当前运行中任务相同时，则重新加载，一直加载到不同时，才停止*/
					while(PlanTaskId == RunAppID)
					{
						TaskRPlanTaskId();//加载下一次运行任务ID
					}
					TimerIRQTouchType = Task_Touch;//将系统中断触发类型设为任务触发
				}
			}
			/*当普通队列或者是中断型任务队列的指针超过最大的容量时，则进入*/
			else if(AQSP >= (TaskQueueMax - 1) || BQSP >= (TaskQueueMax - 1))//溢出挂起
			{
				TaskInterruptQueue_write();//写入到中断型任务队列
				TaskRPlanTaskId();//加载下一次运行任务ID
				TimerIRQTouchType = Task_Touch;//将系统中断触发类型设为任务触发
			}
			/*当普通队列或者是中断型头部的任务ID不为零时，则进入*/
			else if(TaskQueue[NULL].ID > NULL || TaskInterruptQueue[NULL] > NULL)//阻塞挂起
			{
				if(TaskSwitchIf())
				{
					/*检查任务切换锁是否为解锁状态，如果为解锁状态，则进入*/
					if(SnLock == UnLock)
						TaskRPlanTaskId();//加载下一次运行任务ID
					TimerIRQTouchType = Task_Touch;//将系统中断触发类型设为任务触发
				}
			}
			/*当运行的任务不为零时,则进入*/
			else if(RunAppID > NULL)//主进程空闲超时挂起
			{
				Task0Time--;//进行倒计时
				/*倒数为零时，则进入*/
				if(Task0Time == NULL)
				{
					Task0Time = Task0TimeSize;//重新加载倒计时
					TaskInterruptQueue_write();//写入到中断型任务队列
					PlanTaskId = NULL;//清空下一次运行任务ID
					TPC = TaskInfo[NULL].TPC;//加载初始任务地址，注意：本操作为空操作，无实际意义
					RunAppPy = NULL;//清空运行中任务的优先级
					SnLock = Locking;//任务切换锁，上锁
					TimerIRQTouchType = Task_Touch;//将系统中断触发类型设为任务触发
				}
			}
			else 
			{
				Task0Time = Task0TimeSize;//重新加载倒计时
			}
		}
		/*进行倒计时*/
		else 
		{
			ProTime--;	
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/
