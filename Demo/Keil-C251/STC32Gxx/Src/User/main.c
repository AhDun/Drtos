/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
 */

/* *
 * @文件名称: main.c
 *
 * @文件内容: 
 *
 * @注    释: 
*/



#include "main.h"
//#include "SysTick.h"
#include "osConfig.h"
#include "STC32G_UART.h"
#include "STC32G_GPIO.h"
#include "STC32G_ADC.h"
#include "STC32G_Exti.h"
#include "STC32G_I2C.h"
#include "STC32G_SPI.h"
#include "STC32G_Timer.h"
#include "STC32G_UART.h"
#include "STC32G_Compare.h"
#include "STC32G_Delay.h"
#include "STC32G_Switch.h"
#include "STC32G_WDT.h"
#include "STC32G_NVIC.h"


uint8_t CCRAM[MemTank_Max];

_MemoryInfo  Memory_CCRAM = {&CCRAM[0],&CCRAM[0],&CCRAM[MemTank_Max]};


void delay(unsigned long t)
{
	unsigned long i;
	while(t--){
		_nop_();
		i = 5528UL;
		while (i) i--;
	}

}

void func()
{
	P1 = 0x00;
}


void MCUInit()
{
	WTST = 0;     //设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
    EAXFR = 1;    //扩展寄存器(XFR)访问使能
    CKCON = 0;    //提高访问XRAM速度


	P0_MODE_IO_PU(GPIO_Pin_All);		//P0 设置为准双向口
	P1_MODE_IO_PU(GPIO_Pin_All);		//P1 设置为准双向口
//	P1_MODE_IN_HIZ(GPIO_Pin_LOW);		//P1.0~P1.3 设置为高阻输入
//	P1_MODE_OUT_OD(GPIO_Pin_4 | GPIO_Pin_5); //P1.4,P1.5 设置为漏极开路
	P2_MODE_IO_PU(GPIO_Pin_All);		//P2 设置为准双向口
	P3_MODE_IO_PU(GPIO_Pin_All);		//P3 设置为准双向口
	P4_MODE_IO_PU(GPIO_Pin_All);		//P4 设置为准双向口
	P5_MODE_IO_PU(GPIO_Pin_All);		//P5 设置为准双向口
	P6_MODE_IO_PU(GPIO_Pin_All);		//P6 设置为准双向口
	P7_MODE_IO_PU(GPIO_Pin_All);		//P7 设置为准双向口
	
	P1_PULL_UP_ENABLE(GPIO_Pin_4 | GPIO_Pin_5);	//P1.4,P1.5 开启内部上拉
}


/* *
 * @函数名称: 无
 *
 * @函数功能: 无
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
uint32_t s = 0x123;

void main(void)
{
	char i = 0;
	COMx_InitDefine		COMx_InitStructure;					//结构定义
	TIM_InitTypeDef		TIM_InitStructure;
	_TaskHandle* TaskHandleListBuf = osTaskGetTaskHandleListHead();
	_TaskHandle* a;

	MCUInit();

	P0 = 0x00;
	P1 = 0x00;
	P2 = 0x00;
	P3 = 0x00;
	P4 = 0x00;
	P5 = 0x00;
	P6 = 0x00;
	P7 = 0x00;
//	while(1){
//		delay(100);
//		P34 = P33 = 0;
//		delay(100);
//		P34 = P33 = 1;
//	}
	P3 = 0x00;

//	WKTCL	= 4095 & 0xFF;
//	WKTCH	= (4095 >> 8) & 0xFF | 0x80;
	while(1){

		if(i < 1){
			WKTCL	= 4095 & 0xFF;
			WKTCH	= (4095 >> 8) & 0xFF | 0x80;
			PCON	|= 0x02;
			P3 = 0xFF;
		}else{
			WKTCL	= 99 & 0xFF;
			WKTCH	= (99 >> 8) & 0xFF | 0x80;
			PCON	|= 0x02;
			P3 = 0x00 ;
		}
		i++;
		if(i > 2){
			i = 0;
		}
	}
		OsTaskRunTaskHandle = &s;
	osLinkTaskStackInit((uint32_t*)0,(uint32_t*)func,(uint32_t*)34,&s);
	//osLinkJump(func);
	
	osIRQ_Init();
	//ES = 1;

//	TIM_InitStructure.TIM_Mode = TIM_16BitAutoReload;
//	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_12T; 
//	TIM_InitStructure.TIM_ClkOut = DISABLE;
//	TIM_InitStructure.TIM_Value = 0;
//	TIM_InitStructure.TIM_Run = ENABLE;
//	Timer_Inilize(Timer0,&TIM_InitStructure);
//	ET0 = 1;
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//选择波特率发生器, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2, 所以不用选择)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		    //初始化串口2 UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_3);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	//osInit();
	osMemoryInstall(osMemoryInit(&Memory_CCRAM));
	osIRQ_Init();


	a = osTaskLogin(MainName_Config,func,MainStackSize_Config,MainTimeWheel_Config,MainPriorityLevel_Config,MainPass_Config,MainSet_Config); 
	osTaskGetNextTaskHandle() = a; 
	osTaskGetRunTaskHandle() = a;//将即将运行的任务信息表的指针传送给正在运行任务表 
	//osTaskGetNextTaskHandle() -> Config = Task_State_RE;//将这个任务的状态设为轮片挂起(挂起态)
	OsTimeGetTaskTimeWheel() = osTaskGetRunTaskHandle() -> TaskWheel;//将当前任务的时间轮片写入到时间记录器
	//print("任务<%s>\n",TaskHandleListBuf -> Name);
	ISR_Touch();
	


//	print("有符号整测试:%d\n",-123456);
//	print("无符号整测试:%lu\n",-123456);
//	print("浮点测试:%f\n",1234.5678);
//	print("大写十六进制测试:%X\n",0x1234ABCD);
//	print("小写十六进制测试:%x\n",0x1234ABCD);
//	print("八进制测试:%o\n",0123456);
//	print("字符测试:%c\n",'a');
//	print("字符串测试:%s\n","Hello World");
//	print("%3d\n",1);
//	print("浮点测试:%.1f\n",1234.5678); 
	//print("%d\n",osMemoryGetFreeValue());
	TaskHandleListBuf = osTaskGetTaskHandleListHead();
	do{
		print("任务<%s>\n",TaskHandleListBuf -> Name);
		TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
	}while(TaskHandleListBuf != osTaskGetTaskHandleListHead());
	while(1);
//osInit();

}





