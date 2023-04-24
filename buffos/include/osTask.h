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
#ifndef __osTask_H_
#define __osTask_H_
/*
 *
 * @文件名称: osTask.h
 *
 * @文件内容: 
 *
 * @注    释: 
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

#define Task_Set_StopAutoFree	0x80
//}

//调度状态{
#define TaskSwitch_Ready  		0x00u//就绪
#define TaskSwitch_Wait   		0x01u//等待
#define TaskSwitch_Run    		0x02u//运行
//}



#if (osCriticalToProtect_Config > 0)//启用了临界保护
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
#define osProtect_DISABLE() 			osLinkISREnable()
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
#define osProtect_ENABLE() 				osLinkISRDisable()
#endif
/*
 *
 * @函数名称: osTaskSwitch_Config
 *
 * @函数功能: 触发任务上下文切换
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osTaskSwitch_Config() 			do{osTaskGetSwitchState() = TaskSwitch_Wait; ISR_Touch();}while(0);
/*
 *
 * @函数名称: osTaskSwitchConfig_Config
 *
 * @函数功能: 带配置触发任务上下文切换
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osTaskSwitchConfig_Config(a,b)  do{a -> Config = b;osTaskGetSwitchState() = TaskSwitch_Wait; ISR_Touch();}while(0);
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
#define osTaskEnterIRQ()			osTaskGetOIRQFlag() += 1;
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
#define osTaskExitIRQ()				osTaskGetOIRQFlag() -= 1;
/*
 *
 * @函数名称: osTaskGetRunTaskHandle
 *
 * @函数功能: 获取正在运行的任务句柄
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/

#define osTaskGetRunTaskHandle()		OsTaskRunTaskHandle

/*
 *
 * @函数名称: osTaskGetRunTaskHandle
 *
 * @函数功能: 获取正在任务切换状态
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/

#define osTaskGetSwitchState()			OsTaskSwitchState


/*
 *
 * @函数名称: osTaskGetOIRQFlag
 *
 * @函数功能: 获取中断状态
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/

#define osTaskGetOIRQFlag()			OsTaskISRFlag

/*
 *
 * @函数名称: osTaskGetRunTaskHandle
 *
 * @函数功能: 获取正在任务切换状态
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/

#define osTaskGetNextTaskHandle()			OsTaskNextTaskHandle


/*
 *
 * @函数名称: osTaskGetRunTaskHandle
 *
 * @函数功能: 获取任务句柄链表头部指针
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
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
	_TaskRealSP			RealSP;//任务实时栈指针
	_NextTaskHandle*	NextTaskHandle;
	_TaskConfig 		Config;//任务控制量
	_TaskWheel 			TaskWheel;//任务时间轮片
	_TaskLevel 			Level;//任务优先级
	_TaskAddr*			Addr;//任务地址
	_TaskRealSP			RealSPb;//任务实时栈指针
	_TaskDelay			TaskDelay;//任务时间标志
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

typedef struct
{
	_TaskRealSP			RealSP;//任务实时栈指针
	_NextTaskHandle*	NextTaskHandle;
	_TaskConfig 		Config;//任务控制量
	_TaskWheel 			TaskWheel;//任务时间轮片
	_TaskLevel 			Level;//任务优先级
	_TaskAddr*			Addr;//任务地址
	_TaskRealSP			RealSPb;//任务实时栈指针
	_TaskDelay		   TaskDelay;//任务时间标志
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
#if (osPerf_Config > 0) //开启了性能统计
    _TaskOccupyTime      OccupyTime;    //任务占用时长
    _TaskOccupyRatio     OccupyRatio;    //任务占用比
#endif				
} _QuickTaskHandle;

//}


typedef     uint8_t      _SwitchState;//任务调度计数
typedef		uint8_t		_TaskISRFlag;



extern _TaskHandle*		TaskHandle_Main;//Main任务句柄

extern  _TaskHandle* 	volatile OsTaskRunTaskHandle;//正在运行的任务句柄
extern  _TaskHandle* 	volatile OsTaskNextTaskHandle;//下一个要运行的任务句柄
extern _SwitchState	    OsTaskSwitchState;//任务调度状态
extern _TaskISRFlag		OsTaskISRFlag;//中断状态
extern _TaskHandle* 	OsTaskTaskHandleListHead;//任务句柄链表表头



typedef _TaskAddr 		_SIRQList;

	
/*
 *
 * @函数名称: osTaskInit
 *
 * @函数功能: 根据任务名称查询任务表地址
 *
 * @输入参数: 无	
 *
 * @返 回 值: OsErrorValue - 函数错误返回值 (0:表示初始化成功，-1:表示初始化成功)
 *
 * @注    释: 无
*/
OsErrorValue osTaskInit(void);	

OsErrorValue osTaskSIRQInit(void);	

/*
 *
 * @函数名称: osTaskLogin
 *
 * @函数功能: 任务注册(自动分配内存)
 *
 * @输入参数: TN	任务名称	
 * @输入参数: TA	任务地址
 * @输入参数: TSS  	任务栈长度
 * @输入参数: TTW  	任务时间轮片
 * @输入参数: TPL   任务优先级
 * @输入参数: TPP 	任务传参
 * @输入参数: TC 	任务配置（任务配置请参考 - Task_Set_Default - 这个宏定义）
 *
 * @返 回 值: 0:注册失败		任务句柄值:注册成功
 *
 * @注    释: 无
 */
_TaskHandle* osTaskLogin(
#if (osTaskName_Config > 0)
	_TaskName *TN,
#endif
	void*  TA,	
	_TaskStackSize  TSS,
	_TaskWheel  TTW,
	_TaskLevel  TPL,
	#if (osTaskArg_Config > 0)
    void*  TPP, 
	#endif
    _TaskConfig  TC
);
/*
 *
 * @函数名称: osTaskLoginStatic
 *
 * @函数功能: 任务注册(手动提供内存)
 *
 * @输入参数: TaskHandle 任务句柄(存储地址)
 * @输入参数: TN	任务名称	
 * @输入参数: TA	任务地址
 * @输入参数: TSS  	任务栈长度
 * @输入参数: TTW  	任务时间轮片
 * @输入参数: TPL   任务优先级
 * @输入参数: TPP 	任务传参
 * @输入参数: TC 	任务配置（任务配置请参考 - Task_Set_Default - 这个宏定义）
 *
 * @返 回 值: 0:注册失败		任务句柄值:注册成功
 *
 * @注    释: 无
 */

_TaskHandle* osTaskLoginStatic(

	_TaskHandle* TaskHandle,
#if (osTaskName_Config > 0)
	_TaskName *TN,
#endif
	void*  TA,
	_TaskStackSize  TSS,
	_TaskWheel  TTW,
	_TaskLevel  TPL,
#if (osTaskArg_Config > 0)
    void*  TPP, 
#endif
    _TaskConfig  TC
);

/*
 *
 * @函数名称: osTaskLogout
 *
 * @函数功能: 任务注销(自动释放内存)
 *
 * @输入参数: TaskHandle 任务句柄
 *
 * @返 回 值: 0:注册失败		任务句柄值:注册成功
 *
 * @注    释: 无
 */
OsErrorValue  osTaskLogout(_TaskHandle* TaskHandle);
/*
 *
 * @函数名称: osTaskLogoutStatic
 *
 * @函数功能: 任务注销(不释放内存)
 *
 * @输入参数: TaskHandle 任务句柄
 *
 * @返 回 值: 0:注册失败		任务句柄值:注册成功
 *
 * @注    释: 无
 */

OsErrorValue  osTaskLogoutStatic(_TaskHandle* TaskHandle);

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
OsErrorValue osTaskSet(_TaskHandle* TaskHandle,uint8_t Pv);
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
OsErrorValue osTaskAddrReplace(_TaskHandle* TaskHandle,void* NewTA);
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
OsErrorValue osTaskExit(void);

/*
 *
 * @函数名称: osTaskSIRQ_Enable
 *
 * @函数功能: 软中断使能
 *
 * @输入参数:	SIRQList_Addr	软中断表表头
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void osTaskSIRQ_Enable(_SIRQList* SIRQList_Addr);
/*
 *
 * @函数名称: osTaskSIRQLogin
 *
 * @函数功能: 软中断注册
 *
 * @输入参数:	SIRQList_Addr	软中断表表头
 * @输入参数:	Addr			软中断响应函数地址	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
OsErrorValue osTaskSIRQLogin(_SIRQList* SIRQList_Addr,void* Addr);
/*
 *
 * @函数名称: osTaskSIRQ
 *
 * @函数功能: 软中断响应
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void osTaskSIRQ(void);


#endif




