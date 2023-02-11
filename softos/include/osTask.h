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
#ifndef __osTaskH_
#define __osTaskH_
/*
 *
 * @文件名称: osTask.h
 *
 * @文件内容: 
 *
 * @注    释: 
 *
 */




#define osTask_Enable 	//启用任务 ！这个定义无需手动配置，用于自动标记文件，自动增减功能

#define TaskListLength 		osMaximumTask 	//任务轮询表长度，这个意味着最大的任务量


//任务状态{
#define Task_State_Up_TD  0x05u//轮片挂起(挂起态)
/*
	在超时或出现错误时任务，会被轮片挂起，并设为轮片挂起
*/
#define Task_State_Up_IN  0x06u//主动挂起(挂起态)
/*
	任务通过暂停函数，会设为主动挂起
*/
#define Task_State_Up_DT  0x07u//延时挂起(等待态)
/*
	任务通过延时函数，会设为延时挂起
*/
#define Task_State_Up_SI  0x08u//信号挂起(等待态)
/*
	任务因为等待信号量而被挂起，会设为信号挂起
*/
#define Task_State_Up_PT  0x09u//邮件挂起(等待态)
/*
	任务因为等待邮件而被挂起，会设为邮件挂起
*/
/*
	当任务被设为等待态时，当条件满足会被系统恢复运行
	当任务被设为挂起态时，只能通过统一调度恢复运行
*/
#define Task_State_DI 	  0x00u //禁用态
/*
禁用态: 
这个任务永远不会被调度，但依然占用内存与任务ID
*/
#define Task_State_ST	  0x02u//终止态
/*
终止态: 
这个任务曾经运行过，现在以后不再运行了
*/
#define Task_State_RB	  0x01u//重启态
/*
重启态: 
这个任务正在等待重启中
*/
#define Task_State_OP	  0x03u//运行态
/*
运行态: 
这个任务现在正在运行，正在占用CPU
*/
#define Task_State_Up     0x04u//挂起态
/*
运行态: 
这个任务现在正在运行，正在占用CPU
*/
#define Task_State_RE     0x0Au//就绪态
/*
就绪态: 
*
*/
//}


//任务配置{
#define Task_Set_Default	0x00 //默认，不配置任何东西
#define Task_Set_Pause 		0x01u//暂停任务
#define Task_Set_Cont  		0x02u//继续任务
#define Task_Set_Reboot 	0x03u//重启任务
#define Task_Set_Start  	0x04u//立即启动任务
#define Task_Set_Up  		0x05u//挂起任务
//}

//调度状态{
#define TaskSwitch_Ready  		0x00u//就绪
#define TaskSwitch_Wait   		0x01u//等待
#define TaskSwitch_Run    		0x02u//运行
//}





#define osTaskDebug_Enable 1 //Debug配置 1:开启Debug输出 0:关闭Debug输出

#define osTaskRunError_Enable 1 //任务运行时发生致命错误 1:开启Debug输出 0:关闭Debug输出

//------------------------默认轮片时间-----------------------------
#define TaskTimeWheelDefault        100u//默认轮片时间(单位ms)

//--------------------------默认栈大小------------------
#define Default_Stack_Size             1000u//默认栈大小
     
//--------------------------函数替换----------------------
#if (osCriticalToProtect_Enable > 0)//启用了临界保护
/*
 *
 * @函数名称: osProtect_DISABLE
 *
 * @函数功能: 退出临界保护
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osProtect_DISABLE() 			ISR_Enable()
/*
 *
 * @函数名称: osProtect_DISABLE
 *
 * @函数功能: 进入临界保护
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osProtect_ENABLE() 				ISR_Disable()
#endif
/*
 *
 * @函数名称: osTaskSwitch_Enable
 *
 * @函数功能: 触发任务上下文切换
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osTaskSwitch_Enable() 			do{TaskSwitchState.SwitchState = TaskSwitch_Wait; ISR_Touch();}while(0);
/*
 *
 * @函数名称: osTaskSwitchConfig_Enable
 *
 * @函数功能: 带配置触发任务上下文切换
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osTaskSwitchConfig_Enable(a,b)  do{a -> Config = b;TaskSwitchState.SwitchState = TaskSwitch_Wait; ISR_Touch();}while(0);
/*
 *
 * @函数名称: osTaskEnterIRQ
 *
 * @函数功能: 进入中断
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osTaskEnterIRQ()			TaskSwitchState.ISRFlag += 1;
/*
 *
 * @函数名称: osTaskExitIRQ
 *
 * @函数功能: 退出中断
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osTaskExitIRQ()				TaskSwitchState.ISRFlag -= 1;
/*
 *
 * @函数名称: osTaskErrorDebug
 *
 * @函数功能: 进入中断
 *
 * @输入参数: 退出中断	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/

#define osTaskErrorDebug 		osDebugError







/*
                                                  数据类型别名声明区
*/

typedef 	uint8_t 	_TaskID;//任务ID
typedef 	uint8_t 	_TaskName;//任务名称
typedef 	uint8_t 	_TaskConfig;//任务控制量
typedef 	uint32_t 	_TaskStackSize;//任务栈长度
typedef 	uint32_t 	_TaskSemaphore;//任务信号量
typedef 	uint32_t 	_TaskTimeWheel;//任务时间轮片
typedef 	int8_t 		_TaskPriorityLevel;//任务优先级
typedef		uint32_t	_PostFormT;//任务邮箱
typedef 	uint32_t 	_TaskAddr;//任务地址
typedef		uint32_t	_TaskRealSP;//任务实时栈指针
typedef		uint32_t	_TaskTimeFlag;//任务时间标志
#if (osTaskParameterPass_Enable > 0)
typedef     uint32_t     _TaskParameterPass;//任务传参
#endif
#if (osPerformanceStatistics_Enable > 0) //开启了性能统计
typedef     uint16_t     _TaskOccupyTime;//任务占用时长
typedef     uint16_t      _TaskOccupyRatio;//任务占用比
#endif


typedef struct
{
	_TaskRealSP			RealSP;				//任务实时栈指针
	_TaskRealSP			RealSPb;			//任务实时栈指针
	_TaskID				ID;					//任务ID
	_TaskName*			Name; 				//任务名称
	_TaskConfig 		Config;  			//任务控制量	
#ifdef osSignalMutual_Enable
	_TaskPriorityLevel	PriorityLevelb;   	//任务备用优先级
#endif
//#ifdef osPost_Enable
	_PostFormT			PF;					//任务邮箱
//#endif
	_TaskTimeWheel 		TaskTimeWheel;			//任务时间轮片
	_TaskPriorityLevel 	PriorityLevel;			//任务优先级
	_TaskAddr*			Addr;					//任务地址
	_TaskTimeFlag		TimeFlag;			//任务时间标志
#if (osTaskParameterPass_Enable > 0)
	_TaskParameterPass*  ParameterPass;    //任务传参	
#endif

#if (osPerformanceStatistics_Enable > 0) //开启了性能统计
    _TaskOccupyTime      OccupyTime;    //任务占用时长
    _TaskOccupyRatio     OccupyRatio;    //任务占用比
#endif				
} _TaskHandle;
//}

//任务轮询表{
typedef struct
{
	_TaskHandle*		TaskHandle;	  //任务信息表 地址(任务句柄)
} _TaskList;
//}

//任务调度状态表{
typedef		uint8_t		_TaskListMaximumActivity;//任务最大活动量
typedef 	uint8_t		_TaskDispatchNum;//任务调度状态
typedef     uint8_t      _SwitchState;//任务调度计数
typedef		uint8_t		_TaskISRFlag;
typedef struct
{
	_SwitchState	    		SwitchState;//任务调度状态
	_TaskDispatchNum			DispatchNum;//任务调度计数
    _TaskListMaximumActivity	TaskListMax;//任务最大活动量
	_TaskISRFlag				ISRFlag;//中断状态
    
}_TaskSwitchState;
//}

typedef _TaskAddr _SIRQList;


extern _TaskHandle*	RunTaskHandle;//当前正在运行的任务表指针
extern _TaskList TaskList[TaskListLength];//任务轮询表
extern _TaskSwitchState TaskSwitchState;//任务调度状态表

extern _TaskHandle*	TaskHandle_Main;



	
/*
 *
 * @函数名称: osTaskInit
 *
 * @函数功能: 根据任务名称查询任务表地址
 *
 * @输入参数: 无	
 *
 * @返 回 值: osErrorValue - 函数错误返回值 (0:表示初始化成功，-1:表示初始化成功)
 *
 * @注    释: 无
*/
osErrorValue osTaskInit(void);	

osErrorValue osTaskSIRQInit(void);	

/*
 *
 * @函数名称: osTaskNameToTable
 *
 * @函数功能: 根据任务名称查询任务表地址
 *
 * @输入参数: TN		任务名称	
			 TA		任务地址
			 TSS  	任务栈长度
			 TTW  	任务时间轮片
			 TPL    任务优先级
			 TPP 	任务传参
			 TC 	任务配置（任务配置请参考 - Task_Set_Default - 这个宏定义）
	 *
 * @返 回 值: 0:注册失败		任务句柄值:注册成功
			  *
 * @注    释: 无
*/
_TaskHandle* osTaskLogin(
	_TaskName *TN,
	void*  TA,	
	_TaskStackSize  TSS,
	_TaskTimeWheel  TTW,
	_TaskPriorityLevel  TPL,
	#if (osTaskParameterPass_Enable > 0)
    void*  TPP, 
	#endif
    _TaskConfig  TC
);

_TaskHandle* osTaskLogin_Static(

	_TaskHandle* TaskHandle,
	_TaskName *TN,
	void*  TA,
	_TaskStackSize  TSS,
	_TaskTimeWheel  TTW,
	_TaskPriorityLevel  TPL,
	#if (osTaskParameterPass_Enable > 0)
    void*  TPP, 
	#endif
    _TaskConfig  TC
);
osErrorValue  osTaskLogout(_TaskHandle* TaskHandle);

osErrorValue	osTaskLogout_Static(_TaskHandle* TaskHandle);

/*
 *
 * @函数名称: osTaskNext
 *
 * @函数功能: 计算下一个要运行的任务
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void osTaskNext(void);
/*
 *
 * @函数名称: osTaskDelayMs
 *
 * @函数功能: 任务毫秒级阻塞延时
 *
 * @输入参数: ms	要延时的时长	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void osTaskDelayMs(uint32_t ms);
/*
 *
 * @函数名称: osTaskDelayUs
 *
 * @函数功能: 任务微秒级阻塞延时
 *
 * @输入参数: us	要延时的时长
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void osTaskDelayUs(uint32_t us);

//extern osErrorValue osTaskSwitch_State(void);
///*

// * @函数名称: osTaskAddrReplace

// * @函数版本: 1.0.0

// * @函数功能: 任务配置

// * @输入参数: 无	

// * @返 回 值: -1:配置时出现错误，0: 配置成功

// * @注    释: 无

//*/
//extern osErrorValue osTaskISR(_TaskHandle* TaskHandle);
/*
 *
 * @函数名称: osTaskAddrReplace
 *
 * @函数功能: 任务配置
 *
 * @输入参数: 无	
 *
 * @返 回 值: -1:配置时出现错误，0: 配置成功
 *
 * @注    释: 无
 *
 */
osErrorValue osTaskSet(_TaskHandle* TaskHandle,uint8_t Pv);
/*
 *
 * @函数名称: osTaskAddrReplace
 *
 * @函数功能: 任务地址替换
 *
 * @输入参数: 无	
 *
 * @返 回 值: -1:创建错误，0: 创建成功
 *
 * @注    释: 无
 *
 */
osErrorValue osTaskAddrReplace(_TaskHandle* TaskHandle,void* NewTA);
/*
 *
 * @函数名称: osTaskExit
 *
 * @函数功能: 任务结束
 *
 * @输入参数: 无	
 *
 * @返 回 值: 0: 成功结束
 *
 * @注    释: 无
 *
 */
osErrorValue osTaskExit(void);

osErrorValue osTaskErrorHardFault(uint32_t pc,uint32_t psp);


osErrorValue osTaskSpeedTest(void);

osErrorValue osTaskMonitor(void);


void osTaskSIRQ_Enable(_SIRQList* SIRQList_Addr);

osErrorValue osTaskSIRQLogin(_SIRQList* SIRQList_Addr,void* Addr);

void osTaskSIRQ(void);
#endif




