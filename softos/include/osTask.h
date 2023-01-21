/*
                                                  FILE-START
*/
#ifndef __osTaskH_
#define __osTaskH_
/*

 *@文件名称: osTask.h

 *@文件内容: 

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注    释: 

*/

/*
                                                  <引用文件区>
*/
/*
                                                  <宏定义区>
*/

#define TaskListLength 		osMaximumTask 	//任务轮询表长度，这个意味着最大的任务量

#if TaskListLength <= 255 //当任务量小于255时


//---------------------任务优先级--------------------
	#define _TaskPriorityLevelMin   	-127		//任务最小优先级 
	#define _TaskPriorityLevelMax 		126		//任务最大优先级
	/*
	任务的优先级: 
	-127~126
	*/
//任务ID范围{
	#define _TaskIDMin 					0u		//任务ID最小值
	#define _TaskIDMax 					253u	//任务ID最大值
	/*
		任务ID的范围: 0~253
		最大的任务量: 254个
	*/
//}
#endif

#define TaskList_NULLValue	0u	    //任务轮询表空值

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



//------------------------默认轮片时间-----------------------------
#define TaskTimeWheelDefault        100u//默认轮片时间(单位ms)

//--------------------------默认栈大小------------------
#define Default_Stack_Size             1000u//默认栈大小
     
//--------------------------函数替换----------------------
#if (osCriticalToProtect_Enable > 0)//启用了临界保护
	#define osProtect_DISABLE() 			INTX_ENABLE()//退出临界保护
	#define osProtect_ENABLE() 				INTX_DISABLE()//进入临界保护
#endif
#define osTaskSwitch_Enable() 			do{TST.TSS = TaskSwitch_Wait; CPU_PendSV();}while(0);//触发任务切换
//#define osTaskSwitch_Strong_Enable() 	CPU_SVC()//触发强制任务切换

#define osTaskDebug(a,b) print("\nosTask: %s:%s\n",a,b)//DeBug输出函数
#define osTaskInfoPrintOut	 print
#define osTaskDebug_Enable 1 //Debug配置 1:开启Debug输出 0:关闭Debug输出




/*
                                                  数据类型别名声明区
*/

typedef     u8		_Task_Set_Pv;//


//任务表{
#if _TaskIDMax<= 253
	typedef 	u8 	_TaskID;//任务ID
#endif
typedef 	u8 		_TaskName;//任务名称
typedef 	u8 		_TaskConfig;//任务控制量
typedef 	u32 	_TaskHandle;//任务栈地址
typedef 	u32 	_TaskStackSize;//任务栈长度
typedef 	u32 	_TaskSemaphore;//任务信号量
typedef 	u32 	_TaskTimeWheel;//任务时间轮片
#if _TaskPriorityLevelMax <= 126 && _TaskPriorityLevelMin >= -127
	typedef 	s8 		_TaskPriorityLevel;//任务优先级
#endif
typedef		u32		_PostForm;
typedef 	u32 	_TaskAddr;
typedef		u32		_TaskRealSP;
typedef		u32		_TaskTimeFlag;
#if (osPerformanceStatistics_Enable > 0) //开启了性能统计
typedef     u16     _TaskOccupyTime;//任务占用时长
typedef     u16      _TaskOccupyRatio;//任务占用比
#endif
typedef     u32     _TaskParameterPass;//任务传参


typedef struct
{
	_TaskRealSP			TRS;	//任务实时栈指针
	_TaskID				TI;		//任务ID
	_TaskName*			TN; 	//任务名称
	_TaskConfig 		TC;  	//任务控制量	
	_TaskHandle* 		TH;  	//任务栈地址
	_TaskStackSize 	TSS;   	//任务栈长度
#if defined osSignalMutual_Enable ||  defined osSignalBinary_Enable || define osSignalCount_Enable
	_TaskPriorityLevel	TPLb;   //任务备用优先级
#endif
//#ifdef osPost_Enable
	_PostForm*			PF;
//#endif
	_TaskTimeWheel 		TTW;	//任务时间轮片
	_TaskPriorityLevel 	TPL;	//任务优先级
	_TaskAddr*			TA;		//任务地址
	_TaskTimeFlag		TTF;	//任务时间标志
#if (osPerformanceStatistics_Enable > 0) //开启了性能统计
    _TaskOccupyTime      TOT;    //任务占用时长
    _TaskOccupyRatio     TOR;    //任务占用比
#endif
    _TaskParameterPass*  TPP;    //任务传参					
} TaskInfoTable;
//}

//任务轮询表{
typedef struct
{
	TaskInfoTable*		TITA;	  //任务信息表 地址(任务句柄)
} TaskList;
//}

//任务调度状态表{
typedef		u8		_TaskListMaximumActivity;//任务最大活动量
typedef 	u8		_TaskDispatchNum;//任务调度状态
typedef     u8      _TaskSwitchState;//任务调度计数
#if (osTaskUsePrint  > 0)
typedef		u32		_TaskSwitchConut;//任务调度次数
typedef		u8		_TaskSwitchSpeedUs;//任务切换速度测试
#endif
typedef struct
{
	_TaskSwitchState	    TSS;//任务调度状态
	_TaskDispatchNum		TDN;//任务调度计数
    _TaskListMaximumActivity	TLMA;//任务最大活动量
	#if (osTaskUsePrint  > 0)
	_TaskSwitchConut			TSC;//任务调度次数
	_TaskSwitchSpeedUs			TSSU;//任务切换速度测试
	#endif
    
} TaskDispatchStateTable;
//}

/*
                                                  <数据声明区>
*/
extern u32 NULL_Value;//一个空值
extern TaskInfoTable*	RunTask_TIT;//当前正在运行的任务表指针

extern TaskList TL[TaskListLength];//任务轮询表
extern TaskDispatchStateTable TST;//任务调度状态表


/*
                                                  <函数声明区>
*/	
/*

 *@函数名称: osTaskInit

 *@函数版本: 1.0.0

 *@函数功能: 根据任务名称查询任务表地址

 *@输入参数: 无	

 *@返 回 值: osErrorValue - 函数错误返回值 (0:表示初始化成功，-1:表示初始化成功)

 *@注    释: 无
*/
extern osErrorValue osTaskInit(void);	


#if (osTaskAutoStack_Enable > 0)//启用任务栈自动分配
/*

 *@函数名称: osTaskNameToTable

 *@函数版本: 1.0.0

 *@函数功能: 根据任务名称查询任务表地址

 *@输入参数: TN	-	任务名称	
			 TA	-	任务地址
			 TSS - 	任务栈长度
			 TTW - 	任务时间轮片
			 TPL -  任务优先级
			 TPP -	任务传参
			 TC -	任务配置（任务配置请参考 - Task_Set_Default - 这个宏定义）
	
 *@返 回 值: osErrorValue -		函数错误返回值 (-1: 表示创建任务发生错误,> - 1: 注册后任务ID，表示已完成注册)
			 
 *@注    释: 无
*/
extern osErrorValue osTaskLogin(
	_TaskName *TN,
	void*  TA,	
	_TaskStackSize  TSS,
	_TaskTimeWheel  TTW,
	_TaskPriorityLevel  TPL,
    void*  TPP, 
    _TaskConfig  TC
);
extern osErrorValue osTaskRegister_Write(
#else //不启用任务栈自动分配
extern osErrorValue osTaskLogin(
#endif 
	TaskInfoTable* TIT,
	_TaskName *TN,
	void*  TA,
	_TaskHandle* TH,
	_TaskStackSize  TSS,
	_TaskTimeWheel  TTW,
	_TaskPriorityLevel  TPL,
    void*  TPP, 
    _TaskConfig  TC
);

#if (osTaskAutoStack_Enable > 0)//启用任务栈自动分配
osErrorValue osTaskLogout(_TaskName *TN);
osErrorValue osTaskLogout_Write(TaskInfoTable* TIT);
#else 							//不启用任务栈自动分配
osErrorValue	osTaskLogout(TaskInfoTable* TIT);
#endif
/*

 *@函数名称: osTaskNameToTable

 *@函数版本: 1.0.0

 *@函数功能: 根据任务名称查询任务表地址

 *@输入参数: *TN	-	任务名称	

 *@返 回 值: TaskInfoTable* - 任务表地址

 *@注    释: 无
*/
extern TaskInfoTable* osTaskNameToTable(_TaskName *TN);
/*

 *@函数名称: osTaskNext

 *@函数版本: 1.0.0

 *@函数功能: 计算下一个要运行的任务

 *@输入参数: 无	

 *@返 回 值: 无

 *@注    释: 无

*/
extern void osTaskNext(void);
/*

 *@函数名称: osTaskDelayMs

 *@函数版本: 1.0.0

 *@函数功能: 任务毫秒级阻塞延时

 *@输入参数: ms	-	要延时的时长	

 *@返 回 值: 0: 完成延时

 *@注    释: 无

*/
extern osErrorValue osTaskDelayMs(u32 ms);
/*

 *@函数名称: osTaskDelayUs

 *@函数版本: 1.0.0

 *@函数功能: 任务微秒级阻塞延时

 *@输入参数: us	-	要延时的时长

 *@返 回 值: 0: 完成延时

 *@注    释: 无

*/
extern osErrorValue osTaskDelayUs(u32 us);

//extern osErrorValue osTaskSwitch_State(void);
///*

// *@函数名称: osTaskAddrReplace

// *@函数版本: 1.0.0

// *@函数功能: 任务配置

// *@输入参数: 无	

// *@返 回 值: -1:配置时出现错误，0: 配置成功

// *@注    释: 无

//*/
//extern osErrorValue osTaskISR(TaskInfoTable* TIT);
/*

 *@函数名称: osTaskAddrReplace

 *@函数版本: 1.0.0

 *@函数功能: 任务配置

 *@输入参数: 无	

 *@返 回 值: -1:配置时出现错误，0: 配置成功

 *@注    释: 无

*/
extern osErrorValue osTaskSet(TaskInfoTable* TIT,_Task_Set_Pv Pv);
/*

 *@函数名称: osTaskAddrReplace

 *@函数版本: 1.0.0

 *@函数功能: 任务地址替换

 *@输入参数: 无	

 *@返 回 值: -1:创建错误，0: 创建成功

 *@注    释: 无

*/
extern osErrorValue osTaskAddrReplace(TaskInfoTable* TIT,void* NewTA);
/*

 *@函数名称: osTaskExit

 *@函数版本: 1.0.0

 *@函数功能: 任务结束

 *@输入参数: 无	

 *@返 回 值: 0: 成功结束

 *@注    释: 无

*/
extern osErrorValue osTaskExit(void);


#endif

/*
                                                  FILE-END
*/


