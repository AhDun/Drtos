/*
                                                  FILE-START
*/
#ifndef __osConfig_H_
#define __osConfig_H_
/*

 *@�ļ�����: osConfig.h

 *@�ļ�����: ϵͳ����

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@ע    ��: 

*/

/*
                             __ _            
                            / _| |           
                  ___  ___ | |_| |_ ___  ___ 
                 / __|/ _ \|  _| __/ _ \/ __|
                 \__ \ (_) | | | || (_) \__ \
                 |___/\___/|_|  \__\___/|___/
                            
						softos v1.0.0

*/


/*
                                                  <�����ļ���>
*/
#include "main.h"
#include "SysTick.h"
#include "usart.h"
#include "Str.h"
#include "print.h"
#include "LinkList.h"


/*
                                                  <�궨����>
*/

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
#define osClock_Init() 		 SysTick_us_Init(osCPU_Freq,osClockTimePeriod)//ϵͳʱ�ӳ�ʼ������

#define osDebug_Init() 		 USART1_Init(115200)//ϵͳ���ڳ�ʼ������

#define osIRQ_Init()  		 do{\
								NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);\
								NVIC_SetPriority (SysTick_IRQn, 0x04|0x02|0x01);\
								NVIC_SetPriority (PendSV_IRQn, 0x08|0x04|0x02|0x01);\
							 }while(0);//ϵͳ�жϳ�ʼ������


#define osClockPause()   	do{\
									SysTick->CTRL &= ~(0x02) ;\
								}while(0);//��ͣϵͳ

#define osClockRecover() 	do{\
									SysTick->CTRL |= (0x02) ;\
								}while(0);//�ָ�ϵͳ

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

/*
                                                  <����������>
*/
typedef int32_t osErrorValue;//�������󷵻�ֵ

/*
                                                  <�����ļ���>
*/
#include "osCPU.h"
#include "osSignal.h"
#include "osPost.h"
#include "osTask.h"
#include "osClock.h"
#include "osMemory.h"
#include "osPost.h"

#endif
/*
                                                  FILE-END
*/

