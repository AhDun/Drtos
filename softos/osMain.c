/*
                                                  FILE-START
*/

/*

 *@文件名称: osMain.c

 *@文件内容: 系统"主要"文件

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注    释: 

*/

/*
                                                  <引用文件区>
*/
#include "osMain.h"


/*
                                                  <函数区>
*/

/*

 *@函数名称: osInit

 *@函数版本: 1.0.0

 *@函数功能: 系统初始化

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
osErrorValue osInit(void)
{
	/*if(*/osIRQ_Init() /*== Error){//系统中断初始化
		return (Error)*/;//发生错误,返回错误
	/*}*/
	/*if(*/osDebug_Init()/* == Error){//系统串口初始化
		return (Error)*/;//发生错误,返回错误
	/*}*/
	if(osMemoryInit() == Error){
		#if (osMainDebug_Enable > 0)
		osMainDebug("内存初始化错误");
		#endif
		return (Error);//发生错误,返回错误
	}
	if(osPostInit() == Error){//邮箱初始化
		#if (osMainDebug_Enable > 0)
		osMainDebug("邮箱初始化错误");
		#endif
		return (Error);//发生错误,返回错误
	}
	if(osTaskInit() == Error){//任务系统初始化
		#if (osMainDebug_Enable > 0)
		osMainDebug("任务系统初始化错误");
		#endif
		return (Error);//发生错误,返回错误
	}
	if(osClockInit() == Error){//系统时钟初始化
		#if (osMainDebug_Enable > 0)
		osMainDebug("系统时钟初始化错误");
		#endif
		return (Error);//发生错误,返回错误
	} 
	osMainPrintInfo();
	osMainSpeedTest();
	return (OK);//初始化成功,返回OK
}
/*

 *@函数名称: osPrintDebug

 *@函数版本: 1.0.0

 *@函数功能: 串口Debug

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
osErrorValue osMainPrintFunc(void)
{
	osMainDebugInfo("系统功能组件\n",0);
	osMainDebugInfo("多任务 [已编译]\n",0);
	osMainDebugInfo("时钟 [已编译]\n",0);
	#ifdef osSignal_Enable
		osMainDebugInfo("信号量 \n",0);
		#ifdef osSignalMutual_Enable
		osMainDebugInfo("|-  互斥信号量[已编译]\n",0);
		#else
		osMainDebugInfo("|-  互斥信号量[未编译]\n",0);
		#endif
		#ifdef osSignalBinary_Enable
		osMainDebugInfo("|-  二值信号量[已编译]\n",0);
		#else
		osMainDebugInfo("|-  二值信号量[未编译]\n",0);
		#endif
		#ifdef osSignalCount_Enable
		osMainDebugInfo("|-  计数信号量[已编译]\n",0);
		#else
		osMainDebugInfo("|-  计数信号量[未编译]\n",0);
		#endif
	#else
		osMainDebugInfo("信号量 [未编译]\n",0);
	#endif
	#ifdef osMemory_Enable
	osMainDebugInfo("内存管理 [已编译]\n",0);
	#else
		osMainDebugInfo("内存管理 [未编译]\n",0);
	#endif
	#ifdef osPost_Enable
	osMainDebugInfo("邮箱 [已编译]\n",0);
	#else
	osMainDebugInfo("邮箱 [未编译]\n",0);
	#endif
	return (OK);
}
/*

 *@函数名称: osPrintDebug

 *@函数版本: 1.0.0

 *@函数功能: 串口Debug

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
osErrorValue osMainSpeedTest(void)
{
	u32 t0,t1;
	RunTask_TIT -> TC = Task_State_Up_IN;
	t0 = SysTick->VAL;
	osTaskSwitch_Enable();//触发任务切换
	t1 = SysTick->VAL;
	#if (osTaskUsePrint  > 0)
	TST.TSSU = (t0 - t1) / (osCPU_Freq / 8);
	#endif
	print("任务切换速度测试\nt0=%d\nt1=%d\n切换速度=%fus\n",t0,t1,((t0 - t1) / (osCPU_Freq / 8))*1.0);
	return (OK);
}

/*
                                                  FILE-END
*/


