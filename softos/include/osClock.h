/*
                                                  FILE-START
*/
#ifndef __osClockH_
#define __osClockH_

/*

 *@文件名称: osClock.h

 *@文件内容: 

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@注    释: 

*/

/*
                                                  <引用文件区>
*/

/*
                                                  <宏定义区>
*/

#define osClock_Enable 	//启用时钟 ！这个定义无需手动配置，用于自动标记文件，自动增减功能


#define TaskOccupyRatioSamplingTime 		1000 //任务统计时间，单位ms

#define osClockGetTimePulse()	osTime. TSRT

/*
                                                  <数据声明区>
*/

#if (os_TotalSystemRunningTime_Enable > 0)//开启了系统运行时长
typedef uint32_t _TotalSystemRunningTime;//系统运行时间
typedef uint32_t _TaskISRRunningTime;//系统运行时间
#endif
typedef	uint32_t	_TaskTimeWheelMargin;//任务轮片时间
#if (osClockTimePeriod < osClockTimePeriodStandard)
typedef uint32_t _ClockTimePeriodValue; //时间周期计数
#endif

//系统时间{
typedef struct
{
	#if (os_TotalSystemRunningTime_Enable > 0)//开启了系统运行时长
	_TotalSystemRunningTime 	TSRT;//系统运行时间
	_TaskISRRunningTime			TISRRT;
	#endif
	_TaskTimeWheelMargin	   TTWM;//任务轮片时间
	#if (osClockTimePeriod < osClockTimePeriodStandard)
	_ClockTimePeriodValue      CTPV;//时间周期计数
	#endif
}osTIME;
//}

#if (osPerformanceStatistics_Enable > 0)
typedef  uint8_t  	_CPUTaskOccupy;//
typedef  uint8_t  	_CPUISROccupy;//
typedef	 uint8_t 	_CPUSwitchOccupy;
typedef		uint32_t		_TaskSwitchConut;//任务调度次数
typedef		uint8_t		_TaskSwitchSpeedUs;//任务切换速度测试

//性能统计{
typedef struct
{
 
	_CPUTaskOccupy  	CTO;//
	_CPUISROccupy		CISRO;//
	_CPUSwitchOccupy	CSO;//
	_TaskSwitchConut	TSC;//任务调度次数
	_TaskSwitchConut	TSCb;//任务调度次数
	_TaskSwitchSpeedUs	TSSU;//任务切换速度测试

}_PerformanceStatistics;
//}
#endif

extern _PerformanceStatistics PS;//性能统计
extern osTIME osTime;
/*
                                                  <函数声明区>
*/
/*

 *@函数名称: osClockInit

 *@函数版本: 1.0.0

 *@函数功能: 系统时钟初始化

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
osErrorValue osClockInit(void);
/*

 *@函数名称: osClockTimePulse

 *@函数版本: 1.0.0

 *@函数功能: 系统时钟脉冲处理

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
void osClockTimePulse(void);


#endif
/*
                                                  FILE-END
*/

