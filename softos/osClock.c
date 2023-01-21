/*
                                                  FILE-START
*/
/*

 *@文件名称: osClock.c

 *@文件内容: 系统"时钟"系文件

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注    释: 

*/

/*
                                                  <引用文件区>
*/
#include "osMain.h"
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

 *@函数名称: osTime_Handler

 *@函数版本: 1.0.0

 *@函数功能: 系统时钟处理

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
void osClockTimePulse(void)
{
	/*本函数已在中断响应入口中，下面是这个函数的副本*/
	u32 _tr0;//变量初始化

	#if (osClockTimePeriod < osClockTimePeriodStandard) //
	if(++osTime.CTPV >= (osClockTimePeriodStandard /osClockTimePeriod))
	{
		osTime.CTPV = NULL;
	#endif
    /*----------------------------------计时---------------------------------------*/
	#if (os_TotalSystemRunningTime_Enable > 0)//开启了系统运行时长
	#if (osClockTimePeriod > osClockTimePeriodStandard)
	osTime. TSRT = osTime. TSRT + (osClockTimePeriod / osClockTimePeriodStandard);//系统运行时长进行计时
	#else
	osTime. TSRT = osTime. TSRT + 1;//系统运行时长进行计时
	#endif
	#endif
     /*----------------------------------统计---------------------------------------*/
	#if (osPerformanceStatistics_Enable > 0) //开启了性能统计
    if(TST.TSS == TaskSwitch_Ready){//任务调度状态为未调度，进行计时
        RunTask_TIT -> TOT++;//任务占用时长计数
    }
    if(osTime. TSRT % TaskOccupyRatioSamplingTime == 0){//系统每过一定时长，就进行占用比例统计
        CPUS.CO = 0;//CPU占用量设为0
        for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//对每一个任务进行遍历
            //TL[_tr0].TITA -> TOR = TL[_tr0].TITA -> TOT / (TaskOccupyRatioSamplingTime / 100);//计算这个任务占用比
			TL[_tr0].TITA -> TOR = TL[_tr0].TITA -> TOT;//计算这个任务占用比
			//计算公式：占用比 = 单位时间内的占用时长 / (单位时间 / 100)
            CPUS.CO = CPUS.CO + (TL[_tr0].TITA -> TOR / (TaskOccupyRatioSamplingTime / 100));//计算CPU占用量
			//计算公式：CPU占用量 = CPU占用量 + 每个任务的占用量
			#if (osTaskUsePrint  > 0)
			#if (osTaskUsePrintClock > 0)
			print("任务<%s>的使用量为:占用时长:%dms | 任务优先级:%d | 任务状态:",TL[_tr0].TITA -> TN,TL[_tr0].TITA -> TOT,TL[_tr0].TITA -> TPL);
			if(TL[_tr0].TITA != RunTask_TIT || TST.TSS != TaskSwitch_Ready){
				switch(TL[_tr0].TITA -> TC){
					case Task_State_Up_TD:print("轮片挂起\n");break;
					case Task_State_Up_IN:print("主动挂起\n");break;
					case Task_State_Up_DT:print("延时挂起\n");break;
					case Task_State_Up_SI:print("信号挂起\n");break;
					case Task_State_Up_PT:print("邮件挂起\n");break;
					case Task_State_DI:print("禁用态\n");break;
					case Task_State_ST:print("终止态\n");break;
					case Task_State_RB:print("重启态\n");break;
					case Task_State_OP:print("运行态\n");break;
					case Task_State_Up:print("挂起态\n");break;
				}
			}
			else{
				print("正在运行\n");
			}
			#endif
			#endif

            TL[_tr0].TITA -> TOT = 0;//清空单位时间内的占用时长
        }
		#if (osTaskUsePrint  > 0)
		#if (osTaskUsePrintClock > 0)
		print("任务总使用量:%d%% | ",CPUS.CO);
		if(TST.TSC*TST.TSSU > 1000){
			print("任务调度次数:%d | 预计耗时:%d.%dms\n",TST.TSC,TST.TSC*TST.TSSU / 1000,TST.TSC*TST.TSSU % 1000 / 100);
		}else{
			print("任务调度次数:%d | 预计耗时:%dus\n",TST.TSC,TST.TSC*TST.TSSU);
		}
		TST.TSC = 0;
		print("内存总量:%d字节 | 内存余量:%d字节 | 可分配:%d字节\n",osMemoryAllSize(),osMemoryMarginSize(),osMemoryMaxMallocValue());
		tprint("系统已运行: %d天 %h小时 %m分钟 %s秒\n",osTime. TSRT);
		#endif
		#endif
    }
	#endif
    /*----------------------------------轮片---------------------------------------*/
    if(osTime.TTWM > 0 && TST.TSS == TaskSwitch_Ready){ //时间轮片
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
