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
#include "usart.h"
#include "Str.h"
#include "print.h"
#include "LinkList.h"




//ϵͳ��Ϣ{
#define osMaximumTask 	     	64 //ϵͳ���������
#define osVersionNumber        110 //ϵͳ�汾��
#define osVersionNumberS       "v1.1.0" //ϵͳ�汾����
#define osName                 "softos" //ϵͳ����
#define osNameVersionNumberS   "softos v1.1.0" //ϵͳ���� + ϵͳ�汾����
#define osCompileDate		  	__DATE__//ϵͳ��������
#define osCompileTime 		 	__TIME__//ϵͳ����ʱ��
#define osCPU_Name				"STM32F407ZG"//CPU����
#define osCPU_Freq				168u//CPU��Ƶ
#define osCPU_Bit				sizeof(void*)
//}


//Ӳ������{
#define osClock_Init() 		 

#define osDebug_Init() 		 

#define osIRQ_Init()  		 do{}while(0);//ϵͳ�жϳ�ʼ������


#define osClockPause()   	do{}while(0);//��ͣϵͳ

#define osClockRecover() 	do{}while(0);//�ָ�ϵͳ

//}


//�������컯{
#define osTaskTimeUs(a) 	SysTick_us(us)//΢�뼶��ʱ

#define osInfoDebug()  		do{\
							print("ϵͳ����: %s\n",osName);\
							print("ϵͳ�汾��: %s\n",osVersionNumberS);\
							print("ϵͳ���������: %d\n",osMaximumTask);\
							print("ϵͳ��������: %s\n",osCompileDate);\
							print("ϵͳ����ʱ��: %s\n",osCompileTime);\
							print("CPU����: %s\n",osCPU_Name);\
							print("CPU��Ƶ: %dMHz\n",osCPU_Freq);\
							}while(0);//ϵͳ��Ϣ

#define osInit()    do{\
						osIRQ_Init();\
						osDebug_Init();\
						osMemoryInit();\
						osTaskInit();\
						osClockInit();\
						osInfoDebug();\
						osTaskSpeedTest();\
					}while(0);//ϵͳ��ʼ��


#define osDebugError 		print
#define osDebugInfo 		print
#define osDebugWarning 		print

//}

//��������{
#define osCriticalToProtect_Enable   1  //�ٽ籣��  1������ 0������

#define osPerformanceStatistics_Enable 1//����ͳ��  1������ 0������

#define os_TotalSystemRunningTime_Enable 1//��¼ϵͳ����ʱ��  1������ 0������

#if (__FPU_USED == 1)
#define osFPU_Enable                    1//����FPUӲ��   1������ 0������
		/*���ú������˶�FPUѹջ������ͬʱҲ��Ҫ�ڱ������п�������Ӳ���ſ���֧��
		  �����ı�������MCU��֧�ָ���Ӳ��������ã�
		*/
#else
#define osFPU_Enable                    0//����FPUӲ��   1������ 0������
#endif

#define osSignalAutoApply_Enable		1//�ź����Զ�����   1������ 0������
		/*���ú��Ϊ�ź����Զ������ڴ�*/

#define osTaskNewR_Enable				1//��������ʱ�¼Ĵ���   1������ 0������
										/*����ͨ���رռ�������ʱ�¼Ĵ������ӿ�������������ٶȣ����ǿ��ܻ�Ӱ��������ȶ���*/

#define osSpeedTest_Enable 				1//����ʱ���������л��ٶ� 1������ 0������

#define osClockTimePeriod 					1000 //ϵͳʱ�����ڣ���λus

#define osClockTimePeriodStandard			1000 //ϵͳʱ���׼���ڣ���λus

#define	SIRQListLength						10

#define	osTaskErrorSet					0//��������ʱ��������������� 1������������� 0����ͣ�������


#define osTaskParameterPass_Enable 		1//����ʱ���������л��ٶ� 1������ 0������

//}


typedef int32_t osErrorValue;//�������󷵻�ֵ


#include "osLink.h"
#include "osSignal.h"
#include "osPost.h"
#include "osTask.h"
#include "osClock.h"
#include "osMemory.h"
#include "osPost.h"

#endif

