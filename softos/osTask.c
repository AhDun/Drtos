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
 * @�ļ�����: osTask.c
 *
 * @�ļ�����: ϵͳ"����"�ļ�
 *
 * @ע    ��: 
 *
 */


#include "osConfig.h"
#include "osTask.h"



_TaskHandle*	TaskHandle_Main;
_TaskHandle*	TaskHandle_SIRQ;

_TaskHandle* 	OsTaskRunTaskHandle;
_SwitchState	OsTaskSwitchState;//�������״̬
_TaskISRFlag	OsTaskISRFlag;//�ж�״̬
_TaskHandle* 	OsTaskNextTaskHandle;
_TaskHandle* 	OsTaskTaskHandleListHead;



/*
 *
 * @��������: osTaskInit
 *
 * @��������: ����ϵͳ��ʼ��
 *
 * @�������: ��
 *
 * @�� �� ֵ: -1:�������� / 0: ��ʼ���ɹ�
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osTaskInit(void)
{
    /***********************************������ѯ���ʼ��*********************************/
	osTaskGetTaskHandleListHead() = NULL;

	osTaskGetOIRQFlag() = 0;
	osTaskGetSwitchState() = TaskSwitch_Ready;
    /***********************************ϵͳ�����ʼ��**********************************/
	


	TaskHandle_Main = osTaskLogin("Main",(void*)0,Default_Stack_Size,TaskTimeWheelDefault,0,(void*)0,Task_Set_Default ); 
	if(TaskHandle_Main == NULL){

		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("Main ���񴴽�ʧ��\n");
		#endif
		return (Error);//����Error
	}


	osTaskGetNextTaskHandle() = TaskHandle_Main; 
	osTaskGetRunTaskHandle() = TaskHandle_Main;//���������е�������Ϣ���ָ�봫�͸��������������    
	OsTimeGetTaskTimeWheel() = osTaskGetRunTaskHandle() -> TaskTimeWheel;//����ǰ�����ʱ����Ƭд�뵽ʱ���¼��
	osTASK_START(&osTaskGetRunTaskHandle() -> RealSP);//������һ������

    return (OK);//����OK
}		

/*
 *
 * @��������: osTaskLogin
 *
 * @��������: ���񴴽����Զ������ڴ棩
 *
 * @�������:	TN ��������
 * @�������: 	TA �����ַ
 * @�������: 	TSS ����ջ����
 * @�������: 	TTW ����ʱ����Ƭ
 * @�������: 	TPL �������ȼ�
 * @�������: 	TPP ���񴫲�
 * @�������: 	TC ��������	
 *
 * @�� �� ֵ: -1:�������� / 0: �����ɹ�
 *
 * @ע    ��:
 *
 */	


_TaskHandle* osTaskLogin(
	_TaskName *TN,//��������
	void*  TA,//�����ַ	
	_TaskStackSize  TSS,//����ջ����
	_TaskTimeWheel  TTW,//����ʱ����Ƭ
	_TaskPriorityLevel  TPL,//�������ȼ�
	#if (osTaskParameterPass_Enable > 0)
    void*  TPP, //���񴫲�
	#endif
    _TaskConfig  TC//��������
)
{
	uint8_t* Addr1;
	Addr1 = osMemoryMalloc(sizeof(_TaskHandle) + TSS);//Ϊ���������ڴ�
	if(Addr1 == NULL){//���Ϊ�գ���˵���ڴ����ʧ��
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("ע������ʱ,��������ڴ�ʧ�� %s\n",TN);
		#endif
		return (NULL);//���ش���
	}
	return osTaskLogin_Static((_TaskHandle*)Addr1,TN,TA,TSS,TTW,TPL,TPP, TC);//���ʱ���ڴ������ɣ��ͽ��н�����ͨע��
}
/*
 *
 * @��������: 
 *
 * @��������: ���񴴽�
 *
 * @�������: 	TaskHandle �����
 * @�������: 	TN ��������
 * @�������: 	TA �����ַ
 * @�������: 	TSS ����ջ����
 * @�������: 	TTW ����ʱ����Ƭ
 * @�������: 	TPL �������ȼ�
 * @�������: 	TPP ���񴫲�
 * @�������: 	TC ��������	
 *
 * @�� �� ֵ: -1:�������� / 0: �����ɹ�
 *
 * @ע    ��: ����:
 *
 */
_TaskHandle* osTaskLogin_Static(
 
	_TaskHandle* TaskHandle,//�����
	_TaskName *TN,//��������
	void*  TA,//�����ַ
	_TaskStackSize  TSS,//����ջ����
	_TaskTimeWheel  TTW,//����ʱ����Ƭ
	_TaskPriorityLevel  TPL,//�������ȼ�
	#if (osTaskParameterPass_Enable > 0)
    void*  TPP, //���񴫲�
	#endif
    _TaskConfig  TC//��������
)
{
	_TaskHandle* TaskHandleList_Buf1;
	_TaskHandle* TaskHandleList_Buf2;
	uint8_t* StackAddr = (uint8_t*)TaskHandle + sizeof(_TaskHandle);
#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_ENABLE();//���뱣��
#endif
#if (osFPU_Enable > 0) //������FPU
	if(TSS < 320 || (TSS % 2) != 0){//��������˸���Ӳ������������ջ��СӦ����80*4�ֽ�
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("ע������ʱ����ջ�ڴ�̫С %s\n" ,TN);
		#endif
		goto osTaskLogin_Static_Error;
	}
#else
    if(TSS < 200 || (TSS % 2) != 0){//���û�������˸���Ӳ������������ջ��СҲӦ����50*4�ֽ�
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("ע������ʱ����ջ�ڴ�̫С %s\n" ,TN);
		#endif
		goto osTaskLogin_Static_Error;
	}
#endif
	TaskHandle -> Name = TN;//д����������
	TaskHandle -> Addr = TA;////д�������ַ
	TSS -= 1;
    TaskHandle -> RealSPb = TaskHandle -> RealSP = (uint32_t)((uint32_t)StackAddr + TSS);//д������ʵʱջָ��
    TaskHandle -> ParameterPass = TPP;//д�����񴫲�
	TaskHandle -> PriorityLevel = TPL;//д���������ȼ�
	TaskHandle -> PriorityLevelb = TPL;//д�����������ȼ�

	if(TC == Task_Set_Default){//�������ѡ����"��������"ѡ�����Ч
        TaskHandle -> Config = Task_State_RB;//��������Ϊ����̬
    }else{
        osTaskSet(TaskHandle,TC);
    }

	TaskHandle	-> PF = NULL;//����������Ϣ��Ϊ��

	#if (osClockTimePeriod > osClockTimePeriodStandard)//��ʱ�����ڴ���1000ʱ������ת��
	TTW = TTW / (osClockTimePeriod / osClockTimePeriodStandard);
	#endif

    if(TTW > 0){//�������ʱ����Ƭ�����㣬��ֱ�Ӵ��䵱ǰʱ����Ƭֵ
        TaskHandle -> TaskTimeWheel = TTW;//д��ʱ����Ƭ
    }
    else{//������ʹ��Ĭ��ֵ
        TaskHandle -> TaskTimeWheel = TaskTimeWheelDefault;//д��Ĭ��ֵʱ����Ƭ
    }



	if(osTaskGetTaskHandleListHead() == NULL){
		osTaskGetTaskHandleListHead() = TaskHandle;
		TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
	}else{
		TaskHandleList_Buf1  = (_TaskHandle*)osTaskGetTaskHandleListHead();
		if(TaskHandle -> PriorityLevel < TaskHandleList_Buf1 -> PriorityLevel){
			TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandleList_Buf1;
			while(TaskHandleList_Buf1 -> NextTaskHandle != (_NextTaskHandle*)osTaskGetTaskHandleListHead()){
				TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
			}
			TaskHandleList_Buf1 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
			osTaskGetTaskHandleListHead() = TaskHandle;
		}else{
			while(1){
				if(TaskHandle -> PriorityLevel < TaskHandleList_Buf1 -> PriorityLevel){
					TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandleList_Buf1;
					TaskHandleList_Buf2 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
					break;
				}else if(TaskHandleList_Buf1 -> NextTaskHandle == (_NextTaskHandle*)osTaskGetTaskHandleListHead()){
					TaskHandleList_Buf1 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
					TaskHandle -> NextTaskHandle = (_NextTaskHandle*)osTaskGetTaskHandleListHead();
					break;
				}
				TaskHandleList_Buf2 = TaskHandleList_Buf1;
				TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
			}
		}
	}



#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_DISABLE();//�˳�����
#endif
	return (TaskHandle);//����

osTaskLogin_Static_Error:
#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_DISABLE();//�˳�����
#endif
	return (NULL);//���ش���


}
/*
 *
 * @��������: 	osTaskLogout
 *
 * @��������: 	����ע��
 *
 * @�������:	TaskHandle	������
 *
 * @�� �� ֵ: 	-1:ע������0: ע���ɹ�
 *
 * @ע    ��: 	�������ע�����ͷ�
 *
 */	
OsErrorValue  osTaskLogout(_TaskHandle* TaskHandle)
{

	if(osTaskLogout_Static(TaskHandle) != OK){
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("�ͷ�����: �ڴ�ע��ʧ��\n");
		#endif
		return (Error);//�������󣬷��ش���
	}
	
	if(osMemoryFree(TaskHandle) != OK){
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("�ͷ�����: �ڴ��ͷ�ʧ��\n");
		#endif
		return (Error);//�������󣬷��ش���
	}
	return (OK);//���쳣������OK

}
/*
 *
 * @��������: 	osTaskLogout
 *
 * @��������: 	����ע��
 *
 * @�������:	TaskHandle	������
 *
 * @�� �� ֵ: 	-1:ע������0: ע���ɹ�
 *
 * @ע    ��: 	
 *
 */	
OsErrorValue  osTaskLogout_Static(_TaskHandle* TaskHandle)
{
	_TaskHandle* TaskHandleList_Buf1 = osTaskGetTaskHandleListHead();
	_TaskHandle* TaskHandleList_Buf2;
    #if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_ENABLE();//���뱣��
    #endif
	TaskHandleList_Buf1 = osTaskGetTaskHandleListHead();
	if(TaskHandle == osTaskGetTaskHandleListHead()){
		while(TaskHandleList_Buf1 -> NextTaskHandle != (_NextTaskHandle*)osTaskGetTaskHandleListHead()){
			TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
		}
		osTaskGetTaskHandleListHead() = (_TaskHandle*)osTaskGetTaskHandleListHead() -> NextTaskHandle;
		TaskHandleList_Buf1 -> NextTaskHandle = (_NextTaskHandle*)osTaskGetTaskHandleListHead();
		goto osTaskLogout_Static_OK;
	}else{
		do{
			TaskHandleList_Buf2 = TaskHandleList_Buf1;
			TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
			if(TaskHandleList_Buf1 == TaskHandle){
				TaskHandleList_Buf2 -> NextTaskHandle = TaskHandleList_Buf1 -> NextTaskHandle;
				goto osTaskLogout_Static_OK;
			}
		}while(TaskHandleList_Buf1 != osTaskGetTaskHandleListHead());
		goto osTaskLogout_Static_Error;
	}
	
osTaskLogout_Static_OK:
  #if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_DISABLE();//�˳�����
  #endif
	return (OK);//���쳣������OK
osTaskLogout_Static_Error:
  #if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_DISABLE();//�˳�����
  #endif
	return (Error);//���쳣������OK

}

/*
 *
 * @��������: osTaskTime_Choke_ms
 *
 * @��������: ���뼶������ʱ
 *
 * @�������: ms(��ʱʱ������λ����)	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */	
void osTaskDelayMs(uint32_t ms)
{
	if(ms > 0){
		#if (osClockTimePeriod > osClockTimePeriodStandard)
		ms = ms /(osClockTimePeriod / osClockTimePeriodStandard);	
		#endif
		while(osTaskGetSwitchState() != TaskSwitch_Ready);//����ѯCPU�Ƿ��Ѿ�����Ϊ����̬
		//��������ˣ��ͻ᷵����ֵ����whileѭ����ֱ��δ������
		osTaskGetRunTaskHandle() -> TimeFlag = ms;
		osTaskSwitchConfig_Enable(osTaskGetRunTaskHandle(),Task_State_Up_DT);
	}
}
/*
 *
 * @��������: osTaskDelayUs
 *
 * @��������: ΢�뼶������ʱ
 *
 * @�������: ms(��ʱʱ������λ΢��)	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */	
void osTaskDelayUs(uint32_t us)
{
	OsTimeGetTaskTimeWheel() = OsTimeGetTaskTimeWheel() + 1;
	osTaskTimeUs();
}


/*
 *
 * @��������: osTaskSwitch_State
 *
 * @��������: ��ѯ������л�̬
 *
 * @�������: ��	
 *
 * @�� �� ֵ: -1:��������0: �����ɹ�
 *
 * @ע    ��: ��
 *
 */	
/*
OsErrorValue osTaskSwitch_State(void)
{
    register OsErrorValue _tr0 = 1;
    CPU_PendSV_STATE();//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
	//��������ˣ��ͻ᷵����ֵ����whileѭ����ֱ��δ������
    if(_tr0){
        return TaskSwitch_Wait;//���صȴ�̬
    }
    else{
        return TaskSwitch_Ready;///���ؾ���̬
    }
    
}
*/

/*
 *
 * @��������: osTaskNext
 *
 * @��������: �����л�
 *
 * @�������: ��	
 *
 * @�� �� ֵ: -1:��������0: �����ɹ�
 *
 * @ע    ��: ��
 *
 */	
void osTaskNext(void)
{  
    osTaskGetSwitchState() = TaskSwitch_Run;
    //osTASK_HANGUP(&osTaskGetRunTaskHandle() -> RealSP);//ͨ����ǰ���������ջָ��,����ǰ������
    while(1){//������һ������
		switch(osTaskGetNextTaskHandle() -> Config){//����״̬�����������������switch���
				case Task_State_RB:
									osTaskGetNextTaskHandle() -> RealSP = osTaskGetNextTaskHandle() -> RealSPb;
									osTASK_Stack_Init(osTaskGetNextTaskHandle() -> ParameterPass,(void* )osTaskGetNextTaskHandle() -> Addr,(void* )osTaskExit,&osTaskGetNextTaskHandle() -> RealSP);//��������
				case Task_State_Up_IN://�����������������(����̬)
				case Task_State_Up_TD://�����������Ƭ����(����̬)	
				case Task_State_RE:	  //������������
									osTaskGetRunTaskHandle() = osTaskGetNextTaskHandle();//���������е�������Ϣ���ָ�봫�͸��������������
									osTaskGetNextTaskHandle() = (_TaskHandle*)osTaskGetNextTaskHandle() -> NextTaskHandle;
									OsTimeGetTaskTimeWheel() = osTaskGetRunTaskHandle() -> TaskTimeWheel;//����ǰ�����ʱ����Ƭд�뵽ʱ���¼��
									osTaskGetSwitchState() = TaskSwitch_Ready;//������״̬��Ϊ"δ����"
									#if (osPerformanceStatistics_Enable > 0)
									PS.TSC += 1;
									#endif
									return;//�˳�����

				default:break;//����֮��!
			}
			osTaskGetNextTaskHandle() = (_TaskHandle*)osTaskGetNextTaskHandle() -> NextTaskHandle;
    }
}
/*
 *
 * @��������: osTaskSet
 *
 * @��������: ��������
 *
 * @�������: ��	
 *
 * @�� �� ֵ: -1:��������0: �����ɹ�
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osTaskSet(_TaskHandle* TaskHandle,uint8_t Pv)
{

	if(TaskHandle != 0){//������
		switch(Pv){
			case Task_Set_Pause://��ͣ����
									TaskHandle -> Config = Task_State_DI;//��Ϊ����̬
									return (OK);//����OK

			case Task_Set_Cont://��������
									TaskHandle -> Config = Task_State_Up_IN;//��Ϊ����̬
									return (OK);//����OK

			case Task_Set_Reboot://��������									
									TaskHandle -> Config = Task_State_RB;//
									return (OK);//����OK
			case Task_Set_Start://������������
									while(osTaskGetSwitchState() != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
									osTaskGetNextTaskHandle() = TaskHandle;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
									osTaskSwitchConfig_Enable(TaskHandle,Task_State_Up_IN);
									return (OK);//����OK
			case Task_Set_Up://��������
								return (OK);

									
		}
	}else{//����
		switch(Pv){
			case Task_Set_Pause://��ͣ����
									while(osTaskGetSwitchState() != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
									osTaskSwitchConfig_Enable(osTaskGetRunTaskHandle(),Task_State_DI);
									return (OK);//����OK

			case Task_Set_Cont://��������
									return (OK);//����OK

			case Task_Set_Reboot://��������
									while(osTaskGetSwitchState() != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
									osTaskSwitchConfig_Enable(osTaskGetRunTaskHandle(),Task_State_RB);//���������л�
									return (OK);//����OK
			case Task_Set_Start://������������
									return (OK);//����OK
			case Task_Set_Up://��������
								while(osTaskGetSwitchState() != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬								
								osTaskSwitchConfig_Enable(osTaskGetRunTaskHandle(),Task_State_Up_IN);//���������л�
								return (OK);

									
		}
	}
	#if (osTaskDebug_Enable > 0)
	osTaskErrorDebug("��������ʱ������ȷ�������� %s\n" ,osTaskGetRunTaskHandle() -> Name);
	#endif
	return (Error);
}
/*
 *
 * @��������: osTaskEnd
 *
 * @��������: �������
 *
 * @�������: ��	
 *
 * @�� �� ֵ: -1:��������0: �����ɹ�
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osTaskExit(void)
{
	while(true){
		osTaskSwitchConfig_Enable(osTaskGetRunTaskHandle(),Task_State_ST);//���������л�
	}
}
/*
 *
 * @��������: osTaskAddrReplace
 *
 * @��������: �����ַ�滻
 *
 * @�������: ��	
 *
 * @�� �� ֵ: -1:��������0: �����ɹ�
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osTaskAddrReplace(_TaskHandle* TaskHandle,void* NewTA)
{
	if(TaskHandle == 0){
		osTaskGetRunTaskHandle() -> Addr = NewTA;
		while(osTaskGetSwitchState() != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
		osTaskGetRunTaskHandle() -> Config = Task_State_RB;//
		osTaskSwitchConfig_Enable(osTaskGetRunTaskHandle(),Task_State_RB);//���������л�
		return (OK);//����OK

	}else{
		TaskHandle -> Addr = NewTA;
		TaskHandle -> Config = Task_State_RB;//
		return (OK);//����OK
	}

}

OsErrorValue osTaskErrorHardFault(uint32_t pc,uint32_t psp)
{
	#if (osTaskRunError_Enable > 0)
	uint8_t Count = 1;
	osTaskEnterIRQ();
	while(Count--){
		osTaskErrorDebug("\n\n\n����Ϊ%s����������Ӳ�������쳣!!!\n",osTaskGetRunTaskHandle() -> Name);
		osTaskErrorDebug("�������ȼ�:%d\n",osTaskGetRunTaskHandle() -> PriorityLevel);
		osTaskErrorDebug("����ǰʹ����:%d%%\n",osTaskGetRunTaskHandle() -> OccupyRatio);
		osTaskErrorDebug("������ʱʣ��ʱ��:%d%ms\n���񵥴��������ʱ��:%dms\n",osTaskGetRunTaskHandle() -> TimeFlag,osTaskGetRunTaskHandle() -> TaskTimeWheel);
		osTaskErrorDebug("������һ��״̬:",0,0);
		switch(osTaskGetRunTaskHandle() -> Config){
			case Task_State_Up_TD:osTaskErrorDebug("��Ƭ����\n");break;
			case Task_State_Up_IN:osTaskErrorDebug("��������\n");break;
			case Task_State_Up_DT:osTaskErrorDebug("��ʱ����\n");break;
			case Task_State_Up_SI:osTaskErrorDebug("�źŹ���\n");break;
			case Task_State_Up_PT:osTaskErrorDebug("�ʼ�����\n");break;
			case Task_State_DI:osTaskErrorDebug("����̬\n");break;
			case Task_State_ST:osTaskErrorDebug("��ֹ̬\n");break;
			case Task_State_RB:osTaskErrorDebug("����̬\n");break;
			case Task_State_OP:osTaskErrorDebug("����̬\n");break;
			case Task_State_Up:osTaskErrorDebug("����̬\n");break;
		}
		osTaskErrorDebug("��������״̬:");
		if(osTaskGetRunTaskHandle() -> PF == NULL){
			osTaskErrorDebug("�յ�\n");
		}
		else{
			osTaskErrorDebug("�ǿ�\n");
		}
		osTaskErrorDebug("����ջ�ܴ�С:%d�ֽ�\n����ջʣ��:%d�ֽ�\n",(uint32_t)osTaskGetRunTaskHandle() -> RealSPb - (uint32_t)osTaskGetRunTaskHandle() -  sizeof(_TaskHandle),psp - ((uint32_t)osTaskGetRunTaskHandle() +  sizeof(_TaskHandle)));
		osTaskErrorDebug("�����쳣��:%X\n",pc);
		osTaskErrorDebug("�ڴ�����:%d�ֽ�\n�ڴ�����:%d�ֽ�",osMemoryGetAllValue(),osMemoryGetFreeValue());
	}
	#endif
	#if (osTaskErrorSet == 1)
	osTaskSet(NULL,Task_Set_Reboot);
	#elif(osTaskErrorSet == 0)
	osTaskSet(NULL,Task_Set_Pause);
	#endif
	osTaskExitIRQ();
	return (OK);
}
/*
 *
 * @��������: osTaskSpeedTest
 *
 * @��������: �����л��ٶȲ���
 *
 * @�������: ��	
 *
 * @�� �� ֵ: -1:��������0: �����ɹ�
 *
 * @ע    ��: ��
 *
 */

OsErrorValue osTaskSpeedTest(void)
{
	#if (osSpeedTest_Enable > 0)
	uint32_t t0,t1;
	osTaskGetRunTaskHandle() -> Config = Task_State_Up_IN;
	t0 = SysTick->VAL;
	osTaskSwitch_Enable();//���������л�
	t1 = SysTick->VAL;
	#if (osPerformanceStatistics_Enable > 0)
	PS.TSSU = (osCPU_Period*(t0 - t1)*8)/osCPU_Period_Times;
	#endif
	#if (osTaskDebug_Enable > 0)
	osTaskErrorDebug("�����л��ٶȲ���: t0 %d - t1 %d = %d��ʱ������(%fus)\n",t0,t1,(t0 - t1)*8,(osCPU_Period*(t0 - t1)*8)/osCPU_Period_Times);
	#endif
	#endif
	return (OK);
}

OsErrorValue osTaskMonitor(void)

{
	_TaskHandle* TaskHandleListBuf = osTaskGetTaskHandleListHead();;
	do{
		print("����<%s>��ʹ����Ϊ:ռ��ʱ��:%dms | �������ȼ�:%d | ����״̬:",TaskHandleListBuf -> Name,TaskHandleListBuf -> OccupyRatio,TaskHandleListBuf -> PriorityLevel);
		if(TaskHandleListBuf != osTaskGetRunTaskHandle() || osTaskGetSwitchState() != TaskSwitch_Ready){
			switch(TaskHandleListBuf -> Config){
				case Task_State_Up_TD:print("��Ƭ����\n");break;
				case Task_State_Up_IN:print("��������\n");break;
				case Task_State_Up_DT:print("��ʱ����\n");break;
				case Task_State_Up_SI:print("�źŹ���\n");break;
				case Task_State_Up_PT:print("�ʼ�����\n");break;
				case Task_State_DI:print("����̬\n");break;
				case Task_State_ST:print("��ֹ̬\n");break;
				case Task_State_RB:print("����̬\n");break;
				case Task_State_OP:print("����̬\n");break;
				case Task_State_Up:print("����̬\n");break;
			}
		}
		else{
			print("��������\n");
		}
		TaskHandleListBuf = (_TaskHandle*)TaskHandleListBuf -> NextTaskHandle;
	}while(TaskHandleListBuf != osTaskGetTaskHandleListHead());

	
	print("CPU��ʹ����:%d%% = ���� %d%% + �ж�%d%% + ����%d%%\n",PS.CTO + PS.CISRO + PS.CSO,PS.CTO,PS.CISRO,PS.CSO);

	print("������ȴ���:%d | Ԥ�ƺ�ʱ:%fus(%fms)\n",PS.TSCb,PS.TSCb*PS.TSSU,(PS.TSCb*PS.TSSU) / 1000);

	print("�ڴ� ����:%d�ֽ� | ����:%d�ֽ� | �ɷ���:%d�ֽ� | ����:%d\n",osMemoryGetAllValue(),osMemoryGetFreeValue(),osMemoryGetPassValue(),osMemorySum());
	tprint("ϵͳ������: %d�� %hСʱ %m���� %s��\n",OsTimeGetSystemRunTime());
	
	return (OK);
}
OsErrorValue osTaskSIRQInit(void)
{
	TaskHandle_SIRQ = osTaskLogin("SIRQ",osTaskSIRQ,400,TaskTimeWheelDefault,-127,(void*)0,Task_Set_Default); 
	if(TaskHandle_SIRQ == NULL){

		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("SIRQ ���񴴽�ʧ��\n");
		#endif
		return (Error);//����Error
	}
	return (OK);
}
/*
 *
 * @��������: osTaskSIRQ_Enable
 *
 * @��������: �������ж�
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void osTaskSIRQ_Enable(_SIRQList* SIRQList_Addr)
{
	TaskHandle_SIRQ -> ParameterPass = (_TaskParameterPass*)SIRQList_Addr;
	osTaskGetNextTaskHandle() = TaskHandle_SIRQ;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
	osTaskSwitchConfig_Enable(TaskHandle_SIRQ,Task_State_Up_IN);
}
/*
 *
 * @��������: osTaskSIRQLogin
 *
 * @��������: ���ж�ע��
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osTaskSIRQLogin(_SIRQList* SIRQList_Addr,void* Addr)
{
	SIRQList_Addr[++*SIRQList_Addr] = (_TaskAddr)Addr;
	return (OK);//���ش���
}
/*
 *
 * @��������: osTaskSIRQ
 *
 * @��������: ���ж���Ӧ
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void osTaskSIRQ(void)
{
	_SIRQList* SIRQList_Addr;
	uint8_t SIRQList_Count;

	while(1){
		//osTaskGetRunTaskHandle() -> Config = Task_State_Up_SI;//��������(����̬) 
		osTaskSwitchConfig_Enable(osTaskGetRunTaskHandle(),Task_State_Up_SI);
		SIRQList_Addr = (_SIRQList*)osTaskGetRunTaskHandle() -> ParameterPass;
		for(SIRQList_Count = 1; SIRQList_Count <= *SIRQList_Addr; SIRQList_Count++){
			Jump((uint32_t*)SIRQList_Addr[SIRQList_Count]);
		}
	}
	
}





