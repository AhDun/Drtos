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
 * @文件名称: .h
 *
 * @文件内容: 无
 *
 * @注    释: 无
 *
 */


#ifndef __osSignal_H_
#define __osSignal_H_


#include "main.h"
#include "osConfig.h"

//信号量类型{
#define Signal_Mutual       0x01u//互斥信号量
#define Signal_Binary       0x02u//二值信号量
#define Signal_Count        0x03u//计数信号量
#define Signal_AndGroup		0x04u//与组
#define Signal_OrGroup		0x05u//或组
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

/*
 *
 * @函数名称: osSignalLogin
 *
 * @函数功能: 信号量注册
 *
 * @输入参数: _SignalHandle* ST(信号量结构体)
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
_SignalHandle* osSignalLogin(_SignalType SP);
#else
OsErrorValue osSignalLogin(_SignalHandle* ST,_SignalType SP);
#endif
/*
 *
 * @函数名称: osSignalUseWait
 *
 * @函数功能: 信号量等待式占用
 *
 * @输入参数: ST	信号量句柄
 *
 * @返 回 值: 0:占用成功  -1:占用失败
 *
 * @注    释: 无
 *
 */
OsErrorValue osSignalUseWait(_SignalHandle* ST);
/*
 *
 * @函数名称: osSignalUse
 *
 * @函数功能: 信号量非等待式占用
 *
 * @输入参数: ST	信号量句柄
 *
 * @返 回 值: 0:占用成功  -1:占用失败
 *
 * @注    释: 无
 *
 */
OsErrorValue osSignalUse(_SignalHandle* ST);
/*
 *
 * @函数名称: osSignalFree
 *
 * @函数功能: 信号量释放
 *
 * @输入参数:  ST	信号量句柄
 *
 * @返 回 值: 0:释放成功  -1:释放失败
 *
 * @注    释: 无
 *
 */
OsErrorValue osSignalFree(_SignalHandle* ST);


OsErrorValue osSignalSetGroup(_SignalHandle* ST,uint8_t Bits,uint8_t SetBit,uint8_t SetValue);





#endif
