/*------------------------------------------------------------------------------------------------------------------------
 * 文件名称：System_task.h

 * 文件内容：

 * 文件版本：1.0.0

 * 文件作者：阿顿

 * 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5 

 * 注    意：
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  防重复编译宏配置区
------------------------------------------------------------------------------------------------------------------------*/
#ifndef __System_Task_h_
#define __System_Task_h_
/*------------------------------------------------------------------------------------------------------------------------
                                                  加载头文件区
------------------------------------------------------------------------------------------------------------------------*/
#include "Inc_Basic.h"//基本库

/*------------------------------------------------------------------------------------------------------------------------
                                                  数据类型声明区
------------------------------------------------------------------------------------------------------------------------*/
typedef 	unsigned char 	Py_INT;
typedef 	unsigned int  	Type_INT;
typedef 	unsigned int  	TPC_INT;
typedef 	unsigned int  	Pa_INT;
typedef 	unsigned int  	ID_INT;
/*------------------------------------------------------------------------------------------------------------------------
                                                  宏定义区
------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------数值---------------------------------------*/
/*******************任务基本配置*********************/
/*任务队列最大长度*/
#define TaskQueueMax 32
/*任务最大数量*/
#define TaskMax 32
/*应用超时阀值（ms）*/
#define AppRunTimerMax 100
/*应用0超时阀值（ms）*/
#define Task0TimeSize 1000
/*单个栈最大栈深*/
#define MaxStackDepth 50
/*栈缓冲器大小*/
#define StackBuffer 17
/*******************任务类型定义*********************/
/*定时任务*/
#define Task_Time 0x00
/*条件任务*/
#define Task_EX0 0x01
#define Task_UART1_RI 0x02
#define Task_UART1_TI 0x03
#define Task_I2C 0x04
#define Task_PCA 0x05
#define Task_PCA0 0x06
#define Task_PCA1 0x07
#define Task_PCA2 0x08
#define Task_PCA3 0x09
#define Task_ADC 0x0A
#define Task_LVDF 0x0B
#define Task_UART1_RIDAT 0x0C
#define Task_CMPL 0x0D
#define Task_CMPH 0x0E
#define Task_PWMCF 0x0F
#define Task_PWM0 0x10
#define Task_PWM1 0x11
#define Task_PWM2 0x12
#define Task_PWM3 0x13
#define Task_PWM4 0x14
#define Task_PWM5 0x15
#define Task_PWM6 0x16
#define Task_PWM7 0x17
#define Task_PWMFD 0x18
#define Task_UART2_RI 0x19
#define Task_UART2_TI 0x1A
#define Task_UART3_RI 0x1B
#define Task_UART3_TI 0x1C
#define Task_UART4_RI 0x1D
#define Task_UART4_TI 0x1E
#define Task_TIME0 0x1F
#define Task_TIME1 0x20
#define Task_TIME2 0x21
#define Task_TIME3 0x22
#define Task_TIME4 0x22
/*空任务*/
#define Task_NULL 0xFF
/*******************优先级定义*********************/
#define Task_Class_L1 0x01//1级（用户级）
#define Task_Class_L2 0x02
#define Task_Class_L3 0x03
#define Task_Class_L4 0x04
#define Task_Class_L5 0x05
#define Task_Class_L6 0x06
#define Task_Class_L7 0x07
#define Task_Class_L8 0x08
#define Task_Class_L9 0x09
#define Task_Class_H1 0x0A//10级（系统级）
#define Task_Class_H2 0x0B
#define Task_Class_H3 0x0C
#define Task_Class_H4 0x0D
#define Task_Class_H5 0x0E
#define Task_Class_H6 0x0F
/*------------------------------------------------------------------------------------------------------------------------
                                                  变量声明区
------------------------------------------------------------------------------------------------------------------------*/
extern u8 xdata AQSP;//多任务队列指针
extern u8 xdata BQSP;//多任务队列指针
extern u8 xdata TaskDMax;//任务最大活动量
extern u8 xdata SP0;//初始化栈指针
extern u8 xdata RunAppID;//在运行任务的ID
extern u8 xdata RunAppPy;//在运行任务的优先级
extern u8 xdata PlanTaskId;//下一个要运行的任务ID
extern u16 xdata TPC;//任务初始地址
extern u8 xdata SnLock; //任务切换锁 
extern u16 xdata TaskEndAddr;//任务自动终止时，返回的地址
extern u8 xdata TimerIRQTouchType;//定时器中断触发类型

extern u8 stack0[StackBuffer];//栈缓冲区
extern u8 xdata Pstack[TaskMax][MaxStackDepth];//栈池
extern u8 xdata TaskInterruptQueue[TaskQueueMax + 2];//中断型任务队列
/*------------------------------------------------------------------------------------------------------------------------
                                                  结构体声明区
------------------------------------------------------------------------------------------------------------------------*/


/*任务信息表*/
typedef struct
{
	Py_INT 		Py0;//实时优先级
	Py_INT 		Py1;//初始优先级
	Type_INT 	Type;//任务类型
	TPC_INT 	TPC;//任务初始地址
	TPC_INT 	Pa0;//参数0
	Pa_INT 		Pa1;//参数1
}xdata TASKINFO;
extern TASKINFO TaskInfo[TaskMax];

/*普通任务队列表*/
typedef struct
{
 	ID_INT 		ID;//应用ID
	Py_INT 		Py;//优先级
}xdata taskqueue;
extern taskqueue TaskQueue[TaskQueueMax + 2];
/*------------------------------------------------------------------------------------------------------------------------
                                                  函数声明区
------------------------------------------------------------------------------------------------------------------------*/
extern void TaskLoad(u8 TaskId,u8 TaskType,u8 PY,u16 TaskM,u16 TaskPC) reentrant;
extern void TaskRemove(u8 TaskId) reentrant;
extern void MgQueue() reentrant ;
extern void TaskRPlanTaskId();
extern void TaskInterruptQueue_write();
extern void TaskQueue_write(u8 TaskID,u8 Py) reentrant;
extern u8 TaskQueue_read() reentrant;
extern void TypeTaskStartup(u8 TYPE) reentrant;
extern void OpenTask(u8 TaskID) reentrant;
extern void OpenTaskS(u8 TaskID,u8 Py) reentrant;
extern void TASKSWITCH();
extern u2 TaskSwitchIf();
extern void EnableProtection(u16 r1);
extern void DisableProtection();
extern void TaskEnd();

#endif
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/