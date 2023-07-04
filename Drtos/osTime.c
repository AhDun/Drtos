/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
 */

/*
 *
 * @�ļ�����: osClock.c
 *
 * @�ļ�����: ϵͳ"ʱ��"�ļ�
 *
 * @ע    ��: 
 *
 */


#include "osConfig.h"
#include "osTime.h"


/*
                                                  ������ʼ����
*/

#if (STime_Config > 0)
_NextAddr STimeListHead;
#endif

#if (osPerf_Config > 0)
_OSRecord OSRecord;//����ͳ��
#endif
#if (osRunTime_Config > 0)//������ϵͳ����ʱ��
_SystemRunningTime 		OsTimeSystemRunTime;//ϵͳ����ʱ��
_TaskISRRunningTime		OsTimeTaskISRTime;//ϵͳ����ʱ��
#endif
_TaskWheelMargin	   OsTimeTaskTimeWheel;//������Ƭʱ��
#if (osClockTimePeriod < osClockTimePeriodStandard)
_ClockTimePeriodValue      OsTimePeriodValue;//ʱ�����ڼ���
#endif
_OsTimePeriod		OsTimePeriod;

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
	OsTimePeriod = 1;
	if(osClock_Init(OsTimePeriod) == Error){//���ʱ�ӳ�ʼ������
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
    /*��ʱ����*/
	#if (osRunTime_Config > 0)//������ϵͳ����ʱ��
	#if (osClockTimePeriod > osClockTimePeriodStandard)
	OsTimeGetSystemRunTime() += (osClockTimePeriod / osClockTimePeriodStandard);//ϵͳ����ʱ�����м�ʱ
	#else
	OsTimeGetSystemRunTime() += OsTimePeriod;//ϵͳ����ʱ�����м�ʱ
	#endif
	#endif
     /*ͳ�Ʒ���*/
	#if (osPerf_Config > 0) //����������ͳ��
	if(osTaskGetOIRQFlag() > NULL){
		OsTimeGetTaskISRTime() += OsTimePeriod;
	}
	else if(1){//�������״̬Ϊδ���ȣ����м�ʱ
        osTaskGetRunTaskHandle() -> OccupyTime++;//����ռ��ʱ������
    }
    if(OsTimeGetSystemRunTime() % osTaskRunTime_Config == 0){//ϵͳÿ��һ��ʱ�����ͽ���ռ�ñ���ͳ��
        OSRecord.CTO = 0;//CPUռ������Ϊ0
		TaskHandleListBuf = osTaskGetTaskHandleListHead();
		do{//��ÿһ��������б���
			//TaskHandleListBuf -> OccupyRatio = TaskHandleListBuf -> OccupyTime / (osTaskRunTime_Config / 100);//�����������ռ�ñ�
			TaskHandleListBuf -> OccupyRatio = TaskHandleListBuf -> OccupyTime;//�����������ռ�ñ�
			//���㹫ʽ��ռ�ñ� = ��λʱ���ڵ�ռ��ʱ�� / (��λʱ�� / 100)
            OSRecord.CTO += TaskHandleListBuf -> OccupyRatio / (osTaskRunTime_Config / 100);//����CPUռ����
			//���㹫ʽ��CPUռ���� = CPUռ���� + ÿ�������ռ����
            TaskHandleListBuf -> OccupyTime = 0;//��յ�λʱ���ڵ�ռ��ʱ��

			TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
		}while(TaskHandleListBuf != osTaskGetTaskHandleListHead());
		if(OsTimeGetTaskISRTime() > NULL){
			OSRecord.CISRO = OsTimeGetTaskISRTime() / (osTaskRunTime_Config / 100);//����CPUռ����
			OsTimeGetTaskISRTime() = 0;
		}
		OSRecord.CSO = (OSRecord.TSC * OSRecord.TSSU) / (osTaskRunTime_Config /100) /1000;
		OSRecord.TSCb = OSRecord.TSC;
		OSRecord.TSC = 0;
    }
	#endif
    /*��Ƭ����*/
    if(OsTimeGetTaskTimeWheel() > 0 && osTaskGetOIRQFlag() == NULL){
		/*���������������ſ��Դ�����Ƭ��ʱ
		 *1.������Ƭʱ�������
		 *2.�ж�״̬Ϊ��
		 */
	   //��ǰ�������е��������Ƭʱ�����0���ҵ���״̬Ϊδ����״̬
		if(OsTimeGetTaskTimeWheel() >= OsTimePeriod){
			OsTimeGetTaskTimeWheel() -= OsTimePeriod;
		}else{
			OsTimeGetTaskTimeWheel() = 0;
		}
        if(OsTimeGetTaskTimeWheel() == 0){//��Ŀǰ�������е��������Ƭʱ��Ϊ��ʱ
			osTaskSwitch(OSCoreTaskHandle);//���������л�   
        }
    }
	TaskHandleListBuf = osTaskGetTaskHandleListHead();//��ȡ����������ͷ��ָ��
	/*��ʱ����*/
	do{//��ÿһ��������б���
        if(TaskHandleListBuf -> Config == Task_State_Up_DT){//�����������ʱ����(�ȴ�̬)���Ž���
			if(TaskHandleListBuf -> Delay >= OsTimePeriod){
				TaskHandleListBuf -> Delay -= OsTimePeriod;//���������ʱ���־�����ݼ�һ
			}else{
				TaskHandleListBuf -> Delay = 0;
			}
            if(TaskHandleListBuf -> Delay == 0){	//���������ʱ���־������Ϊ��ʱ
                TaskHandleListBuf  -> Config = Task_State_RE;//����������״̬��Ϊ����̬
                if(TaskHandleListBuf -> Level <  osTaskGetRunTaskHandle() -> Level){//������������ڵ�ǰ����������������ȼ�������ռ
                    TaskHandleListBuf -> Config = Task_State_RE;//����������״̬��Ϊ����̬
                    osTaskSwitch(TaskHandleListBuf); //���������л�
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
	OsTimePeriod = 1;
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
	if(osTaskLogin(
	osSTimer,
	STimeStackSize_Config,
	STimePriorityLevel_Config,
	STimeTimeWheel_Config,
	STimePass_Config,
	STimeName_Config,
	STimeSet_Config) 
	== NULL){

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
_STimer* osTimerLoginStatic(uint8_t* ListAddr,_STimeName* Name,_STaskDelay Flag,_STimeConfig Config,void* Addr)
{
	_STimer* STime_Buf = (_STimer*)ListAddr;
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
_STimer* osTimerLogin(_STimeName* Name,_STaskDelay Flag,_STimeConfig Config,void* Addr)
{
	uint8_t* Addr1;
	if(Config >= STimeConfig_NRestartL){
		Addr1 = osMemoryMalloc(sizeof(_STime));//Ϊ�����������ڴ�
	}else{
		Addr1 = osMemoryMalloc(sizeof(_STimer));//Ϊ�����������ڴ�
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
 * @��������: osSTimerLogout
 *
 * @��������: 
 *
 * @�������: STimer	�����ʱ�����
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osSTimerLogout(_STimer* STimer)
{
	return uLinkListDel(&STimeListHead,(uint32_t*)STimer);

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
	_STimer* STime_Buf;
	for(;;){
		STime_Buf = (_STimer*)STimeListHead;
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
			STime_Buf = (_STimer*)STime_Buf -> DownAddr;
		}
		osTaskDelayMs(1);
	}
	
}
#endif
