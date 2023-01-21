/*
                                                  FILE-START
*/
/*

 *@文件名称: .c

 *@文件内容: 系统"错误处理"文件

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注    释: 无

*/

/*
                                                  <引用文件区>
*/

#include "main.h"
#include "osError.h"
#include "osMain.h"
#include "print.h"

/*
                                                  <数据初始区>
*/
/*
                                                  <函数区>
*/
/*

 *@函数名称: osError

 *@函数版本: 1.0.0

 *@函数功能: 硬件错误与异常处理

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
void osTaskError_HardFault(void)
{
	u8 _v1;
	for(_v1 = 0; _v1 < 3; _v1++){
		osErrorDebug("\n\n\nHardFault:名称为%s的任务发生“硬件错误”异常!!!\n",RunTask_TIT -> TN,0);
		osErrorDebug("任务优先级:%d\n",RunTask_TIT -> TPL,0);
		osErrorDebug("任务当前使用量:%d%%\n",RunTask_TIT -> TOR,0);
		osErrorDebug("任务延时剩余时间:%d%ms\n任务单次最大运行时长:%dms\n",RunTask_TIT -> TTF,RunTask_TIT -> TTW);
		osErrorDebug("任务最一近状态:",0,0);
		switch(RunTask_TIT -> TC){
			case Task_State_Up_TD:osErrorDebug("轮片挂起\n",0,0);break;
			case Task_State_Up_IN:osErrorDebug("主动挂起\n",0,0);break;
			case Task_State_Up_DT:osErrorDebug("延时挂起\n",0,0);break;
			case Task_State_Up_SI:osErrorDebug("信号挂起\n",0,0);break;
			case Task_State_Up_PT:osErrorDebug("邮件挂起\n",0,0);break;
			case Task_State_DI:osErrorDebug("禁用态\n",0,0);break;
			case Task_State_ST:osErrorDebug("终止态\n",0,0);break;
			case Task_State_RB:osErrorDebug("重启态\n",0,0);break;
			case Task_State_OP:osErrorDebug("运行态\n",0,0);break;
			case Task_State_Up:osErrorDebug("挂起态\n",0,0);break;
		}
		osErrorDebug("任务邮箱状态:",0,0);
		if(RunTask_TIT -> PF == NULL){
			osErrorDebug("空的\n",0,0);
		}
		else{
			osErrorDebug("非空\n",0,0);
		}
		osErrorDebug("任务栈总大小:%d字节\n任务栈剩余:%d字节\n",(RunTask_TIT -> TSS - 1),Read_PSP() - ((u32)RunTask_TIT -> TH - ((RunTask_TIT -> TSS - 1))));
		osErrorDebug("任务异常处:%X\n",Read_PC(),0);
		osErrorDebug("内存总量:%d字节\n内存余量:%d字节",osMemoryGetAllValue(),osMemoryGetFreeValue());
	}
	osTaskSet(0,Task_Set_Pause);

	
}

/*
                                                  FILE-END
*/
