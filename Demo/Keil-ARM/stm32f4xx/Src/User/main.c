/*
 * Copyright (c) 2022-2023 AhDun
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

/* *
 * @文件名称: main.c
 *
 * @文件内容: 
 *
 * @注    释: 
*/


#include "main.h"
#include "SysTick.h"
#include "osConfig.h"
#include "Demo.h"
#include "print.h"

uint8_t CCRAM[MemTank_Max] __attribute__((at(0x10000000)));

_MemoryInfo  Memory_CCRAM = {&CCRAM[0],&CCRAM[0],&CCRAM[MemTank_Max]};



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

int main(void)
{
/*--------------------------------------demo---------------------------------------------------------*/
	u32 _tr0;

	osInit();
	osTaskSpeedTest();

	//osMemoryMalloc(25000);
//	_tr0 = -2;
	print("%d\n\n",MemoryStructLength);

	TaskHandle_Task1 = osTaskLogin(
	"RTC", 			                    //任务名称
	Task1_Func,			            //任务地址
	Task1_Stack_size,		                    //任务栈长度s
	50,		                            //任务时间轮片
	-2,	                                    //任务优先级
	"Hello Task1\n",									//任务传参   
	Task_Set_Default);

	print("%s\n",osPostReadWait());


	TaskHandle_Task2 = osTaskLogin(    
	"TaskList", 			                    //任务名称
	Task2_Func,			            //任务地址
	Task2_Stack_size,		                    //任务栈长度
	50,		                            //任务时间轮片
	-1,	                                    //任务优先级
	"Hello",									//任务传参
	Task_Set_Default
	); 

	TaskHandle_Task3 = osTaskLogin( 
	"LED1", 			                        //任务名称
	Task3_Func,			                //任务地址
	Task3_Stack_size,		                        //任务栈长度
	50,		                                    //任务时间轮片
	-3,                                          //任务优先级
	"Hello",									//任务传参
	Task_Set_Default                                    
	);

	TaskHandle_Task4 = osTaskLogin( 
	"LED2", 			                        //任务名称
	Task4_Func,			                //任务地址
	Task4_Stack_size,		                        //任务栈长度
	50,		                                    //任务时间轮片
	-3,                                          //任务优先级
	"Hello",									//任务传参
	Task_Set_Default                                    
	);


	//osTaskLogout(TaskHandle_Task3);

	for(;;){
		for(_tr0 = 0;_tr0 < 500;_tr0++){
			osPostReadWait();
		}
		osTaskMonitor();
//		for(_tr0 = 10;_tr0 < MemTank_Max;_tr0++){
//			MemoryPool[_tr0] = _tr0;
//			osTaskDelayMs(10);
//		}
	}
/*---------------------------------------------------------------------------------------------------*/
}




