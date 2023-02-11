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
osTIME osTime;//系统时间
#if (osPerformanceStatistics_Enable > 0)
_PerformanceStatistics PS;//性能统计
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
osErrorValue osClockInit(void)
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
	uint32_t _tr0;//变量初始化

	#if (osClockTimePeriod < osClockTimePeriodStandard) //
	if(++osTime.CTPV >= (osClockTimePeriodStandard /osClockTimePeriod)){
		osTime.CTPV = NULL;
	#endif
    /*----------------------------------计时---------------------------------------*/
	#if (os_TotalSystemRunningTime_Enable > 0)//开启了系统运行时长
	#if (osClockTimePeriod > osClockTimePeriodStandard)
	osTime. TSRT += (osClockTimePeriod / osClockTimePeriodStandard);//系统运行时长进行计时
	#else
	osTime. TSRT += 1;//系统运行时长进行计时
	#endif
	#endif
     /*----------------------------------统计---------------------------------------*/
	#if (osPerformanceStatistics_Enable > 0) //开启了性能统计
	if(TaskSwitchState.ISRFlag > NULL){
		osTime.TISRRT++;
	}
	else if(TaskSwitchState.SwitchState == TaskSwitch_Ready){//任务调度状态为未调度，进行计时
        RunTaskHandle -> OccupyTime++;//任务占用时长计数
    }
    if(osTime. TSRT % TaskOccupyRatioSamplingTime == 0){//系统每过一定时长，就进行占用比例统计
        PS.CTO = 0;//CPU占用量设为0
        for(_tr0 = NULL;_tr0 < TaskSwitchState.TaskListMax;_tr0++){//对每一个任务进行遍历
            //TaskList[_tr0].TaskHandle -> OccupyRatio = TaskList[_tr0].TaskHandle -> OccupyTime / (TaskOccupyRatioSamplingTime / 100);//计算这个任务占用比
			TaskList[_tr0].TaskHandle -> OccupyRatio = TaskList[_tr0].TaskHandle -> OccupyTime;//计算这个任务占用比
			//计算公式：占用比 = 单位时间内的占用时长 / (单位时间 / 100)
            PS.CTO += (TaskList[_tr0].TaskHandle -> OccupyRatio / (TaskOccupyRatioSamplingTime / 100));//计算CPU占用量
			//计算公式：CPU占用量 = CPU占用量 + 每个任务的占用量
            TaskList[_tr0].TaskHandle -> OccupyTime = 0;//清空单位时间内的占用时长
        }
		if(osTime.TISRRT > NULL){
			PS.CISRO = (osTime.TISRRT / (TaskOccupyRatioSamplingTime / 100));//计算CPU占用量
			osTime.TISRRT = 0;
		}
		PS.CSO = ((PS.TSC * PS.TSSU) / (TaskOccupyRatioSamplingTime)) / 10;
		PS.TSCb = PS.TSC;
		PS.TSC = 0;
    }
	#endif
    /*----------------------------------轮片---------------------------------------*/
    if(osTime.TTWM > 0 && TaskSwitchState.SwitchState == TaskSwitch_Ready && TaskSwitchState.ISRFlag == NULL){ //时间轮片
	   //当前正在运行的任务的轮片时间大于0并且调度状态为未调度状态
        osTime.TTWM--;//当前正在运行的任务的轮片时间减一
        if(osTime.TTWM == 0){//当目前正在运行的任务的轮片时间为零时
            //RunTaskHandle -> Config &= TIT_Task_State_TC_RST;//清除正在运行的任务的状态位
            RunTaskHandle -> Config = Task_State_Up_TD;//将正在运行的任务的状态设为位轮片挂起(挂起态)
            if(TaskSwitchState.SwitchState == TaskSwitch_Ready){//查询是否己被悬起，如果没有就触发任务切换
                osTaskSwitch_Enable();//触发任务切换
            }
            else{//如果已经悬起了
                osTime.TTWM = 1;//当前正在运行的任务的轮片时间置为一，意味着轮片时间向后推迟一秒
            }
             
        }
    }
    for(_tr0 = NULL;_tr0 < TaskSwitchState.TaskListMax;_tr0++){//根据任务最大活动量，进行遍历
		/*----------------------------------延时---------------------------------------*/
        if(TaskList[_tr0].TaskHandle -> Config == Task_State_Up_DT){//这个任务是延时挂起(等待态)，才进入
            TaskList[_tr0].TaskHandle -> TimeFlag--;//把这个任务时间标志中内容减一
            if(TaskList[_tr0].TaskHandle -> TimeFlag == 0){	//当这个任务时间标志中内容为零时
                if(TaskSwitchState.SwitchState != TaskSwitch_Ready){//如果已经正在调度中，就把这个任务设为轮片挂起(挂起态)
                    //TaskList[_tr0].TaskHandle  -> Config &= TIT_Task_State_TC_RST;//清除这个任务的状态位
                    TaskList[_tr0].TaskHandle  -> Config = Task_State_Up_TD;//将这个任务的状态设为轮片挂起(挂起态)
                }
                else if(TaskList[_tr0].TaskHandle -> PriorityLevel <  RunTaskHandle -> PriorityLevel){//如果这个任务高于当前工作运行任务栏的优先级，就占用
                    //TaskList[_tr0].TaskHandle -> Config &= TIT_Task_State_TC_RST;//清除这个任务的状态位
                    TaskList[_tr0].TaskHandle -> Config = Task_State_Up_TD;//将这个任务的状态设为轮片挂起(挂起态)
                    //RunTaskHandle -> Config &= TIT_Task_State_TC_RST;//清除正在运行任务的状态位
                    RunTaskHandle -> Config = Task_State_Up_TD;//将正在运行任务的状态设为轮片挂起(挂起态)
                    if(TaskSwitchState.SwitchState == TaskSwitch_Ready){//查询是否己被悬起，如果没有就触发任务切换
                        TaskSwitchState.DispatchNum = _tr0;//把这个任务ID加载到任务调度计数中，这样任务调度才认识这个任务，否则将会向下调度
                        osTaskSwitch_Enable(); //触发任务切换
                    }
                    else{//如果已经悬起了
                        TaskList[_tr0].TaskHandle -> TimeFlag = 1;//当前正在运行的任务的轮片时间置为一，意味着轮片时间向后推迟一秒
                    }
                }
                else{//意外之料的情况
                        //TaskList[_tr0].TaskHandle -> Config &= TIT_Task_State_TC_RST;//清除这个任务的状态位
                        TaskList[_tr0].TaskHandle -> Config = Task_State_Up_TD;//将这个任务的状态设为轮片挂起(挂起态)
                }
            }
        }
    }
	#if (osClockTimePeriod < osClockTimePeriodStandard)
	}
	#endif
}






