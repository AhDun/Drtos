/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
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

#endif
