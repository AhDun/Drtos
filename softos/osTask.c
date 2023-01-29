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
uint32_t NULL_Value = 0;
TaskDispatchStateTable TST;//任务调度状态表
TaskInfoTable*	RunTask_TIT;//当前正在运行任务的信息表
TaskList TL[TaskListLength];//任务轮询表

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
    TST.TLMA = NULL;
    for(_tr0 = 0;_tr0 < TaskListLength;_tr0++){
        TL[_tr0].TITA = (TaskInfoTable*)TaskList_NULLValue;
    }

	TST.TISRF = 0;
	TST.TSS = TaskSwitch_Ready;
    /***********************************系统任务初始化**********************************/
#if (osTaskAutoStack_Enable > 0)//启用任务栈自动分配
	if(osTaskLogin("Main",(void*)0,Default_Stack_Size,TaskTimeWheelDefault,0,(void*)0,Task_Set_Default ) == NULL){

		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("Main 任务创建失败\n");
		#endif
		return (Error);//返回Error
	}
#else
	if(osTaskLogin( 
	&Main_TaskInfoTable, 	//任务表
	"Main",					//任务名称
	(void*)0,				//任务地址
	Main_Stack,				//任务栈地址
	Default_Stack_Size,		//任务栈长度
	TaskTimeWheelDefault,	//任务时间轮片
	0,						//任务优先级
    (void*)0,				//任务传参   
    Task_Set_Default    	//任务配置
	) == Error){
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("Main 任务创建失败\n");
		#endif
		return (Error);//返回Error
	}
#endif

	TST. TDN = NULL;    
	RunTask_TIT = TL[TST. TDN].TITA;//将即将运行的任务信息表的指针传送给正在运行任务表
	TST. TDN = TST. TDN + 1;//轮盘指针向后移一位     
	osTime.TTWM = RunTask_TIT -> TTW;//将当前任务的时间轮片写入到时间记录器
	osTASK_START(&RunTask_TIT -> TRS);//启动第一个任务
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


#if (osTaskAutoStack_Enable > 0)//启用任务栈自动分配
TaskInfoTable* osTaskLogin(
	_TaskName *TN,//任务名称
	void*  TA,//任务地址	
	_TaskStackSize  TSS,//任务栈长度
	_TaskTimeWheel  TTW,//任务时间轮片
	_TaskPriorityLevel  TPL,//任务优先级
    void*  TPP, //任务传参
    _TaskConfig  TC//任务配置
)
{
	void* TIT;
	void* TH;
	TaskInfoTable* TaskInfoTable_Buf;

	TIT = osMemoryMalloc(sizeof(TaskInfoTable));//为任务表分配内存
	if(TIT == NULL){//如果为空，就说明内存分配失败
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("注册任务时,任务表分配内存失败 %s\n",TN);
		#endif
		return (NULL);//返回错误
	}
	TH = osMemoryMalloc(TSS);//为任务栈分配内存
	if(TH == NULL){//如果为空，就说明内存分配失败
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("注册任务时,任务栈分配内存失败 %s\n",TN);
		#endif
		return (NULL);//返回错误
	}
	TaskInfoTable_Buf = osTaskRegister_Write(TIT,TN,TA,TH,TSS,TTW,TPL,TPP, TC);//这个时候内存分配完成，就进行进行普通注册
	if(TaskInfoTable_Buf == NULL){//如果为错误值，就说明内存分配失败
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("注册任务时,任务注册失败 %s\n",TN);
		#endif
		return (NULL);//返回错误
	}
	return (TaskInfoTable_Buf);//
}
/*

 *@函数名称: osTaskRegister_Write（启用自动栈分配时） / osTaskLogin（没有启用自动栈分配时）

 *@函数版本: 1.0.0

 *@函数功能: 任务创建

 *@输入参数: 	1.任务表
				2.任务名称
				3.任务地址
				4.任务句柄
				5.任务栈长度		
				6.任务时间轮片
				7.任务优先级
				8.任务传参
				9.任务配置
				

 *@返 回 值: -1:创建错误 / 0: 创建成功

 *@注    释: 例如:

*/
TaskInfoTable* osTaskRegister_Write(
#else 
TaskInfoTable* osTaskLogin(
#endif 
	TaskInfoTable* TIT,//任务表
	_TaskName *TN,//任务名称
	void*  TA,//任务地址
	_TaskHandle* TH,//任务句柄	
	_TaskStackSize  TSS,//任务栈长度
	_TaskTimeWheel  TTW,//任务时间轮片
	_TaskPriorityLevel  TPL,//任务优先级
    void*  TPP, //任务传参
    _TaskConfig  TC//任务配置
)
{
	int32_t _tr0,_tr1;
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
    TIT -> TI = (_TaskID)TST.TLMA;//写入任务ID
	TIT -> TN = TN;//写入任务名称
	TIT -> TA = TA;////写入任务地址
	TIT -> TH = (uint32_t*)(((uint32_t)TH)+ (TSS - 1));//写入任务句柄
    TIT -> TRS = (uint32_t)(((uint32_t)TH)+ (TSS - 1));//写入任务实时栈指针
	TIT -> TSS = TSS;//写入任务栈长度
    TIT -> TPP = TPP;//写入任务传参

	TIT	-> PF = (uint32_t*)NULL_Value;//任务邮箱消息设为零

	#if (osClockTimePeriod > osClockTimePeriodStandard)//当时钟周期大于1000时，进行转换
	TTW = TTW / (osClockTimePeriod / osClockTimePeriodStandard);
	#endif

    if(TTW > 0){//如果任务时间轮片大于零，则直接传输当前时间轮片值
        TIT -> TTW = TTW;//写入时间轮片
    }
    else{//否则，则使用默认值
        TIT -> TTW = TaskTimeWheelDefault;//写入默认值时间轮片
    }
	TIT -> TPL = TPL;//写入任务优先级
	TIT -> TPLb = TPL;//写入任务备用优先级

	if(TST.TLMA > (TaskListLength - 1)){//检查任务轮询表指针是否大于任务轮询表的长度，如果大于则进入
#if (osCriticalToProtect_Enable > 0)//启用了临界保护
		osProtect_DISABLE();//退出保护
#endif
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("注册任务时,任务量数量已最大 %s\n",TN);
		#endif
		return (NULL);//返回错误
	}
	for(_tr0 = 0;_tr0 < TST.TLMA;_tr0++){//对任务轮询表进行正向遍历
		if(TL[_tr0].TITA->TPL > TPL || TL[_tr0].TITA == (TaskInfoTable*)TaskList_NULLValue){//如果当前任务优先级大于表中任务任务的优先级，或者，当前指针指向的表为空，则进入
			break;//退出循环
		}
	}
	for(_tr1 = TST.TLMA - 1;_tr1 >= 0; _tr1--){//对任务轮询表进行反向遍历
		if(TL[_tr1].TITA !=  (TaskInfoTable*)TaskList_NULLValue){//如果当前指针指向的表为了空，则进入
			break;//退出循环
		}
	}
	_tr1++;//对其反向遍历结果，进行加一
	for(;_tr1 >= _tr0;_tr1--){//将表中数据进行对应的移位
		TL[_tr1].TITA = TL[_tr1 - 1].TITA;//进行
	}
	TL[_tr0].TITA = TIT;//将当前任务写入表中

	TST.TLMA++;//表指针加一 

	for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//重新计算任务ID
		TL[_tr0].TITA -> TI = _tr0;
	}

	if(TC == Task_Set_Default){//如果任务选择了"禁用任务"选项，则生效
        //TIT -> TC &= TIT_Task_State_TC_RST;//清除任务的确状态位
        TIT -> TC = Task_State_RB;//将任务设为创建态
    }
    else{
        //TIT -> TC &= TIT_Task_State_TC_RST;//清除任务的确状态位
        osTaskSet(TIT,TC);
    }
    //osTASK_Stack_Init(TIT ->TPP,(void* )TIT -> TA,(void* )osTaskExit,&TIT -> TRS);//启动任务
#if (osCriticalToProtect_Enable > 0)//启用了临界保护
	osProtect_DISABLE();//退出保护
#endif
	return (TIT);//返回
}
	

#if (osTaskAutoStack_Enable > 0)//启用任务栈自动分配
/*

 *@函数名称: osTaskLogout

 *@函数版本: 1.0.0

 *@函数功能: 任务注销

 *@输入参数: _TaskName *TN //任务名称	

 *@返 回 值: -1:注销错误，0: 注销成功

 *@注    释: 在启用任务栈自动分配的情况下调用的任务注销函数

*/
//osErrorValue osTaskLogout(_TaskName *TN)
/*

 *@函数名称: osTaskLogout_Write

 *@函数版本: 1.0.0

 *@函数功能: 任务写入注销写入

 *@输入参数: TaskInfoTable* TIT //任务信息表指针

 *@返 回 值: -1:注销错误，0: 注销成功

 *@注    释: 在启用任务栈自动分配的情况下的任务内部

*/
osErrorValue osTaskLogout_Write(TaskInfoTable* TIT)
#else 
/*

 *@函数名称: osTaskLogout

 *@函数版本: 1.0.0

 *@函数功能: 任务写入注销写入

 *@输入参数: TaskInfoTable* TIT //任务信息表指针

 *@返 回 值: -1:注销错误，0: 注销成功

 *@注    释: 在不启用任务栈自动分配的情况下调用的任务注销函数

*/
osErrorValue	osTaskLogout(TaskInfoTable* TIT)
#endif
{
	int32_t _tr0,_tr1;//定义变量
    #if (osCriticalToProtect_Enable > 0)//启用了临界保护
	osProtect_ENABLE();//进入保护
    #endif
	//TIT -> TC &= TIT_Task_State_TC_RST;//清除任务的状态位
	for(_tr0 = 0;_tr0 < TaskListLength;_tr0++){//根据任务轮询表长度，进行遍历
		if(TL[_tr0].TITA == TIT){//如果当前任务ID与任务轮询表当前所指向的任务ID相同，就进入
			break;//退出当前循环
		}
	}
	if(_tr0 == TaskListLength || TST.TLMA == 0){//如果_tr0的值是任务轮询表长度，或者任务最大活动量为零时，就进入
		#if (osCriticalToProtect_Enable > 0)//启用了临界保护
		osProtect_DISABLE();//退出保护
		#endif
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("释放任务: 未知\n");
		#endif
		return (Error);//发生错误，返回错误
	}
	for(_tr1 = TST.TLMA;_tr1 >= 0; _tr1--){//根据任务最大活动量，进行遍历
		if(TL[_tr1].TITA !=  (TaskInfoTable*)TaskList_NULLValue){//如果当前任务表的指针为空，就进入
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
		TL[_tr0].TITA = TL[_tr0 + 1].TITA ;//进行数组前移
		//指向对应的任务ID的下标指向的数组中值会被后一项的数组的值覆盖掉
	}
	TL[_tr1].TITA = (TaskInfoTable*)TaskList_NULLValue ;//将任务轮询表的尾端清零
	TST.TLMA--;//任务最大活动量减一
	
	for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//重新计算任务ID
		TL[_tr0].TITA -> TI = _tr0;
	}

  #if (osCriticalToProtect_Enable > 0)//启用了临界保护
	osProtect_DISABLE();//退出保护
  #endif
	return (OK);//无异常，返回OK
}

/*

 *@函数名称: osTaskNameToTable

 *@函数版本: 1.0.0

 *@函数功能: 任务句柄查询

 *@输入参数: _TaskName *TN	- 任务名称

 *@返 回 值: 0:查询错误，x: 任务句柄

 *@注    释: 无

*/
TaskInfoTable* osTaskNameToTable(_TaskName *TN)
{
	uint32_t _var0;
	for(_var0 = 0;_var0 < TST.TLMA;_var0++){//根据任务最大活动量，进行遍历
		if(StrComp((int8_t*)TN,(int8_t*)TL[_var0].TITA -> TN)){//
			return (TL[_var0].TITA);//返回任务ID
		}
	}
	#if (osTaskDebug_Enable > 0)
	osTaskErrorDebug("查询任务时没有找到对应的任务句柄 %s\n",TN);
	#endif
	return (NULL);//没有对应的任务ID,返回错误
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
		while(TST.TSS != TaskSwitch_Ready);//检查查询CPU是否已经被设为悬起态
		//如果悬起了，就会返回真值，就while循环，直到未来悬起
		//RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//清除正在运行任务的状态位
		RunTask_TIT -> TC = Task_State_Up_DT;//将正在运行任务的状态设为延时挂起(等待态)
		RunTask_TIT -> TTF = ms;
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
	osTaskTimeUs(us);
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
    TST.TSS = TaskSwitch_Run;
    //osTASK_HANGUP(&RunTask_TIT -> TRS);//通过当前运行任务的栈指针,挂起当前的任务
    while(1){//启动下一个任务
		for(;TST. TDN < TST.TLMA;TST. TDN++){//进行遍历
			switch(TL[TST. TDN].TITA -> TC){//进行状态码分离操作，并传输给switch语句
					case Task_State_RB:
										TL[TST. TDN].TITA -> TRS = (_TaskRealSP)(TL[TST. TDN].TITA -> TH);
										osTASK_Stack_Init(TL[TST. TDN].TITA ->TPP,(void* )TL[TST. TDN].TITA -> TA,(void* )osTaskExit,&TL[TST. TDN].TITA -> TRS);//启动任务
					case Task_State_Up_IN://这个任务是主动挂起(挂起态)
					case Task_State_Up_TD://这个任务是轮片挂起(挂起态)	
					case Task_State_RE:	  //这个任务就绪了
										RunTask_TIT = TL[TST. TDN].TITA;//将即将运行的任务信息表的指针传送给正在运行任务表
										TST. TDN = TST. TDN + 1;//轮盘指针向后移一位  
										osTime.TTWM = RunTask_TIT -> TTW;//将当前任务的时间轮片写入到时间记录器
										TST.TSS = TaskSwitch_Ready;//将调度状态设为"未调度"
										#if (osPerformanceStatistics_Enable > 0)
										PS.TSC += 1;
										#endif
										return;//退出函数

					default:break;//意料之外!
				}
		}
		TST.TDN = NULL;//清空任务调度计数
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
osErrorValue osTaskSet(TaskInfoTable* TIT,_Task_Set_Pv Pv)
{

	if(TIT != 0){//非自身
		switch(Pv){
			case Task_Set_Pause://暂停任务
									//TIT -> TC &= TIT_Task_State_TC_RST;//置位状态位
									TIT -> TC = Task_State_DI;//设为禁用态
									return (OK);//返回OK

			case Task_Set_Cont://继续任务
									//TIT -> TC &= TIT_Task_State_TC_RST;//置位状态位
									TIT -> TC = Task_State_Up_IN;//设为挂起态
									return (OK);//返回OK

			case Task_Set_Reboot://重启任务
									//TIT -> TC &= TIT_Task_State_TC_RST;//置位状态位									
									TIT -> TC = Task_State_RB;//
									return (OK);//返回OK
			case Task_Set_Start://立即启动任务
									while(TST.TSS != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
									//TIT -> TC &= TIT_Task_State_TC_RST;//置位状态位
									TIT -> TC = Task_State_Up_IN;//主动挂起(挂起态)
									TST. TDN = TIT -> TI;//把这个任务ID加载到任务调度计数中，这样任务调度才认识这个任务，否则将会向下调度
									osTaskSwitch_Enable();
									return (OK);//返回OK
			case Task_Set_Up://挂起任务
								return (OK);

									
		}
	}else{//自身
		switch(Pv){
			case Task_Set_Pause://暂停任务
									//TIT -> TC &= TIT_Task_State_TC_RST;//置位状态位
									while(TST.TSS != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
									RunTask_TIT -> TC = Task_State_DI;//设为禁用态
									osTaskSwitch_Enable();//触发任务切换
									return (OK);//返回OK

			case Task_Set_Cont://继续任务
									return (OK);//返回OK

			case Task_Set_Reboot://重启任务
									//TIT -> TC &= TIT_Task_State_TC_RST;//置位状态位
									while(TST.TSS != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
									RunTask_TIT -> TC = Task_State_RB;//
									osTaskSwitch_Enable();//触发任务切换
									return (OK);//返回OK
			case Task_Set_Start://立即启动任务
									return (OK);//返回OK
			case Task_Set_Up://挂起任务
								while(TST.TSS != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
								//RunTask_TIT -> TC &= TIT_Task_State_TC_RST;
								RunTask_TIT -> TC = Task_State_Up_IN;
								osTaskSwitch_Enable();//触发任务切换
								return (OK);

									
		}
	}
	#if (osTaskDebug_Enable > 0)
	osTaskErrorDebug("任务配置时不是正确的配置项 %s\n" ,RunTask_TIT -> TN);
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
	//RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//置位状态位
	while(true){
		RunTask_TIT -> TC = Task_State_ST;//设为终止态
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
osErrorValue osTaskAddrReplace(TaskInfoTable* TIT,void* NewTA)
{
	if(TIT == 0){
		RunTask_TIT -> TA = NewTA;
		while(TST.TSS != TaskSwitch_Ready);//查询CPU是否已经被设为悬起态
		RunTask_TIT -> TC = Task_State_RB;//
		osTaskSwitch_Enable();//触发任务切换
		return (OK);//返回OK

	}else{
		TIT -> TA = NewTA;
		TIT -> TC = Task_State_RB;//
		return (OK);//返回OK
	}

}

osErrorValue osTaskErrorHardFault(uint32_t pc,uint32_t psp)
{
	#if (osTaskRunError_Enable > 0)
	uint8_t Count = 1;
	osTaskEnterISR();
	while(Count--){
		osTaskErrorDebug("\n\n\n名称为%s的任务发生“硬件错误”异常!!!\n",RunTask_TIT -> TN);
		osTaskErrorDebug("任务优先级:%d\n",RunTask_TIT -> TPL);
		osTaskErrorDebug("任务当前使用量:%d%%\n",RunTask_TIT -> TOR);
		osTaskErrorDebug("任务延时剩余时间:%d%ms\n任务单次最大运行时长:%dms\n",RunTask_TIT -> TTF,RunTask_TIT -> TTW);
		osTaskErrorDebug("任务最一近状态:",0,0);
		switch(RunTask_TIT -> TC){
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
		if(RunTask_TIT -> PF == NULL){
			osTaskErrorDebug("空的\n");
		}
		else{
			osTaskErrorDebug("非空\n");
		}
		osTaskErrorDebug("任务栈总大小:%d字节\n任务栈剩余:%d字节\n",(RunTask_TIT -> TSS - 1),psp - ((uint32_t)RunTask_TIT -> TH - ((RunTask_TIT -> TSS - 1))));
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
	RunTask_TIT -> TC = Task_State_Up_IN;
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
	for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//对每一个任务进行遍历
		print("任务<%s>的使用量为:占用时长:%dms | 任务优先级:%d | 任务状态:",TL[_tr0].TITA -> TN,TL[_tr0].TITA -> TOR,TL[_tr0].TITA -> TPL);
		if(TL[_tr0].TITA != RunTask_TIT || TST.TSS != TaskSwitch_Ready){
			switch(TL[_tr0].TITA -> TC){
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

