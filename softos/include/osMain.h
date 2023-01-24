/*
                                                  FILE-START
*/
/*

 *@�ļ�����: osMain.h

 *@�ļ�����: 

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע    ��: 

*/
/*
                                                  ���ظ������������
*/
#ifndef __osMain_H_
#define __osMain_H_
/*
                                                  <�����ļ���>
*/

#include "Main.h"
#include "SysTick.h"
#include "usart.h"
#include "Str.h"
#include "print.h"
#include "LinkList.h"


#include "osError.h"
#include "osConfig.h"
#include "osSignal.h"
#include "osPost.h"
#include "osTask.h"
#include "osCPU.h"
#include "osClock.h"
#include "osMemory.h"
#include "osPost.h"



#define osMainDebug(a) print("\nosMain: %s\n",a)//DeBug�������
#define osMainDebugInfo(a,b) print(a,b)//DeBug�������

#define osMainDebug_Enable 1 //Debug���� 1:����Debug��� 0:�ر�Debug���

#define osMainPrintInfo()  do{\
							osMainDebugInfo("ϵͳ����: %s\n",osName);\
							osMainDebugInfo("ϵͳ�汾��: %s\n",osVersionNumberS);\
							osMainDebugInfo("ϵͳ���������: %d\n",osMaximumTask);\
							osMainDebugInfo("ϵͳ��������: %s\n",__DATE__);\
							osMainDebugInfo("ϵͳ����ʱ��: %s\n",__TIME__);\
							osMainDebugInfo("CPU����: %s\n",osCPU_Name);\
							osMainDebugInfo("CPU��Ƶ: %dMHz\n",osCPU_Freq);\
							}while(0);


/*
                                                  <����������>
*/
osErrorValue osInit(void);
osErrorValue osMainPrintFunc(void);
osErrorValue osMainSpeedTest(void);



#endif
/*
                                                  FILE-END
*/
