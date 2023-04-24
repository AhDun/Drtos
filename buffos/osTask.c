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
/*
 *
 * @文件名称: osTask.c
 *
 * @文件内容: 系统"任务"文件
 *
 * @注    释: 
 *
 */


#include "osConfig.h"
#include "osTask.h"



_TaskHandle*	TaskHandle_Main;
_TaskHandle*	TaskHandle_SIRQ;

 _TaskHandle* 	volatile OsTaskRunTaskHandle;
 _TaskHandle* 	volatile OsTaskNextTaskHandle;
_SwitchState	OsTaskSwitchState;//任务调度状态
_TaskISRFlag	OsTaskISRFlag;//中断状态
_TaskHandle* 	OsTaskTaskHandleListHead;



/*
 *
 * @函数名称: osTaskInit
 *
 * @函数功能: 任务系统初始化
 *
 * @输入参数: 无
 *
 * @返 回 值: -1:发生错误 / 0: 初始化成功
 *
 * @注    释: 无
 *
 */
OsErrorValue osTaskInit(void)
{
    /***********************************任务轮询表初始化*********************************/
	osTaskGetTaskHandleListHead() = NULL;

	osTaskGetOIRQFlag() = 0;
	osTaskGetSwitchState() = TaskSwitch_Ready;
    /***********************************系统任务初始化**********************************/
	


	TaskHandle_Main = osTaskLogin(
#if (osTaskName_Config > 0)
								MainName_Config,
#endif
								(void*)0,
								MainStackSize_Config,
								MainTimeWheel_Config,
								MainPriorityLevel_Config,
								MainPass_Config,
								MainSet_Config); 
	if(TaskHandle_Main == NULL){
		#if (osTaskLog_Config > 0)
		osLogE("osTaskInit","Main 任务创建失败\n");
		#endif
		return (Error);//返回Error
	}


	osTaskGetNextTaskHandle() = TaskHandle_Main; 
	osTaskGetRunTaskHandle() = TaskHandle_Main;//将即将运行的任务信息表的指针传送给正在运行任务表 
	osTaskGetNextTaskHandle() -> Config = Task_State_RE;//将这个任务的状态设为轮片挂起(挂起态)
	OsTimeGetTaskTimeWheel() = osTaskGetRunTaskHandle() -> TaskWheel;//将当前任务的时间轮片写入到时间记录器
#if (osTaskUseStack_Config > 0)
	osLinkUseEnable();//启动进程栈
#endif
    return (OK);//返回OK
}		

/*
 *
 * @函数名称: osTaskLogin
 *
 * @函数功能: 任务创建（自动分配内存）
 *
 * @输入参数:	TN 任务名称
 * @输入参数: 	TA 任务地址
 * @输入参数: 	TSS 任务栈长度
 * @输入参数: 	TTW 任务时间轮片
 * @输入参数: 	TPL 任务优先级
 * @输入参数: 	TPP 任务传参
 * @输入参数: 	TC 任务配置	
 *
 * @返 回 值: -1:创建错误 / 0: 创建成功
 *
 * @注    释:
 *
 */	


_TaskHandle* osTaskLogin(
#if (osTaskName_Config > 0)
	_TaskName *TN,
#endif
	void*  TA,//任务地址	
	_TaskStackSize  TSS,//任务栈长度
	_TaskWheel  TTW,//任务时间轮片
	_TaskLevel  TPL,//任务优先级
	#if (osTaskArg_Config > 0)
    void*  TPP, //任务传参
	#endif
    _TaskConfig  TC//任务配置
)
{
	uint8_t* Addr1;

	if(TSS < osTaskMinimumStackSize){//如果启用了浮点硬件，至少任务栈大小应大于80*4字节
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLogin","任务栈内存太小\n");
		#endif
		return (NULL);//返回错误
	}
	if((TSS % 2) != 0){//如果启用了浮点硬件，至少任务栈大小应大于80*4字节
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLogin","任务栈长度必须为偶数\n");
		#endif
		return (NULL);//返回错误
	}

	Addr1 = osMemoryMalloc(sizeof(_TaskHandle) + TSS);//为任务表分配内存
	if(Addr1 == NULL){//如果为空，就说明内存分配失败
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLogin","任务分配内存失败\n");
		#endif
		return (NULL);//返回错误
	}
#if (osTaskName_Config > 0)
	return osTaskLoginStatic((_TaskHandle*)Addr1,TN,TA,TSS,TTW,TPL,TPP, TC);//这个时候内存分配完成，就进行进行普通注册
#else
	return osTaskLoginStatic((_TaskHandle*)Addr1,TA,TSS,TTW,TPL,TPP, TC);//这个时候内存分配完成，就进行进行普通注册
#endif
}
/*
 *
 * @函数名称: 
 *
 * @函数功能: 任务创建
 *
 * @输入参数: 	TaskHandle 任务表
 * @输入参数: 	TN 任务名称
 * @输入参数: 	TA 任务地址
 * @输入参数: 	TSS 任务栈长度
 * @输入参数: 	TTW 任务时间轮片
 * @输入参数: 	TPL 任务优先级
 * @输入参数: 	TPP 任务传参
 * @输入参数: 	TC 任务配置	
 *
 * @返 回 值: -1:创建错误 / 0: 创建成功
 *
 * @注    释: 例如:
 *
 */
_TaskHandle* osTaskLoginStatic(
 
	_TaskHandle* TaskHandle,//任务表
#if (osTaskName_Config > 0)
	_TaskName *TN,
#endif
	void*  TA,//任务地址
	_TaskStackSize  TSS,//任务栈长度
	_TaskWheel  TTW,//任务时间轮片0
	_TaskLevel  TPL,//任务优先级
	#if (osTaskArg_Config > 0)
    void*  TPP, //任务传参
	#endif
    _TaskConfig  TC//任务配置
)
{
	_TaskHandle* TaskHandleList_Buf1;
	_TaskHandle* TaskHandleList_Buf2;
	uint8_t* StackAddr = (uint8_t*)TaskHandle + sizeof(_TaskHandle);
#if (osCriticalToProtect_Config > 0)//启用了临界保护
	osProtect_ENABLE();//进入保护
#endif

	if(TSS < osTaskMinimumStackSize){//如果启用了浮点硬件，至少任务栈大小应大于80*4字节
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLoginStatic","任务栈内存太小\n");
		#endif
		goto osTaskLoginStatic_Error;
	}
	if((TSS % 2) != 0){//如果启用了浮点硬件，至少任务栈大小应大于80*4字节
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLoginStatic","任务栈长度必须为偶数\n");
		#endif
		goto osTaskLoginStatic_Error;
	}

#if (osTaskName_Config > 0)
	TaskHandle -> Name = TN;//写入任务名称
#endif
	TaskHandle -> Addr = TA;////写入任务地址
	TSS -= 1;
	#if (osTaskStackDir_Config > 0)
    TaskHandle -> RealSPb = TaskHandle -> RealSP = (uint32_t)((uint32_t)StackAddr + TSS);//写入任务实时栈指针
	#else
	TaskHandle -> RealSPb = TaskHandle -> RealSP =  (uint32_t)StackAddr;
	#endif
    TaskHandle -> Arg = TPP;//写入任务传参
	TaskHandle -> Level = TPL;//写入任务优先级
	TaskHandle -> Levelb = TPL;//写入任务备用优先级

	switch(TC){
		case Task_Set_Default:TaskHandle -> Config = Task_State_RB;break;//将任务设为创建态
		default: osTaskSet(TaskHandle,TC);break;
	}
	


	TaskHandle	-> Arg1 = NULL;//任务邮箱消息设为零

	#if (osClockTimePeriod > osClockTimePeriodStandard)//当时钟周期大于1000时，进行转换
	TTW = TTW / (osClockTimePeriod / osClockTimePeriodStandard);
	#endif

    if(TTW > 0){//如果任务时间轮片大于零，则直接传输当前时间轮片值
        TaskHandle -> TaskWheel = TTW;//写入时间轮片
    }
    else{//否则，则使用默认值
        TaskHandle -> TaskWheel = TaskTimeWheelDefault;//写入默认值时间轮片
    }



	if(osTaskGetTaskHandleListHead() == NULL){
		osTaskGetTaskHandleListHead() = TaskHandle;
		TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
	}else{
		TaskHandleList_Buf1  = (_TaskHandle*)osTaskGetTaskHandleListHead();
		if(TaskHandle -> Level < TaskHandleList_Buf1 -> Level){
			TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandleList_Buf1;
			while(TaskHandleList_Buf1 -> NextTaskHandle != (_NextTaskHandle*)osTaskGetTaskHandleListHead()){
				TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
			}
			TaskHandleList_Buf1 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
			osTaskGetTaskHandleListHead() = TaskHandle;
		}else{
			for(;;){
				if(TaskHandle -> Level < TaskHandleList_Buf1 -> Level){
					TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandleList_Buf1;
					TaskHandleList_Buf2 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
					break;
				}else if(TaskHandleList_Buf1 -> NextTaskHandle == (_NextTaskHandle*)osTaskGetTaskHandleListHead()){
					TaskHandleList_Buf1 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
					TaskHandle -> NextTaskHandle = (_NextTaskHandle*)osTaskGetTaskHandleListHead();
					break;
				}
				TaskHandleList_Buf2 = TaskHandleList_Buf1;
				TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
			}
		}
	}



#if (osCriticalToProtect_Config > 0)//启用了临界保护
	osProtect_DISABLE();//退出保护
#endif
	return (TaskHandle);//返回

osTaskLoginStatic_Error:
#if (osCriticalToProtect_Config > 0)//启用了临界保护
	osProtect_DISABLE();//退出保护
#endif
	return (NULL);//返回错误


}
/*
 *
 * @函数名称: 	osTaskLogout
 *
 * @函数功能: 	任务注销
 *
 * @输入参数:	TaskHandle	任务句柄
 *
 * @返 回 值: 	-1:注销错误，0: 注销成功
 *
 * @注    释: 	这个任务注销会释放
 *
 */	
OsErrorValue  osTaskLogout(_TaskHandle* TaskHandle)
{

	if(osTaskLogoutStatic(TaskHandle) != OK){
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLogout","任务表注销失败\n");
		#endif
		return (Error);//发生错误，返回错误
	}
	
	if(osMemoryFree(TaskHandle) != OK){
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLogout","任务内存释放失败\n");
		#endif
		return (Error);//发生错误，返回错误
	}
	return (OK);//无异常，返回OK

}
/*
 *
 * @函数名称: 	osTaskLogout
 *
 * @函数功能: 	任务注销
 *
 * @输入参数:	TaskHandle	任务句柄
 *
 * @返 回 值: 	-1:注销错误，0: 注销成功
 *
 * @注    释: 	
 *
 */	
OsErrorValue  osTaskLogoutStatic(_TaskHandle* TaskHandle)
{
	_TaskHandle* TaskHandleList_Buf1 = osTaskGetTaskHandleListHead();
	_TaskHandle* TaskHandleList_Buf2;
    #if (osCriticalToProtect_Config > 0)//启用了临界保护
	osProtect_ENABLE();//进入保护
    #endif
	TaskHandleList_Buf1 = osTaskGetTaskHandleListHead();
	if(TaskHandle == osTaskGetTaskHandleListHead()){
		while(TaskHandleList_Buf1 -> NextTaskHandle != (_NextTaskHandle*)osTaskGetTaskHandleListHead()){
			TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
		}
		osTaskGetTaskHandleListHead() = (_TaskHandle*)osTaskGetTaskHandleListHead() -> NextTaskHandle;
		TaskHandleList_Buf1 -> NextTaskHandle = (_NextTaskHandle*)osTaskGetTaskHandleListHead();
		goto osTaskLogoutStatic_OK;
	}else{
		do{
			TaskHandleList_Buf2 = TaskHandleList_Buf1;
			TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
			if(TaskHandleList_Buf1 == TaskHandle){
				TaskHandleList_Buf2 -> NextTaskHandle = TaskHandleList_Buf1 -> NextTaskHandle;
				goto osTaskLogoutStatic_OK;
			}
		}while(TaskHandleList_Buf1 != osTaskGetTaskHandleListHead());
		goto osTaskLogoutStatic_Error;
	}
	
osTaskLogoutStatic_OK:
  #if (osCriticalToProtect_Config > 0)//启用了临界保护
	osProtect_DISABLE();//退出保护
  #endif
	return (OK);//无异常，返回OK
osTaskLogoutStatic_Error:
  #if (osCriticalToProtect_Config > 0)//启用了临界保护
	osProtect_DISABLE();//退出保护
  #endif
	return (Error);//无异常，返回OK

}

/*
 *
 * @函数名称: osTaskTime_Choke_ms
 *
 * @函数功能: 毫秒级任务延时
 *
 * @输入参数: ms(延时时长，单位毫秒)	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */	
void osTaskDelayMs(uint32_t ms)
{
	if(ms > 0){
		#if (osClockTimePeriod > osClockTimePeriodStandard)
		ms = ms /(osClockTimePeriod / osClockTimePeriodStandard);	
		#endif
		while(osTaskGetSwitchState() != TaskSwitch_Ready);//检查查询CPU是否已经被设为悬起态
		//如果悬起了，就会返回真值，就while循环，直到未来悬起
		osTaskGetRunTaskHandle() -> TaskDelay = ms;
		osTaskSwitchConfig_Config(osTaskGetRunTaskHandle(),Task_State_Up_DT);
	}
}
/*
 *
 * @函数名称: osTaskDelayUs
 *
 * @函数功能: 微秒级任务延时
 *
 * @输入参数: ms(延时时长，单位微秒)	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */	
void osTaskDelayUs(uint32_t us)
{
	OsTimeGetTaskTimeWheel() = OsTimeGetTaskTimeWheel() + 1;
	osTaskTimeUs();
}


/*
 *
 * @函数名称: osTaskSwitch_State
 *
 * @函数功能: 查询任务可切换态
 *
 * @输入参数: 无	
 *
 * @返 回 值: -1:创建错误，0: 创建成功
 *
 * @注    释: 无
 *
 */	
/*
OsErrorValue osTaskSwitch_State(void)
{
    register OsErrorValue _tr0 = 1;
    CPU_PendSV_STATE();//查询CPU是否已经被设为悬起态
	//如果悬起了，就会返回真值，就while循环，直到未来悬起
    if(_tr0){
        return TaskSwitch_Wait;//返回等待态
    }
    else{
        return TaskSwitch_Ready;///返回就绪态
    }
    
}
*/

/*
 *
 * @函数名称: osTaskNext
 *
 * @函数功能: 任务切换
 *
 * @输入参数: 无	
 *
 * @返 回 值: -1:创建错误，0: 创建成功
 *
 * @注    释: 无
 *
 */	
void osTaskNext(void)
{  
    osTaskGetSwitchState() = TaskSwitch_Run;
    //osTASK_HANGUP(&osTaskGetRunTaskHandle() -> RealSP);//通过当前运行任务的栈指针,挂起当前的任务
    for(;;){//启动下一个任务
		switch(osTaskGetNextTaskHandle() -> Config){//进行状态码分离操作，并传输给switch语句
				case Task_State_RB:
									osTaskGetNextTaskHandle() -> RealSP = osTaskGetNextTaskHandle() -> RealSPb;
									osTaskGetNextTaskHandle() -> Config = Task_State_RE;//将这个任务的状态设为轮片挂起(挂起态)
									osLinkTaskStackInit(osTaskGetNextTaskHandle() -> Arg,(void* )osTaskGetNextTaskHandle() -> Addr,(void* )osTaskExit,&osTaskGetNextTaskHandle() -> RealSP);//启动任务
				case Task_State_RE:	  //就绪态
									osTaskGetRunTaskHandle() = osTaskGetNextTaskHandle();//将即将运行的任务信息表的指针传送给正在运行任务表
									osTaskGetNextTaskHandle() = (_TaskHandle*)osTaskGetNextTaskHandle() -> NextTaskHandle;
									OsTimeGetTaskTimeWheel() = osTaskGetRunTaskHandle() -> TaskWheel;//将当前任务的时间轮片写入到时间记录器
									osTaskGetSwitchState() = TaskSwitch_Ready;//将调度状态设为"未调度"
									#if (osPerf_Config > 0)
									PerformanceStatistics.TSC += 1;
									#endif
									return;//退出函数

				default:break;//意料之外!
			}
			osTaskGetNextTaskHandle() = (_TaskHandle*)osTaskGetNextTaskHandle() -> NextTaskHandle;
			
    }
}
/*
 *
 * @函数名称: osTaskSet
 *
 * @函数功能: 任务配置
 *
 * @输入参数: 无	
 *
 * @返 回 值: -1:创建错误，0: 创建成功
 *
 * @注    释: 无
 *
 */
OsErrorValue osTaskSet(_TaskHandle* TaskHandle,uint8_t Pv)
{

	if(TaskHandle != 0){//非自身
		switch(Pv){
			case Task_Set_Pause://暂停任务
									TaskHandle -> Config = Task_State_DI;//设为禁用态
									return (OK);//返回OK

			case Task_Set_Cont://继续任务
									TaskHandle -> Config = Task_State_RE;//设为挂起态
									return (OK);//返回OK

			case Task_Set_Reboot://重启任务									
									TaskHandle -> Config = Task_State_RB;//
									return (OK);//返回OK
			case Task_Set_Start://立即启动任务
									while(osTaskGetSwitchState() != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
									osTaskGetNextTaskHandle() = TaskHandle;//把这个任务ID加载到任务调度计数中，这样任务调度才认识这个任务，否则将会向下调度
									osTaskSwitchConfig_Config(TaskHandle,Task_State_RE);
									return (OK);//返回OK
			case Task_Set_Up://挂起任务
								return (OK);

									
		}
	}else{//自身
		switch(Pv){
			case Task_Set_Pause://暂停任务
									while(osTaskGetSwitchState() != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
									osTaskSwitchConfig_Config(osTaskGetRunTaskHandle(),Task_State_DI);
									return (OK);//返回OK

			case Task_Set_Cont://继续任务
									return (OK);//返回OK

			case Task_Set_Reboot://重启任务
									while(osTaskGetSwitchState() != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
									osTaskSwitchConfig_Config(osTaskGetRunTaskHandle(),Task_State_RB);//触发任务切换
									return (OK);//返回OK
			case Task_Set_Start://立即启动任务
									return (OK);//返回OK
			case Task_Set_Up://挂起任务
								while(osTaskGetSwitchState() != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态								
								osTaskSwitchConfig_Config(osTaskGetRunTaskHandle(),Task_State_RE);//触发任务切换
								return (OK);

									
		}
	}
	#if (osTaskLog_Config > 0)
	osLogE("osTaskSet","任务配置时不是正确的配置项\n");
	#endif
	return (Error);
}
/*
 *
 * @函数名称: osTaskEnd
 *
 * @函数功能: 任务结束
 *
 * @输入参数: 无	
 *
 * @返 回 值: -1:创建错误，0: 创建成功
 *
 * @注    释: 无
 *
 */
OsErrorValue osTaskExit(void)
{
	for(;;){
		osTaskSwitchConfig_Config(osTaskGetRunTaskHandle(),Task_State_ST);//触发任务切换m
	}
}
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
OsErrorValue osTaskAddrReplace(_TaskHandle* TaskHandle,void* NewTA)
{
	if(TaskHandle == 0){
		osTaskGetRunTaskHandle() -> Addr = NewTA;
		while(osTaskGetSwitchState() != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
		osTaskGetRunTaskHandle() -> Config = Task_State_RB;//
		osTaskSwitchConfig_Config(osTaskGetRunTaskHandle(),Task_State_RB);//触发任务切换
		return (OK);//返回OK

	}else{
		TaskHandle -> Addr = NewTA;
		TaskHandle -> Config = Task_State_RB;//
		return (OK);//返回OK
	}

}

#if (SIRQ_Config > 0)
/*
 *
 * @函数名称: osTaskSIRQInit
 *
 * @函数功能: 软中断初始化
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
OsErrorValue osTaskSIRQInit(void)
{
	TaskHandle_SIRQ = osTaskLogin(
							SIRQName_Config,
							osTaskSIRQ,
							SIRQStackSize_Config,
							SIRQTimeWheel_Config,
							SIRQPriorityLevel_Config,
							SIRQPass_Config,
							SIRQSet_Config); 
	if(TaskHandle_SIRQ == NULL){

		#if (osTaskLog_Config > 0)
		osLogE("osTaskSIRQInit","SIRQ 任务创建失败\n");
		#endif
		return (Error);//返回Error
	}
	return (OK);
}
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
void osTaskSIRQ_Enable(_SIRQList* SIRQList_Addr)
{
	TaskHandle_SIRQ -> Arg = (_TaskArg*)SIRQList_Addr;
	osTaskGetNextTaskHandle() = TaskHandle_SIRQ;//把这个任务ID加载到任务调度计数中，这样任务调度才认识这个任务，否则将会向下调度
	osTaskSwitchConfig_Config(TaskHandle_SIRQ,Task_State_RE);
}
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
OsErrorValue osTaskSIRQLogin(_SIRQList* SIRQList_Addr,void* Addr)
{
	SIRQList_Addr[++*SIRQList_Addr] = (_TaskAddr)Addr;
	return (OK);//返回错误
}
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
void osTaskSIRQ(void)
{
	_SIRQList* SIRQList_Addr;
	uint8_t SIRQList_Count;

	for(;;){
		//osTaskGetRunTaskHandle() -> Config = Task_State_Up_SI;//主动挂起(挂起态) 
		osTaskSwitchConfig_Config(osTaskGetRunTaskHandle(),Task_State_Up_SI);
		SIRQList_Addr = (_SIRQList*)osTaskGetRunTaskHandle() -> Arg;
		for(SIRQList_Count = 1; SIRQList_Count <= *SIRQList_Addr; SIRQList_Count++){
			osLinkJump((uint32_t*)SIRQList_Addr[SIRQList_Count]);
		}
	}
	
}

#endif




