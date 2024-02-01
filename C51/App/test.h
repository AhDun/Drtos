/*--------------------------------------------------------------------------
文件:TrafficLights.h
说明:交通灯
芯片:STC8A8K64S4A12@22.1184MHz
编写:阿顿
--------------------------------------------------------------------------*/
#ifndef __TrafficLights_h_
#define __TrafficLights_h_

#include"System_Task.h"

extern void Step0();
extern void Step1();
extern void Step2();
extern void Step3();
extern void Step4();
extern void led1();
extern void led2();
extern void ledoff();

#endif