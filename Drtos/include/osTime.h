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
#ifndef __osClockH_
#define __osClockH_

/**
 *
 * @file osClock.h
 *
 * @brief 
 *
 * @note 
 *
 */




//定时器类型{
#define STimeConfig_Restart		0x01 // 重复
#define STimeConfig_NRestartL	0x02 // 一次并删除
#define STimeConfig_NRestart	0x03 // 一次
//}



/**
 *
 * @name osClockGetOsRTC
 *
 * @brief 获取OSRTC
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osClockGetOsRTC()		OsTimeSystemRunTime		
/**
 *
 * @name osClockGetOsRTCD
 *
 * @brief 获取OSRTC天数
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osClockGetOsRTCD()	(osClockGetOsRTC() / 1000) /86400
/**
 *
 * @name osClockRTCGetH
 *
 * @brief 获取OSRTC小时数
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osClockGetOsRTCH()		((osClockGetOsRTC() / 1000) /3600) % 24
/**
 *
 * @name osClockRTCGetH
 *
 * @brief 获取OSRTC分钟数
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osClockGetOsRTCM()	((osClockGetOsRTC() / 1000) /60) % 60
/**
 *
 * @name osClockRTCGetH
 *
 * @brief 获取OSRTC秒数
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osClockGetOsRTCS()	(osClockGetOsRTC() / 1000) % 60


/**
 *
 * @name osClockGetTimePulse
 *
 * @brief 获取系统的时钟数
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define OsTimeGetSystemRunTime()		OsTimeSystemRunTime
/**
 *
 * @name osClockGetTimePulse
 *
 * @brief 获取系统的时钟数
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define OsTimeGetTaskISRTime()			OsTimeTaskISRTime

/**
 *
 * @name osClockGetTimePulse
 *
 * @brief 任务轮片时间
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define OsTimeGetTaskTimeWheel()			OsTimeTaskTimeWheel
/**
 *
 * @name osClockGetTimePulse
 *
 * @brief 获取系统的时钟数
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define OsTimeGetPeriodValue()			OsTimePeriodValue


//系统时间{
#if (osRunTime_Config > 0)//开启了系统运行时长
typedef uint32_t _SystemRunningTime;//系统运行时间
extern _SystemRunningTime 		OsTimeSystemRunTime;//系统运行时间
typedef uint32_t _TaskISRRunningTime;//系统运行时间
extern _TaskISRRunningTime		OsTimeTaskISRTime;//系统运行时长
#endif
typedef	uint32_t	_TaskWheelMargin;//任务轮片时间
extern _TaskWheelMargin	   OsTimeTaskTimeWheel;//任务轮片时间
#if (osClockTimePeriod < osClockTimePeriodStandard)
typedef uint32_t _ClockTimePeriodValue; //时间周期计数
extern _ClockTimePeriodValue      OsTimePeriodValue;//时间周期计数
#endif
typedef	uint16_t			_OsTimePeriod;
extern _OsTimePeriod		OsTimePeriod;


//性能统计{
#if (osPerf_Config > 0)
typedef  uint8_t  	_CPUTaskOccupy;//任务占用比
typedef  uint8_t  	_CPUISROccupy;//中断占用比
typedef	 uint8_t 	_CPUSwitchOccupy;//切换占用比
typedef	 uint32_t	_TaskSwitchConut;//任务调度次数
typedef	 double		_TaskSwitchSpeedUs;//任务切换速度测试
typedef struct
{
	_TaskSwitchConut	TSC;//任务调度次数
	_CPUTaskOccupy  	CTO;//任务占用比
	_CPUISROccupy		CISRO;//中断占用比
	_CPUSwitchOccupy	CSO;//切换占用比
	_TaskSwitchConut	TSCb;//任务调度次数
	_TaskSwitchSpeedUs	TSSU;//任务切换速度测试

}_OSRecord;
extern _OSRecord OSRecord;//性能统计

//}
#endif

//软件定时器{
typedef	 uint8_t		_STimeName;
typedef	 uint32_t		_STaskDelay;
typedef	 uint8_t		_STimeConfig;
typedef	 uint32_t		_STimeAddr;
typedef struct
{
	_NextAddr	  DownAddr;//下一个邮件的地址
	_STimeName* 	Name;
	_STimeConfig  	Config;
	_STimeAddr*	  	Addr;
	_STaskDelay		Flag;
}_STime;//不可重载

typedef struct
{
	_NextAddr	  DownAddr;//下一个邮件的地址
	_STimeName* 	Name;
	_STimeConfig  	Config;
	_STimeAddr*	  	Addr;
	_STaskDelay		Flag;
	_STaskDelay		Flagb;
}_STimer;//可重载




/**
 *
 * @name osClockInit
 *
 * @brief 系统时钟初始化
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
OsErrorValue osClockInit(void);
/**
 *
 * @name osClockTimePulse
 *
 * @brief 系统时钟脉冲处理
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
void osClockTimePulse(void);

/**
 *
 * @name osTimeLoginStatic
 *
 * @brief 软定时器注册
 *
 * @param ListAddr	软定时器句柄地址
 * @param Name	软定时器名称
 * @param Flag	软定时器类型标志
 * @param Config	软定时器句柄配置
 * @param Addr	回调函数地址
 *
 * @retval none
 *
 * @note none
 *
 */
_STimer* osTimerLoginStatic(uint8_t* ListAddr,_STimeName* Name,_STaskDelay Flag,_STimeConfig Config,void* Addr);
/**
 *
 * @name osSTimeLogout
 *
 * @brief 软定时器注销
 *
 * @param STimer	软定时器地址
 *
 * @retval none
 *
 * @note none
 *
 */
OsErrorValue osSTimerLogout(_STimer* STimer);
/**
 *
 * @name osTimeLogin
 *
 * @brief 软定时器注册
 *
 * @param Name	软定时器名称
 * @param Flag	软定时器类型标志
 * @param Config	软定时器句柄配置
 * @param Addr	回调函数地址
 *
 * @retval none
 *
 * @note none
 *
 */

_STimer* osTimerLogin(_STimeName* Name,_STaskDelay Flag,_STimeConfig Config,void* Addr);
/**
 *
 * @name osSTimeInit
 *
 * @brief 软定时器初始化
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
OsErrorValue osSTimerInit(void);
/**
 *
 * @name osSTime
 *
 * @brief 软定时器响应程序
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
void osSTimer(void);


#endif



