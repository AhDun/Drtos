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
uint32_t RAM[1000];

_MemoryInfo  Memory_CCRAM = {&CCRAM[0],&CCRAM[0],&CCRAM[MemTank_Max]};
_MemoryInfoStatic  Memory_RAM = {&RAM[0],&RAM[999],1,2};



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
	//_SignalHandle* a;

	osInit();
	osTaskSpeedTest();
	osMemoryInstallStatic(osMemoryInitStatic(&Memory_RAM));
	print("static memory:%d\n",osMemoryStaticGetPassValue());
//	a = osSignalLogin(Signal_AndGroup);
//	osSignalSetGroup(a,2,2,1);
//	osSignalSetGroup(a,2,1,1);
//	print("\n\n\n\n\n\n");
//	print("�з�����������:%d\n",-123456);
//	print("�޷�����������:%lu\n",-123456);
//	print("����������:%f\n",1234.5678);
//	print("��дʮ�����Ʋ���:%X\n",0x1234ABCD);
//	print("Сдʮ�����Ʋ���:%x\n",0x1234ABCD);
//	print("�˽��Ʋ���:%o\n",0123456);
//	print("�ַ�����:%c\n",'a');
//	print("�ַ�������:%s\n","Hello World");
//	print("��������:%3d\n",99);
//	print("����������:%.2f\n",1234.5678);
//	print("\n\n\n\n\n\n");
	//print("%M","%d\n",10);
	//osLogF("ad","A:%d",100);
	//osMemoryMalloc(25000);
//	_tr0 = -2;
	//print("%d\n\n",MemoryStructLength);
	//print("%f %d %f %d %f %s\n",123.456,123,12.123,456,456.789,"very");

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




