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
#ifndef __osConfig_H_
#define __osConfig_H_
/*
 *
 * @�ļ�����: osConfig.h
 *
 * @�ļ�����: ϵͳ����
 *
 * @ע    ��: 
 *
 */




#include "main.h"
#include "SysTick.h"
#include "usart.h"
#include "Str.h"
#include "print.h"
#include "LinkList.h"




//ϵͳ��Ϣ{
#define osVersionNumber        110 //ϵͳ�汾��
#define osVersionNumberS       "v1.1.0" //ϵͳ�汾����
#define osName                 "softos" //ϵͳ����
#define osNameVersionNumberS   "softos v1.1.0" //ϵͳ���� + ϵͳ�汾����
#define osCompileDate		  	__DATE__//ϵͳ��������
#define osCompileTime 		 	__TIME__//ϵͳ����ʱ��
#define osCPU_Name				"STM32F407ZG"//CPU����
#define osCPU_Freq				168u//CPU��Ƶ
#define osCPU_Period			5.95f//CPUʱ������
#define osCPU_Period_Times		1000//CPUʱ�����ڵĵ�λ��
#define osCPU_Bit				sizeof(void*)*8//CPUλ��
//}


//Ӳ������{

/*
 *
 * @��������: osClock_Init
 *
 * @��������: ϵͳʱ�ӳ�ʼ��
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osClock_Init() 		 SysTick_us_Init(osCPU_Freq,osClockTimePeriod)//
/*
 *
 * @��������: osDebug_Init
 *
 * @��������: ϵͳDebug��ʼ��
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osDebug_Init() 		 USART1_Init(115200)//
/*
 *
 * @��������: osIRQ_Init
 *
 * @��������: ϵͳ�жϳ�ʼ��
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osIRQ_Init()  		 do{\
								NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);\
								NVIC_SetPriority (SysTick_IRQn, 0x04|0x02|0x01);\
								NVIC_SetPriority (PendSV_IRQn, 0x08|0x04|0x02|0x01);\
							 }while(0);
/*
 *
 * @��������: osClockPause
 *
 * @��������: ϵͳʱ����ͣ
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/

#define osClockPause()   	do{\
									SysTick->CTRL &= ~(0x02) ;\
								}while(0);//��ͣϵͳ
/*
 *
 * @��������: osClockRecover
 *
 * @��������: ϵͳʱ�ӻָ�
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osClockRecover() 	do{\
									SysTick->CTRL |= (0x02) ;\
								}while(0);//�ָ�ϵͳ

//}


//�������컯{
#define osTaskTimeUs(a) 	SysTick_us(us)//΢�뼶��ʱ
//}

/*
 *
 * @��������: osInfoDebug
 *
 * @��������: ϵͳ��Ϣ��ӡ
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osInfoDebug()  		do{\
							print("ϵͳ����: %s\n",osName);\
							print("ϵͳ�汾��: %s\n",osVersionNumberS);\
							print("ϵͳ��������: %s\n",osCompileDate);\
							print("ϵͳ����ʱ��: %s\n",osCompileTime);\
							print("CPU����: %s\n",osCPU_Name);\
							print("CPU��Ƶ: %dMHz\n",osCPU_Freq);\
							print("CPUλ��: %d\n",osCPU_Bit);\
							osTaskSpeedTest();\
							}while(0);//ϵͳ��Ϣ
/*
 *
 * @��������: osInit
 *
 * @��������: ϵͳ��ʼ��
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osInit()    do{\
						osIRQ_Init();\
						osDebug_Init();\
						osMemoryInit(&Memory_CCRAM);\
						osTaskInit();\
						osClockInit();\
						osInfoDebug();\
						osTaskSIRQInit();\
						osSTimeInit();\
					}while(0);//ϵͳ��ʼ��






//Debug����{
#define osDebugError 		print
#define osDebugInfo 		print
#define osDebugWarning 		print
//}

//��������{
#define osTaskDebug_Enable 1 //Debug���� 1:����Debug��� 0:�ر�Debug���
#define osCriticalToProtect_Enable   1  //�ٽ籣��  1������ 0������
#if (__FPU_USED == 1)
#define osFPU_Enable                    1//����FPUӲ��   1������ 0������
		/*���ú������˶�FPUѹջ������ͬʱҲ��Ҫ�ڱ������п�������Ӳ���ſ���֧��
		  �����ı�������MCU��֧�ָ���Ӳ��������ã�
		*/
#else
#define osFPU_Enable                    0//����FPUӲ��   1������ 0������
#endif

#define osTaskNewR_Enable				1//��������ʱ�¼Ĵ���   1������ 0������
										/*����ͨ���رռ�������ʱ�¼Ĵ������ӿ�������������ٶȣ����ǿ��ܻ�Ӱ��������ȶ���*/

#define TaskTimeWheelDefault        	100u//Ĭ����Ƭʱ��(��λms)
#define Default_Stack_Size             1000u//Ĭ��ջ��С
//}



//��������{
#define osTaskRunError_Enable 1 //��������ʱ������������ 1:����Debug��� 0:�ر�Debug���
#define	osTaskErrorSet					0//��������ʱ��������������� 1������������� 0����ͣ�������
typedef int32_t OsErrorValue;//�������󷵻�ֵ
//}


//ͳ������{
#define osPerformanceStatistics_Enable 1//����ͳ��  1������ 0������
#define os_TotalSystemRunningTime_Enable 1//��¼ϵͳ����ʱ��  1������ 0������
#define TaskOccupyRatioSamplingTime 		1000 //����ͳ��ʱ�䣬��λms
#define osSpeedTest_Enable 				1//����ʱ���������л��ٶ� 1������ 0������
#define osTaskParameterPass_Enable 		1//����ʱ���������л��ٶ� 1������ 0������
//}


//ʱ������{

#define osClockTimePeriod 					1000 //ϵͳʱ�����ڣ���λus
#define osClockTimePeriodStandard			1000 //ϵͳʱ���׼���ڣ���λus

//}

//�ź�������{
#define osSignalAutoApply_Enable		1//�ź����Զ�����   1������ 0������
		/*���ú��Ϊ�ź����Զ������ڴ�*/
#define osSignalMutual_Enable //���û����ź���
#define osSignalBinary_Enable //���ö�ֵ�ź���
#define osSignalCount_Enable  //���ü����ź���
#define osSignalDebugError_Enable 1 //�ź�������DeBug  1:����Debug��� 0:�ر�Debug���
#define osSignalDebugError	osDebugError

//}

//��������{
#define osPostHead		1	 //���ʼ���ʽ  1:����ʽ  0:ջʽ
#define osPostDebugError_Enable 1 //�������DeBug  1:����Debug��� 0:�ر�Debug���
#define osPostDebugError	osDebugError 
//}

//�ڴ�����{
#define MemTank_Max 					16 * 1024 //�ڴ�ش�С����

#define MemoryProtect_Enable 			0 // �ڴ汣������ 	1:�������� 0:�رձ���	
										//���ñ��������ڴ����ͷ��ڴ����õ�ʱ����������
										//�ڴ汣��Ҳ��һ����֤�ڴ��һ�����ᷢ������!!!,ֻ�ή���ڴ淢������ĸ���

#define osMemoryInitReset_Enable 		0 //��ʼ���ڴ�ʱ��λ�ڴ� 1:���� 0:�ر�
#define osMemorySequence_Enable 		0 //�ڴ�˳�����   1������ 0������

#if (osMemorySequence_Enable == 0)

#define osMemoryFreeReset_Enable 		0 //�ͷ��ڴ�ʱ��λ�ڴ� 1:���� 0:�ر�
#define osMemoryFreeTest_Enable 		1 //�ͷ��ڴ�ʱ����ڴ� 1:���� 0:�ر�
#define osMemoryPart_Enable				1 //��ָ�  1:���� 0:�ر�
#define osMemoryMerge_Enable			1 //��ϲ�  1:���� 0:�ر�

#endif

#define osMemoryDebug_Enable 			1 //Debug���� 1:����Debug��� 0:�ر�Debug���
#define osMemoryErrorDebug osDebugError//DeBug�������
//}







#include "osLink.h"
#include "osSignal.h"
#include "osPost.h"
#include "osTask.h"
#include "osTime.h"
#include "osMemory.h"
#include "osPost.h"

#endif


