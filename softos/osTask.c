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

_TaskSwitchState TaskSwitchState;//�������״̬��

_TaskHandle*	TaskHandle_Main;
_TaskHandle*	TaskHandle_SIRQ;

_TaskHandle*	RunTaskHandle;//��ǰ������������ľ��

_TaskHandle*    TaskHandleListHead;


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
osErrorValue osTaskInit(void)
{
    /***********************************������ѯ���ʼ��*********************************/
	TaskHandleListHead = NULL;

	TaskSwitchState.ISRFlag = 0;
	TaskSwitchState.SwitchState = TaskSwitch_Ready;
    /***********************************ϵͳ�����ʼ��**********************************/
	


	TaskHandle_Main = osTaskLogin("Main",(void*)0,Default_Stack_Size,TaskTimeWheelDefault,0,(void*)0,Task_Set_Default ); 
	if(TaskHandle_Main == NULL){

		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("Main ���񴴽�ʧ��\n");
		#endif
		return (Error);//����Error
	}


	TaskSwitchState.NextTaskHandle = TaskHandle_Main; 
	RunTaskHandle = TaskHandle_Main;//���������е�������Ϣ���ָ�봫�͸��������������    
	osTime.TTWM = RunTaskHandle -> TaskTimeWheel;//����ǰ�����ʱ����Ƭд�뵽ʱ���¼��
	osTASK_START(&RunTaskHandle -> RealSP);//������һ������

    return (OK);//����OK
}		
osErrorValue osTaskSIRQInit(void)
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
#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
		osProtect_DISABLE();//�˳�����
#endif
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("ע������ʱ����ջ�ڴ�̫С %s\n" ,TN);
		#endif
		return (NULL);//���ش���
	}
#else
    if(TSS < 200 || (TSS % 2) != 0){//���û�������˸���Ӳ������������ջ��СҲӦ����50*4�ֽ�
#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
		osProtect_DISABLE();//�˳�����
#endif
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("ע������ʱ����ջ�ڴ�̫С %s\n" ,TN);
		#endif
		return (NULL);//���ش���
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



	

	if(TaskHandleListHead == NULL){
		TaskHandleListHead = TaskHandle;
		TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
	}else{
		TaskHandleList_Buf1  = (_TaskHandle*)TaskHandleListHead;
		if(TaskHandle -> PriorityLevel < TaskHandleList_Buf1 -> PriorityLevel){
			TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandleList_Buf1;
			while(TaskHandleList_Buf1 -> NextTaskHandle != (_NextTaskHandle*)TaskHandleListHead){
				TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
			}
			TaskHandleList_Buf1 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
			TaskHandleListHead = TaskHandle;
		}else{
			while(1){
				if(TaskHandle -> PriorityLevel < TaskHandleList_Buf1 -> PriorityLevel){
					TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandleList_Buf1;
					TaskHandleList_Buf2 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
					break;
				}else if(TaskHandleList_Buf1 -> NextTaskHandle == (_NextTaskHandle*)TaskHandleListHead){
					TaskHandleList_Buf1 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
					TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandleListHead;
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
osErrorValue  osTaskLogout(_TaskHandle* TaskHandle)
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
osErrorValue  osTaskLogout_Static(_TaskHandle* TaskHandle)
{

    #if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_ENABLE();//���뱣��
    #endif


  #if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_DISABLE();//�˳�����
  #endif
	return (OK);//���쳣������OK
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
		while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//����ѯCPU�Ƿ��Ѿ�����Ϊ����̬
		//��������ˣ��ͻ᷵����ֵ����whileѭ����ֱ��δ������
		RunTaskHandle -> TimeFlag = ms;
		osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_Up_DT);
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
	osTime.TTWM = osTime.TTWM + 1;
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
osErrorValue osTaskSwitch_State(void)
{
    register osErrorValue _tr0 = 1;
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
    TaskSwitchState.SwitchState = TaskSwitch_Run;
    //osTASK_HANGUP(&RunTaskHandle -> RealSP);//ͨ����ǰ���������ջָ��,����ǰ������
    while(1){//������һ������
		switch(TaskSwitchState.NextTaskHandle -> Config){//����״̬�����������������switch���
				case Task_State_RB:
									TaskSwitchState.NextTaskHandle -> RealSP = TaskSwitchState.NextTaskHandle -> RealSPb;
									osTASK_Stack_Init(TaskSwitchState.NextTaskHandle -> ParameterPass,(void* )TaskSwitchState.NextTaskHandle -> Addr,(void* )osTaskExit,&TaskSwitchState.NextTaskHandle -> RealSP);//��������
				case Task_State_Up_IN://�����������������(����̬)
				case Task_State_Up_TD://�����������Ƭ����(����̬)	
				case Task_State_RE:	  //������������
									RunTaskHandle = TaskSwitchState.NextTaskHandle;//���������е�������Ϣ���ָ�봫�͸��������������
									TaskSwitchState.NextTaskHandle = (_TaskHandle*)TaskSwitchState.NextTaskHandle -> NextTaskHandle;
									osTime.TTWM = RunTaskHandle -> TaskTimeWheel;//����ǰ�����ʱ����Ƭд�뵽ʱ���¼��
									TaskSwitchState.SwitchState = TaskSwitch_Ready;//������״̬��Ϊ"δ����"
									#if (osPerformanceStatistics_Enable > 0)
									PS.TSC += 1;
									#endif
									return;//�˳�����

				default:break;//����֮��!
			}
			TaskSwitchState.NextTaskHandle = (_TaskHandle*)TaskSwitchState.NextTaskHandle -> NextTaskHandle;
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
osErrorValue osTaskSet(_TaskHandle* TaskHandle,uint8_t Pv)
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
									while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
									TaskSwitchState.NextTaskHandle = TaskHandle;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
									osTaskSwitchConfig_Enable(TaskHandle,Task_State_Up_IN);
									return (OK);//����OK
			case Task_Set_Up://��������
								return (OK);

									
		}
	}else{//����
		switch(Pv){
			case Task_Set_Pause://��ͣ����
									while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
									osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_DI);
									return (OK);//����OK

			case Task_Set_Cont://��������
									return (OK);//����OK

			case Task_Set_Reboot://��������
									while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
									osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_RB);//���������л�
									return (OK);//����OK
			case Task_Set_Start://������������
									return (OK);//����OK
			case Task_Set_Up://��������
								while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬								
								osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_Up_IN);//���������л�
								return (OK);

									
		}
	}
	#if (osTaskDebug_Enable > 0)
	osTaskErrorDebug("��������ʱ������ȷ�������� %s\n" ,RunTaskHandle -> Name);
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
osErrorValue osTaskExit(void)
{
	while(true){
		osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_ST);//���������л�
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
osErrorValue osTaskAddrReplace(_TaskHandle* TaskHandle,void* NewTA)
{
	if(TaskHandle == 0){
		RunTaskHandle -> Addr = NewTA;
		while(TaskSwitchState.SwitchState != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
		RunTaskHandle -> Config = Task_State_RB;//
		osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_RB);//���������л�
		return (OK);//����OK

	}else{
		TaskHandle -> Addr = NewTA;
		TaskHandle -> Config = Task_State_RB;//
		return (OK);//����OK
	}

}

osErrorValue osTaskErrorHardFault(uint32_t pc,uint32_t psp)
{
	#if (osTaskRunError_Enable > 0)
	uint8_t Count = 1;
	osTaskEnterIRQ();
	while(Count--){
		osTaskErrorDebug("\n\n\n����Ϊ%s����������Ӳ�������쳣!!!\n",RunTaskHandle -> Name);
		osTaskErrorDebug("�������ȼ�:%d\n",RunTaskHandle -> PriorityLevel);
		osTaskErrorDebug("����ǰʹ����:%d%%\n",RunTaskHandle -> OccupyRatio);
		osTaskErrorDebug("������ʱʣ��ʱ��:%d%ms\n���񵥴��������ʱ��:%dms\n",RunTaskHandle -> TimeFlag,RunTaskHandle -> TaskTimeWheel);
		osTaskErrorDebug("������һ��״̬:",0,0);
		switch(RunTaskHandle -> Config){
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
		if(RunTaskHandle -> PF == NULL){
			osTaskErrorDebug("�յ�\n");
		}
		else{
			osTaskErrorDebug("�ǿ�\n");
		}
		osTaskErrorDebug("����ջ�ܴ�С:%d�ֽ�\n����ջʣ��:%d�ֽ�\n",(uint32_t)RunTaskHandle -> RealSPb - (uint32_t)RunTaskHandle -  sizeof(_TaskHandle),psp - ((uint32_t)RunTaskHandle +  sizeof(_TaskHandle)));
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

osErrorValue osTaskSpeedTest(void)
{
	#if (osSpeedTest_Enable > 0)
	uint32_t t0,t1;
	RunTaskHandle -> Config = Task_State_Up_IN;
	t0 = SysTick->VAL;
	osTaskSwitch_Enable();//���������л�
	t1 = SysTick->VAL;
	#if (osPerformanceStatistics_Enable > 0)
	PS.TSSU = (t0 - t1) / (osCPU_Freq / 8);
	#endif
	#if (osTaskDebug_Enable > 0)
	osTaskErrorDebug("�����л��ٶȲ���\nt0=%d\nt1=%d\n�л��ٶ�=%fus\n",t0,t1,((t0 - t1) / (osCPU_Freq / 8))*1.0);
	#endif
	#endif
	return (OK);
}

osErrorValue osTaskMonitor(void)

{
	_TaskHandle* TaskHandleListBuf = TaskHandleListHead;;
	do{
		print("����<%s>��ʹ����Ϊ:ռ��ʱ��:%dms | �������ȼ�:%d | ����״̬:",TaskHandleListBuf -> Name,TaskHandleListBuf -> OccupyRatio,TaskHandleListBuf -> PriorityLevel);
		if(TaskHandleListBuf != RunTaskHandle || TaskSwitchState.SwitchState != TaskSwitch_Ready){
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
	}while(TaskHandleListBuf != TaskHandleListHead);

	
	print("CPU��ʹ����:%d%% = ���� %d%% + �ж�%d%% + ����%d%%\n",PS.CTO + PS.CISRO + PS.CSO,PS.CTO,PS.CISRO,PS.CSO);
	if(PS.TSC*PS.TSSU > 1000){
		print("������ȴ���:%d | Ԥ�ƺ�ʱ:%dms\n",PS.TSCb,PS.TSCb*PS.TSSU / 1000);
	}else{
		print("������ȴ���:%d | Ԥ�ƺ�ʱ:%dus\n",PS.TSCb,PS.TSCb*PS.TSSU);
	}
	print("�ڴ� ����:%d�ֽ� | ����:%d�ֽ� | �ɷ���:%d�ֽ� | ����:%d\n",osMemoryGetAllValue(),osMemoryGetFreeValue(),osMemoryGetPassValue(),osMemorySum());
	tprint("ϵͳ������: %d�� %hСʱ %m���� %s��\n",osTime. TSRT);
	
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
	TaskHandle_SIRQ -> Config = Task_State_Up_IN;//��������(����̬)
	TaskSwitchState.NextTaskHandle = TaskHandle_SIRQ;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
	osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_Up_IN);
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
osErrorValue osTaskSIRQLogin(_SIRQList* SIRQList_Addr,void* Addr)
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
		//RunTaskHandle -> Config = Task_State_Up_SI;//��������(����̬) 
		osTaskSwitchConfig_Enable(RunTaskHandle,Task_State_Up_SI);
		SIRQList_Addr = (_SIRQList*)RunTaskHandle -> ParameterPass;
		for(SIRQList_Count = 1; SIRQList_Count <= *SIRQList_Addr; SIRQList_Count++){
			Jump((uint32_t*)SIRQList_Addr[SIRQList_Count]);
		}
	}
	
}





