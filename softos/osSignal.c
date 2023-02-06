/*
                                                  FILE-START
*/
/*
 *
 * @文件名称: .c
 *
 * @文件内容: 系统"信号量"文件
 *
 * @文件作者: AhDun (mail: ahdunxx@163.com)
 *
 * @注    释: 无
 *
 */

/*
                                                  <引用文件区>
*/
#include "osConfig.h"
#include "osSignal.h"
/*

 @头文件名称: 无

 @头文件功能: 无

 @注      释: 无
 *
 */

/*
                                                  <数据初始区>
*/
/*

 @变量名称: 无

 @变量功能: 无
 *
 * @注    释: 无
 *
 */
/*
                                                  <函数区>
*/

/*
 *
 * @函数名称: osSignalRegister
 *
 * @函数功能: 注册信号量
 *
 * @输入参数: _SignalType SP(信号量的类型)
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
#if (osSignalAutoApply_Enable > 0)//启用了信号量自动分配
_Signal* osSignalLogin(_SignalType SP)
{
	#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
		_Signal* ST = osMemoryMalloc(sizeof(_Signal));//为信号量结构体申请内存
		if(ST == NULL){//如果内存申请函数返回为零,说明申请失败
			#if (osSignalDebugError_Enable > 0)
			osSignalDebugError("注册信号量时内存申请失败 %s\n",RunTaskHandle -> Name);
			#endif
			return (NULL);//返回空,表示错误
		}
		ST -> Value = 0;//将信号值设为零
		if(SP == Signal_Mutual || SP == Signal_Binary || SP == Signal_Count){
			ST -> Type = SP;//写入信号类型
		}else{
			#if (osSignalDebugError_Enable > 0)
			osSignalDebugError("注册信号量时类型错误 %s\n",RunTaskHandle -> Name);
			#endif
			return (NULL);
		}
		ST -> NextAddr = NULL;
		return (ST);
	#else
		return (NULL);
	#endif 
}
#else
/*
 *
 * @函数名称: osSignalRegister
 *
 * @函数功能: 注册信号量
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
osErrorValue osSignalLogin(_Signal* ST,_SignalType SP)
{
    switch(SP){
#ifdef osSignalMutual_Enable 
        case Signal_Mutual://互斥信号量
                            ST ->SV = false;//将信号值设为假
                            ST ->SP = NULL;//写入信号类型
                            return (OK);
#endif
#ifdef osSignalBinary_Enable 
        case Signal_Binary://二值信号量
                            ST ->SV = false;//将信号值设为假
							ST ->SP = NULL;//写入信号类型
							return (OK);
#endif
#ifdef osSignalCount_Enable
        case Signal_Count://计数信号量
							ST ->SV = 0;//将信号值设为零
                            ST ->SP = NULL;//写入信号类型
                            return (OK);
#endif
        default:
				#if (osSignalDebugError_Enable > 0)
				osSignalDebugError("注册信号量时类型错误 %s\n",RunTaskHandle -> Name);
				#endif
				return (Error);//break;
    }
}
#endif

/*
 *
 * @函数名称: osSignalApply_Wait
 *
 * @函数功能: 信号量请求
 *
 * @输入参数: _Signal* ST(信号量结构体)
 *
 * @返 回 值: -1:发生错误 / 0:请求成功
 *
 * @注    释: 无
 *
 */

static osErrorValue osSignalApplyToken(_Signal* ST)
{
	_SignalToken* SemaphoreToken_Buf = osMemoryMalloc(sizeof(_SignalToken));//为信号量结构体申请内存
	if(SemaphoreToken_Buf == NULL){
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("申请占用信号量令牌时内存申请失败 %s\n",RunTaskHandle -> Name);
		#endif
		return (Error);
	}else{
		SemaphoreToken_Buf -> DownAddr = NULL;
		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)RunTaskHandle;
		ST -> NextAddr = (uint32_t)SemaphoreToken_Buf;
		return (OK);
	}
}


/*
 *
 * @函数名称: osSignalApply_Wait
 *
 * @函数功能: 信号量请求
 *
 * @输入参数: _Signal* ST(信号量结构体)
 *
 * @返 回 值: -1:发生错误 / 0:请求成功
 *
 * @注    释: 无
 *
 */

static osErrorValue osSignalWaitToken(_Signal* ST)
{
	_NextAddr* NextAddr_Buf;
	_NextAddr NextAddr_Buf1;
	_SignalToken* SemaphoreToken_Buf1;
	_TaskHandle*	TaskInfoTable_Buf;
	_SignalToken* SemaphoreToken_Buf = osMemoryMalloc(sizeof(_SignalToken));//为信号量结构体申请内存
	if(SemaphoreToken_Buf == NULL){
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("申请等待信号量令牌时内存申请失败 %s\n",RunTaskHandle -> Name);
		#endif
		return (Error);
	}else{
		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)RunTaskHandle;
		SemaphoreToken_Buf -> DownAddr = NULL;
	
		NextAddr_Buf = &ST -> NextAddr;
		
		while(*NextAddr_Buf != NULL){
			SemaphoreToken_Buf1 = (_SignalToken*)*NextAddr_Buf;
			TaskInfoTable_Buf = (_TaskHandle*)SemaphoreToken_Buf1 -> TaskInfo;
			if(RunTaskHandle -> PriorityLevel < TaskInfoTable_Buf -> PriorityLevel){
				NextAddr_Buf1 = (_NextAddr)*NextAddr_Buf;
				*NextAddr_Buf = (_NextAddr)SemaphoreToken_Buf;
				SemaphoreToken_Buf -> DownAddr = NextAddr_Buf1;
				if(NextAddr_Buf == &ST -> NextAddr){
					TaskInfoTable_Buf -> Config = Task_State_Up_SI;
					return (OK);
				}
				RunTaskHandle -> Config = Task_State_Up_SI;  //修改为信号挂起(等待态)
				osTaskSwitch_Enable();//触发异常,进行任务切换
				return (OK);
			}
			NextAddr_Buf = (_NextAddr*)*NextAddr_Buf;
		}
		*NextAddr_Buf = (_NextAddr)SemaphoreToken_Buf;
		RunTaskHandle -> Config = Task_State_Up_SI;  //修改为信号挂起(等待态)
		osTaskSwitch_Enable();//触发异常,进行任务切换
		return(OK);
	}
}


osErrorValue osSignalUseWait(_Signal* ST)
{
#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
	_TaskHandle* TaskHandle;
	_SignalToken* SemaphoreToken_Buf;
	switch(ST -> Type){
#ifdef osSignalBinary_Enable 
		case Signal_Binary:	
							if(ST -> NextAddr != NULL){
								return osSignalWaitToken(ST);

							}else{
								return osSignalApplyToken(ST);
							}
#endif
#ifdef osSignalMutual_Enable 
		case Signal_Mutual:
							if(ST -> NextAddr != NULL){
								SemaphoreToken_Buf = (_SignalToken*)ST -> NextAddr;
								TaskHandle = (_TaskHandle*)SemaphoreToken_Buf -> TaskInfo;
								if(RunTaskHandle -> PriorityLevel < TaskHandle -> PriorityLevel){
									TaskHandle -> PriorityLevel = RunTaskHandle -> PriorityLevel;//
								}
								return osSignalWaitToken(ST);
							}else{
								return osSignalApplyToken(ST);
							}
#endif
#ifdef osSignalCount_Enable
		case Signal_Count:
							if(ST -> Value > 0){
								ST -> Value =  ST -> Value - 1;
								return (OK);	
							}else{
								if(ST -> NextAddr != NULL){
									return osSignalWaitToken(ST);
								}else{
									return osSignalApplyToken(ST);
								}
							}
#endif
		default:
				#if (osSignalDebugError_Enable > 0)
				osSignalDebugError("占用信号量时输入类型错误 %s\n",RunTaskHandle -> Name);
				#endif
				return(Error);
	}
#endif
}

/*
 *
 * @函数名称: osSignalFree
 *
 * @函数功能: 释放信号量
 *
 * @输入参数: _Signal* ST(信号量结构体)
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
osErrorValue osSignalFree(_Signal* ST)
{
#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
	_SignalToken* SemaphoreToken_Buf;
	_TaskHandle*	TaskInfoTable_Buf;

	switch(ST -> Type){
#ifdef osSignalBinary_Enable
		case Signal_Binary:
							break;
#endif
#ifdef osSignalMutual_Enable
		case Signal_Mutual:
							RunTaskHandle -> PriorityLevel = RunTaskHandle -> PriorityLevelb;
							break;
#endif
#ifdef osSignalCount_Enable
		case Signal_Count:	
							if(ST -> NextAddr == NULL){
								ST -> Value = ST -> Value + 1;
								return (OK);
							}
							break;
#endif
		default:
				#if (osSignalDebugError_Enable > 0)
				osSignalDebugError("释放信号量时类型错误 %s\n",RunTaskHandle -> Name);
				#endif
				return(Error);
	}
	if(ST -> NextAddr != NULL){
		SemaphoreToken_Buf = (_SignalToken*)uLinkListHeadRead(&ST -> NextAddr);
		TaskInfoTable_Buf = (_TaskHandle*)SemaphoreToken_Buf  -> TaskInfo;
		TaskInfoTable_Buf -> Config = Task_State_Up_IN;  //主动挂起(挂起态)
		if(osMemoryFree(SemaphoreToken_Buf) != OK){
			#if (osSignalDebugError_Enable > 0)
			osSignalDebugError("释放信号量时释放内存错误 %s\n",RunTaskHandle -> Name);
			#endif
			return (Error);
		}
		if(TaskInfoTable_Buf -> PriorityLevel < RunTaskHandle -> PriorityLevel){
			osTaskSwitch_Enable();//触发异常,进行任务切换
		}
		return (OK);
	}else{
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("释放信号量时已经为空 %s\n",RunTaskHandle -> Name);
		#endif
		return (Error);
	}
	#endif
}

/*
 *
 * @函数名称: osSignalLogout
 *
 * @函数功能: 信号量注销
 *
 * @输入参数: _Signal* ST(信号量结构体)
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
osErrorValue osSignalLogout(_Signal* ST)
{
	#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
	ST -> NextAddr =  ST -> Type =  ST -> Value = 0;
	#if (osSignalAutoApply_Enable > 0)//启用了信号量自动分配

	if(osMemoryFree((uint8_t*)ST) == Error){//需要把信号量的所占内存释放
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("注销信号量时释放内存错误 %s\n",RunTaskHandle -> Name);
		#endif
		return (Error);//释放内存时,发生错误,返回错误
	}
	return (OK);//注销成功!返回OK
	#endif
	#else 
	return (Error);//注销成功!返回OK
	#endif

}


/*
                                                  FILE-END
*/
