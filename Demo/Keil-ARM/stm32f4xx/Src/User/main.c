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
 * @�ļ�����: main.c
 *
 * @�ļ�����: 
 *
 * @ע    ��: 
*/


#include "main.h"
#include "SysTick.h"
#include "osConfig.h"
#include "Demo.h"
#include "print.h"

uint8_t CCRAM[MemTank_Max] __attribute__((at(0x10000000)));

_MemoryInfo  Memory_CCRAM = {&CCRAM[0],&CCRAM[0],&CCRAM[MemTank_Max]};



/* *
 * @��������: ��
 *
 * @��������: ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
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
	"RTC", 			                    //��������
	Task1_Func,			            //�����ַ
	Task1_Stack_size,		                    //����ջ����s
	50,		                            //����ʱ����Ƭ
	-2,	                                    //�������ȼ�
	"Hello Task1\n",									//���񴫲�   
	Task_Set_Default);

	print("%s\n",osPostReadWait());


	TaskHandle_Task2 = osTaskLogin(    
	"TaskList", 			                    //��������
	Task2_Func,			            //�����ַ
	Task2_Stack_size,		                    //����ջ����
	50,		                            //����ʱ����Ƭ
	-1,	                                    //�������ȼ�
	"Hello",									//���񴫲�
	Task_Set_Default
	); 

	TaskHandle_Task3 = osTaskLogin( 
	"LED1", 			                        //��������
	Task3_Func,			                //�����ַ
	Task3_Stack_size,		                        //����ջ����
	50,		                                    //����ʱ����Ƭ
	-3,                                          //�������ȼ�
	"Hello",									//���񴫲�
	Task_Set_Default                                    
	);

	TaskHandle_Task4 = osTaskLogin( 
	"LED2", 			                        //��������
	Task4_Func,			                //�����ַ
	Task4_Stack_size,		                        //����ջ����
	50,		                                    //����ʱ����Ƭ
	-3,                                          //�������ȼ�
	"Hello",									//���񴫲�
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




