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
 * @文件名称: osClock.c
 *
 * @文件内容: 系统时钟文件
 *
 * @注    释: 
 *
 */


#include "osConfig.h"
#include "osClock.h"


/*
                                                  变量初始化区
*/
_NextAddr STimeListHead;
_TaskHandle* TaskHandle_STime;
#if (osPerformanceStatistics_Enable > 0)
_PerformanceStatistics PS;//性能统计
#endif
#if (os_TotalSystemRunningTime_Enable > 0)//开启了系统运行时长
_SystemRunningTime 		OsTimeSystemRunTime;//系统运行时间
_TaskISRRunningTime		OsTimeTaskISRTime;//系统运行时长
#endif
_TaskTimeWheelMargin	   OsTimeTaskTimeWheel;//任务轮片时间
#if (osClockTimePeriod < osClockTimePeriodStandard)
_ClockTimePeriodValue      OsTimePeriodValue;//时间周期计数
#endif

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
OsErrorValue osClockInit(void)
{
	if(osClock_Init() == Error){//如果时钟初始化错误
		return (Error);//表示时钟初始化时发生错误,返回错误
	}
	return (OK);//返回OK
}
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
void osClockTimePulse(void)
{
	/*本函数已在中断响应入口中，下面是这个函数的副本*/
	_TaskHandle* TaskHandleListBuf;

	#if (osClockTimePeriod < osClockTimePeriodStandard) //
	if(++OsTimeGetPeriodValue() >= (osClockTimePeriodStandard /osClockTimePeriod)){
		OsTimeGetPeriodValue() = NULL;
	#endif
    /*----------------------------------计时---------------------------------------*/
	#if (os_TotalSystemRunningTime_Enable > 0)//开启了系统运行时长
	#if (osClockTimePeriod > osClockTimePeriodStandard)
	OsTimeGetSystemRunTime() += (osClockTimePeriod / osClockTimePeriodStandard);//系统运行时长进行计时
	#else
	OsTimeGetSystemRunTime() += 1;//系统运行时长进行计时
	#endif
	#endif
     /*----------------------------------统计---------------------------------------*/
	#if (osPerformanceStatistics_Enable > 0) //开启了性能统计
	if(osTaskGetOIRQFlag() > NULL){
		OsTimeGetTaskISRTime()++;
	}
	else if(osTaskGetSwitchState() == TaskSwitch_Ready){//任务调度状态为未调度，进行计时
        osTaskGetRunTaskHandle() -> OccupyTime++;//任务占用时长计数
    }
    if(OsTimeGetSystemRunTime() % TaskOccupyRatioSamplingTime == 0){//系统每过一定时长，就进行占用比例统计
        PS.CTO = 0;//CPU占用量设为0
		TaskHandleListBuf = osTaskGetTaskHandleListHead();
		do{//对每一个任务进行遍历
			//TaskHandleListBuf -> OccupyRatio = TaskHandleListBuf -> OccupyTime / (TaskOccupyRatioSamplingTime / 100);//计算这个任务占用比
			TaskHandleListBuf -> OccupyRatio = TaskHandleListBuf -> OccupyTime;//计算这个任务占用比
			//计算公式：占用比 = 单位时间内的占用时长 / (单位时间 / 100)
            PS.CTO += TaskHandleListBuf -> OccupyRatio / (TaskOccupyRatioSamplingTime / 100);//计算CPU占用量
			//计算公式：CPU占用量 = CPU占用量 + 每个任务的占用量
            TaskHandleListBuf -> OccupyTime = 0;//清空单位时间内的占用时长

			TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
		}while(TaskHandleListBuf != osTaskGetTaskHandleListHead());
		if(OsTimeGetTaskISRTime() > NULL){
			PS.CISRO = OsTimeGetTaskISRTime() / (TaskOccupyRatioSamplingTime / 100);//计算CPU占用量
			OsTimeGetTaskISRTime() = 0;
		}
		PS.CSO = (PS.TSC * PS.TSSU) / (TaskOccupyRatioSamplingTime /100) /1000;
		PS.TSCb = PS.TSC;
		PS.TSC = 0;
    }
	#endif
    /*----------------------------------轮片---------------------------------------*/
    if(OsTimeGetTaskTimeWheel() > 0 && osTaskGetSwitchState() == TaskSwitch_Ready && osTaskGetOIRQFlag() == NULL){ //时间轮片
	   //当前正在运行的任务的轮片时间大于0并且调度状态为未调度状态
        if(--OsTimeGetTaskTimeWheel() == 0){//当目前正在运行的任务的轮片时间为零时
			osTaskSwitch_Enable();//触发任务切换   
        }
    }
	TaskHandleListBuf = osTaskGetTaskHandleListHead();
	do{//对每一个任务进行遍历
		/*----------------------------------延时---------------------------------------*/
        if(TaskHandleListBuf -> Config == Task_State_Up_DT){//这个任务是延时挂起(等待态)，才进入
            TaskHandleListBuf -> TimeFlag--;//把这个任务时间标志中内容减一
            if(TaskHandleListBuf -> TimeFlag == 0){	//当这个任务时间标志中内容为零时
                if(osTaskGetSwitchState() != TaskSwitch_Ready){//如果已经正在调度中，就把这个任务设为轮片挂起(挂起态)
                    //TaskHandleListBuf  -> Config &= TIT_Task_State_TC_RST;//清除这个任务的状态位
                    TaskHandleListBuf  -> Config = Task_State_RE;//将这个任务的状态设为轮片挂起(挂起态)
                }
                else if(TaskHandleListBuf -> PriorityLevel <  osTaskGetRunTaskHandle() -> PriorityLevel){//如果这个任务高于当前工作运行任务栏的优先级，就占用
                    TaskHandleListBuf -> Config = Task_State_RE;//将这个任务的状态设为轮片挂起(挂起态)
                    if(osTaskGetSwitchState() == TaskSwitch_Ready){//查询是否己被悬起，如果没有就触发任务切换
                        osTaskGetNextTaskHandle() = TaskHandleListBuf;//把这个任务ID加载到任务调度计数中，这样任务调度才认识这个任务，否则将会向下调度
                        osTaskSwitch_Enable(); //触发任务切换
                    }
                }
                else{//意外之料的情况
                        TaskHandleListBuf -> Config = Task_State_RE;//将这个任务的状态设为轮片挂起(挂起态)
                }
            }
        }
		TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
	}while(TaskHandleListBuf != osTaskGetTaskHandleListHead());
	#if (osClockTimePeriod < osClockTimePeriodStandard)
	}
	#endif
}

_STimes* osTimeLogin_Static(uint8_t* ListAddr,_STimeName* Name,_STimeFlag Flag,_STimeConfig Config,void* Addr)
{
	_STimes* STime_Buf = (_STimes*)ListAddr;
	STime_Buf -> Name = Name;
	STime_Buf -> Addr = (_STimeAddr*)Addr;
	STime_Buf -> Flag = Flag;
	STime_Buf -> Config = Config;
	if(Config < STimeConfig_NRestartL){
		STime_Buf -> Flagb = Flag;
	}
	if(uLinkListTailWrtie(&STimeListHead,(uint32_t*)ListAddr) == OK){
		return STime_Buf;
	}else{
		return NULL;
	}
}


_STimes* osTimeLogin(_STimeName* Name,_STimeFlag Flag,_STimeConfig Config,void* Addr)
{
	uint8_t* Addr1;
	if(Config >= STimeConfig_NRestartL){
		Addr1 = osMemoryMalloc(sizeof(_STime));//为任务表分配内存
	}else{
		Addr1 = osMemoryMalloc(sizeof(_STimes));//为任务表分配内存
	}
//	if(Addr1 == NULL){//如果为空，就说明内存分配失败
//		#if (osTaskDebug_Enable > 0)
//		osTaskErrorDebug("注册任务时,任务分配内存失败 %s\n",TN);
//		#endif
//		return (NULL);//返回错误
//	}
	return osTimeLogin_Static(Addr1, Name, Flag, Config, Addr);
}

OsErrorValue osSTimeInit(void)
{
	STimeListHead = NULL;
	TaskHandle_STime = osTaskLogin("STime",osSTime,400,TaskTimeWheelDefault,-126,(void*)0,Task_Set_Default); 
	if(TaskHandle_STime == NULL){

		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("SIRQ 任务创建失败\n");
		#endif
		return (Error);//返回Error
	}
	return (OK);
}

void osSTime(void)
{
	_STimes* STime_Buf;
	while(1){
		STime_Buf = (_STimes*)STimeListHead;
		while(STime_Buf != NULL){
			STime_Buf -> Flag -= 1;
			if(STime_Buf -> Flag == 0){
				Jump((uint32_t*)STime_Buf -> Addr);
				switch(STime_Buf -> Config){
					case STimeConfig_Restart:STime_Buf -> Flag =  STime_Buf -> Flagb;break;
					case STimeConfig_NRestartL: break;
					case STimeConfig_NRestart: break;
				}
			}
			STime_Buf = (_STimes*)STime_Buf -> DownAddr;
		}
		osTaskDelayMs(1);
	}
	
}


