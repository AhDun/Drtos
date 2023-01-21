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

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注    释: 

*/

/*
                                                  <引用文件区>
*/

/*
                                                  <宏定义区>
*/

#define osClockTimePeriod 					1000 //系统时间周期，单位us
#define osClockTimePeriodStandard			1000 //系统时间基准周期，单位us


#define TaskOccupyRatioSamplingTime 		1000 //任务统计时间，单位ms

/*
                                                  <数据声明区>
*/

#if (os_TotalSystemRunningTime_Enable > 0)//开启了系统运行时长
typedef u32 _TotalSystemRunningTime;//系统运行时间
#endif
typedef	u32	_TaskTimeWheelMargin;//任务轮片时间
#if (osClockTimePeriod < osClockTimePeriodStandard)
typedef u32 _ClockTimePeriodValue; //时间周期计数
#endif
typedef struct
{
#if (os_TotalSystemRunningTime_Enable > 0)//开启了系统运行时长
	_TotalSystemRunningTime TSRT;//系统运行时间
#endif
	_TaskTimeWheelMargin	   TTWM;//任务轮片时间
#if (osClockTimePeriod < osClockTimePeriodStandard)
	_ClockTimePeriodValue      CTPV;//时间周期计数
#endif
}osTIME;//系统时间

extern osTIME osTime;
/*
                                                  <函数声明区>
*/
extern osErrorValue osClockInit(void);

extern void osClockTimePulse(void);


#endif
/*
                                                  FILE-END
*/

