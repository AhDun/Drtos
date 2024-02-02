/*------------------------------------------------------------------------------------------------------------------------
 * 文件名称：CPU.c

 * 文件内容：系统任务内核

 * 文件版本：1.0.0

 * 文件作者：阿顿

 * 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5 

 * 注    意：
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  加载头文件区
------------------------------------------------------------------------------------------------------------------------*/
#include "Inc_Basic.h"//基本库
#include "System_Task.h"
#include "System_Clock.h"
#include "Timer.h"
#include "System_Control.h"
#include "CPU.h"
/*------------------------------------------------------------------------------------------------------------------------
 * 函数名称：TaskSwitch

 * 函数功能：任务切换

 * 输入参数：无

 * 输出参数：无

 * 注    意：无
------------------------------------------------------------------------------------------------------------------------*/
void TaskSwitch()
{
	u8 TS_F0;
	if(TimerIRQTouchType)
	{
		/*如果目标任务ID与当前任务ID相同，则放弃切换*/
		if(PlanTaskId != RunAppID)
		{
			/*将栈加载到缓冲区*/
			#pragma asm
			POP   stack0+0CH
			POP   stack0+0CH
			POP  	stack0+0CH
			POP  	stack0+0BH
			POP  	stack0+0AH
			POP  	stack0+09H
			POP  	stack0+08H
			POP  	stack0+07H
			POP  	stack0+06H
			POP  	stack0+05H
			POP  	stack0+04H
			POP  	stack0+03H
			POP  	stack0+02H
			POP  	stack0+01H
			POP  	stack0+00H
			POP		stack0+0DH
			POP		stack0+0EH
			#pragma endasm
			/*将任务计时器清零*/
			AppRunTimer = NULL;
			/*如果TimerTouchType == 1，则表示为任务并非自动结束运行*/
			if(TimerIRQTouchType == Task_Touch)
			{
				/*保存标准的栈*/
				for(TS_F0 = NULL;TS_F0 < 15;TS_F0++)
				{
					/*标准栈*/
					/*栈缓冲区-----写入---->扩展RAM中*/
					Pstack [RunAppID][TS_F0 + 1] = stack0[TS_F0];
				}
				/*保存扩展的栈，根据上电初始的栈指针，自动计算栈的长度*/
				for(;(SP - SP0) > NULL;TS_F0++)
				{
					/*当超过栈池的深度时，立即停止写入*/
					if(TS_F0 >= MaxStackDepth)
					{
						break;
					}
					/*进入出栈操作*/
					#pragma asm
					POP		stack0+1
					#pragma endasm
					/*扩展栈*/
					/*栈缓冲区-----写入---->扩展RAM中*/
					Pstack [RunAppID][TS_F0 + 1]  = stack0[1];
				}
				Pstack [RunAppID][NULL] = TS_F0 - 1;//将栈长度记录到栈池的顶端
			}
			else/*如果任务并非自动结束运行，则与该任务的栈池*/
				RunAppPy = Pstack [RunAppID][NULL] = NULL;
			RunAppID = PlanTaskId;/*刷新运行ID*/
			if(Pstack[RunAppID][NULL] == NULL)//准备就绪态
			{
				/*加载初始函数地址到缓冲区*/
				stack0 [13] = TPC >> 8;
				stack0 [14]=  TPC & 0x00FF;
				
				if(RunAppID > NULL)
				{
					/*将运行自动返回的指针写入到缓冲区中*/
					stack0 [16] = TaskEndAddr & 0x00FF;
					stack0 [15] = TaskEndAddr >> 8;
					/*进行压栈操作，将运行自动返回的指针从缓冲区中写入到栈中*/
					#pragma asm
					PUSH 	stack0 + 10H
					PUSH 	stack0 + 0FH
					#pragma endasm
				}
			}
			else if(Pstack [RunAppID][NULL] > NULL)//挂起就绪态
			{
				/*扩展栈*/
				/*以保存到栈池中的头部的长度信息，将栈池中数据压到栈中*/
				for(TS_F0 = Pstack [RunAppID][NULL];TS_F0 > 14;TS_F0--)
				{
					/*扩展RAM-----写入---->栈缓冲区*/
					stack0[NULL] = Pstack [RunAppID][TS_F0 + 1] ;
					#pragma asm
					PUSH	stack0
					#pragma endasm
				}
				/*标准栈*/
				/*扩展RAM-----写入---->栈缓冲区*/
				for(TS_F0 = 0;TS_F0 < 15;TS_F0++)
				{
					stack0 [TS_F0] = Pstack [RunAppID][TS_F0 + 1] ;
				}
			}
			/*复位激活标志位*/
			TimerIRQTouchType = NULL;
			/*复位切换锁*/
			SnLock = NULL; 
			/*复位刷新锁*/
			PlanTaskId = NULL;
			/*重新装载到任务计时器中*/
			AppRunTimer = 0xFF;
			/*复位保护时长*/
			ProTime = NULL;

			/*将缓冲区加载到栈*/
			#pragma asm
			MOV 	ACC , stack0+00H
			MOV 	B , stack0+01H
			MOV 	DPH , stack0+02H
			MOV 	DPL , stack0+03H
			MOV 	PSW , stack0+04H
			MOV 	0x00 , stack0+05H
			MOV 	0x01 , stack0+06H
			MOV 	0x02 , stack0+07H
			MOV 	0x03 , stack0+08H
			MOV 	0x04 , stack0+09H
			MOV 	0x05 , stack0+0AH
			MOV 	0x06 , stack0+0BH
			MOV 	0x07 , stack0+0CH
			PUSH	stack0+0EH
			PUSH	stack0+0DH
			RETI
			#pragma endasm
		}
		/*复位激活标志位*/
		TimerIRQTouchType = NULL;
		/*复位切换锁*/
		SnLock = NULL; 
		/*复位刷新锁*/
		PlanTaskId = NULL;
		/*重新装载到任务计时器中*/
		AppRunTimer = 0xFF;
		/*复位保护时长*/
		ProTime = NULL;
	}
}
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/