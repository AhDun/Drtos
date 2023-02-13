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

/*
 *
 * @�ļ�����: osClock.c
 *
 * @�ļ�����: ϵͳʱ���ļ�
 *
 * @ע    ��: 
 *
 */


#include "osConfig.h"
#include "osClock.h"


/*
                                                  ������ʼ����
*/
_NextAddr STimeListHead;
_TaskHandle* TaskHandle_STime;
#if (osPerformanceStatistics_Enable > 0)
_PerformanceStatistics PS;//����ͳ��
#endif
#if (os_TotalSystemRunningTime_Enable > 0)//������ϵͳ����ʱ��
_SystemRunningTime 		OsTimeSystemRunTime;//ϵͳ����ʱ��
_TaskISRRunningTime		OsTimeTaskISRTime;//ϵͳ����ʱ��
#endif
_TaskTimeWheelMargin	   OsTimeTaskTimeWheel;//������Ƭʱ��
#if (osClockTimePeriod < osClockTimePeriodStandard)
_ClockTimePeriodValue      OsTimePeriodValue;//ʱ�����ڼ���
#endif

/*
 *
 * @��������: osClockInit
 *
 * @��������: ϵͳʱ�ӳ�ʼ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osClockInit(void)
{
	if(osClock_Init() == Error){//���ʱ�ӳ�ʼ������
		return (Error);//��ʾʱ�ӳ�ʼ��ʱ��������,���ش���
	}
	return (OK);//����OK
}
/*
 *
 * @��������: osClockTimePulse
 *
 * @��������: ϵͳʱ�����崦��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void osClockTimePulse(void)
{
	/*�����������ж���Ӧ����У���������������ĸ���*/
	_TaskHandle* TaskHandleListBuf;

	#if (osClockTimePeriod < osClockTimePeriodStandard) //
	if(++OsTimeGetPeriodValue() >= (osClockTimePeriodStandard /osClockTimePeriod)){
		OsTimeGetPeriodValue() = NULL;
	#endif
    /*----------------------------------��ʱ---------------------------------------*/
	#if (os_TotalSystemRunningTime_Enable > 0)//������ϵͳ����ʱ��
	#if (osClockTimePeriod > osClockTimePeriodStandard)
	OsTimeGetSystemRunTime() += (osClockTimePeriod / osClockTimePeriodStandard);//ϵͳ����ʱ�����м�ʱ
	#else
	OsTimeGetSystemRunTime() += 1;//ϵͳ����ʱ�����м�ʱ
	#endif
	#endif
     /*----------------------------------ͳ��---------------------------------------*/
	#if (osPerformanceStatistics_Enable > 0) //����������ͳ��
	if(osTaskGetOIRQFlag() > NULL){
		OsTimeGetTaskISRTime()++;
	}
	else if(osTaskGetSwitchState() == TaskSwitch_Ready){//�������״̬Ϊδ���ȣ����м�ʱ
        osTaskGetRunTaskHandle() -> OccupyTime++;//����ռ��ʱ������
    }
    if(OsTimeGetSystemRunTime() % TaskOccupyRatioSamplingTime == 0){//ϵͳÿ��һ��ʱ�����ͽ���ռ�ñ���ͳ��
        PS.CTO = 0;//CPUռ������Ϊ0
		TaskHandleListBuf = osTaskGetTaskHandleListHead();
		do{//��ÿһ��������б���
			//TaskHandleListBuf -> OccupyRatio = TaskHandleListBuf -> OccupyTime / (TaskOccupyRatioSamplingTime / 100);//�����������ռ�ñ�
			TaskHandleListBuf -> OccupyRatio = TaskHandleListBuf -> OccupyTime;//�����������ռ�ñ�
			//���㹫ʽ��ռ�ñ� = ��λʱ���ڵ�ռ��ʱ�� / (��λʱ�� / 100)
            PS.CTO += TaskHandleListBuf -> OccupyRatio / (TaskOccupyRatioSamplingTime / 100);//����CPUռ����
			//���㹫ʽ��CPUռ���� = CPUռ���� + ÿ�������ռ����
            TaskHandleListBuf -> OccupyTime = 0;//��յ�λʱ���ڵ�ռ��ʱ��

			TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
		}while(TaskHandleListBuf != osTaskGetTaskHandleListHead());
		if(OsTimeGetTaskISRTime() > NULL){
			PS.CISRO = OsTimeGetTaskISRTime() / (TaskOccupyRatioSamplingTime / 100);//����CPUռ����
			OsTimeGetTaskISRTime() = 0;
		}
		PS.CSO = (PS.TSC * PS.TSSU) / (TaskOccupyRatioSamplingTime /100) /1000;
		PS.TSCb = PS.TSC;
		PS.TSC = 0;
    }
	#endif
    /*----------------------------------��Ƭ---------------------------------------*/
    if(OsTimeGetTaskTimeWheel() > 0 && osTaskGetSwitchState() == TaskSwitch_Ready && osTaskGetOIRQFlag() == NULL){ //ʱ����Ƭ
	   //��ǰ�������е��������Ƭʱ�����0���ҵ���״̬Ϊδ����״̬
        if(--OsTimeGetTaskTimeWheel() == 0){//��Ŀǰ�������е��������Ƭʱ��Ϊ��ʱ
			osTaskSwitch_Enable();//���������л�   
        }
    }
	TaskHandleListBuf = osTaskGetTaskHandleListHead();
	do{//��ÿһ��������б���
		/*----------------------------------��ʱ---------------------------------------*/
        if(TaskHandleListBuf -> Config == Task_State_Up_DT){//�����������ʱ����(�ȴ�̬)���Ž���
            TaskHandleListBuf -> TimeFlag--;//���������ʱ���־�����ݼ�һ
            if(TaskHandleListBuf -> TimeFlag == 0){	//���������ʱ���־������Ϊ��ʱ
                if(osTaskGetSwitchState() != TaskSwitch_Ready){//����Ѿ����ڵ����У��Ͱ����������Ϊ��Ƭ����(����̬)
                    //TaskHandleListBuf  -> Config &= TIT_Task_State_TC_RST;//�����������״̬λ
                    TaskHandleListBuf  -> Config = Task_State_RE;//����������״̬��Ϊ��Ƭ����(����̬)
                }
                else if(TaskHandleListBuf -> PriorityLevel <  osTaskGetRunTaskHandle() -> PriorityLevel){//������������ڵ�ǰ�������������������ȼ�����ռ��
                    TaskHandleListBuf -> Config = Task_State_RE;//����������״̬��Ϊ��Ƭ����(����̬)
                    if(osTaskGetSwitchState() == TaskSwitch_Ready){//��ѯ�Ƿ񼺱��������û�оʹ��������л�
                        osTaskGetNextTaskHandle() = TaskHandleListBuf;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
                        osTaskSwitch_Enable(); //���������л�
                    }
                }
                else{//����֮�ϵ����
                        TaskHandleListBuf -> Config = Task_State_RE;//����������״̬��Ϊ��Ƭ����(����̬)
                }
            }
        }
		TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
	}while(TaskHandleListBuf != osTaskGetTaskHandleListHead());
	#if (osClockTimePeriod < osClockTimePeriodStandard)
	}
	#endif
}

_STimes* osTimeLogin_Static(uint8_t* ListAddr,_STimeName* Name,_STimeFlag Flag,_STimeConfig Config,void* Addr)
{
	_STimes* STime_Buf = (_STimes*)ListAddr;
	STime_Buf -> Name = Name;
	STime_Buf -> Addr = (_STimeAddr*)Addr;
	STime_Buf -> Flag = Flag;
	STime_Buf -> Config = Config;
	if(Config < STimeConfig_NRestartL){
		STime_Buf -> Flagb = Flag;
	}
	if(uLinkListTailWrtie(&STimeListHead,(uint32_t*)ListAddr) == OK){
		return STime_Buf;
	}else{
		return NULL;
	}
}


_STimes* osTimeLogin(_STimeName* Name,_STimeFlag Flag,_STimeConfig Config,void* Addr)
{
	uint8_t* Addr1;
	if(Config >= STimeConfig_NRestartL){
		Addr1 = osMemoryMalloc(sizeof(_STime));//Ϊ���������ڴ�
	}else{
		Addr1 = osMemoryMalloc(sizeof(_STimes));//Ϊ���������ڴ�
	}
//	if(Addr1 == NULL){//���Ϊ�գ���˵���ڴ����ʧ��
//		#if (osTaskDebug_Enable > 0)
//		osTaskErrorDebug("ע������ʱ,��������ڴ�ʧ�� %s\n",TN);
//		#endif
//		return (NULL);//���ش���
//	}
	return osTimeLogin_Static(Addr1, Name, Flag, Config, Addr);
}

OsErrorValue osSTimeInit(void)
{
	STimeListHead = NULL;
	TaskHandle_STime = osTaskLogin("STime",osSTime,400,TaskTimeWheelDefault,-126,(void*)0,Task_Set_Default); 
	if(TaskHandle_STime == NULL){

		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("SIRQ ���񴴽�ʧ��\n");
		#endif
		return (Error);//����Error
	}
	return (OK);
}

void osSTime(void)
{
	_STimes* STime_Buf;
	while(1){
		STime_Buf = (_STimes*)STimeListHead;
		while(STime_Buf != NULL){
			STime_Buf -> Flag -= 1;
			if(STime_Buf -> Flag == 0){
				Jump((uint32_t*)STime_Buf -> Addr);
				switch(STime_Buf -> Config){
					case STimeConfig_Restart:STime_Buf -> Flag =  STime_Buf -> Flagb;break;
					case STimeConfig_NRestartL: break;
					case STimeConfig_NRestart: break;
				}
			}
			STime_Buf = (_STimes*)STime_Buf -> DownAddr;
		}
		osTaskDelayMs(1);
	}
	
}


