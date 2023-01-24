/*
                                                  FILE-START
*/
/*

 *@文件名称: osMain.h

 *@文件内容: 

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注    释: 

*/
/*
                                                  防重复编译宏配置区
*/
#ifndef __osMain_H_
#define __osMain_H_
/*
                                                  <引用文件区>
*/

#include "Main.h"
#include "SysTick.h"
#include "usart.h"
#include "Str.h"
#include "print.h"
#include "LinkList.h"


#include "osError.h"
#include "osConfig.h"
#include "osSignal.h"
#include "osPost.h"
#include "osTask.h"
#include "osCPU.h"
#include "osClock.h"
#include "osMemory.h"
#include "osPost.h"



#define osMainDebug(a) print("\nosMain: %s\n",a)//DeBug输出函数
#define osMainDebugInfo(a,b) print(a,b)//DeBug输出函数

#define osMainDebug_Enable 1 //Debug配置 1:开启Debug输出 0:关闭Debug输出

#define osMainPrintInfo()  do{\
							osMainDebugInfo("系统名称: %s\n",osName);\
							osMainDebugInfo("系统版本号: %s\n",osVersionNumberS);\
							osMainDebugInfo("系统最大任务量: %d\n",osMaximumTask);\
							osMainDebugInfo("系统编译日期: %s\n",__DATE__);\
							osMainDebugInfo("系统编译时间: %s\n",__TIME__);\
							osMainDebugInfo("CPU名称: %s\n",osCPU_Name);\
							osMainDebugInfo("CPU主频: %dMHz\n",osCPU_Freq);\
							}while(0);


/*
                                                  <函数声明区>
*/
osErrorValue osInit(void);
osErrorValue osMainPrintFunc(void);
osErrorValue osMainSpeedTest(void);



#endif
/*
                                                  FILE-END
*/
