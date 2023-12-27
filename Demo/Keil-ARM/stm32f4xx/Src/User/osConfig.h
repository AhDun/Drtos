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
#ifndef __osConfig_H_
#define __osConfig_H_
/**
 *
 * @file osConfig.h
 *
 * @brief ϵͳ����
 *
 * @note 
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
#define osName                 "Drtos" //ϵͳ����
#define osNameAndVersion  		"Drtos v1.1.0" //ϵͳ���� + ϵͳ�汾����
#define osCompileDate		  	__DATE__//ϵͳ��������
#define osCompileTime 		 	__TIME__//ϵͳ����ʱ��
#define osCPU_Name				"STM32F407ZG"//CPU����
#define osCPU_Freq				168u//CPU��Ƶ
#define osCPU_Period			5.95f//CPUʱ������
#define osCPU_Period_Times		1000//CPUʱ�����ڵĵ�λ��
#define osCPU_Bit				sizeof(void*)*8//CPUλ��
//}


//Ӳ������{

/**
 *
 * @name osClock_Init
 *
 * @brief ϵͳʱ�ӳ�ʼ��
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osClock_Init(a) 		 SysTick_us_Init(osCPU_Freq,a * 1000)//


#define osClockSetLoad(a)		 SysTick_us_load(osCPU_Freq,a * 1000)
/**
 *
 * @name osDebug_Init
 *
 * @brief ϵͳDebug��ʼ��
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osDebug_Init() 		 USART1_Init(115200)//
/**
 *
 * @name osIRQ_Init
 *
 * @brief ϵͳ�жϳ�ʼ��
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osIRQ_Init()  		 do{\
								NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);\
								NVIC_SetPriority (SysTick_IRQn, 0x04|0x02|0x01);\
								NVIC_SetPriority (PendSV_IRQn, 0x08|0x04|0x02|0x01);\
							 }while(0);
/**
 *
 * @name osClockPause
 *
 * @brief ϵͳʱ����ͣ
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/

#define osClockPause()   	do{\
									SysTick->CTRL &= ~(0x02) ;\
								}while(0);//��ͣϵͳ
/**
 *
 * @name osClockRecover
 *
 * @brief ϵͳʱ�ӻָ�
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osClockRecover() 	do{\
									SysTick->CTRL |= (0x02) ;\
								}while(0);//�ָ�ϵͳ

//}


//�������컯{
#define osTaskTimeUs(a) 	SysTick_us(us)//΢�뼶��ʱ
//}

/**
 *
 * @name osInfoPrint
 *
 * @brief ϵͳ��Ϣ��ӡ
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osInfoPrint()  		do{\
							print("ϵͳ����: %s\n",osName);\
							print("ϵͳ�汾��: %s\n",osVersionNumberS);\
							print("ϵͳ��������: %s\n",osCompileDate);\
							print("ϵͳ����ʱ��: %s\n",osCompileTime);\
							print("CPU����: %s\n",osCPU_Name);\
							print("CPU��Ƶ: %dMHz\n",osCPU_Freq);\
							print("CPUλ��: %d\n",osCPU_Bit);\
							osTaskSpeedTest();\
							}while(0);//ϵͳ��Ϣ
/**
 *
 * @name osInit
 *
 * @brief ϵͳ��ʼ��
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osInit()    do{\
						osIRQ_Init();\
						osDebug_Init();\
						osMemoryInstall(osMemoryInit(&Memory_CCRAM));\
						osTaskInit();\
						osClockInit();\
						osInfoPrint();\
						osTaskSIRQInit();\
						osSTimerInit();\
					}while(0);


//}

//log����{
#define osLogF(a,...)				print("[Fatal] %s - %M",a,##__VA_ARGS__)// ���ؼ�
#define osLogE(a,...)				print("[Error] %s - %M",a,##__VA_ARGS__)// ����
#define osLogW(a,...)				print("[Warn] %s - %M",a,##__VA_ARGS__)// ���漶
#define osLogI(a,...)				print("[Info] %s - %M",a,##__VA_ARGS__)// ��Ϣ��
#define osLogD(a,...)				print("[Debug] %s - %M",a,##__VA_ARGS__)// ���Լ�
	
//}

//��������{
#define osTaskLog_Config 			 1 //Debug���� 1:����Log��� 0:�ر�Log���
#define osCriticalToProtect_Config   1  //�ٽ籣��  1������ 0������
#define osTaskName_Config			 1// ��������� 1������ 0������
#define osTaskUseStack_Config 		 1//���ý���ջ  1������ 0������
#if (__FPU_USED == 1)
#define osFPU_Config                    1//����FPUӲ��   1������ 0������
		/*���ú������˶�FPUѹջ������ͬʱҲ��Ҫ�ڱ������п�������Ӳ���ſ���֧��
		  �����ı�������MCU��֧�ָ���Ӳ��������ã�
		*/
#else
#define osFPU_Config                    0//����FPUӲ��   1������ 0������
#endif

#define osTaskNewR_Config				1//��������ʱ�¼Ĵ���   1������ 0������
										/*����ͨ���رռ�������ʱ�¼Ĵ������ӿ�������������ٶȣ����ǿ��ܻ�Ӱ��������ȶ���*/

#define TaskTimeWheelDefault        100u//Ĭ����Ƭʱ��(��λms)
#define Default_Stack_Size          1000u//Ĭ��ջ��С
#define osTaskArg_Config 			1 //�������񴫲� 1������ 0������

#define osTaskStackDir_Config		CPUStackDir //		����ջ��������  1:�ݼ� 0:����

#if( osFPU_Config > 0)
#define osTaskMinimumStackSize		40*4 //��������˸���Ӳ��������ջ��С����40*4�ֽ�
#else
#define osTaskMinimumStackSize		20*4 //���û�������˸���Ӳ��������ջ��С����20*4�ֽ�
#endif


#define osTaskIDE

//}
//����������{
#define OSCoreName_Config 			"OSCore"//��������
#define OSCoreStackSize_Config 		400	
#define OSCoreTimeWheel_Config 		3
#define OSCorePriorityLevel_Config 	-128
#define OSCorePass_Config 			(void*)0
#define OSCoreSet_Config 			Task_Set_OSCore
//}
//���ж�����{
#define SIRQ_Config					1 //���ж�����  0:����  1:����
#define SIRQName_Config 			"SIRQ"
#define SIRQStackSize_Config 		400
#define SIRQTimeWheel_Config 		TaskTimeWheelDefault
#define SIRQPriorityLevel_Config 	-127
#define SIRQPass_Config 			(void*)0
#define SIRQSet_Config 				Task_Set_Default
//}
//��ʱ������{
#define STime_Config				1 //��ʱ������  0:����  1:����
#define STimeName_Config 			"STime"
#define STimeStackSize_Config 		400
#define STimeTimeWheel_Config 		TaskTimeWheelDefault
#define STimePriorityLevel_Config 	-126
#define STimePass_Config 			(void*)0
#define STimeSet_Config 			Task_Set_Default
//}





//��������{
#define osTaskRunError_Config 		1 //��������ʱ������������ 1:����Log��� 0:�ر�Log���
#define	osTaskErrorSet					0//��������ʱ��������������� 1������������� 0����ͣ�������
typedef int32_t OsErrorValue;//�������󷵻�ֵ
//}


//ͳ������{
#define osPerf_Config 				1//����ͳ��  1������ 0������
#define osRunTime_Config 			1	//��¼ϵͳ����ʱ��  1������ 0������
#define osTaskRunTime_Config 		1000 //����ͳ��ʱ�䣬��λms
//}


//ʱ������{

#define osClockTimePeriod 					1000 //ϵͳʱ�����ڣ���λus
#define osClockTimePeriodStandard			1000 //ϵͳʱ���׼���ڣ���λus

//}

//�ź�������{
#define osSignalAutoApply_Config		1//�ź����Զ��ڴ����   1������ 0������

#define Signal_Mutual       0x01u//�����ź���
#define Signal_Binary       0x02u//��ֵ�ź���
#define Signal_Count        0x04u//�����ź���
#define Signal_AndGroup		0x08u//����
#define Signal_OrGroup		0x10u//����

#define osSignal_Config		Signal_Mutual | Signal_Binary | Signal_Count | Signal_AndGroup | Signal_OrGroup
							/*ͨ��������*/

#define osSignalLog_Config		 1 //�ź�������DeBug  1:����Log��� 0:�ر�Log���
#define osSignalMemoryMalloc	osMemoryMalloc	//�ڴ����뷽��
#define osSignalMemoryFree		osMemoryFree	//�ڴ��ͷŷ���

//}

//��������{
#define osPost_Config			1 	 //�������� 1������ 0������
#define osPostHead_Config		1	 //���ʼ���ʽ  1:����ʽ  0:ջʽ
#define osPostLog_Config 		1 	//�������DeBug  1:����Log��� 0:�ر�Log���
#define osPostMemoryMalloc		osMemoryMallocStatic	//�ڴ����뷽��
#define osPostMemoryFree		osMemoryFreeStatic	//�ڴ��ͷŷ���
//}

//�ڴ�����{
#define MemTank_Max 					16 * 1024 //�ڴ�ش�С����

#define MemoryProtect_Config 			0 // �ڴ汣������ 	1:�������� 0:�رձ���	
										//���ñ��������ڴ����ͷ��ڴ����õ�ʱ����������
										//�ڴ汣��Ҳ��һ����֤�ڴ��һ�����ᷢ������!!!,ֻ�ή���ڴ淢������ĸ���

#define osMemoryInitReset_Config 		1 //��ʼ���ڴ�ʱ��λ�ڴ� 1:���� 0:�ر�

#define osMemorySequence_Config 		0 //�ڴ�˳�����   1������ 0������

#if (osMemorySequence_Config == 0)

#define osMemoryFreeReset_Config 		0 //�ͷ��ڴ�ʱ��λ�ڴ� 1:���� 0:�ر�
#define osMemoryFreeTest_Config 		1 //�ͷ��ڴ�ʱ����ڴ� 1:���� 0:�ر�
#define osMemoryPart_Config				1 //��ָ�  1:���� 0:�ر�
#define osMemoryMerge_Config			1 //��ϲ�  1:���� 0:�ر�

#endif

#define	osMemoryStatic_Config			1 //��̬�ڴ� 1:���� 0: �ر�

#define osMemoryLog_Config 				1 //Debug���� 1:����Log��� 0:�ر�Log���

//}





#include "osLink.h"
#include "osSignal.h"
#include "osPost.h"
#include "osTask.h"
#include "osTime.h"
#include "osMemory.h"
#include "osPost.h"


#endif


