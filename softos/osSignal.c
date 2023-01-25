/*
                                                  FILE-START
*/
/*

 *@文件名称: .c

 *@文件内容: 系统"信号量"文件

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注    释: 无

*/

/*
                                                  <引用文件区>
*/
#include "osMain.h"
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
			return (NULL);//返回空,表示错误
		}
		ST -> SV = 0;//将信号值设为零
		ST -> ST = SP;//写入信号类型
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
        default:return (Error);//break;
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
				if(SemaphoreToken_Buf2 == NULL){
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
				SemaphoreToken_Buf2 = SemaphoreToken_Buf1;
				SemaphoreToken_Buf1 = (SemaphoreToken*)SemaphoreToken_Buf1 -> DownAddr;
			}
		}
	}
}


osErrorValue osSignalUseWait(SemaphoreTable* ST)
{
	TaskInfoTable* TIT;
	_uList* uList;
	switch(ST ->ST){
		case Signal_Binary:	
							if(ST -> SP != NULL){
								return osSignalWaitToken(ST);

							}else{
								return osSignalApplyToken(ST);
							}
		case Signal_Mutual:
							if(ST -> SP != NULL){
								uList = (_uList*)ST -> SP;
								TIT = (TaskInfoTable*)uList -> Body;
								if(RunTask_TIT -> TPL < TIT -> TPL){
									TIT -> TPL = RunTask_TIT -> TPL;//
								}
								return osSignalWaitToken(ST);
							}else{
								return osSignalApplyToken(ST);
							}
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
		default:return(Error);
	}
}


static osErrorValue osSignalFreeToken(SemaphoreTable* ST)
{
	SemaphoreToken* SemaphoreToken_Buf;
	TaskInfoTable*	TaskInfoTable_Buf;


	if(ST -> SP != NULL){
		SemaphoreToken_Buf = (SemaphoreToken*)ST -> SP;
		TaskInfoTable_Buf = (TaskInfoTable*)SemaphoreToken_Buf  -> TaskInfo;
		TaskInfoTable_Buf -> TC = Task_State_Up_IN;  //主动挂起(挂起态)
		ST -> SP = (SemaphoreToken*)SemaphoreToken_Buf -> DownAddr;
		if(osMemoryFree(SemaphoreToken_Buf) != OK){
			return (Error);
		}
		if(TaskInfoTable_Buf -> TPL < RunTask_TIT -> TPL){
			osTaskSwitch_Enable();//触发异常,进行任务切换
		}
		return (OK);
	}else{
		return (Error);
	}

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
	switch(ST ->ST){
		case Signal_Binary:
							return osSignalFreeToken(ST);
		case Signal_Mutual:
							RunTask_TIT -> TPL = RunTask_TIT -> TPLb;
							return osSignalFreeToken(ST);
		case Signal_Count:
							ST -> SV = ST -> SV + 1;
							return osSignalFreeToken(ST);
		default:return(Error);
	}
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
	#if (osSignalAutoApply_Enable > 0)//启用了信号量自动分配

	if(osMemoryFree((u8*)ST) == Error){//需要把信号量的所占内存释放
		return (Error);//释放内存时,发生错误,返回错误
	}
	
	#endif


	ST -> SV = 0;//将信号值设为零
	ST -> ST = 0;//写入信号类型
	ST -> SP = 0;
	return (OK);//注销成功!返回OK
	#else 
	return (Error);//注销成功!返回OK
	#endif

}


/*
                                                  FILE-END
*/
