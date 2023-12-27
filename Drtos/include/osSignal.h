/**
 * Copyright 2022-2023 AhDun. All rights reserved.
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
/**
 *
 * @file .h
 *
 * @brief 无
 *
 * @note none
 *
 */


#ifndef __osSignal_H_
#define __osSignal_H_



#include "main.h"
#include "osConfig.h"


#if (osSignal_Config > 0)

//信号量类型{

//}


//信号量令牌{
typedef		uint32_t		_TaskInfo;
typedef struct
{
	_NextAddr  DownAddr;//下一个表的地址
	_TaskInfo*	TaskInfo;//任务句柄
}_SignalToken;
//}

//信号量句柄{
typedef     uint32_t    _SignalValue;
typedef     uint8_t     _SignalType;
typedef struct
{
    _SignalType   	 Type;//信号的类型
	_NextAddr		 NextAddr;//信号量令牌链头
}_SignalHandle;
typedef struct
{
    _SignalType   	 Type;//信号的类型
	_NextAddr		 NextAddr;//信号量令牌链头
	_SignalValue 	 Value;//信号值
}_SignalHandleValue;

//}




#if (osSignalAutoApply_Config > 0)//启用了信号量自动分配

/**
 *
 * @name osSignalLogin
 *
 * @brief 信号量注册
 *
 * @param _SignalHandle* ST(信号量结构体)
 *
 * @retval none
 *
 * @note none
 *
 */
_SignalHandle* osSignalLogin(_SignalType SP);
#else
OsErrorValue osSignalLogin(_SignalHandle* ST,_SignalType SP);
#endif
/**
 *
 * @name osSignalUseWait
 *
 * @brief 信号量等待式占用
 *
 * @param ST	信号量句柄
 *
 * @retval 0:占用成功  -1:占用失败
 *
 * @note none
 *
 */
OsErrorValue osSignalUseWait(_SignalHandle* ST);
/**
 *
 * @name osSignalUse
 *
 * @brief 信号量非等待式占用
 *
 * @param ST	信号量句柄
 *
 * @retval 0:占用成功  -1:占用失败
 *
 * @note none
 *
 */
OsErrorValue osSignalUse(_SignalHandle* ST);
/**
 *
 * @name osSignalFree
 *
 * @brief 信号量释放
 *
 * @param  ST	信号量句柄
 *
 * @retval 0:释放成功  -1:释放失败
 *
 * @note none
 *
 */
OsErrorValue osSignalFree(_SignalHandle* ST);


OsErrorValue osSignalSetGroup(_SignalHandle* ST,uint8_t Bits,uint8_t SetBit,uint8_t SetValue);



#endif

#endif
