/*
                                                  FILE-START
*/
/*

 *@文件名称: osTask.c

 *@文件内容: 系统"任务"文件

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@注    释: 

*/

/*
                                                  <引用文件区>
*/
#include "osConfig.h"
#include "osTask.h"
/*
                                                  <数据初始区>
*/
_TaskSwitchState TaskSwitchState;//任务调度状态表
_TaskHandle*	RunTaskHandle;//当前正在运行任务的信息表
_TaskList TaskList[TaskListLength];//任务轮询表

_TaskHandle*	TaskHandle_Main;

/*
                                                  <函数区>
*/
/*

 *@函数名称: osTaskInit

 *@函数版本: 1.0.0

 *@函数功能: 任务系统初始化

 *@输入参数: 无

 *@返 回 值: -1:发生错误 / 0: 初始化成功

 *@注    释: 无

*/
osErrorValue osTaskInit(void)
{
    uint32_t _tr0;
    /***********************************任务轮询表初始化*********************************/
    TaskSwitchState.TaskListMax = NULL;
    for(_tr0 = 0;_tr0 < TaskListLength;_tr0++){
        TaskList[_tr0].TaskHandle = (_TaskHandle*)NULL;
    }

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

	TaskSwitchState.DispatchNum = NULL;    
	RunTaskHandle = TaskList[TaskSwitchState.DispatchNum].TaskHandle;//将即将运行的任务信息表的指针传送给正在运行任务表
	TaskSwitchState.DispatchNum = TaskSwitchState.DispatchNum + 1;//轮盘指针向后移一位     
	osTime.TTWM = RunTaskHandle -> TaskTimeWheel;//将当前任务的时间轮片写入到时间记录器
	osTASK_START(&RunTaskHandle -> RealSP);//启动第一个任务
    return (OK);//返回OK
}		
/*

 *@函数名称: osTaskLogin

 *@函数版本: 1.0.0

 *@函数功能: 任务创建（自动分配内存）

 *@输入参数:  	1.任务名称 
				2.任务地址
				3.任务栈长度		
				4.任务时间轮片
				5.任务优先级
				6.任务传参
				7.任务配置

 *@返 回 值: -1:创建错误 / 0: 创建成功

 *@注    释:

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

 *@函数名称: 

 *@函数版本: 1.0.0

 *@函数功能: 任务创建

 *@输入参数: 	1.任务表
				2.任务名称
				3.任务地址
				5.任务栈长度		
				6.任务时间轮片
				7.任务优先级
				8.任务传参
				9.任务配置
				

 *@返 回 值: -1:创建错误 / 0: 创建成功

 *@注    释: 例如:

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
	int32_t _tr0,_tr1;
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
    TaskHandle -> ID = (_TaskID)TaskSwitchState.TaskListMax;//写入任务ID
	TaskHandle -> Name = TN;//写入任务名称
	TaskHandle -> Addr = TA;////写入任务地址
	TSS -= 1;
    TaskHandle -> RealSPb = TaskHandle -> RealSP = (uint32_t)((uint32_t)StackAddr + TSS);//写入任务实时栈指针
    TaskHandle -> ParameterPass = TPP;//写入任务传参
	TaskHandle -> PriorityLevel = TPL;//写入任务优先级
	TaskHandle -> PriorityLevelb = TPL;//写入任务备用优先级

	if(TC == Task_Set_Default){//如果任务选择了"禁用任务"选项，则生效
        TaskHandle -> Config = Task_State_RB;//将任务设为创建态
    }
    else{
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


	if(TaskSwitchState.TaskListMax > (TaskListLength - 1)){//检查任务轮询表指针是否大于任务轮询表的长度，如果大于则进入
#if (osCriticalToProtect_Enable > 0)//启用了临界保护
		osProtect_DISABLE();//退出保护
#endif
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("注册任务时,任务量数量已最大 %s\n",TN);
		#endif
		return (NULL);//返回错误
	}
	for(_tr0 = 0;_tr0 < TaskSwitchState.TaskListMax;_tr0++){//对任务轮询表进行正向遍历
		if(TaskList[_tr0].TaskHandle -> PriorityLevel > TPL || TaskList[_tr0].TaskHandle == (_TaskHandle*)NULL){//如果当前任务优先级大于表中任务任务的优先级，或者，当前指针指向的表为空，则进入
			break;//退出循环
		}
	}
	for(_tr1 = TaskSwitchState.TaskListMax - 1;_tr1 >= 0; _tr1--){//对任务轮询表进行反向遍历
		if(TaskList[_tr1].TaskHandle !=  (_TaskHandle*)NULL){//如果当前指针指向的表为了空，则进入
			break;//退出循环
		}
	}
	_tr1++;//对其反向遍历结果，进行加一
	for(;_tr1 >= _tr0;_tr1--){//将表中数据进行对应的移位
		TaskList[_tr1].TaskHandle = TaskList[_tr1 - 1].TaskHandle;//进行
	}
	TaskList[_tr0].TaskHandle = TaskHandle;//将当前任务写入表中

	TaskSwitchState.TaskListMax++;//表指针加一 

	for(_tr0 = NULL;_tr0 < TaskSwitchState.TaskListMax;_tr0++){//重新计算任务ID
		TaskList[_tr0].TaskHandle -> ID = _tr0;
	}


#if (osCriticalToProtect_Enable > 0)//启用了临界保护
	osProtect_DISABLE();//退出保护
#endif
	return (TaskHandle);//返回
}
	
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

 *@函数名称: osTaskLogout

 *@函数版本: 1.0.0

 *@函数功能: 任务写入注销写入

 *@输入参数: _TaskHandle* TaskHandle //任务信息表指针

 *@返 回 值: -1:注销错误，0: 注销成功

 *@注    释: 在不启用任务栈自动分配的情况下调用的任务注销函数

*/
osErrorValue  osTaskLogout_Static(_TaskHandle* TaskHandle)
{
	int32_t _tr0,_tr1;//定义变量
    #if (osCriticalToProtect_Enable > 0)//启用了临界保护
	osProtect_ENABLE();//进入保护
    #endif
	for(_tr0 = 0;_tr0 < TaskListLength;_tr0++){//根据任务轮询表长度，进行遍历
		if(TaskList[_tr0].TaskHandle == TaskHandle){//如果当前任务ID与任务轮询表当前所指向的任务ID相同，就进入
			break;//退出当前循环
		}
	}
	if(_tr0 == TaskListLength || TaskSwitchState.TaskListMax == 0){//如果_tr0的值是任务轮询表长度，或者任务最大活动量为零时，就进入
		#if (osCriticalToProtect_Enable > 0)//启用了临界保护
		osProtect_DISABLE();//退出保护
		#endif
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("释放任务: 未知\n");
		#endif
		return (Error);//发生错误，返回错误
	}
	for(_tr1 = TaskSwitchState.TaskListMax;_tr1 >= 0; _tr1--){//根据任务最大活动量，进行遍历
		if(TaskList[_tr1].TaskHandle !=  (_TaskHandle*)NULL){//如果当前任务表的指针为空，就进入
			break;//退出当前循环
		}
	}
	/*
	这个时候
	_tr0 = 指向对应的任务ID的下标值
	_tr1 = 任务轮询表的尾端
	*/
	for(;_tr0 + 1 != (_tr1 + 1);_tr0++){//根据指向对应的任务ID的下标值和任务轮询表的尾端，进行遍历
		//指向对应的任务ID的下标值的下一个数据开始
		TaskList[_tr0].TaskHandle = TaskList[_tr0 + 1].TaskHandle ;//进行数组前移
		//指向对应的任务ID的下标指向的数组中值会被后一项的数组的值覆盖掉
	}
	TaskList[_tr1].TaskHandle = (_TaskHandle*)NULL ;//将任务轮询表的尾端清零
	TaskSwitchState.TaskListMax--;//任务最大活动量减一
	
	for(_tr0 = NULL;_tr0 < TaskSwitchState.TaskListMax;_tr0++){//重新计算任务ID
		TaskList[_tr0].TaskHandle -> ID = _tr0;
	}

  #if (osCriticalToProtect_Enable > 0)//启用了临界保护
	osProtect_DISABLE();//退出保护
  #endif
	return (OK);//无异常，返回OK
}

/*

 *@函数名称: osTaskTime_Choke_ms

 *@函数版本: 1.0.0

 *@函数功能: 毫秒级任务延时

 *@输入参数: ms(延时时长，单位毫秒)	

 *@返 回 值: 0: 时间阻塞成功

 *@注    释: 无

*/	
osErrorValue osTaskDelayMs(uint32_t ms)
{
    if(ms > 0){//不特别
		#if (osClockTimePeriod > osClockTimePeriodStandard)
		ms = ms /(osClockTimePeriod / osClockTimePeriodStandard);	
		#endif
		while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//检查查询CPU是否已经被设为悬起态
		//如果悬起了，就会返回真值，就while循环，直到未来悬起
		//RunTaskHandle -> Config &= TIT_Task_State_TC_RST;//清除正在运行任务的状态位
		RunTaskHandle -> Config = Task_State_Up_DT;//将正在运行任务的状态设为延时挂起(等待态)
		RunTaskHandle -> TimeFlag = ms;
		osTaskSwitch_Enable();
    }
	return (OK);
}
/*

 *@函数名称: osTaskDelayUs

 *@函数版本: 1.0.0

 *@函数功能: 微秒级任务延时

 *@输入参数: ms(延时时长，单位微秒)	

 *@返 回 值: 0: 时间阻塞成功

 *@注    释: 无

*/	
osErrorValue osTaskDelayUs(uint32_t us)
{
	osTime.TTWM = osTime.TTWM + 1;
	osTaskTimeUs();
	return (OK);
}


/*

 *@函数名称: osTaskSwitch_State

 *@函数版本: 1.0.0

 *@函数功能: 查询任务可切换态

 *@输入参数: 无	

 *@返 回 值: -1:创建错误，0: 创建成功

 *@注    释: 无

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

 *@函数名称: osTaskNext

 *@函数版本: 1.0.0

 *@函数功能: 任务切换

 *@输入参数: 无	

 *@返 回 值: -1:创建错误，0: 创建成功

 *@注    释: 无

*/	
void osTaskNext(void)
{  
    TaskSwitchState.SwitchState = TaskSwitch_Run;
    //osTASK_HANGUP(&RunTaskHandle -> RealSP);//通过当前运行任务的栈指针,挂起当前的任务
    while(1){//启动下一个任务
		for(;TaskSwitchState.DispatchNum < TaskSwitchState.TaskListMax;TaskSwitchState.DispatchNum++){//进行遍历
			switch(TaskList[TaskSwitchState.DispatchNum].TaskHandle -> Config){//进行状态码分离操作，并传输给switch语句
					case Task_State_RB:
										TaskList[TaskSwitchState.DispatchNum].TaskHandle -> RealSP = TaskList[TaskSwitchState.DispatchNum].TaskHandle -> RealSPb;
										osTASK_Stack_Init(TaskList[TaskSwitchState.DispatchNum].TaskHandle -> ParameterPass,(void* )TaskList[TaskSwitchState.DispatchNum].TaskHandle -> Addr,(void* )osTaskExit,&TaskList[TaskSwitchState.DispatchNum].TaskHandle -> RealSP);//启动任务
					case Task_State_Up_IN://这个任务是主动挂起(挂起态)
					case Task_State_Up_TD://这个任务是轮片挂起(挂起态)	
					case Task_State_RE:	  //这个任务就绪了
										RunTaskHandle = TaskList[TaskSwitchState.DispatchNum].TaskHandle;//将即将运行的任务信息表的指针传送给正在运行任务表
										TaskSwitchState.DispatchNum = TaskSwitchState.DispatchNum + 1;//轮盘指针向后移一位  
										osTime.TTWM = RunTaskHandle -> TaskTimeWheel;//将当前任务的时间轮片写入到时间记录器
										TaskSwitchState.SwitchState = TaskSwitch_Ready;//将调度状态设为"未调度"
										#if (osPerformanceStatistics_Enable > 0)
										PS.TSC += 1;
										#endif
										return;//退出函数

					default:break;//意料之外!
				}
		}
		TaskSwitchState.DispatchNum = NULL;//清空任务调度计数
    }
}
/*

 *@函数名称: osTaskSet

 *@函数版本: 1.0.0

 *@函数功能: 任务配置

 *@输入参数: 无	

 *@返 回 值: -1:创建错误，0: 创建成功

 *@注    释: 无

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
									TaskHandle -> Config = Task_State_Up_IN;//主动挂起(挂起态)
									TaskSwitchState.DispatchNum = TaskHandle -> ID;//把这个任务ID加载到任务调度计数中，这样任务调度才认识这个任务，否则将会向下调度
									osTaskSwitch_Enable();
									return (OK);//返回OK
			case Task_Set_Up://挂起任务
								return (OK);

									
		}
	}else{//自身
		switch(Pv){
			case Task_Set_Pause://暂停任务
									while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
									RunTaskHandle -> Config = Task_State_DI;//设为禁用态
									osTaskSwitch_Enable();//触发任务切换
									return (OK);//返回OK

			case Task_Set_Cont://继续任务
									return (OK);//返回OK

			case Task_Set_Reboot://重启任务
									while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
									RunTaskHandle -> Config = Task_State_RB;//
									osTaskSwitch_Enable();//触发任务切换
									return (OK);//返回OK
			case Task_Set_Start://立即启动任务
									return (OK);//返回OK
			case Task_Set_Up://挂起任务
								while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态								
								RunTaskHandle -> Config = Task_State_Up_IN;
								osTaskSwitch_Enable();//触发任务切换
								return (OK);

									
		}
	}
	#if (osTaskDebug_Enable > 0)
	osTaskErrorDebug("任务配置时不是正确的配置项 %s\n" ,RunTaskHandle -> Name);
	#endif
	return (Error);
}
/*

 *@函数名称: osTaskEnd

 *@函数版本: 1.0.0

 *@函数功能: 任务结束

 *@输入参数: 无	

 *@返 回 值: -1:创建错误，0: 创建成功

 *@注    释: 无

*/
osErrorValue osTaskExit(void)
{
	while(true){
		RunTaskHandle -> Config = Task_State_ST;//设为终止态
		osTaskSwitch_Enable();//触发任务切换
	}
}
/*

 *@函数名称: osTaskAddrReplace

 *@函数版本: 1.0.0

 *@函数功能: 任务地址替换

 *@输入参数: 无	

 *@返 回 值: -1:创建错误，0: 创建成功

 *@注    释: 无

*/
osErrorValue osTaskAddrReplace(_TaskHandle* TaskHandle,void* NewTA)
{
	if(TaskHandle == 0){
		RunTaskHandle -> Addr = NewTA;
		while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
		RunTaskHandle -> Config = Task_State_RB;//
		osTaskSwitch_Enable();//触发任务切换
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
	osTaskEnterISR();
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
		osTaskErrorDebug("任务栈总大小:%d字节\n任务栈剩余:%d字节\n",(uint32_t)RunTaskHandle -> RealSPb - (uint32_t)RunTaskHandle -  sizeof(_TaskHandle),(uint32_t)RunTaskHandle -> RealSPb - psp);
		osTaskErrorDebug("任务异常处:%X\n",pc);
		osTaskErrorDebug("内存总量:%d字节\n内存余量:%d字节",osMemoryGetAllValue(),osMemoryGetFreeValue());
	}
	#endif
	#if (osTaskErrorSet == 1)
	osTaskSet(NULL,Task_Set_Reboot);
	#elif(osTaskErrorSet == 0)
	osTaskSet(NULL,Task_Set_Pause);
	#endif
	osTaskExitISR();
	return (OK);
}
/*

 *@函数名称: osTaskSpeedTest

 *@函数版本: 1.0.0

 *@函数功能: 任务切换速度测试

 *@输入参数: 无	

 *@返 回 值: -1:创建错误，0: 创建成功

 *@注    释: 无

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
	uint8_t _tr0;
	for(_tr0 = NULL;_tr0 < TaskSwitchState.TaskListMax;_tr0++){//对每一个任务进行遍历
		print("任务<%s>的使用量为:占用时长:%dms | 任务优先级:%d | 任务状态:",TaskList[_tr0].TaskHandle -> Name,TaskList[_tr0].TaskHandle -> OccupyRatio,TaskList[_tr0].TaskHandle -> PriorityLevel);
		if(TaskList[_tr0].TaskHandle != RunTaskHandle || TaskSwitchState.SwitchState != TaskSwitch_Ready){
			switch(TaskList[_tr0].TaskHandle -> Config){
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
	}
	
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
                                                  FILE-END
*/

