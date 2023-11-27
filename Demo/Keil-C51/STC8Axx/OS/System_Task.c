/*------------------------------------------------------------------------------------------------------------------------
 * 文件名称：System_Task.c

 * 文件内容：系统任务API

 * 文件版本：1.0.0

 * 文件作者：麦特实验室

 * 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5 

 * 注    意：
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  加载头文件区
------------------------------------------------------------------------------------------------------------------------*/
#include "Inc_Basic.h"//基本库
#include "System_Control.h"
#include "System_Task.h"
#include "System_Clock.h"
#include "Timer.h"
/*------------------------------------------------------------------------------------------------------------------------
                                                  变量初始化区
------------------------------------------------------------------------------------------------------------------------*/
u8 xdata AQSP = NULL;//多任务队列指针
u8 xdata BQSP = NULL;//多任务队列指针
#ifdef EnableECF
u8 xdata TaskDMax = NULL;//任务最大活动量
#endif
u8 xdata PlanTaskId = NULL;//下一个要运行的任务ID
u8 xdata SP0 = NULL;//初始化栈指针
u8 xdata RunAppID = NULL;//在运行任务的ID
u8 xdata RunAppPy = NULL;//在运行任务的优先级
u8 xdata SnLock = NULL; //任务切换锁
u8 xdata AppRunTimer = NULL;
u16 xdata TPC = NULL;//任务初始地址
u16 xdata TaskEndAddr = NULL;//任务自动终止时，返回的地址
u8 xdata TimerIRQTouchType  = NULL;//定时器中断触发类型

u8 xdata Pstack[TaskMax][MaxStackDepth] = {NULL};//栈池
taskqueue TaskQueue[TaskQueueMax + 2] = {NULL};//任务队列表
TASKINFO TaskInfo[TaskMax] = {NULL};//任务信息表
u8 xdata TaskInterruptQueue[TaskQueueMax + 2] = {NULL};//中断任务队列
u8 stack0[StackBuffer] = {NULL};//栈缓冲区
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：TaskLoad

 * 函数功能：注册任务

 * 输入参数：TaskId(应用ID) TaskType(任务类型) PY(任务优先级) TaskM(任务参数) TaskPC(函数名)

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void TaskLoad(u8 TaskId,u8 TaskType,u8 PY,u16 TaskM,u16 TaskPC) reentrant
{
	System_IMS_Disable;//关闭总中断
	TaskInfo[TaskId].Py0 = PY;//输入优先级
	TaskInfo[TaskId].Py1 = PY;//输入优先级
	TaskInfo[TaskId].Type = TaskType;//输入类型
	TaskInfo[TaskId].TPC = TaskPC;//输入地址
	/*当TaskType大于零时，则判断为条件型任务*/
	if(TaskType)
	{
		TaskInfo[TaskId].Pa0 = TaskInfo[TaskId].Pa1 = NULL;//输入数值//条件型任务信息
	}
	/*等于零时，则判断为定时型任务*/
	else
	{
		TaskInfo[TaskId].Pa0 = TaskInfo[TaskId].Pa1 = TaskM;//输入数值//定时型任务信息
	}
	#ifdef EnableECF
	if(TaskId >= TaskDMax )//获取最大值
	{
			TaskDMax  = TaskId;
	}
	#endif
	System_IMS_Enable;//开启总中断
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：TaskRemove

 * 函数功能：注销任务

 * 输入参数：TaskId(应用ID)

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void TaskRemove(u8 TaskId) reentrant
{
	#ifdef EnableECF
	u8 R0;
	#endif
	System_IMS_Disable;//关闭总中断
	TaskInfo[TaskId].Py0 = NULL;//输入优先级
	TaskInfo[TaskId].Py1 = NULL;//输入优先级
	TaskInfo[TaskId].Type = NULL;//输入类型
	TaskInfo[TaskId].Pa0 = NULL;//输入数值
	TaskInfo[TaskId].Pa1 = NULL;//输入数值
	#ifdef EnableECF
	for(R0 = TaskMax;R0 > NULL ;R0--)//重新计算最大值 
	{
		if(TaskInfo[R0].Py0 == NULL)
		{
			TaskDMax = R0 - 1;
			break;
		}
	}
	#endif
	System_IMS_Enable;//开启总中断
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：MgQueue

 * 函数功能：队列管理

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
#ifdef EnableQueueCheck
void MgQueue() reentrant 
{
 	u8 MgQ_F0;
																										/*触发条件*/
	if(TaskQueue[NULL].ID == NULL && AQSP > NULL || // 1.当队列头部没有数据，而队列指针大于零时
		 TaskQueue[AQSP].ID != NULL || // 							 2.当队列指针，指向的队列数据，不为零时
		 AQSP > TaskQueueMax)//													 3.当队列指针大于队列的长度时
	{
		AQSP = NULL;//进行队列指针清零
		/*进行队列指针校准，从后往前进行校准*/
		for(MgQ_F0 = TaskQueueMax;MgQ_F0 >= NULL;MgQ_F0--)
		{
			/*当前队列指针指向的数据不为零，下一个指针指针指向数据为零时，触发*/
			 if(TaskQueue[MgQ_F0].ID != NULL && TaskQueue[MgQ_F0 + 1].ID == NULL)
			 {
				  AQSP = MgQ_F0 + 1;//将新指针加载上
				  break;
			 }	
			 /*没有触发条件时，结束运行*/
			 else if(MgQ_F0 == NULL)
			 	break;
		}
	}
}
#endif
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：TaskInterruptQueue_write

 * 函数功能：写中断任务队列

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void TaskInterruptQueue_write()
{
	u8 AQISP1;
	for(AQISP1 = NULL;AQISP1 < TaskQueueMax;AQISP1++)
	{
		/*当指针指向的数据与当前运行任务ID相同时，或者指针指向的数据为空时，触发*/
		if(TaskInterruptQueue[AQISP1] == RunAppID ||TaskInterruptQueue[AQISP1] == 0)//整体向后移一位
		{
			/*将当前运行任务ID，写入到队列中*/
			TaskInterruptQueue[BQSP] = RunAppID;
			BQSP++;//指针加一
			break;//结束运行
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：TaskQueue_write

 * 函数功能：写任务队列

 * 输入参数：TaskID(应用ID)Py(任务优先级)

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void TaskQueue_write(u8 TaskID,u8 Py) reentrant
{
 	u8 AQSP1,AQSP2;//定义变量
	if(Py > RunAppPy && RunAppID > NULL && ProTime == NULL)
	{
		TaskInterruptQueue_write();//写入到中断型任务队列
		PlanTaskId = TaskID;//将任务ID加载到
		RunAppPy = TaskInfo[PlanTaskId].Py1;
		TPC = TaskInfo[PlanTaskId].TPC;
		SnLock = Locking;//任务切换锁，上锁
		TimerIRQTouchType = Task_Touch;//将系统中断触发类型设为任务触发
	}
	else
	{
		#ifdef EnableQueueCheck
		MgQueue();//进行队列管理
		#endif
		if(AQSP < TaskQueueMax)//在任务指针小于任务队列的最大长度时，才可以写入
		{
			 AQSP1 = NULL;
			 while(AQSP1 < TaskQueueMax)//在任务指针大于任务队列的最大长度时，停止写入
			 {
				 if(TaskQueue[AQSP1].Py >= Py)
					AQSP1++;
				 else
				 {
					 for(AQSP2 = AQSP;AQSP2 > AQSP1;AQSP2--)//整体向后移一位
					 {
						 TaskQueue[AQSP2] = TaskQueue[AQSP2 - 1];
					 }
					 TaskQueue[AQSP1].ID = TaskID;//写入应用ID
					 TaskQueue[AQSP1].Py = Py;//写入任务优先级
					 AQSP++;//任务指针加一
					 break;//退出循环
				 }
			 }
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：TaskQueue_read

 * 函数功能：读任务队列

 * 输入参数：无

 * 输出参数：任务ID

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
u8 TaskQueue_read() reentrant
{
 	u8 Aqw_F0,Aqw_temp;
	/*当中断型队列，不为空时，则进入*/
	if(TaskInterruptQueue[NULL] > NULL)
	{
		Aqw_temp = TaskInterruptQueue[NULL];//加载任务ID
		RunAppPy = TaskInfo[Aqw_temp].Py1;//从任务表加载初始优先级
		/*整体向前移一位*/
		for(Aqw_F0 = NULL;Aqw_F0 < BQSP;Aqw_F0++)
		{
			TaskInterruptQueue[Aqw_F0] = TaskInterruptQueue[Aqw_F0 + 1];
		}
		TaskInterruptQueue[Aqw_F0] = NULL;//清空最后一位
		if(BQSP > NULL)//下限
		{
			BQSP--;//任务指针减一
		}
		return Aqw_temp;//返回应用ID
	}
	else
	{
		#ifdef EnableQueueCheck
		MgQueue();//进行队列管理
		#endif
		/*当任务队列，不为空*/
		if(TaskQueue[NULL].ID > NULL)
		{
			Aqw_temp = TaskQueue[NULL].ID;//从任务队列装载任务ID
			RunAppPy = TaskQueue[NULL].Py;//从任务队列装载任务初始优先级
		}
		else
		{
			Task0Time = Task0TimeSize;//任务0重新加载
			RunAppPy = NULL;//清空优先级
			return false;//返回假
		}
		for(Aqw_F0 = NULL;Aqw_F0 < AQSP;Aqw_F0++)//整体向前移一位
		{
			TaskQueue[Aqw_F0] = TaskQueue[Aqw_F0 + 1];
		}
		TaskQueue[Aqw_F0].Py = TaskQueue[Aqw_F0].ID = NULL;//清空最后一位
		if(AQSP > NULL)//下限
		{
			AQSP--;//任务指针减一
		}
		return Aqw_temp;//返回应用ID
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：TaskRPlanTaskId

 * 函数功能：刷新等待应用Id

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void TaskRPlanTaskId()
{
	PlanTaskId = TaskQueue_read();//从任务队列读取任务ID
	TPC = TaskInfo[PlanTaskId].TPC;//根据任务ID读取任务的初始地址
	/*当前任务的初始优先级小于0x0A时，进行减一*/
	if(TaskInfo[PlanTaskId].Py1 < 0x0A)
	{
		TaskInfo[PlanTaskId].Py1--;
	}
	/*当前任务的初始优先级等于零时，重置优先级*/
	if(TaskInfo[PlanTaskId].Py1 == NULL)
	{
		TaskInfo[PlanTaskId].Py1 = TaskInfo[PlanTaskId].Py0;
	}
	SnLock = Locking;//任务切换锁，上锁
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：TypeTaskStartup

 * 函数功能：条件任务启动

 * 输入参数：TYPE(类型)

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void TypeTaskStartup(u8 TYPE) reentrant 
{
 	u8 TTS_F0;
	#ifdef EnableECF
	for(TTS_F0 = NULL;TTS_F0 <= TaskDMax ; TTS_F0++)//使用for，进行遍历
	#else
	for(TTS_F0 = NULL;TTS_F0 <= TaskMax ; TTS_F0++)//使用for，进行遍历
	#endif
	{
		if(TaskInfo[TTS_F0].Type == TYPE && TaskInfo[TTS_F0].Py1 > NULL)//与当前输入事件ID相同
		{
			TaskQueue_write(TTS_F0,TaskInfo[TTS_F0].Py1);//注入ID
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：OpenTask

 * 函数功能：立刻运行任务

 * 输入参数：TaskID(应用ID)

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void OpenTask(u8 TaskID) reentrant
{
	if(TaskInfo[TaskID].Py1 > NULL)
	{
		TaskQueue_write(TaskID,TaskInfo[TaskID].Py1);//注入ID
	}
	else
	{
		TaskQueue_write(TaskID,Task_Class_L9);//注入ID
	}
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：OpenTaskS

 * 函数功能：带优先级立刻运行任务

 * 输入参数：TaskID(应用ID) Py(任务优先级)

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void OpenTaskS(u8 TaskID,u8 Py) reentrant
{
		TaskQueue_write(TaskID,Py);//注入ID
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：TaskSwitchIf

 * 函数功能：任务ID刷新请求

 * 输入参数：无

 * 输出参数：0:不允许 1:允许

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
u2 TaskSwitchIf()
{
		/*如果当前运行的任务优先级小于任务队列头部优先级时，则返回真*/
		if(RunAppPy < TaskQueue[NULL].Py)
		{
			return true;
		}
		/*中断型任务队列不为空时，则进入*/
		else if (TaskInterruptQueue[NULL] > NULL)
		{
			/*查询中断型任务队列头部中任务ID的优先级，当优先级大于当前运行任务的优先级，则返回真*/
			if(RunAppPy < TaskInfo[TaskInterruptQueue[0]].Py1)
				return true;
			else
				return false;//返回假
		}
		else
			return false;//返回假
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：EnableProtection

 * 函数功能：开启任务任务

 * 输入参数：r1(保护时长-单位ms)

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void EnableProtection(u16 r1)
{
	/*r1值加载到保护值*/
	ProTime = r1;
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：DisableProtection

 * 函数功能：关闭任务任务

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void DisableProtection()
{
	/*清零保护值*/
	ProTime = NULL;
}
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：TaskEnd

 * 函数功能：任务结束处理

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void TaskEnd()
{
	TimerIRQTouchType = Task_End_Touch;
	System_Timer_Touch;
	while(true);
}
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/