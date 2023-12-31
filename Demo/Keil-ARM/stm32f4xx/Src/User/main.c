/**
 * Copyright 2022-2023 AhDun. All rights reserved.
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

/**
 * @file main.c
 *
 * @brief 
 *
 * @note 
*/

#include "main.h"
#include "SysTick.h"
#include "osConfig.h"
#include "Demo.h"
#include "print.h"

uint8_t CCRAM[MemTank_Max] __attribute__((at(0x10000000)));
uint32_t RAM[1000];

_MemoryInfo  Memory_CCRAM = {&CCRAM[0],&CCRAM[0],&CCRAM[MemTank_Max]};
_MemoryInfoStatic  Memory_RAM = {&RAM[0],&RAM[999],1,2};





/**
 * @name none
 *
 * @brief none
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */



int main(void)
{
/*--------------------------------------demo---------------------------------------------------------*/
	u32 _tr0;
	//_SignalHandle* a;
	//_TaskHandle t;
	osInit();
	osMemoryInstallStatic(osMemoryInitStatic(&Memory_RAM));
	print("static memory:%d\n",osMemoryStaticGetPassValue());
//	a = osSignalLogin(Signal_AndGroup);
//	osSignalSetGroup(a,2,2,1);
//	osSignalSetGroup(a,2,1,1);
//	print("\n\n\n\n\n\n");
//	print("有符号整数测试:%d\n",-123456);
//	print("无符号整数测试:%lu\n",-123456);
//	print("浮点数测试:%f\n",1234.5678);
//	print("大写十六进制测试:%X\n",0x1234ABCD);
//	print("小写十六进制测试:%x\n",0x1234ABCD);
//	print("八进制测试:%o\n",0123456);
//	print("字符测试:%c\n",'a');
//	print("字符串测试:%s\n","Hello World");
//	print("整数测试:%3d\n",99);
//	print("浮点数测试:%.2f\n",1234.5678);
//	print("\n\n\n\n\n\n");
	//print("%M","%d\n",10);
	//osLogF("ad","A:%d",100);
	//osMemoryMalloc(25000);
//	_tr0 = -2;
	//print("%d\n\n",MemoryStructLength);
	//print("%f %d %f %d %f %s\n",123.456,123,12.123,456,456.789,"very");



//	t.Name = "RTC";
//	t.Addr = (void*)Task1_Func;
//	t.Length = Task1_Stack_size;
//	t.Wheel = 50;
//	t.Level = -2;
//	t.Arg = (void*)"Hello Task1\n";

//	osTaskLoad(&t,Load_Create);

	TaskHandle_Task1 = osTaskLogin(
	Task1_Func,			            //任务地址
	Task1_Stack_size,		                    //任务栈长度
	-2,	                                    //任务优先级
	50,		                            //任务时间轮片
	"Hello Task1\n",									//任务传参   
	"RTC", 			                    //任务名称
	Task_Set_Default);

	//print("%s\n",osPostReadWait());


	TaskHandle_Task2 = osTaskLogin(    
	Task2_Func,			            //任务地址
	Task2_Stack_size,		                    //任务栈长度
	-1,	                                    //任务优先级
	50,		                            //任务时间轮片
	"Hello",									//任务传参
	"TaskList", 			                    //任务名称
	Task_Set_Default
	); 

	TaskHandle_Task3 = osTaskLogin( 
	Task3_Func,			                //任务地址
	Task3_Stack_size,		                        //任务栈长度
	-3,                                          //任务优先级
	50,		                                    //任务时间轮片
	"Hello",									//任务传参
	"LED1", 			                        //任务名称
	Task_Set_Default                                    
	);

	TaskHandle_Task4 = osTaskLogin( 
	Task4_Func,			                //任务地址
	Task4_Stack_size,		                        //任务栈长度
	-3,                                          //任务优先级
	50,		                                    //任务时间轮片
	"Hello",									//任务传参
	"LED2", 			                        //任务名称
	Task_Set_Default                                    
	);
	OSCoreTaskHandle -> Config = Task_Set_OSCore; 


	//osTaskLogout(TaskHandle_Task3);
	osTaskStart();
//	for(;;){
//		for(_tr0 = 0;_tr0 < 500;_tr0++){
//			osPostReadWait();
//		}
////		for(_tr0 = 10;_tr0 < MemTank_Max;_tr0++){
////			MemoryPool[_tr0] = _tr0;
////			osTaskDelayMs(10);
////		}
//	}
/*---------------------------------------------------------------------------------------------------*/
}




