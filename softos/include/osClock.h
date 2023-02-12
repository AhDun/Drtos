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


#define osClock_Enable 	//启用时钟 ！这个定义无需手动配置，用于自动标记文件，自动增减功能


#define TaskOccupyRatioSamplingTime 		1000 //任务统计时间，单位ms

#define STimeConfig_Restart		0x01
#define STimeConfig_NRestartL	0x02
#define STimeConfig_NRestart	0x03

#define osClockGetTimePulse()		osTime.TSRT//获取系统的时钟数


//系统时间{
#if (os_TotalSystemRunningTime_Enable > 0)//开启了系统运行时长
typedef uint32_t _TotalSystemRunningTime;//系统运行时间
typedef uint32_t _TaskISRRunningTime;//系统运行时间
#endif
typedef	uint32_t	_TaskTimeWheelMargin;//任务轮片时间
#if (osClockTimePeriod < osClockTimePeriodStandard)
typedef uint32_t _ClockTimePeriodValue; //时间周期计数
#endif
typedef struct
{
	#if (os_TotalSystemRunningTime_Enable > 0)//开启了系统运行时长
	_TotalSystemRunningTime 	TSRT;//系统运行时间
	_TaskISRRunningTime			TISRRT;//系统运行时长
	#endif
	_TaskTimeWheelMargin	   TTWM;//任务轮片时间
	#if (osClockTimePeriod < osClockTimePeriodStandard)
	_ClockTimePeriodValue      CTPV;//时间周期计数
	#endif
}osTIME;
//}

//性能统计{
#if (osPerformanceStatistics_Enable > 0)
typedef  uint8_t  	_CPUTaskOccupy;//任务占用比
typedef  uint8_t  	_CPUISROccupy;//中断占用比
typedef	 uint8_t 	_CPUSwitchOccupy;//切换占用比
typedef	 uint32_t	_TaskSwitchConut;//任务调度次数
typedef	 uint8_t	_TaskSwitchSpeedUs;//任务切换速度测试
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
typedef	 uint32_t		_STimeFlag;
typedef	 uint8_t		_STimeConfig;
typedef	 uint32_t		_STimeAddr;
typedef struct
{
	_NextAddr	  DownAddr;//下一个邮件的地址
	_STimeName* 	Name;
	_STimeConfig  	Config;
	_STimeAddr*	  	Addr;
	_STimeFlag		Flag;
}_STime;

typedef struct
{
	_NextAddr	  DownAddr;//下一个邮件的地址
	_STimeName* 	Name;
	_STimeConfig  	Config;
	_STimeAddr*	  	Addr;
	_STimeFlag		Flag;
	_STimeFlag		Flagb;
}_STimes;
//}
#endif

extern _PerformanceStatistics PS;//性能统计

extern _NextAddr STimeListHead;
extern _TaskHandle* TaskHandle_STime;

extern osTIME osTime;

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
osErrorValue osClockInit(void);
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


_STimes* osTimeLogin_Static(uint8_t* ListAddr,_STimeName* Name,_STimeFlag Flag,_STimeConfig Config,void* Addr);
_STimes* osTimeLogin(_STimeName* Name,_STimeFlag Flag,_STimeConfig Config,void* Addr);
osErrorValue osSTimeInit(void);
void osSTime(void);


#endif


