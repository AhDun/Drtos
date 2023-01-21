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
	SemaphoreTable* ST = osMemoryMalloc(sizeof(SemaphoreTable));//为信号量结构体申请内存
	if(ST == NULL){//如果内存申请函数返回为零,说明申请失败
		return (NULL);//返回空,表示错误
	}
    switch(SP){
#ifdef osSignalMutual_Enable 
        case Signal_Mutual: //互斥信号量
                            ST ->SV = false;//将信号值设为假
                            ST ->ST = SP;//写入信号类型
							ST -> SP = NULL;
                            return (ST);
#endif
#ifdef osSignalBinary_Enable 
        case Signal_Binary://二值信号量
                            ST ->SV = false;//将信号值设为假
							ST ->ST = SP;//写入信号类型	
							ST -> SP = NULL;
							return (ST);
#endif
#ifdef osSignalCount_Enable
        case Signal_Count://计数信号量
							ST ->SV = 0;//将信号值设为零
                            ST ->ST = SP;//写入信号类型
							ST -> SP = NULL;
                            return (ST);
#endif
        default:return (NULL);//break;
    }
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
                            ST ->SP = SP;//写入信号类型
                            return (OK);
#endif
#ifdef osSignalBinary_Enable 
        case Signal_Binary://二值信号量
                            ST ->SV = false;//将信号值设为假
							ST ->SP = SP;//写入信号类型
							return (OK);
#endif
#ifdef osSignalCount_Enable
        case Signal_Count://计数信号量
							ST ->SV = 0;//将信号值设为零
                            ST ->SP = SP;//写入信号类型
                            return (OK);
#endif
        default:return (Error);//break;
    }
}
#endif
/*

 *@函数名称: osSignalWaitPost

 *@函数版本: 1.0.0

 *@函数功能: 需等待发送信号量邮箱

 *@输入参数: SemaphoreTable* ST(信号量结构体)

 *@返 回 值: 无

 *@注    释: 无

*/
osErrorValue osSignalWaitPost(SemaphoreTable* ST)
{
	
	_uList* uList;
	TaskInfoTable* TIT;
	_uList* TuList;
	TuList = osMemoryMalloc(sizeof(_uList));//为信号量结构体申请内存
	if(TuList == NULL){
		return (Error);
	}else{
		TuList -> Body = (_Body*)RunTask_TIT;
		TuList -> DownAddr = NULL;
		uList = (_uList*)ST -> SP;
		TIT = (TaskInfoTable*)uList -> Body;
		do{
			if(uList -> DownAddr == NULL){
				uList -> DownAddr = (_NextAddr*)TuList;
				RunTask_TIT -> TC = Task_State_Up_SI;//修改为信号挂起(等待态)
				osTaskSwitch_Enable();//触发异常,进行任务切换
				return (OK);
			}
			uList = (_uList*)uList -> DownAddr;
			TIT = (TaskInfoTable*)uList -> Body;
		}while(RunTask_TIT -> TPL < TIT -> TPL);
		uLinkListInsert(&ST -> SP,uList,TuList);

		RunTask_TIT -> TC = Task_State_Up_SI;//修改为信号挂起(等待态)
		osTaskSwitch_Enable();//触发异常,进行任务切换
		return (OK);
	}
}
/*

 *@函数名称: osSignalApplyPost

 *@函数版本: 1.0.0

 *@函数功能: 无需等待发送信号量邮箱

 *@输入参数: SemaphoreTable* ST(信号量结构体)

 *@返 回 值: 无

 *@注    释: 无

*/
osErrorValue osSignalApplyPost(SemaphoreTable* ST)
{
	
	_uList* TuList;
	TuList = osMemoryMalloc(sizeof(_uList));//为信号量结构体申请内存
	if(TuList == NULL){
		return (Error);
	}else{
		TuList -> Body = (_Body*)RunTask_TIT;
		TuList -> DownAddr = NULL;
		ST -> SP = (_SignalPost*)TuList;
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

osErrorValue osSignalApply_Wait(SemaphoreTable* ST)
{
	TaskInfoTable* TIT;
	_uList* uList;
	switch(ST ->ST){
		case Signal_Binary:	
							if(ST -> SP != NULL){
								return osSignalWaitPost(ST);

							}else{
								return osSignalApplyPost(ST);
							}
		case Signal_Mutual:
							if(ST -> SP != NULL){
								uList = (_uList*)ST -> SP;
								TIT = (TaskInfoTable*)uList -> Body;
								if(RunTask_TIT -> TPL < TIT -> TPL){
									TIT -> TPL = RunTask_TIT -> TPL;//
									return osSignalWaitPost(ST);
								}else{
									return osSignalWaitPost(ST);
								}
							}else{
								return osSignalApplyPost(ST);
							}
		case Signal_Count:
							if(ST -> SV > 0){
								ST -> SV =  ST -> SV - 1;
								return (OK);	
							}else{
								if(ST -> SP != NULL){
									return osSignalWaitPost(ST);
								}else{
									return osSignalApplyPost(ST);
								}
							}
		default:return(Error);
	}
}


/*
osErrorValue osSignalApply_Wait(SemaphoreTable* ST)
{
	 switch(ST ->SP){
#ifdef osSignalMutual_Enable 
        case Signal_Mutual://互斥信号量 
							if(ST -> SV == false){
								if(RunTask_TIT -> TPL < TL[ST -> OTID].TITA -> TPL && ST -> OTID < (_TaskIDMax + 1)){
									TL[ST -> OTID].TITA -> TPL = RunTask_TIT -> TPL;//临时提高优先级
								}
                                while(TST.TSS != TaskSwitch_Ready);//查询任务可切换态,如果是不可切换,无限循环,直到可切换态
                                //RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//任务的状态位复位
                                RunTask_TIT -> TC = Task_State_Up_SI;//修改为信号挂起(等待态)
                                RunTask_TIT -> TS =  &ST->SV;
                                osTaskSwitch_Enable();//触发异常,进行任务切换
                            }
							ST -> OTID = RunTask_TIT -> TI;
							ST -> SV = false;
                            return (OK);//请求成功!返回OK
#endif
#ifdef osSignalBinary_Enable                            
        case Signal_Binary://二值信号量
                            if(ST -> SV == false){
                                while(TST.TSS != TaskSwitch_Ready);//查询任务可切换态,如果是不可切换,无限循环,直到可切换态
                                //RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//任务的状态位复位
                                RunTask_TIT -> TC = Task_State_Up_SI;//修改为信号挂起(等待态)
                                RunTask_TIT -> TS =  &ST->SV;
                                osTaskSwitch_Enable();//触发异常,进行任务切换
                            }
							ST -> SV = false;
                            return (OK);//请求成功!返回OK
                            
#endif
#ifdef osSignalCount_Enable
        case Signal_Count://计数信号量
                           if(ST -> SV == 0){
                                while(TST.TSS != TaskSwitch_Ready);//查询任务可切换态,如果是不可切换,无限循环,直到可切换态
                                //RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//任务的状态位复位
                                RunTask_TIT -> TC = Task_State_Up_SI;//修改为信号挂起(等待态)
                                RunTask_TIT -> TS =  &ST->SV;
                                osTaskSwitch_Enable();//触发异常,进行任务切换
                            }
							if(ST -> SV > 0){
								ST -> SV = ST -> SV - 1;
							}
                            return (OK);//请求成功!返回OK
#endif
		case Signal_Logout://无效信号量
							return (OK);
        default:return (Error);//信号量的类型,发生错误,返回错误
    }
}
*/
/*

 *@函数名称: osSignalFreePost

 *@函数版本: 1.0.0

 *@函数功能: 释放信号量邮箱

 *@输入参数: SemaphoreTable* ST(信号量结构体)

 *@返 回 值: 无

 *@注    释: 无

*/
osErrorValue osSignalFreePost(SemaphoreTable* ST)
{
	TaskInfoTable* TIT;
	_uList* uList;
	_SignalPost* SignalPost;
	if(ST -> SP != NULL){
		uList = (_uList*)ST -> SP;
		SignalPost = (_SignalPost*) uList -> DownAddr;
		if(osMemoryFree((u8*)ST -> SP) == Error){
			return (Error);
		}else{
			ST -> SP = SignalPost;
			if(ST -> SP != NULL){
				uList = (_uList*)ST -> SP;
				TIT = (TaskInfoTable*)uList -> Body;
				if(RunTask_TIT -> TPL > TIT ->TPL){
					TST. TDN = TIT -> TI;//把这个任务ID加载到任务调度计数中，这样任务调度才认识这个任务，否则将会向下调度
					TIT -> TC = Task_State_Up_IN;  //主动挂起(挂起态)
					osTaskSwitch_Enable();//触发异常,进行任务切换
				}else{
					TIT -> TC = Task_State_Up_IN;  //主动挂起(挂起态)
				}
			}
			else{
				return (OK);
			}
			return (OK);
		}
	}else{
		return (OK);
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
							return osSignalFreePost(ST);
		case Signal_Mutual:
							RunTask_TIT -> TPL = RunTask_TIT -> TPLb;
							return osSignalFreePost(ST);
		case Signal_Count:
							ST -> SV = ST -> SV + 1;
							return osSignalFreePost(ST);
		default:return(Error);
	}
}
/*
osErrorValue osSignalFree(SemaphoreTable* ST)
{
	switch(ST ->ST){
#ifdef osSignalMutual_Enable 
        case Signal_Mutual://互斥信号量
							if(ST -> SV == false){
								RunTask_TIT -> TPL = RunTask_TIT -> TPLb;//将当前正在运行的任务的副优先级加载到主优先级中
								ST -> SV = true;//设信号值为有效值
								ST -> OTID = _TaskIDMax + 1;//设为就绪态
								return (OK);//释放成功,返回OK
							}
							else{
								return (Error);//发生错误 
							}
#endif
#ifdef osSignalBinary_Enable                            
        case Signal_Binary://二值信号量
							if(ST -> SV == false){
								ST -> SV = true;//设信号值为有效值
								return (OK);//释放成功,返回OK
							}
							else{
								return (Error);//发生错误
							}
                            
#endif
#ifdef osSignalCount_Enable
        case Signal_Count://计数信号量
							ST -> SV = ST -> SV + 1;//
                            return (OK);//释放成功,返回OK
#endif
        default:return (Error);//信号量的类型,发生错误,返回错误
    }
}
*/
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

#if (osSignalAutoApply_Enable > 0)//启用了信号量自动分配

	if(osMemoryFree((u8*)ST) == Error){//需要把信号量的所占内存释放
		return (Error);//释放内存时,发生错误,返回错误
	}

#endif
	switch(ST -> ST){
#ifdef osSignalMutual_Enable
		case Signal_Mutual://互斥信号量
#endif
#ifdef osSignalBinary_Enable 
		case Signal_Binary://二值信号量
#endif
#ifdef osSignalCount_Enable
		case Signal_Count://计数信号量
						ST -> ST = Signal_Logout;//设为无效信号量
						break;
#endif
		default: return(Error);//找不到当前信号量所属类型,返回错误
	}
	return (OK);//注销成功!返回OK

}


/*
                                                  FILE-END
*/
