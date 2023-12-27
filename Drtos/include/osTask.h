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
#ifndef __osTask_H_
#define __osTask_H_
/**
 *
 * @file osTask.h
 *
 * @brief 
 *
 * @note 
 *
 */



//任务状态{
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
#define Task_State_RB	  0x01u//创建态
/*
重启态: 
这个任务正在等待重启中
*/
#define Task_State_OP	  0x03u//运行态
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

#define Task_Set_OSCore		0x0Fu//

#define Task_Set_StopAutoFree	0x80
//}


//装载设置{
#define Load_Only	0x00
#define Load_Create	0x01
#define Load_Stack	0x02
//}


#if (osCriticalToProtect_Config > 0)//启用了临界保护
/**
 *
 * @name osProtect_DISABLE
 *
 * @brief 退出临界保护
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osProtect_DISABLE() 			osLinkISREnable()
/**
 *
 * @name osProtect_DISABLE
 *
 * @brief 进入临界保护
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osProtect_ENABLE() 				osLinkISRDisable()
#endif
/**
 *
 * @name osTaskSwitch
 *
 * @brief 触发任务上下文切换
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
//#define osTaskSwitch() 			do{osTaskGetSwitchQueue()++; ISR_Touch();}while(0);
#define osTaskSwitch(a)				do{OsTaskNextTaskHandle = a;OsTimeTaskTimeWheel = OsTaskNextTaskHandle -> Wheel;ISR_Touch();}while(0);
//#define osTaskSwitchChock()			do{osTaskNext();}while(0);
/**
 *
 * @name osTaskSwitchConfig_Config
 *
 * @brief 带配置触发任务上下文切换
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osTaskSwitchConfig(a,b,c)			do{b -> Config = c;OsTaskNextTaskHandle = a;OsTimeTaskTimeWheel = OsTaskNextTaskHandle -> Wheel;ISR_Touch();}while(0);
//#define osTaskSwitchChockConfig(a,b)		do{a -> Config = b;OsTaskNextTaskHandle = a;osTaskNext();}while(0);
//#define osTaskSwitchConfig(a,b)  do{a -> Config = b;osTaskGetSwitchQueue()++; ISR_Touch();}while(0);


/**
 *
 * @name osTaskEnterIRQ
 *
 * @brief 进入中断
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osTaskEnterIRQ()			osTaskGetOIRQFlag() += 1;
/**
 *
 * @name osTaskExitIRQ
 *
 * @brief 退出中断
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osTaskExitIRQ()				osTaskGetOIRQFlag() -= 1;
/**
 *
 * @name osTaskGetRunTaskHandle
 *
 * @brief 获取正在运行的任务句柄
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/

#define osTaskGetRunTaskHandle()		OsTaskRunTaskHandle

/**
 *
 * @name osTaskGetRunTaskHandle
 *
 * @brief 获取正在任务切换状态
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/


//#define osTaskGetSwitchQueue()			OsTaskSwitchQueue//任务调度请求队列


/**
 *
 * @name osTaskGetOIRQFlag
 *
 * @brief 获取中断状态
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/

#define osTaskGetOIRQFlag()			OsTaskISRFlag

/**
 *
 * @name osTaskGetRunTaskHandle
 *
 * @brief 获取正在任务切换状态
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/

#define osTaskGetNextTaskHandle()			OsTaskNextTaskHandle


/**
 *
 * @name osTaskGetRunTaskHandle
 *
 * @brief 获取任务句柄链表头部指针
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/

#define osTaskGetTaskHandleListHead()			OsTaskTaskHandleListHead





//任务句柄{
#if (osTaskName_Config > 0)
typedef 	uint8_t 	_TaskName;//任务名称
#endif
typedef 	uint8_t 	_TaskConfig;//任务控制量
typedef 	uint32_t 	_TaskStackSize;//任务栈长度
typedef 	uint32_t 	_TaskSemaphore;//任务信号量
typedef 	uint32_t 	_TaskWheel;//任务时间轮片
typedef 	int8_t 		_TaskLevel;//任务优先级
typedef		uint32_t	_PostFormT;//任务邮箱
typedef 	uint32_t 	_TaskAddr;//任务地址
typedef		uint32_t	_TaskRealSP;//任务实时栈指针
typedef		uint32_t	_TaskDelay;//任务时间标志
typedef		uint32_t	_NextTaskHandle;//任务时间标志
#if (osTaskArg_Config > 0)
typedef     uint32_t     _TaskArg;//任务传参
#endif
#if (osPerf_Config > 0) //开启了性能统计
typedef     uint16_t     _TaskOccupyTime;//任务占用时长
typedef     uint16_t     _TaskOccupyRatio;//任务占用比
#endif

typedef struct
{
	/*基本*/
	_TaskRealSP			RealSP;//任务实时栈指针
	_NextTaskHandle*	NextTaskHandle;
	_TaskAddr*			Addr;//任务地址
	_TaskConfig 		Config;//任务控制量
	/*扩展*/
	_TaskRealSP			Length;//任务实时栈指针
	_TaskLevel 			Level;//任务优先级
	_TaskWheel 			Wheel;//任务时间轮片
	_TaskDelay			Delay;//延时时间标志
#if (osTaskName_Config > 0)
	_TaskName*			Name;//任务名称
#endif	
#if (osSignal_Config & Signal_Mutual)
	_TaskLevel			Levelb;//任务备用优先级
#endif
#if (osTaskArg_Config > 0)
	_TaskArg*  			Arg;//任务传参	
#endif
#if (osPost_Config > 0)
	_TaskArg			Arg1;//任务邮箱
#endif
#if (osPerf_Config > 0)//开启了性能统计
    _TaskOccupyTime      OccupyTime;//任务占用时长
    _TaskOccupyRatio     OccupyRatio;//任务占用比
#endif				
} _TaskHandle;
//}


typedef     uint8_t     _SwitchState;//任务调度计数
typedef		uint8_t		_TaskISRFlag;
typedef		uint8_t 	_TaskSwitchQueue;


extern 	_TaskHandle*	OSCoreTaskHandle;//Main任务句柄
extern  _TaskHandle* 	volatile OsTaskRunTaskHandle;//正在运行的任务句柄
extern  _TaskHandle* 	volatile OsTaskNextTaskHandle;//下一个要运行的任务句柄
extern  _TaskSwitchQueue	OsTaskSwitchQueue;//任务调度请求队列
extern _TaskISRFlag		OsTaskISRFlag;//中断状态
extern _TaskHandle* 	OsTaskTaskHandleListHead;//任务句柄链表表头
extern uint16_t		OsTaskIdle;

typedef _TaskAddr 		_SIRQList;

	
/**
 *
 * @name osTaskInit
 *
 * @brief 根据任务名称查询任务句柄地址
 *
 * @param none	
 *
 * @retval OsErrorValue - 函数错误返回值 (0:表示初始化成功，-1:表示初始化成功)
 *
 * @note none
*/
OsErrorValue osTaskInit(void);	

OsErrorValue osTaskSIRQInit(void);	

void osTaskStart(void);

_TaskHandle* osTaskLoad(_TaskHandle* TaskHandle,uint8_t Config);

/**
 *
 * @name osTaskLogin
 *
 * @brief 任务注册(自动分配内存)
 *
 * @param TN	任务名称	
 * @param TA	任务地址
 * @param TSS  	任务栈长度
 * @param TTW  	任务时间轮片
 * @param TPL   任务优先级
 * @param TPP 	任务传参
 * @param TC 	任务配置（任务配置请参考 - Task_Set_Default - 这个宏定义）
 *
 * @retval 0:注册失败		任务句柄值:注册成功
 *
 * @note none
 */
_TaskHandle* osTaskLogin(
	void*  Addr,//任务地址	
	_TaskStackSize  StackSize,//任务栈长度
	_TaskLevel  Level,//任务优先级
	_TaskWheel  Wheel,//任务时间轮片
	#if (osTaskArg_Config > 0)
    void*  Arg, //任务传参
	#endif
	#if (osTaskName_Config > 0)
	_TaskName *Name,
	#endif
    _TaskConfig  Config//任务配置
);
/**
 *
 * @name osTaskLoginStatic
 *
 * @brief 任务注册(手动提供内存)
 *
 * @param TaskHandle 任务句柄(存储地址)
 * @param TN	任务名称	
 * @param TA	任务地址
 * @param TSS  	任务栈长度
 * @param TTW  	任务时间轮片
 * @param TPL   任务优先级
 * @param TPP 	任务传参
 * @param TC 	任务配置（任务配置请参考 - Task_Set_Default - 这个宏定义）
 *
 * @retval 0:注册失败		任务句柄值:注册成功
 *
 * @note none
 */

_TaskHandle* osTaskLoginStatic(
	_TaskHandle* TaskHandle,//任务句柄
	void*  Addr,//任务地址
	_TaskStackSize  StackSize,//任务栈长度
	_TaskLevel  Level,//任务优先级
	_TaskWheel  Wheel,//任务时间轮片
	#if (osTaskArg_Config > 0)
    void*  Arg, //任务传参
	#endif
	#if (osTaskName_Config > 0)
	_TaskName *Name,
#endif
    _TaskConfig  Config//任务配置
);

/**
 *
 * @name osTaskLogout
 *
 * @brief 任务注销(自动释放内存)
 *
 * @param TaskHandle 任务句柄
 *
 * @retval 0:注册失败		任务句柄值:注册成功
 *
 * @note none
 */
OsErrorValue  osTaskLogout(_TaskHandle* TaskHandle);
/**
 *
 * @name osTaskLogoutStatic
 *
 * @brief 任务注销(不释放内存)
 *
 * @param TaskHandle 任务句柄
 *
 * @retval 0:注册失败		任务句柄值:注册成功
 *
 * @note none
 */

OsErrorValue  osTaskLogoutStatic(_TaskHandle* TaskHandle);

/**
 *
 * @name osTaskNext
 *
 * @brief 计算下一个要运行的任务
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
 *
 */
void osTaskNext(void);
/**
 *
 * @name osTaskDelayMs
 *
 * @brief 任务毫秒级阻塞延时
 *
 * @param ms	要延时的时长	
 *
 * @retval none
 *
 * @note none
 *
 */
void osTaskDelayMs(uint32_t ms);
/**
 *
 * @name osTaskDelayUs
 *
 * @brief 任务微秒级阻塞延时
 *
 * @param us	要延时的时长
 *
 * @retval none
 *
 * @note none
 *
 */
void osTaskDelayUs(uint32_t us);

/**
 *
 * @name osTaskAddrReplace
 *
 * @brief 任务配置
 *
 * @param none	
 *
 * @retval -1:配置时出现错误，0: 配置成功
 *
 * @note none
 *
 */
OsErrorValue osTaskSet(_TaskHandle* TaskHandle,uint8_t Pv);
/**
 *
 * @name osTaskAddrReplace
 *
 * @brief 任务地址替换
 *
 * @param none	
 *
 * @retval -1:创建错误，0: 创建成功
 *
 * @note none
 *
 */
OsErrorValue osTaskAddrReplace(_TaskHandle* TaskHandle,void* NewTA);
/**
 *
 * @name osTaskExit
 *
 * @brief 任务结束
 *
 * @param none	
 *
 * @retval 0: 成功结束
 *
 * @note none
 *
 */
OsErrorValue osTaskExit(void);

/**
 *
 * @name osTaskSIRQ_Enable
 *
 * @brief 软中断使能
 *
 * @param 	SIRQList_Addr	软中断表表头
 *
 * @retval none
 *
 * @note none
 *
 */
void osTaskSIRQ_Enable(_SIRQList* SIRQList_Addr);
/**
 *
 * @name osTaskSIRQLogin
 *
 * @brief 软中断注册
 *
 * @param 	SIRQList_Addr	软中断表表头
 * @param 	Addr			软中断响应函数地址	
 *
 * @retval none
 *
 * @note none
 *
 */
OsErrorValue osTaskSIRQLogin(_SIRQList* SIRQList_Addr,void* Addr);
/**
 *
 * @name osTaskSIRQ
 *
 * @brief 软中断响应
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
 *
 */
void osTaskSIRQ(void);


#endif




