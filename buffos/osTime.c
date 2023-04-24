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
#include "osTime.h"


/*
                                                  ������ʼ����
*/
_NextAddr STimeListHead;
_TaskHandle* TaskHandle_STime;
#if (osPerf_Config > 0)
_PerformanceStatistics PerformanceStatistics;//����ͳ��
#endif
#if (osRunTime_Config > 0)//������ϵͳ����ʱ��
_SystemRunningTime 		OsTimeSystemRunTime;//ϵͳ����ʱ��
_TaskISRRunningTime		OsTimeTaskISRTime;//ϵͳ����ʱ��
#endif
_TaskWheelMargin	   OsTimeTaskTimeWheel;//������Ƭʱ��
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
	_TaskHandle* TaskHandleListBuf;

	#if (osClockTimePeriod < osClockTimePeriodStandard) //
	if(++OsTimeGetPeriodValue() >= (osClockTimePeriodStandard /osClockTimePeriod)){
		OsTimeGetPeriodValue() = NULL;
	#endif
    /*----------------------------------��ʱ---------------------------------------*/
	#if (osRunTime_Config > 0)//������ϵͳ����ʱ��
	#if (osClockTimePeriod > osClockTimePeriodStandard)
	OsTimeGetSystemRunTime() += (osClockTimePeriod / osClockTimePeriodStandard);//ϵͳ����ʱ�����м�ʱ
	#else
	OsTimeGetSystemRunTime() += 1;//ϵͳ����ʱ�����м�ʱ
	#endif
	#endif
     /*----------------------------------ͳ��---------------------------------------*/
	#if (osPerf_Config > 0) //����������ͳ��
	if(osTaskGetOIRQFlag() > NULL){
		OsTimeGetTaskISRTime()++;
	}
	else if(osTaskGetSwitchState() == TaskSwitch_Ready){//�������״̬Ϊδ���ȣ����м�ʱ
        osTaskGetRunTaskHandle() -> OccupyTime++;//����ռ��ʱ������
    }
    if(OsTimeGetSystemRunTime() % osTaskRunTime_Config == 0){//ϵͳÿ��һ��ʱ�����ͽ���ռ�ñ���ͳ��
        PerformanceStatistics.CTO = 0;//CPUռ������Ϊ0
		TaskHandleListBuf = osTaskGetTaskHandleListHead();
		do{//��ÿһ��������б���
			//TaskHandleListBuf -> OccupyRatio = TaskHandleListBuf -> OccupyTime / (osTaskRunTime_Config / 100);//�����������ռ�ñ�
			TaskHandleListBuf -> OccupyRatio = TaskHandleListBuf -> OccupyTime;//�����������ռ�ñ�
			//���㹫ʽ��ռ�ñ� = ��λʱ���ڵ�ռ��ʱ�� / (��λʱ�� / 100)
            PerformanceStatistics.CTO += TaskHandleListBuf -> OccupyRatio / (osTaskRunTime_Config / 100);//����CPUռ����
			//���㹫ʽ��CPUռ���� = CPUռ���� + ÿ�������ռ����
            TaskHandleListBuf -> OccupyTime = 0;//��յ�λʱ���ڵ�ռ��ʱ��

			TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
		}while(TaskHandleListBuf != osTaskGetTaskHandleListHead());
		if(OsTimeGetTaskISRTime() > NULL){
			PerformanceStatistics.CISRO = OsTimeGetTaskISRTime() / (osTaskRunTime_Config / 100);//����CPUռ����
			OsTimeGetTaskISRTime() = 0;
		}
		PerformanceStatistics.CSO = (PerformanceStatistics.TSC * PerformanceStatistics.TSSU) / (osTaskRunTime_Config /100) /1000;
		PerformanceStatistics.TSCb = PerformanceStatistics.TSC;
		PerformanceStatistics.TSC = 0;
    }
	#endif
    /*----------------------------------ʱ����Ƭ---------------------------------------*/
    if(OsTimeGetTaskTimeWheel() > 0 && osTaskGetSwitchState() == TaskSwitch_Ready && osTaskGetOIRQFlag() == NULL){
		/*���������������ſ��Դ�����Ƭ��ʱ
		 *1.������Ƭʱ�������
		 *2.�����л�״̬Ϊ����̬
		 *3.�ж�״̬Ϊ��
		 */
	   //��ǰ�������е��������Ƭʱ�����0���ҵ���״̬Ϊδ����״̬
        if(--OsTimeGetTaskTimeWheel() == 0){//��Ŀǰ�������е��������Ƭʱ��Ϊ��ʱ
			osTaskSwitch_Config();//���������л�   
        }
    }
	TaskHandleListBuf = osTaskGetTaskHandleListHead();//��ȡ����������ͷ��ָ��
	do{//��ÿһ��������б���
		/*----------------------------------��ʱ---------------------------------------*/
        if(TaskHandleListBuf -> Config == Task_State_Up_DT){//�����������ʱ����(�ȴ�̬)���Ž���
            TaskHandleListBuf -> TaskDelay--;//���������ʱ���־�����ݼ�һ
            if(TaskHandleListBuf -> TaskDelay == 0){	//���������ʱ���־������Ϊ��ʱ
                if(osTaskGetSwitchState() != TaskSwitch_Ready){//��ѯ�л�״̬�Ƿ�Ϊ����̬
                    TaskHandleListBuf  -> Config = Task_State_RE;//����������״̬��Ϊ����̬
                }
                else if(TaskHandleListBuf -> Level <  osTaskGetRunTaskHandle() -> Level){//������������ڵ�ǰ����������������ȼ�������ռ
                    TaskHandleListBuf -> Config = Task_State_RE;//����������״̬��Ϊ����̬
                    if(osTaskGetSwitchState() == TaskSwitch_Ready){//��ѯ�л�״̬�Ƿ�Ϊ����̬
                        osTaskGetNextTaskHandle() = TaskHandleListBuf;//��������������ص�����������
                        osTaskSwitch_Config(); //���������л�
                    }
                }
                else{//����֮�ϵ����
                        TaskHandleListBuf -> Config = Task_State_RE;//����������״̬��Ϊ��Ƭ����(����̬)
                }
            }
        }
		TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;//������һ��ָ��
	}while(TaskHandleListBuf != osTaskGetTaskHandleListHead());//�����������������������
	#if (osClockTimePeriod < osClockTimePeriodStandard)
	}
	#endif
}
#if (STime_Config > 0)
/*
 *
 * @��������: osSTimeInit
 *
 * @��������: �����ʱ����ʼ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osSTimerInit(void)
{
	STimeListHead = NULL;
	TaskHandle_STime = osTaskLogin(
						STimeName_Config,
						osSTimer,
						STimeStackSize_Config,
						STimeTimeWheel_Config,
						STimePriorityLevel_Config,
						STimePass_Config,
						STimeSet_Config); 
	if(TaskHandle_STime == NULL){

		#if (osTaskLog_Config > 0)
		osLogE("osSTimeInit","SIRQ ���񴴽�ʧ��\n");
		#endif
		return (Error);//����Error
	}
	return (OK);
}
/*
 *
 * @��������: osTimeLoginStatic
 *
 * @��������: ��ʱ����̬ע��
 *
 * @�������: ListAddr	��������ͷ��ַ		
 * @�������: Name		����
 * @�������: Flag		ʱ��
 * @�������: Config	����
 * @�������: Addr		��Ӧ��ַ
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
_STimes* osTimerLoginStatic(uint8_t* ListAddr,_STimeName* Name,_STaskDelay Flag,_STimeConfig Config,void* Addr)
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

/*
 *
 * @��������: osTimeLogin
 *
 * @��������: �����ʱ��ע��
 *
 * @�������: Name		����
 * @�������: Flag		ʱ��
 * @�������: Config	����
 * @�������: Addr		��Ӧ��ַ
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
_STimes* osTimerLogin(_STimeName* Name,_STaskDelay Flag,_STimeConfig Config,void* Addr)
{
	uint8_t* Addr1;
	if(Config >= STimeConfig_NRestartL){
		Addr1 = osMemoryMalloc(sizeof(_STime));//Ϊ���������ڴ�
	}else{
		Addr1 = osMemoryMalloc(sizeof(_STimes));//Ϊ���������ڴ�
	}
//	if(Addr1 == NULL){//���Ϊ�գ���˵���ڴ����ʧ��
//		#if (osTaskLog_Config > 0)
//		osTaskErrorDebug("ע������ʱ,��������ڴ�ʧ�� %s\n",TN);
//		#endif
//		return (NULL);//���ش���
//	}
	return osTimerLoginStatic(Addr1, Name, Flag, Config, Addr);
}
/*
 *
 * @��������: osClockTimePulse
 *
 * @��������: ϵͳʱ�����崦��
 *
 * @�������: STimes	�����ʱ�����
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osSTimerLogout(_STimes* STimes)
{
	return uLinkListDel(&STimeListHead,(uint32_t*)STimes);

}
/*
 *
 * @��������: osSTime
 *
 * @��������: �����ʱ������
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void osSTimer(void)
{
	_STimes* STime_Buf;
	for(;;){
		STime_Buf = (_STimes*)STimeListHead;
		while(STime_Buf != NULL){
			STime_Buf -> Flag -= 1;
			if(STime_Buf -> Flag == 0){
				osLinkJump((uint32_t*)STime_Buf -> Addr);
				switch(STime_Buf -> Config){
					case STimeConfig_Restart:STime_Buf -> Flag =  STime_Buf -> Flagb;break;
					case STimeConfig_NRestartL:osSTimerLogout(STime_Buf); break;
//					case STimeConfig_NRestart: break;
				}
			}
			STime_Buf = (_STimes*)STime_Buf -> DownAddr;
		}
		osTaskDelayMs(1);
	}
	
}
#endif
