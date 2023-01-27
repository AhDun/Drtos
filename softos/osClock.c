/*
                                                  FILE-START
*/

/*

* softos内核

* 版权所有(C) 2023 AhDun 版权所有.

* 本处现免费准许任何人士取得本处的副本

* 本软件和相关的文档文件(以下简称“软件”)，用于处理

* 本软件不受限制，包括但不限制的权利

* 使用、复制、修改、合并、发布、分发、转许可和/或销售的副本软件，并允许向其提供软件的人这样做，

* 须符合以下条件:

* 上述版权声明及本许可声明应包括在所有

* 本软件的副本或大部分。

* 软件是“按原样”提供的，没有任何形式的保证，明示或

* 暗示，包括但不限于适销性、适用性的保证

* 用于特定目的和不侵权。在任何情况下，作者或

* 版权拥有人须承担任何申索、损害赔偿或其他责任，不论是否

* 在合同、侵权或其他诉讼中，由，由或在

* 与软件的联系或对软件的使用或其他交易。

*/

/*

 *@文件名称: osClock.c

 *@文件内容: 系统时钟文件

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@注    释: 

*/

/*
                                                  <引用文件区>
*/
#include "osConfig.h"
#include "osClock.h"

/*
                                                  变量初始化区
*/
osTIME osTime;//系统时间
/*
                                                  <函数区>
*/
/*

 *@函数名称: osClockInit

 *@函数版本: 1.0.0

 *@函数功能: 系统时钟初始化

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
osErrorValue osClockInit(void)
{
	if(osClock_Init() == Error){//如果时钟初始化错误
		return (Error);//表示时钟初始化时发生错误,返回错误
	}
	return (OK);//返回OK
}
/*

 *@函数名称: osClockTimePulse

 *@函数版本: 1.0.0

 *@函数功能: 系统时钟脉冲处理

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
void osClockTimePulse(void)
{
	/*本函数已在中断响应入口中，下面是这个函数的副本*/
	u32 _tr0;//变量初始化

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
	if(TST.TISRF > NULL){
		osTime.TISRRT++;
	}
	else if(TST.TSS == TaskSwitch_Ready){//任务调度状态为未调度，进行计时
        RunTask_TIT -> TOT++;//任务占用时长计数
    }
    if(osTime. TSRT % TaskOccupyRatioSamplingTime == 0){//系统每过一定时长，就进行占用比例统计
        CPUS.CTO = 0;//CPU占用量设为0
        for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//对每一个任务进行遍历
            //TL[_tr0].TITA -> TOR = TL[_tr0].TITA -> TOT / (TaskOccupyRatioSamplingTime / 100);//计算这个任务占用比
			TL[_tr0].TITA -> TOR = TL[_tr0].TITA -> TOT;//计算这个任务占用比
			//计算公式：占用比 = 单位时间内的占用时长 / (单位时间 / 100)
            CPUS.CTO += (TL[_tr0].TITA -> TOR / (TaskOccupyRatioSamplingTime / 100));//计算CPU占用量
			//计算公式：CPU占用量 = CPU占用量 + 每个任务的占用量
            TL[_tr0].TITA -> TOT = 0;//清空单位时间内的占用时长
        }
		if(osTime.TISRRT > NULL){
			CPUS.CISRO = (osTime.TISRRT / (TaskOccupyRatioSamplingTime / 100));//计算CPU占用量
			osTime.TISRRT = 0;
		}
		
    }
	#endif
    /*----------------------------------轮片---------------------------------------*/
    if(osTime.TTWM > 0 && TST.TSS == TaskSwitch_Ready && TST.TISRF == NULL){ //时间轮片
	   //当前正在运行的任务的轮片时间大于0并且调度状态为未调度状态
        osTime.TTWM--;//当前正在运行的任务的轮片时间减一
        if(osTime.TTWM == 0){//当目前正在运行的任务的轮片时间为零时
            //RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//清除正在运行的任务的状态位
            RunTask_TIT -> TC = Task_State_Up_TD;//将正在运行的任务的状态设为位轮片挂起(挂起态)
            if(TST.TSS == TaskSwitch_Ready){//查询是否己被悬起，如果没有就触发任务切换
                osTaskSwitch_Enable();//触发任务切换
            }
            else{//如果已经悬起了
                osTime.TTWM = 1;//当前正在运行的任务的轮片时间置为一，意味着轮片时间向后推迟一秒
            }
             
        }
    }
    for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//根据任务最大活动量，进行遍历
		/*----------------------------------延时---------------------------------------*/
        if((TL[_tr0].TITA -> TC) == Task_State_Up_DT){//这个任务是延时挂起(等待态)，才进入
            TL[_tr0].TITA -> TTF--;//把这个任务时间标志中内容减一
            if(TL[_tr0].TITA -> TTF == 0){	//当这个任务时间标志中内容为零时
                if(TST.TSS != TaskSwitch_Ready){//如果已经正在调度中，就把这个任务设为轮片挂起(挂起态)
                    //TL[_tr0].TITA  -> TC &= TIT_Task_State_TC_RST;//清除这个任务的状态位
                    TL[_tr0].TITA  -> TC = Task_State_Up_TD;//将这个任务的状态设为轮片挂起(挂起态)
                }
                else if(TL[_tr0].TITA -> TPL <  RunTask_TIT -> TPL){//如果这个任务高于当前工作运行任务栏的优先级，就占用
                    //TL[_tr0].TITA -> TC &= TIT_Task_State_TC_RST;//清除这个任务的状态位
                    TL[_tr0].TITA -> TC = Task_State_Up_TD;//将这个任务的状态设为轮片挂起(挂起态)
                    //RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//清除正在运行任务的状态位
                    RunTask_TIT -> TC = Task_State_Up_TD;//将正在运行任务的状态设为轮片挂起(挂起态)
                    if(TST.TSS == TaskSwitch_Ready){//查询是否己被悬起，如果没有就触发任务切换
                        TST. TDN = _tr0;//把这个任务ID加载到任务调度计数中，这样任务调度才认识这个任务，否则将会向下调度
                        osTaskSwitch_Enable(); //触发任务切换
                    }
                    else{//如果已经悬起了
                        TL[_tr0].TITA -> TTF = 1;//当前正在运行的任务的轮片时间置为一，意味着轮片时间向后推迟一秒
                    }
                }
                else{//意外之料的情况
                        //TL[_tr0].TITA -> TC &= TIT_Task_State_TC_RST;//清除这个任务的状态位
                        TL[_tr0].TITA -> TC = Task_State_Up_TD;//将这个任务的状态设为轮片挂起(挂起态)
                }
            }
        }
    }
	#if (osClockTimePeriod < osClockTimePeriodStandard)
	}
	#endif
}





/*
                                                  FILE-END
*/
