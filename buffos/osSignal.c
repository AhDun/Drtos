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
 * @文件名称: .c
 *
 * @文件内容: 系统"信号量"文件
 *
 * @注    释: 无
 *
 */


#include "osConfig.h"
#include "osSignal.h"


#if (osSignal_Config > 0)
/*

 @头文件名称: 无

 @头文件功能: 无

 @注      释: 无
 *
 */


/*

 @变量名称: 无

 @变量功能: 无
 *
 * @注    释: 无
 *
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
#if (osSignalAutoApply_Config > 0)//启用了信号量自动分配
_SignalHandle* osSignalLogin(_SignalType SP)
{
	_SignalHandle* ST;
	_SignalHandleValue* STV;
	if(SP >= Signal_Mutual && SP <= Signal_OrGroup){
		if(SP >=Signal_Count){
			STV = osSignalMemoryMalloc(sizeof(_SignalHandleValue));//为信号量结构体申请内存
		}else{
			ST = osSignalMemoryMalloc(sizeof(_SignalHandle));//为信号量结构体申请内存
		}
		if(ST == NULL && STV == NULL){//如果内存申请函数返回为零,说明申请失败
			#if (osSignalLog_Config > 0)
			osLogE("osSignalLogin","注册信号量时内存申请失败\n");
			#endif
			return (NULL);//返回空,表示错误
		}
		if(SP >=Signal_Count){
			STV -> Value = 0;//将信号值设为零
			STV -> Type = SP;//写入信号类型
			STV -> NextAddr = NULL;
			return (_SignalHandle*)STV;
		}else{
			ST -> Type = SP;//写入信号类型
			ST -> NextAddr = NULL;
			return (ST);
		}
		
	}else{
		#if (osSignalLog_Config > 0)
		osLogE("osSignalLogin","注册信号量时遇到未知类型\n");
		#endif
		return (NULL);
	}
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
OsErrorValue osSignalLogin(_SignalHandle* ST,_SignalType SP)
{
    switch(SP){
#if	(osSignal_Config & Signal_Mutual) 
        case Signal_Mutual://互斥信号量
                            ST ->SV = false;//将信号值设为假
                            ST ->SP = NULL;//写入信号类型
                            return (OK);
#endif
#if	(osSignal_Config & Signal_Binary)
        case Signal_Binary://二值信号量
                            ST ->SV = false;//将信号值设为假
							ST ->SP = NULL;//写入信号类型
							return (OK);
#endif
#if	(osSignal_Config & Signal_Count)
        case Signal_Count://计数信号量
							ST ->SV = 0;//将信号值设为零
                            ST ->SP = NULL;//写入信号类型
                            return (OK);
#endif
        default:
				#if (osSignalLog_Config > 0)
				osLogE("osSignalLogin","注册信号量时遇到未知类型\n");
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
 * @输入参数: _SignalHandle* ST(信号量结构体)
 *
 * @返 回 值: -1:发生错误 / 0:请求成功
 *
 * @注    释: 无
 *
 */

static OsErrorValue osSignalApplyToken(_SignalHandle* ST)
{
	_SignalToken* SemaphoreToken_Buf = osSignalMemoryMalloc(sizeof(_SignalToken));//为信号量结构体申请内存
	if(SemaphoreToken_Buf == NULL){
		#if (osSignalLog_Config > 0)
		osLogE("osSignalApplyToken","申请占用信号量令牌时内存申请失败\n");
		#endif
		return (Error);
	}else{
		SemaphoreToken_Buf -> DownAddr = NULL;
		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)osTaskGetRunTaskHandle();
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
 * @输入参数: _SignalHandle* ST(信号量结构体)
 *
 * @返 回 值: -1:发生错误 / 0:请求成功
 *
 * @注    释: 无
 *
 */

static OsErrorValue osSignalWaitToken(_SignalHandle* ST)
{
	_NextAddr* NextAddr_Buf;
	_NextAddr NextAddr_Buf1;
	_SignalToken* SemaphoreToken_Buf1;
	_TaskHandle*	TaskInfoTable_Buf;
	_SignalToken* SemaphoreToken_Buf = osSignalMemoryMalloc(sizeof(_SignalToken));//为信号量结构体申请内存
	if(SemaphoreToken_Buf == NULL){
		#if (osSignalLog_Config > 0)
		osLogE("osSignalWaitToken","申请等待信号量令牌时内存申请失败\n");
		#endif
		return (Error);
	}else{
		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)osTaskGetRunTaskHandle();
		SemaphoreToken_Buf -> DownAddr = NULL;
	
		NextAddr_Buf = &ST -> NextAddr;
		
		while(*NextAddr_Buf != NULL){
			SemaphoreToken_Buf1 = (_SignalToken*)*NextAddr_Buf;
			TaskInfoTable_Buf = (_TaskHandle*)SemaphoreToken_Buf1 -> TaskInfo;
			if(osTaskGetRunTaskHandle() -> Level < TaskInfoTable_Buf -> Level){
				NextAddr_Buf1 = (_NextAddr)*NextAddr_Buf;
				*NextAddr_Buf = (_NextAddr)SemaphoreToken_Buf;
				SemaphoreToken_Buf -> DownAddr = NextAddr_Buf1;
				if(NextAddr_Buf == &ST -> NextAddr){
					TaskInfoTable_Buf -> Config = Task_State_Up_SI;
					return (OK);
				}
				osTaskSwitchConfig_Config(osTaskGetRunTaskHandle(),Task_State_Up_SI);//触发异常,进行任务切换 //修改为信号挂起(等待态)
				return (OK);
			}
			NextAddr_Buf = (_NextAddr*)*NextAddr_Buf;
		}
		*NextAddr_Buf = (_NextAddr)SemaphoreToken_Buf;
		osTaskSwitchConfig_Config(osTaskGetRunTaskHandle(),Task_State_Up_SI);//触发异常,进行任务切换 //修改为信号挂起(等待态)
		return(OK);
	}
}


OsErrorValue osSignalUseWait(_SignalHandle* ST)
{
	_TaskHandle* TaskHandle;
	_SignalToken* SemaphoreToken_Buf;
	_SignalHandleValue* STV = (_SignalHandleValue*)ST;
	switch(ST -> Type){
#if	(osSignal_Config & Signal_Binary) 
		case Signal_Binary:	
							if(ST -> NextAddr != NULL){
								return osSignalWaitToken(ST);

							}else{
								return osSignalApplyToken(ST);
							}
#endif
#if	(osSignal_Config & Signal_Mutual) 
		case Signal_Mutual:
							if(ST -> NextAddr != NULL){
								SemaphoreToken_Buf = (_SignalToken*)ST -> NextAddr;
								TaskHandle = (_TaskHandle*)SemaphoreToken_Buf -> TaskInfo;
								if(osTaskGetRunTaskHandle() -> Level < TaskHandle -> Level){
									TaskHandle -> Level = osTaskGetRunTaskHandle() -> Level;//
								}
								return osSignalWaitToken(ST);
							}else{
								return osSignalApplyToken(ST);
							}
#endif
#if	(osSignal_Config & Signal_Count)
		case Signal_Count:
							if(STV -> Value > 0){
								STV -> Value =  STV -> Value - 1;
								return (OK);	
							}else{
								if(STV -> NextAddr != NULL){
									return osSignalWaitToken(ST);
								}else{
									return osSignalApplyToken(ST);
								}
							}
#endif
		default:
				#if (osSignalLog_Config > 0)
				osLogE("osSignalUseWait","占用信号量时输入未知类型\n");
				#endif
				return(Error);
	}
}


OsErrorValue osSignalUse(_SignalHandle* ST)
{
	if(ST -> NextAddr != NULL){
		return (Error);

	}else{
		return osSignalApplyToken(ST);
	}
}

/*
 *
 * @函数名称: osSignalFree
 *
 * @函数功能: 释放信号量
 *
 * @输入参数: _SignalHandle* ST(信号量结构体)
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
OsErrorValue osSignalFree(_SignalHandle* ST)
{
	_SignalToken* 	SemaphoreToken_Buf;
	_TaskHandle*	TaskInfoTable_Buf;
	_SignalHandleValue* STV = (_SignalHandleValue*)ST;
	switch(ST -> Type){
#if	(osSignal_Config & Signal_Binary)
		case Signal_Binary:
							break;
#endif
#if	(osSignal_Config & Signal_Mutual)
		case Signal_Mutual:
							osTaskGetRunTaskHandle() -> Level = osTaskGetRunTaskHandle() -> Levelb;
							break;
#endif
#if	(osSignal_Config & Signal_Count)
		case Signal_Count:	
							if(STV -> NextAddr == NULL){
								STV -> Value = STV -> Value + 1;
								return (OK);
							}
		case Signal_AndGroup:
		case Signal_OrGroup:
							break;
#endif
		default:
				#if (osSignalLog_Config > 0)
				osLogE("osSignalFree","释放信号量时类型错误\n");
				#endif
				return(Error);
	}
	if(ST -> NextAddr != NULL){
		SemaphoreToken_Buf = (_SignalToken*)uLinkListHeadRead(&ST -> NextAddr);
		TaskInfoTable_Buf = (_TaskHandle*)SemaphoreToken_Buf  -> TaskInfo;
		TaskInfoTable_Buf -> Config = Task_State_RE;  //主动挂起(挂起态)
		if(osSignalMemoryFree(SemaphoreToken_Buf) != OK){
			#if (osSignalLog_Config > 0)
			osLogE("osSignalFree","释放信号量时释放内存错误\n");
			#endif
			return (Error);
		}
		if(TaskInfoTable_Buf -> Level < osTaskGetRunTaskHandle() -> Level){
			osTaskSwitch_Config();//触发异常,进行任务切换
		}
		return (OK);
	}else{
		#if (osSignalLog_Config > 0)
		osLogW("osSignalFree","释放信号量时已经为空\n");
		#endif
		return (Error);
	}
}

/*
 *
 * @函数名称: osSignalLogout
 *
 * @函数功能: 信号量注销
 *
 * @输入参数: _SignalHandle* ST(信号量结构体)
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
OsErrorValue osSignalLogout(_SignalHandle* ST)
{
	ST -> NextAddr =  ST -> Type = 0;
	#if (osSignalAutoApply_Config > 0)//启用了信号量自动分配

	if(osSignalMemoryFree((uint8_t*)ST) == Error){//需要把信号量的所占内存释放
		#if (osSignalLog_Config > 0)
		osLogE("osSignalLogout","注销信号量时释放内存错误\n");
		#endif
		return (Error);//释放内存时,发生错误,返回错误
	}
	return (OK);//注销成功!返回OK
	#endif

}
OsErrorValue osSignalSetGroup(_SignalHandle* ST,uint8_t Bits,uint8_t SetBit,uint8_t SetValue)
{
	_SignalHandleValue* STV = (_SignalHandleValue*)ST;
	uint32_t Bit,Precision;
	if(ST -> Type >= Signal_AndGroup && ST -> Type <= Signal_AndGroup){
		Bit = 0x00000001;
		for(Precision = 32 / Bits;Precision > 1;Precision--){
			Bit = (Bit << 1) | 0x01;
		}
		Bit <<= (32 / Bits) * (SetBit - 1);
		if(SetValue){
			STV -> Value |=  Bit;
		}else{
			STV -> Value &= ~Bit;
		}
		switch(STV -> Type){
			case Signal_AndGroup:
				 if(STV -> Value != 0xFFFFFFFF){
					return (OK);
				 }
				 break;
			case Signal_OrGroup:
				 if(STV -> Value == 0x00000000){
					return (OK);
				 }
				 break;
			default:
				break;
			
		}
		STV -> Value = 0x00000000;
		osSignalFree(ST);
		return (OK);

	}else{
		#if (osSignalLog_Config > 0)
		osLogE("osSignalSetAndGroup","未知类型\n");
		#endif
		return (Error);
	}

}

#endif

