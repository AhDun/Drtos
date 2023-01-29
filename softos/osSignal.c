/*
                                                  FILE-START
*/
/*

 *@文件名称: .c

 *@文件内容: 系统"信号量"文件

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@注    释: 无

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

*/

/*
                                                  <数据初始区>
*/
/*

 @变量名称: 无

 @变量功能: 无

 *@注    释: 无

*/
/*
                                                  <函数区>
*/

/*

 *@函数名称: osSignalRegister

 *@函数版本: 1.0.0

 *@函数功能: 注册信号量

 *@输入参数: _SemaphoreType SP(信号量的类型)

 *@返 回 值: 无

 *@注    释: 无

*/
#if (osSignalAutoApply_Enable > 0)//启用了信号量自动分配
SemaphoreTable* osSignalLogin(_SemaphoreType SP)
{
	#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
		SemaphoreTable* ST = osMemoryMalloc(sizeof(SemaphoreTable));//为信号量结构体申请内存
		if(ST == NULL){//如果内存申请函数返回为零,说明申请失败
			#if (osSignalDebugError_Enable > 0)
			osSignalDebugError("注册信号量时内存申请失败 %s\n",RunTask_TIT -> TN);
			#endif
			return (NULL);//返回空,表示错误
		}
		ST -> SV = 0;//将信号值设为零
		if(SP == Signal_Mutual || SP == Signal_Binary || SP == Signal_Count){
			ST -> ST = SP;//写入信号类型
		}else{
			#if (osSignalDebugError_Enable > 0)
			osSignalDebugError("注册信号量时类型错误 %s\n",RunTask_TIT -> TN);
			#endif
			return (NULL);
		}
		ST -> SP = NULL;
		return (ST);
	#else
		return (NULL);
	#endif 
}
#else
/*

 *@函数名称: osSignalRegister

 *@函数版本: 1.0.0

 *@函数功能: 注册信号量

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
osErrorValue osSignalLogin(SemaphoreTable* ST,_SemaphoreType SP)
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
				osSignalDebugError("注册信号量时类型错误 %s\n",RunTask_TIT -> TN);
				#endif
				return (Error);//break;
    }
}
#endif

/*

 *@函数名称: osSignalApply_Wait

 *@函数版本: 1.0.0

 *@函数功能: 信号量请求

 *@输入参数: SemaphoreTable* ST(信号量结构体)

 *@返 回 值: -1:发生错误 / 0:请求成功

 *@注    释: 无

*/

static osErrorValue osSignalApplyToken(SemaphoreTable* ST)
{
	SemaphoreToken* SemaphoreToken_Buf = osMemoryMalloc(sizeof(SemaphoreToken));//为信号量结构体申请内存
	if(SemaphoreToken_Buf == NULL){
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("申请占用信号量令牌时内存申请失败 %s\n",RunTask_TIT -> TN);
		#endif
		return (Error);
	}else{
		SemaphoreToken_Buf -> DownAddr = NULL;
		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)RunTask_TIT;
		ST -> SP = (SemaphoreToken*)SemaphoreToken_Buf;
		return (OK);
	}
}


/*

 *@函数名称: osSignalApply_Wait

 *@函数版本: 1.0.0

 *@函数功能: 信号量请求

 *@输入参数: SemaphoreTable* ST(信号量结构体)

 *@返 回 值: -1:发生错误 / 0:请求成功

 *@注    释: 无

*/

static osErrorValue osSignalWaitToken(SemaphoreTable* ST)
{
	SemaphoreToken* SemaphoreToken_Buf1;
	SemaphoreToken* SemaphoreToken_Buf2;
	TaskInfoTable*	TaskInfoTable_Buf;
	SemaphoreToken* SemaphoreToken_Buf = osMemoryMalloc(sizeof(SemaphoreToken));//为信号量结构体申请内存
	if(SemaphoreToken_Buf == NULL){
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("申请等待信号量令牌时内存申请失败 %s\n",RunTask_TIT -> TN);
		#endif
		return (Error);
	}else{

		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)RunTask_TIT;
		SemaphoreToken_Buf -> DownAddr = NULL;

		SemaphoreToken_Buf1 = (SemaphoreToken*)ST -> SP;
		SemaphoreToken_Buf2 = NULL;
		while(1){
			if(SemaphoreToken_Buf1 -> DownAddr == NULL){
				SemaphoreToken_Buf1 -> DownAddr = (_NextAddr*)SemaphoreToken_Buf;
				RunTask_TIT -> TC = Task_State_Up_SI;  //修改为信号挂起(等待态)
				osTaskSwitch_Enable();//触发异常,进行任务切换
				return (OK);
			}
			TaskInfoTable_Buf = (TaskInfoTable*)SemaphoreToken_Buf1 -> TaskInfo;
			if(RunTask_TIT -> TPL < TaskInfoTable_Buf -> TPL){
				if(SemaphoreToken_Buf2 == NULL){//
					SemaphoreToken_Buf -> DownAddr = (_NextAddr*)ST -> SP;
					ST -> SP = (SemaphoreToken*)SemaphoreToken_Buf;
				}else{
					SemaphoreToken_Buf -> DownAddr = (_NextAddr*)SemaphoreToken_Buf1;
					SemaphoreToken_Buf2 -> DownAddr = (_NextAddr*)SemaphoreToken_Buf;
				}
				RunTask_TIT -> TC = Task_State_Up_SI;  //修改为信号挂起(等待态)
				osTaskSwitch_Enable();//触发异常,进行任务切换
				return (OK);
			}else{
				SemaphoreToken_Buf2 = SemaphoreToken_Buf1;//备份当前令牌
				SemaphoreToken_Buf1 = (SemaphoreToken*)SemaphoreToken_Buf1 -> DownAddr;//加载下一个令牌
			}
		}
	}
}


osErrorValue osSignalUseWait(SemaphoreTable* ST)
{
#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
	TaskInfoTable* TIT;
	SemaphoreToken* SemaphoreToken_Buf;
	switch(ST ->ST){
#ifdef osSignalBinary_Enable 
		case Signal_Binary:	
							if(ST -> SP != NULL){
								return osSignalWaitToken(ST);

							}else{
								return osSignalApplyToken(ST);
							}
#endif
#ifdef osSignalMutual_Enable 
		case Signal_Mutual:
							if(ST -> SP != NULL){
								SemaphoreToken_Buf = (SemaphoreToken*)ST -> SP;
								TIT = (TaskInfoTable*)SemaphoreToken_Buf -> TaskInfo;
								if(RunTask_TIT -> TPL < TIT -> TPL){
									TIT -> TPL = RunTask_TIT -> TPL;//
								}
								return osSignalWaitToken(ST);
							}else{
								return osSignalApplyToken(ST);
							}
#endif
#ifdef osSignalCount_Enable
		case Signal_Count:
							if(ST -> SV > 0){
								ST -> SV =  ST -> SV - 1;
								return (OK);	
							}else{
								if(ST -> SP != NULL){
									return osSignalWaitToken(ST);
								}else{
									return osSignalApplyToken(ST);
								}
							}
#endif
		default:
				#if (osSignalDebugError_Enable > 0)
				osSignalDebugError("占用信号量时输入类型错误 %s\n",RunTask_TIT -> TN);
				#endif
				return(Error);
	}
#endif
}

/*

 *@函数名称: osSignalFree

 *@函数版本: 1.0.0

 *@函数功能: 释放信号量

 *@输入参数: SemaphoreTable* ST(信号量结构体)

 *@返 回 值: 无

 *@注    释: 无

*/
osErrorValue osSignalFree(SemaphoreTable* ST)
{
#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
	SemaphoreToken* SemaphoreToken_Buf;
	TaskInfoTable*	TaskInfoTable_Buf;

	switch(ST ->ST){
#ifdef osSignalBinary_Enable
		case Signal_Binary:
							break;
#endif
#ifdef osSignalMutual_Enable
		case Signal_Mutual:
							RunTask_TIT -> TPL = RunTask_TIT -> TPLb;
							break;
#endif
#ifdef osSignalCount_Enable
		case Signal_Count:
							ST -> SV = ST -> SV + 1;
							break;
#endif
		default:
				#if (osSignalDebugError_Enable > 0)
				osSignalDebugError("释放信号量时类型错误 %s\n",RunTask_TIT -> TN);
				#endif
				return(Error);
	}
	if(ST -> SP != NULL){
		SemaphoreToken_Buf = (SemaphoreToken*)ST -> SP;
		TaskInfoTable_Buf = (TaskInfoTable*)SemaphoreToken_Buf  -> TaskInfo;
		TaskInfoTable_Buf -> TC = Task_State_Up_IN;  //主动挂起(挂起态)
		ST -> SP = (SemaphoreToken*)SemaphoreToken_Buf -> DownAddr;
		if(osMemoryFree(SemaphoreToken_Buf) != OK){
			#if (osSignalDebugError_Enable > 0)
			osSignalDebugError("释放信号量时释放内存错误 %s\n",RunTask_TIT -> TN);
			#endif
			return (Error);
		}
		if(TaskInfoTable_Buf -> TPL < RunTask_TIT -> TPL){
			osTaskSwitch_Enable();//触发异常,进行任务切换
		}
		return (OK);
	}else{
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("释放信号量时已经为空 %s\n",RunTask_TIT -> TN);
		#endif
		return (Error);
	}
	#endif
}

/*

 *@函数名称: osSignalLogout

 *@函数版本: 1.0.0

 *@函数功能: 信号量注销

 *@输入参数: SemaphoreTable* ST(信号量结构体)

 *@返 回 值: 无

 *@注    释: 无

*/
osErrorValue osSignalLogout(SemaphoreTable* ST)
{
	#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
	ST -> SV = 0;//将信号值设为零
	ST -> ST = 0;//写入信号类型
	ST -> SP = 0;
	#if (osSignalAutoApply_Enable > 0)//启用了信号量自动分配

	if(osMemoryFree((uint8_t*)ST) == Error){//需要把信号量的所占内存释放
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("注销信号量时释放内存错误 %s\n",RunTask_TIT -> TN);
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
