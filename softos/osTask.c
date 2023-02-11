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

_TaskSwitchState TaskSwitchState;//任务调度状态表

_TaskHandle*	TaskHandle_Main;
_TaskHandle*	TaskHandle_SIRQ;

_TaskHandle*	RunTaskHandle;//当前正在运行任务的句柄

_TaskHandle*    TaskHandleListHead;


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
osErrorValue osTaskInit(void)
{
    /***********************************任务轮询表初始化*********************************/
	TaskHandleListHead = NULL;

	TaskSwitchState.ISRFlag = 0;
	TaskSwitchState.SwitchState = TaskSwitch_Ready;
    /***********************************系统任务初始化**********************************/
	


	TaskHandle_Main = osTaskLogin("Main",(void*)0,Default_Stack_Size,TaskTimeWheelDefault,0,(void*)0,Task_Set_Default ); 
	if(TaskHandle_Main == NULL){

		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("Main 任务创建失败\n");
		#endif
		return (Error);//返回Error
	}


	TaskSwitchState.NextTaskHandle = TaskHandle_Main; 
	RunTaskHandle = TaskHandle_Main;//将即将运行的任务信息表的指针传送给正在运行任务表    
	osTime.TTWM = RunTaskHandle -> TaskTimeWheel;//将当前任务的时间轮片写入到时间记录器
	osTASK_START(&RunTaskHandle -> RealSP);//启动第一个任务

    return (OK);//返回OK
}		
osErrorValue osTaskSIRQInit(void)
{
	TaskHandle_SIRQ = osTaskLogin("SIRQ",osTaskSIRQ,400,TaskTimeWheelDefault,-127,(void*)0,Task_Set_Default); 
	if(TaskHandle_SIRQ == NULL){

		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("SIRQ 任务创建失败\n");
		#endif
		return (Error);//返回Error
	}
	return (OK);
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
	_TaskName *TN,//任务名称
	void*  TA,//任务地址	
	_TaskStackSize  TSS,//任务栈长度
	_TaskTimeWheel  TTW,//任务时间轮片
	_TaskPriorityLevel  TPL,//任务优先级
	#if (osTaskParameterPass_Enable > 0)
    void*  TPP, //任务传参
	#endif
    _TaskConfig  TC//任务配置
)
{
	uint8_t* Addr1;
	Addr1 = osMemoryMalloc(sizeof(_TaskHandle) + TSS);//为任务表分配内存
	if(Addr1 == NULL){//如果为空，就说明内存分配失败
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("注册任务时,任务分配内存失败 %s\n",TN);
		#endif
		return (NULL);//返回错误
	}
	return osTaskLogin_Static((_TaskHandle*)Addr1,TN,TA,TSS,TTW,TPL,TPP, TC);//这个时候内存分配完成，就进行进行普通注册
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
_TaskHandle* osTaskLogin_Static(
 
	_TaskHandle* TaskHandle,//任务表
	_TaskName *TN,//任务名称
	void*  TA,//任务地址
	_TaskStackSize  TSS,//任务栈长度
	_TaskTimeWheel  TTW,//任务时间轮片
	_TaskPriorityLevel  TPL,//任务优先级
	#if (osTaskParameterPass_Enable > 0)
    void*  TPP, //任务传参
	#endif
    _TaskConfig  TC//任务配置
)
{
	_TaskHandle* TaskHandleList_Buf1;
	_TaskHandle* TaskHandleList_Buf2;
	uint8_t* StackAddr = (uint8_t*)TaskHandle + sizeof(_TaskHandle);
#if (osCriticalToProtect_Enable > 0)//启用了临界保护
	osProtect_ENABLE();//进入保护
#endif
#if (osFPU_Enable > 0) //启用了FPU
	if(TSS < 320 || (TSS % 2) != 0){//如果启用了浮点硬件，至少任务栈大小应大于80*4字节
#if (osCriticalToProtect_Enable > 0)//启用了临界保护
		osProtect_DISABLE();//退出保护
#endif
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("注册任务时任务栈内存太小 %s\n" ,TN);
		#endif
		return (NULL);//返回错误
	}
#else
    if(TSS < 200 || (TSS % 2) != 0){//如果没有启用了浮点硬件，至少任务栈大小也应大于50*4字节
#if (osCriticalToProtect_Enable > 0)//启用了临界保护
		osProtect_DISABLE();//退出保护
#endif
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("注册任务时任务栈内存太小 %s\n" ,TN);
		#endif
		return (NULL);//返回错误
	}
#endif
	TaskHandle -> Name = TN;//写入任务名称
	TaskHandle -> Addr = TA;////写入任务地址
	TSS -= 1;
    TaskHandle -> RealSPb = TaskHandle -> RealSP = (uint32_t)((uint32_t)StackAddr + TSS);//写入任务实时栈指针
    TaskHandle -> ParameterPass = TPP;//写入任务传参
	TaskHandle -> PriorityLevel = TPL;//写入任务优先级
	TaskHandle -> PriorityLevelb = TPL;//写入任务备用优先级

	if(TC == Task_Set_Default){//如果任务选择了"禁用任务"选项，则生效
        TaskHandle -> Config = Task_State_RB;//将任务设为创建态
    }else{
        osTaskSet(TaskHandle,TC);
    }

	TaskHandle	-> PF = NULL;//任务邮箱消息设为零

	#if (osClockTimePeriod > osClockTimePeriodStandard)//当时钟周期大于1000时，进行转换
	TTW = TTW / (osClockTimePeriod / osClockTimePeriodStandard);
	#endif

    if(TTW > 0){//如果任务时间轮片大于零，则直接传输当前时间轮片值
        TaskHandle -> TaskTimeWheel = TTW;//写入时间轮片
    }
    else{//否则，则使用默认值
        TaskHandle -> TaskTimeWheel = TaskTimeWheelDefault;//写入默认值时间轮片
    }



	

	if(TaskHandleListHead == NULL){
		TaskHandleListHead = TaskHandle;
		TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
	}else{
		TaskHandleList_Buf1  = (_TaskHandle*)TaskHandleListHead;
		if(TaskHandle -> PriorityLevel < TaskHandleList_Buf1 -> PriorityLevel){
			TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandleList_Buf1;
			while(TaskHandleList_Buf1 -> NextTaskHandle != (_NextTaskHandle*)TaskHandleListHead){
				TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
			}
			TaskHandleList_Buf1 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
			TaskHandleListHead = TaskHandle;
		}else{
			while(1){
				if(TaskHandle -> PriorityLevel < TaskHandleList_Buf1 -> PriorityLevel){
					TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandleList_Buf1;
					TaskHandleList_Buf2 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
					break;
				}else if(TaskHandleList_Buf1 -> NextTaskHandle == (_NextTaskHandle*)TaskHandleListHead){
					TaskHandleList_Buf1 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
					TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandleListHead;
					break;
				}
				TaskHandleList_Buf2 = TaskHandleList_Buf1;
				TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
			}
		}
	}



#if (osCriticalToProtect_Enable > 0)//启用了临界保护
	osProtect_DISABLE();//退出保护
#endif
	return (TaskHandle);//返回
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
osErrorValue  osTaskLogout(_TaskHandle* TaskHandle)
{

	if(osTaskLogout_Static(TaskHandle) != OK){
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("释放任务: 内存注销失败\n");
		#endif
		return (Error);//发生错误，返回错误
	}
	if(osMemoryFree(TaskHandle) != OK){
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("释放任务: 内存释放失败\n");
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
osErrorValue  osTaskLogout_Static(_TaskHandle* TaskHandle)
{

    #if (osCriticalToProtect_Enable > 0)//启用了临界保护
	osProtect_ENABLE();//进入保护
    #endif


  #if (osCriticalToProtect_Enable > 0)//启用了临界保护
	osProtect_DISABLE();//退出保护
  #endif
	return (OK);//无异常，返回OK
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
		while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//检查查询CPU是否已经被设为悬起态
		//如果悬起了，就会返回真值，就while循环，直到未来悬起
		RunTaskHandle -> TimeFlag = ms;
		osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_Up_DT);
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
	osTime.TTWM = osTime.TTWM + 1;
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
osErrorValue osTaskSwitch_State(void)
{
    register osErrorValue _tr0 = 1;
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
    TaskSwitchState.SwitchState = TaskSwitch_Run;
    //osTASK_HANGUP(&RunTaskHandle -> RealSP);//通过当前运行任务的栈指针,挂起当前的任务
    while(1){//启动下一个任务
		switch(TaskSwitchState.NextTaskHandle -> Config){//进行状态码分离操作，并传输给switch语句
				case Task_State_RB:
									TaskSwitchState.NextTaskHandle -> RealSP = TaskSwitchState.NextTaskHandle -> RealSPb;
									osTASK_Stack_Init(TaskSwitchState.NextTaskHandle -> ParameterPass,(void* )TaskSwitchState.NextTaskHandle -> Addr,(void* )osTaskExit,&TaskSwitchState.NextTaskHandle -> RealSP);//启动任务
				case Task_State_Up_IN://这个任务是主动挂起(挂起态)
				case Task_State_Up_TD://这个任务是轮片挂起(挂起态)	
				case Task_State_RE:	  //这个任务就绪了
									RunTaskHandle = TaskSwitchState.NextTaskHandle;//将即将运行的任务信息表的指针传送给正在运行任务表
									TaskSwitchState.NextTaskHandle = (_TaskHandle*)TaskSwitchState.NextTaskHandle -> NextTaskHandle;
									osTime.TTWM = RunTaskHandle -> TaskTimeWheel;//将当前任务的时间轮片写入到时间记录器
									TaskSwitchState.SwitchState = TaskSwitch_Ready;//将调度状态设为"未调度"
									#if (osPerformanceStatistics_Enable > 0)
									PS.TSC += 1;
									#endif
									return;//退出函数

				default:break;//意料之外!
			}
			TaskSwitchState.NextTaskHandle = (_TaskHandle*)TaskSwitchState.NextTaskHandle -> NextTaskHandle;
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
osErrorValue osTaskSet(_TaskHandle* TaskHandle,uint8_t Pv)
{

	if(TaskHandle != 0){//非自身
		switch(Pv){
			case Task_Set_Pause://暂停任务
									TaskHandle -> Config = Task_State_DI;//设为禁用态
									return (OK);//返回OK

			case Task_Set_Cont://继续任务
									TaskHandle -> Config = Task_State_Up_IN;//设为挂起态
									return (OK);//返回OK

			case Task_Set_Reboot://重启任务									
									TaskHandle -> Config = Task_State_RB;//
									return (OK);//返回OK
			case Task_Set_Start://立即启动任务
									while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
									TaskSwitchState.NextTaskHandle = TaskHandle;//把这个任务ID加载到任务调度计数中，这样任务调度才认识这个任务，否则将会向下调度
									osTaskSwitchConfig_Enable(TaskHandle,Task_State_Up_IN);
									return (OK);//返回OK
			case Task_Set_Up://挂起任务
								return (OK);

									
		}
	}else{//自身
		switch(Pv){
			case Task_Set_Pause://暂停任务
									while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
									osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_DI);
									return (OK);//返回OK

			case Task_Set_Cont://继续任务
									return (OK);//返回OK

			case Task_Set_Reboot://重启任务
									while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
									osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_RB);//触发任务切换
									return (OK);//返回OK
			case Task_Set_Start://立即启动任务
									return (OK);//返回OK
			case Task_Set_Up://挂起任务
								while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态								
								osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_Up_IN);//触发任务切换
								return (OK);

									
		}
	}
	#if (osTaskDebug_Enable > 0)
	osTaskErrorDebug("任务配置时不是正确的配置项 %s\n" ,RunTaskHandle -> Name);
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
osErrorValue osTaskExit(void)
{
	while(true){
		osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_ST);//触发任务切换
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
osErrorValue osTaskAddrReplace(_TaskHandle* TaskHandle,void* NewTA)
{
	if(TaskHandle == 0){
		RunTaskHandle -> Addr = NewTA;
		while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
		RunTaskHandle -> Config = Task_State_RB;//
		osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_RB);//触发任务切换
		return (OK);//返回OK

	}else{
		TaskHandle -> Addr = NewTA;
		TaskHandle -> Config = Task_State_RB;//
		return (OK);//返回OK
	}

}

osErrorValue osTaskErrorHardFault(uint32_t pc,uint32_t psp)
{
	#if (osTaskRunError_Enable > 0)
	uint8_t Count = 1;
	osTaskEnterIRQ();
	while(Count--){
		osTaskErrorDebug("\n\n\n名称为%s的任务发生“硬件错误”异常!!!\n",RunTaskHandle -> Name);
		osTaskErrorDebug("任务优先级:%d\n",RunTaskHandle -> PriorityLevel);
		osTaskErrorDebug("任务当前使用量:%d%%\n",RunTaskHandle -> OccupyRatio);
		osTaskErrorDebug("任务延时剩余时间:%d%ms\n任务单次最大运行时长:%dms\n",RunTaskHandle -> TimeFlag,RunTaskHandle -> TaskTimeWheel);
		osTaskErrorDebug("任务最一近状态:",0,0);
		switch(RunTaskHandle -> Config){
			case Task_State_Up_TD:osTaskErrorDebug("轮片挂起\n");break;
			case Task_State_Up_IN:osTaskErrorDebug("主动挂起\n");break;
			case Task_State_Up_DT:osTaskErrorDebug("延时挂起\n");break;
			case Task_State_Up_SI:osTaskErrorDebug("信号挂起\n");break;
			case Task_State_Up_PT:osTaskErrorDebug("邮件挂起\n");break;
			case Task_State_DI:osTaskErrorDebug("禁用态\n");break;
			case Task_State_ST:osTaskErrorDebug("终止态\n");break;
			case Task_State_RB:osTaskErrorDebug("重启态\n");break;
			case Task_State_OP:osTaskErrorDebug("运行态\n");break;
			case Task_State_Up:osTaskErrorDebug("挂起态\n");break;
		}
		osTaskErrorDebug("任务邮箱状态:");
		if(RunTaskHandle -> PF == NULL){
			osTaskErrorDebug("空的\n");
		}
		else{
			osTaskErrorDebug("非空\n");
		}
		osTaskErrorDebug("任务栈总大小:%d字节\n任务栈剩余:%d字节\n",(uint32_t)RunTaskHandle -> RealSPb - (uint32_t)RunTaskHandle -  sizeof(_TaskHandle),psp - ((uint32_t)RunTaskHandle +  sizeof(_TaskHandle)));
		osTaskErrorDebug("任务异常处:%X\n",pc);
		osTaskErrorDebug("内存总量:%d字节\n内存余量:%d字节",osMemoryGetAllValue(),osMemoryGetFreeValue());
	}
	#endif
	#if (osTaskErrorSet == 1)
	osTaskSet(NULL,Task_Set_Reboot);
	#elif(osTaskErrorSet == 0)
	osTaskSet(NULL,Task_Set_Pause);
	#endif
	osTaskExitIRQ();
	return (OK);
}
/*
 *
 * @函数名称: osTaskSpeedTest
 *
 * @函数功能: 任务切换速度测试
 *
 * @输入参数: 无	
 *
 * @返 回 值: -1:创建错误，0: 创建成功
 *
 * @注    释: 无
 *
 */

osErrorValue osTaskSpeedTest(void)
{
	#if (osSpeedTest_Enable > 0)
	uint32_t t0,t1;
	RunTaskHandle -> Config = Task_State_Up_IN;
	t0 = SysTick->VAL;
	osTaskSwitch_Enable();//触发任务切换
	t1 = SysTick->VAL;
	#if (osPerformanceStatistics_Enable > 0)
	PS.TSSU = (t0 - t1) / (osCPU_Freq / 8);
	#endif
	#if (osTaskDebug_Enable > 0)
	osTaskErrorDebug("任务切换速度测试\nt0=%d\nt1=%d\n切换速度=%fus\n",t0,t1,((t0 - t1) / (osCPU_Freq / 8))*1.0);
	#endif
	#endif
	return (OK);
}

osErrorValue osTaskMonitor(void)

{
	_TaskHandle* TaskHandleListBuf = TaskHandleListHead;;
	do{
		print("任务<%s>的使用量为:占用时长:%dms | 任务优先级:%d | 任务状态:",TaskHandleListBuf -> Name,TaskHandleListBuf -> OccupyRatio,TaskHandleListBuf -> PriorityLevel);
		if(TaskHandleListBuf != RunTaskHandle || TaskSwitchState.SwitchState != TaskSwitch_Ready){
			switch(TaskHandleListBuf -> Config){
				case Task_State_Up_TD:print("轮片挂起\n");break;
				case Task_State_Up_IN:print("主动挂起\n");break;
				case Task_State_Up_DT:print("延时挂起\n");break;
				case Task_State_Up_SI:print("信号挂起\n");break;
				case Task_State_Up_PT:print("邮件挂起\n");break;
				case Task_State_DI:print("禁用态\n");break;
				case Task_State_ST:print("终止态\n");break;
				case Task_State_RB:print("重启态\n");break;
				case Task_State_OP:print("运行态\n");break;
				case Task_State_Up:print("挂起态\n");break;
			}
		}
		else{
			print("正在运行\n");
		}
		TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
	}while(TaskHandleListBuf != TaskHandleListHead);

	
	print("CPU总使用量:%d%% = 任务 %d%% + 中断%d%% + 调度%d%%\n",PS.CTO + PS.CISRO + PS.CSO,PS.CTO,PS.CISRO,PS.CSO);
	if(PS.TSC*PS.TSSU > 1000){
		print("任务调度次数:%d | 预计耗时:%dms\n",PS.TSCb,PS.TSCb*PS.TSSU / 1000);
	}else{
		print("任务调度次数:%d | 预计耗时:%dus\n",PS.TSCb,PS.TSCb*PS.TSSU);
	}
	print("内存 总量:%d字节 | 余量:%d字节 | 可分配:%d字节 | 块数:%d\n",osMemoryGetAllValue(),osMemoryGetFreeValue(),osMemoryGetPassValue(),osMemorySum());
	tprint("系统已运行: %d天 %h小时 %m分钟 %s秒\n",osTime. TSRT);
	
	return (OK);
}
/*
 *
 * @函数名称: osTaskSIRQ_Enable
 *
 * @函数功能: 启动软中断
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void osTaskSIRQ_Enable(_SIRQList* SIRQList_Addr)
{
	TaskHandle_SIRQ -> ParameterPass = (_TaskParameterPass*)SIRQList_Addr;
	TaskHandle_SIRQ -> Config = Task_State_Up_IN;//主动挂起(挂起态)
	TaskSwitchState.NextTaskHandle = TaskHandle_SIRQ;//把这个任务ID加载到任务调度计数中，这样任务调度才认识这个任务，否则将会向下调度
	osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_Up_IN);
}
/*
 *
 * @函数名称: osTaskSIRQLogin
 *
 * @函数功能: 软中断注册
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
osErrorValue osTaskSIRQLogin(_SIRQList* SIRQList_Addr,void* Addr)
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

	while(1){
		//RunTaskHandle -> Config = Task_State_Up_SI;//主动挂起(挂起态) 
		osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_Up_SI);
		SIRQList_Addr = (_SIRQList*)RunTaskHandle -> ParameterPass;
		for(SIRQList_Count = 1; SIRQList_Count <= *SIRQList_Addr; SIRQList_Count++){
			Jump((uint32_t*)SIRQList_Addr[SIRQList_Count]);
		}
	}
	
}





