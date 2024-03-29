/*------------------------------------------------------------------------------------------------------------------------
 * 文件名称：System_Control.h

 * 文件内容：

 * 文件版本：1.0.0

 * 文件作者：阿顿

 * 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5 

 * 注    意：
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  防重复编译宏配置区
------------------------------------------------------------------------------------------------------------------------*/
#ifndef __System_Control_h_
#define __System_Control_h_
/*------------------------------------------------------------------------------------------------------------------------
                                                  加载头文件区
------------------------------------------------------------------------------------------------------------------------*/
#include "Inc_Basic.h"//基本库
/*系统所需库*/
#include "System_Clock.h"
#include "WDT.h"//看门狗库
#include "Interrupt.h"//中断库
#include "UARTApp.h"//串口应用库
#include "UART.h"//串口库
#include "Timer.h"//定时器库
#include "system_task.h"//系统多任务库
#include "Power.h"//电源管理库
#include "System_Control.h"//系统控制库
#include "system_uart.h"//系统串口库
#include "delay_Lib.h"//软件延时库 
/*------------------------------------------------------------------------------------------------------------------------
                                                  宏定义区
------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------字符串--------------------------------------*/
/*系统启动成功串口输出的字符串*/
#define System_OK_UART "D RTOS Success Start!\n"
/*系统启动失败串口输出的字符串*/
#define System_Error_UART "D RTOS Fali Start!\n"
/*----------------------------------数值---------------------------------------*/
/*配置系统版本*/
#define Systemv 168
/*配置系统内部版本代码区位置*/
#define SystemSvP 0x2165
/*配置初始指针差值*/
#define SP_Init_Va 2
/*看门狗单周期时长*/
#define WDT_SingleCycle_Time 1500
/*系统测试时长*/
#define SYS_TEST_Time 2
/*系统测试等待时长*/
#define SYS_TEST_Wait_Time 4
/*主应用ID*/
#define Main_AID 0
/*重置看门狗应用ID*/
#define RSTWDT_AID 30
/*系统重启并下载模式应用ID*/
#define ISP_AID 29
/*串口接收完成应用ID*/
#define UARTDAEND_AID 28
/*多任务测试应用ID*/
#define SYS_TEST 27
/*系统监视器应用ID*/
#define MonitorOutUART_AID 26
/*----------------------------------函数---------------------------------------*/
/*指定系统定时器初始化函数*/
#define System_Timer_Init {Timer0Init();}
/*指定系统串口初始化函数*/
#define System_UART_Init {UART1Init();}
/*指定系统看门狗初始化函数*/
#define System_WDT_Init {WDT_Init();}
/*----------------------------------代码---------------------------------------*/
/*配置系统定时器关闭代码*/
#define System_Timer_Disable {ET0 = Disable;}
/*配置系统定时器开启代码*/
#define System_Timer_Enable {ET0 = Enable;}
/*配置总中断关闭代码*/
#define System_IMS_Disable {EA = Disable;}
/*配置总中断开启代码*/
#define System_IMS_Enable {EA = Enable;}
/*配置系统定时器中断激活代码*/
#define System_Timer_Touch {TF0 = Enable;}
/*----------------------------------开关---------------------------------------*/
/*配置是否使用串口功能*/
#define EnableSerialPortDebugging//启串口功能
/*配置是否使用看门狗功能功能*/
#define EnableWDT//启看门狗功能
/*配置是否使用弹性检查功能*/
#define EnableECF//启弹性检查功能
/*配置是否使用队列检查功能*/
#define EnableQueueCheck//启队列检查功能
/*配置是否使用系统运行时间计时*/
#define EnableRunningTime//系统运行时间计时
/*------------------------------------------------------------------------------------------------------------------------
                                                  结构体声明区
------------------------------------------------------------------------------------------------------------------------*/
/*系统状态*/
typedef struct 
{
	u8 SystemOk;//系统运行标志位
	u8 TaskSwitch;//多任务运行标志位
}xdata SystemFlag;
extern SystemFlag Sf;

/*------------------------------------------------------------------------------------------------------------------------
                                                  函数声明区
------------------------------------------------------------------------------------------------------------------------*/
extern void System_Init();//系统初始化
extern void OffTask();//关闭多任务
extern void OnTask();//开启多任务
extern void Start_Test();//多任务测试
extern u16 Gma(u16 ADD_R0);//获取函数地址

#endif
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/