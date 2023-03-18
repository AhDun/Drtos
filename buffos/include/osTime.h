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
#ifndef __osClockH_
#define __osClockH_

/*
 *
 * @文件名称: osClock.h
 *
 * @文件内容: 
 *
 * @注    释: 
 *
 */




//定时器类型{
#define STimeConfig_Restart		0x01 // 重复
#define STimeConfig_NRestartL	0x02 // 一次并删除
#define STimeConfig_NRestart	0x03 // 一次
//}



/*
 *
 * @函数名称: osClockGetOsRTC
 *
 * @函数功能: 获取OSRTC
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osClockGetOsRTC()		OsTimeSystemRunTime		
/*
 *
 * @函数名称: osClockGetOsRTCD
 *
 * @函数功能: 获取OSRTC天数
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osClockGetOsRTCD()	(osClockGetOsRTC() / 1000) /86400
/*
 *
 * @函数名称: osClockRTCGetH
 *
 * @函数功能: 获取OSRTC小时数
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osClockGetOsRTCH()		((osClockGetOsRTC() / 1000) /3600) % 24
/*
 *
 * @函数名称: osClockRTCGetH
 *
 * @函数功能: 获取OSRTC分钟数
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osClockGetOsRTCM()	((osClockGetOsRTC() / 1000) /60) % 60
/*
 *
 * @函数名称: osClockRTCGetH
 *
 * @函数功能: 获取OSRTC秒数
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define osClockGetOsRTCS()	(osClockGetOsRTC() / 1000) % 60


/*
 *
 * @函数名称: osClockGetTimePulse
 *
 * @函数功能: 获取系统的时钟数
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define OsTimeGetSystemRunTime()		OsTimeSystemRunTime
/*
 *
 * @函数名称: osClockGetTimePulse
 *
 * @函数功能: 获取系统的时钟数
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define OsTimeGetTaskISRTime()			OsTimeTaskISRTime

/*
 *
 * @函数名称: osClockGetTimePulse
 *
 * @函数功能: 获取系统的时钟数
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define OsTimeGetTaskTimeWheel()			OsTimeTaskTimeWheel
/*
 *
 * @函数名称: osClockGetTimePulse
 *
 * @函数功能: 获取系统的时钟数
 *
 * @输入参数: 无	
 *
 * @返 回 值: 无
 *
 * @注    释: 无
*/
#define OsTimeGetPeriodValue()			OsTimePeriodValue


//系统时间{
#if (os_TotalSystemRunningTime_Config > 0)//开启了系统运行时长
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


//性能统计{
#if (osPerformanceStatistics_Config > 0)
typedef  uint8_t  	_CPUTaskOccupy;//任务占用比
typedef  uint8_t  	_CPUISROccupy;//中断占用比
typedef	 uint8_t 	_CPUSwitchOccupy;//切换占用比
typedef	 uint32_t	_TaskSwitchConut;//任务调度次数
typedef	 double		_TaskSwitchSpeedUs;//任务切换速度测试
typedef struct
{
 
	_CPUTaskOccupy  	CTO;//任务占用比
	_CPUISROccupy		CISRO;//中断占用比
	_CPUSwitchOccupy	CSO;//切换占用比
	_TaskSwitchConut	TSC;//任务调度次数
	_TaskSwitchConut	TSCb;//任务调度次数
	_TaskSwitchSpeedUs	TSSU;//任务切换速度测试

}_PerformanceStatistics;

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
}_STimes;//可重载
//}
#endif

extern _PerformanceStatistics PS;//性能统计

extern _NextAddr STimeListHead;

extern _TaskHandle* TaskHandle_STime;



/*
 *
 * @函数名称: osClockInit
 *
 * @函数功能: 系统时钟初始化
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
OsErrorValue osClockInit(void);
/*
 *
 * @函数名称: osClockTimePulse
 *
 * @函数功能: 系统时钟脉冲处理
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void osClockTimePulse(void);

/*
 *
 * @函数名称: osTimeLogin_Static
 *
 * @函数功能: 软定时器注册
 *
 * @输入参数: ListAddr	软定时器句柄地址
 * @输入参数: Name	软定时器名称
 * @输入参数: Flag	软定时器类型标志
 * @输入参数: Config	软定时器句柄配置
 * @输入参数: Addr	回调函数地址
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
_STimes* osTimeLogin_Static(uint8_t* ListAddr,_STimeName* Name,_STaskDelay Flag,_STimeConfig Config,void* Addr);
/*
 *
 * @函数名称: osSTimeLogout
 *
 * @函数功能: 软定时器注销
 *
 * @输入参数: STimes	软定时器地址
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
OsErrorValue osSTimeLogout(_STimes* STimes);
/*
 *
 * @函数名称: osTimeLogin
 *
 * @函数功能: 软定时器注册
 *
 * @输入参数: Name	软定时器名称
 * @输入参数: Flag	软定时器类型标志
 * @输入参数: Config	软定时器句柄配置
 * @输入参数: Addr	回调函数地址
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */

_STimes* osTimeLogin(_STimeName* Name,_STaskDelay Flag,_STimeConfig Config,void* Addr);
/*
 *
 * @函数名称: osSTimeInit
 *
 * @函数功能: 软定时器初始化
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
OsErrorValue osSTimeInit(void);
/*
 *
 * @函数名称: osSTime
 *
 * @函数功能: 软定时器响应程序
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
void osSTime(void);


#endif



