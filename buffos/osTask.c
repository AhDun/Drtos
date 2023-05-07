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

#if (SIRQ_Config > 0)
_TaskHandle*	TaskHandle_SIRQ;
#endif

_TaskHandle*	OSCoreTaskHandle;//Main������
uint32_t		OSCoreTaskStack[sizeof(_TaskHandle)];
_TaskHandle* 	volatile OsTaskRunTaskHandle;//�������е�������
_TaskHandle* 	volatile OsTaskNextTaskHandle;//��һ��Ҫ���е�������
_TaskSwitchQueue	OsTaskSwitchQueue;//��������������
_TaskISRFlag	OsTaskISRFlag;//�ж�״̬
_TaskHandle* 	OsTaskTaskHandleListHead;//�����������ͷ
uint16_t		OsTaskIdle;




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
	OsTaskIdle = 0;
    /***********************************ϵͳ�����ʼ��**********************************/
	
	OSCoreTaskHandle = (_TaskHandle*)OSCoreTaskStack;
	osTaskLoginStatic(OSCoreTaskHandle,
						(void*)0,
						OSCoreStackSize_Config,
						OSCorePriorityLevel_Config,
						OSCoreTimeWheel_Config,
						OSCorePass_Config,
						#if (osTaskName_Config > 0)
						OSCoreName_Config,
						#endif
						OSCoreSet_Config); 

								
	if(OSCoreTaskHandle == NULL){
		#if (osTaskLog_Config > 0)
		osLogE("osTaskInit","Main ���񴴽�ʧ��\n");
		#endif
		return (Error);//����Error
	}



	osTaskGetNextTaskHandle() = OSCoreTaskHandle; 
	osTaskGetRunTaskHandle() = OSCoreTaskHandle;//���������е�������Ϣ���ָ�봫�͸��������������� 
	osTaskGetNextTaskHandle() -> Config = Task_State_RE;//����������״̬��Ϊ
	OsTimeGetTaskTimeWheel() = osTaskGetRunTaskHandle() -> Wheel;//����ǰ�����ʱ����Ƭд�뵽ʱ���¼��
	#if (osTaskUseStack_Config > 0)
	osLinkUseEnable();//��������ջ
	#endif
	//ISR_Touch();
    return (OK);//����OK
}		


void osTaskStart(void)
{
	for(;;){osTaskNext();}
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





_TaskHandle* osTaskLoad(_TaskHandle* TaskHandle,uint8_t Config)
{
	uint8_t* Addr0;
	uint32_t Length = TaskHandle -> Length;
	_TaskHandle* TaskHandleList_Buf1;
	_TaskHandle* TaskHandleList_Buf2;
	TaskHandle -> Levelb = 	TaskHandle -> Level;
	switch(Config){
		case Load_Stack://����ջ�ڴ�
			 Addr0 = osMemoryMalloc(Length);//�����ڴ�
			if(Addr0 == NULL){//���Ϊ�գ���˵���ڴ����ʧ��
				#if (osTaskLog_Config > 0)
				osLogE("osTaskLogin","��������ڴ�ʧ��\n");
				#endif
				return (NULL);//���ش���
			}
			break;			
		case Load_Create://��������
			TaskHandleList_Buf1 = osMemoryMalloc(Length + sizeof(_TaskHandle));//�����ڴ�
			if(TaskHandleList_Buf1 == NULL){//���Ϊ�գ���˵���ڴ����ʧ��
				#if (osTaskLog_Config > 0)
				osLogE("osTaskLogin","��������ڴ�ʧ��\n");
				#endif
				return (NULL);//���ش���
			}
			//TaskHandleList_Buf1 = TaskHandle;

			TaskHandleList_Buf1 -> Config = TaskHandle -> Config;
			TaskHandleList_Buf1 -> Wheel = TaskHandle -> Wheel;
			TaskHandleList_Buf1 -> Level = TaskHandle -> Level;
			TaskHandleList_Buf1 -> Addr = TaskHandle -> Addr;

			#if (osTaskName_Config > 0)
			TaskHandleList_Buf1 -> Name = TaskHandle -> Name;
			#endif
			#if (osSignal_Config & Signal_Mutual)
			TaskHandleList_Buf1 -> Levelb = TaskHandle -> Levelb;
			#endif
			#if (osTaskArg_Config > 0)
			TaskHandleList_Buf1 -> Arg = TaskHandle -> Arg;
			#endif
			TaskHandle	-> Arg1 = NULL;//����������Ϣ��Ϊ��

			TaskHandle = TaskHandleList_Buf1;
			Addr0 = (uint8_t*)TaskHandle + sizeof(_TaskHandle);
			break;	
	}
	#if (osTaskStackDir_Config > 0)
	TaskHandle -> Length = TaskHandle -> RealSP = (uint32_t)((uint32_t)Addr0 + (Length - 1));//д������ʵʱջָ��
	#else
	TaskHandle -> Length = TaskHandle -> RealSP =  (uint32_t)Addr0;
	#endif

	if(osTaskGetTaskHandleListHead() == NULL){
		osTaskGetTaskHandleListHead() = TaskHandle;
		TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
	}else{
		TaskHandleList_Buf1  = (_TaskHandle*)osTaskGetTaskHandleListHead();
		if(TaskHandle -> Level < TaskHandleList_Buf1 -> Level){
			TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandleList_Buf1;
			while(TaskHandleList_Buf1 -> NextTaskHandle != (_NextTaskHandle*)osTaskGetTaskHandleListHead()){
				TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
			}
			TaskHandleList_Buf1 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
			osTaskGetTaskHandleListHead() = TaskHandle;
		}else{
			for(;;){
				if(TaskHandle -> Level < TaskHandleList_Buf1 -> Level){
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
	TaskHandle -> Config = Task_State_RB;
	return (TaskHandle);

}


_TaskHandle* osTaskLogin(
	void*  Addr,//�����ַ	
	_TaskStackSize  StackSize,//����ջ����
	_TaskLevel  Level,//�������ȼ�
	_TaskWheel  Wheel,//����ʱ����Ƭ
	#if (osTaskArg_Config > 0)
    void*  Arg, //���񴫲�
	#endif
	#if (osTaskName_Config > 0)
	_TaskName *Name,
	#endif
    _TaskConfig  Config//��������
)
{
	uint8_t* Addr1;

	if(StackSize < osTaskMinimumStackSize){//��������˸���Ӳ������������ջ��СӦ����80*4�ֽ�
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLogin","����ջ�ڴ�̫С\n");
		#endif
		return (NULL);//���ش���
	}
	if((StackSize % 2) != 0){//��������˸���Ӳ������������ջ��СӦ����80*4�ֽ�
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLogin","����ջ���ȱ���Ϊż��\n");
		#endif
		return (NULL);//���ش���
	}

	Addr1 = osMemoryMalloc(sizeof(_TaskHandle) + StackSize);//Ϊ�����������ڴ�
	if(Addr1 == NULL){//���Ϊ�գ���˵���ڴ����ʧ��
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLogin","��������ڴ�ʧ��\n");
		#endif
		return (NULL);//���ش���
	}
	return osTaskLoginStatic((_TaskHandle*)Addr1,
	Addr,StackSize,Level,Wheel,Arg, 
	#if (osTaskName_Config > 0)
	Name,
	#endif
	Config);//���ʱ���ڴ������ɣ��ͽ��н�����ͨע��
}



/*
 *
 * @��������: 
 *
 * @��������: ���񴴽�
 *
 * @�������: 	TaskHandle ������
 * @�������: 	Name ��������
 * @�������: 	Addr �����ַ
 * @�������: 	StackSize ����ջ����
 * @�������: 	Wheel ����ʱ����Ƭ
 * @�������: 	Level �������ȼ�
 * @�������: 	Arg ���񴫲�
 * @�������: 	Config ��������	
 *
 * @�� �� ֵ: -1:�������� / 0: �����ɹ�
 *
 * @ע    ��: ����:
 *
 */
_TaskHandle* osTaskLoginStatic(
	_TaskHandle* TaskHandle,//������
	void*  Addr,//�����ַ
	_TaskStackSize  StackSize,//����ջ����
	_TaskLevel  Level,//�������ȼ�
	_TaskWheel  Wheel,//����ʱ����Ƭ
	#if (osTaskArg_Config > 0)
    void*  Arg, //���񴫲�
	#endif
	#if (osTaskName_Config > 0)
	_TaskName *Name,
#endif
    _TaskConfig  Config//��������
)
{
	_TaskHandle* TaskHandleList_Buf1;
	_TaskHandle* TaskHandleList_Buf2;
	uint8_t* StackAddr = (uint8_t*)TaskHandle + sizeof(_TaskHandle);
#if (osCriticalToProtect_Config > 0)//�������ٽ籣��
	osProtect_ENABLE();//���뱣��
#endif

	if(StackSize < osTaskMinimumStackSize){//��������˸���Ӳ������������ջ��СӦ����80*4�ֽ�
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLoginStatic","����ջ�ڴ�̫С\n");
		#endif
		goto osTaskLoginStatic_Error;
	}
	if((StackSize % 2) != 0){//��������˸���Ӳ������������ջ��СӦ����80*4�ֽ�
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLoginStatic","����ջ���ȱ���Ϊż��\n");
		#endif
		goto osTaskLoginStatic_Error;
	}

#if (osTaskName_Config > 0)
	TaskHandle -> Name = Name;//д����������
#endif
	TaskHandle -> Addr = Addr;////д�������ַ
	StackSize -= 1;
	#if (osTaskStackDir_Config > 0)
    TaskHandle -> Length = TaskHandle -> RealSP = (uint32_t)((uint32_t)StackAddr + StackSize);//д������ʵʱջָ��
	#else
	TaskHandle -> Length = TaskHandle -> RealSP =  (uint32_t)StackAddr;
	#endif

	#if (osTaskArg_Config > 0)
    TaskHandle -> Arg = Arg;//д�����񴫲�
	#endif

	TaskHandle -> Level = Level;//д���������ȼ�

	#if (osSignal_Config & Signal_Mutual)
	TaskHandle -> Levelb = Level;//д�����������ȼ�
	#endif

	switch(Config){
		case Task_Set_Default:TaskHandle -> Config = Task_State_RB;break;//��������Ϊ����̬
		default: osTaskSet(TaskHandle,Config);break;
	}
	

	#if (osPost_Config > 0)
	TaskHandle	-> Arg1 = NULL;//����������Ϣ��Ϊ��
	#endif

	#if (osClockTimePeriod > osClockTimePeriodStandard)//��ʱ�����ڴ���1000ʱ������ת��
	Wheel = Wheel / (osClockTimePeriod / osClockTimePeriodStandard);
	#endif

    if(Wheel > 0){//�������ʱ����Ƭ�����㣬��ֱ�Ӵ��䵱ǰʱ����Ƭֵ
        TaskHandle -> Wheel = Wheel;//д��ʱ����Ƭ
    }
    else{//������ʹ��Ĭ��ֵ
        TaskHandle -> Wheel = TaskTimeWheelDefault;//д��Ĭ��ֵʱ����Ƭ
    }



	if(osTaskGetTaskHandleListHead() == NULL){
		osTaskGetTaskHandleListHead() = TaskHandle;
		TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
	}else{
		TaskHandleList_Buf1  = (_TaskHandle*)osTaskGetTaskHandleListHead();
		if(TaskHandle -> Level < TaskHandleList_Buf1 -> Level){
			TaskHandle -> NextTaskHandle = (_NextTaskHandle*)TaskHandleList_Buf1;
			while(TaskHandleList_Buf1 -> NextTaskHandle != (_NextTaskHandle*)osTaskGetTaskHandleListHead()){
				TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
			}
			TaskHandleList_Buf1 -> NextTaskHandle = (_NextTaskHandle*)TaskHandle;
			osTaskGetTaskHandleListHead() = TaskHandle;
		}else{
			for(;;){
				if(TaskHandle -> Level < TaskHandleList_Buf1 -> Level){
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


#if (osCriticalToProtect_Config > 0)//�������ٽ籣��
	osProtect_DISABLE();//�˳�����
#endif
	return (TaskHandle);//����

osTaskLoginStatic_Error:
#if (osCriticalToProtect_Config > 0)//�������ٽ籣��
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

	if(osTaskLogoutStatic(TaskHandle) != OK){
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLogout","������ע��ʧ��\n");
		#endif
		return (Error);//�������󣬷��ش���
	}
	
	if(osMemoryFree(TaskHandle) != OK){
		#if (osTaskLog_Config > 0)
		osLogE("osTaskLogout","�����ڴ��ͷ�ʧ��\n");
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
OsErrorValue  osTaskLogoutStatic(_TaskHandle* TaskHandle)
{
	_TaskHandle* TaskHandleList_Buf1 = osTaskGetTaskHandleListHead();
	_TaskHandle* TaskHandleList_Buf2;
    #if (osCriticalToProtect_Config > 0)//�������ٽ籣��
	osProtect_ENABLE();//���뱣��
    #endif
	TaskHandleList_Buf1 = osTaskGetTaskHandleListHead();
	if(TaskHandle == osTaskGetTaskHandleListHead()){
		while(TaskHandleList_Buf1 -> NextTaskHandle != (_NextTaskHandle*)osTaskGetTaskHandleListHead()){
			TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
		}
		osTaskGetTaskHandleListHead() = (_TaskHandle*)osTaskGetTaskHandleListHead() -> NextTaskHandle;
		TaskHandleList_Buf1 -> NextTaskHandle = (_NextTaskHandle*)osTaskGetTaskHandleListHead();
		goto osTaskLogoutStatic_OK;
	}else{
		do{
			TaskHandleList_Buf2 = TaskHandleList_Buf1;
			TaskHandleList_Buf1 = (_TaskHandle*)TaskHandleList_Buf1 -> NextTaskHandle;
			if(TaskHandleList_Buf1 == TaskHandle){
				TaskHandleList_Buf2 -> NextTaskHandle = TaskHandleList_Buf1 -> NextTaskHandle;
				goto osTaskLogoutStatic_OK;
			}
		}while(TaskHandleList_Buf1 != osTaskGetTaskHandleListHead());
		goto osTaskLogoutStatic_Error;
	}
	
osTaskLogoutStatic_OK:
  #if (osCriticalToProtect_Config > 0)//�������ٽ籣��
	osProtect_DISABLE();//�˳�����
  #endif
	return (OK);//���쳣������OK
osTaskLogoutStatic_Error:
  #if (osCriticalToProtect_Config > 0)//�������ٽ籣��
	osProtect_DISABLE();//�˳�����
  #endif
	return (Error);//���쳣������OK

}

/*
 *
 * @��������: osTaskDelayMs
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
		osTaskGetRunTaskHandle() -> Delay = ms;
		osTaskSwitchConfig(OSCoreTaskHandle,osTaskGetRunTaskHandle(),Task_State_Up_DT);
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
    //osTASK_HANGUP(&osTaskGetRunTaskHandle() -> RealSP);//ͨ����ǰ���������ջָ��,����ǰ������
    for(;;){//������һ������
		osTaskGetNextTaskHandle() = (_TaskHandle*)osTaskGetNextTaskHandle() -> NextTaskHandle;	
		switch(osTaskGetNextTaskHandle() -> Config){//����״̬�����������������switch���
				case Task_State_RB:
									osTaskGetNextTaskHandle() -> RealSP = osTaskGetNextTaskHandle() -> Length;
									osTaskGetNextTaskHandle() -> Config = Task_State_RE;//����������״̬��Ϊ��Ƭ����(����̬)
									osLinkTaskStackInit(osTaskGetNextTaskHandle() -> Arg,(void* )osTaskGetNextTaskHandle() -> Addr,(void* )osTaskExit,&osTaskGetNextTaskHandle() -> RealSP);//��������
				case Task_State_RE:	  //����̬
									OsTimeGetTaskTimeWheel() = osTaskGetNextTaskHandle() -> Wheel;//����ǰ�����ʱ����Ƭд�뵽ʱ���¼��
									OsTaskIdle = 0;
									ISR_Touch();
									return;//�˳�����
				case Task_Set_OSCore:
									if(++OsTaskIdle == 1000){

										OsTimePeriod = 10;
										osClock_Init(OsTimePeriod);
										//("sleep\n");
									}
									break;

				default:break;//����֮��!
			}
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
									TaskHandle -> Config = Task_State_RE;//��Ϊ����̬
									return (OK);//����OK

			case Task_Set_Reboot://��������									
									TaskHandle -> Config = Task_State_RB;//
									return (OK);//����OK
			case Task_Set_Start://������������
									osTaskSwitchConfig(TaskHandle,TaskHandle,Task_State_RE);
									return (OK);//����OK
			case Task_Set_Up://��������
								return (OK);

									
		}
	}else{//����
		switch(Pv){
			case Task_Set_Pause://��ͣ����
									osTaskSwitchConfig(OSCoreTaskHandle,osTaskGetRunTaskHandle(),Task_State_DI);
									return (OK);//����OK

			case Task_Set_Cont://��������
									return (OK);//����OK

			case Task_Set_Reboot://��������
									osTaskSwitchConfig(OSCoreTaskHandle,osTaskGetRunTaskHandle(),Task_State_RB);//���������л�
									return (OK);//����OK
			case Task_Set_Start://������������
									return (OK);//����OK
			case Task_Set_Up://��������							
									osTaskSwitchConfig(OSCoreTaskHandle,osTaskGetRunTaskHandle(),Task_State_RE);//���������л�
									return (OK);

									
		}
	}
	#if (osTaskLog_Config > 0)
	osLogE("osTaskSet","��������ʱ������ȷ��������\n");
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
	for(;;){
		osTaskSwitchConfig(OSCoreTaskHandle,osTaskGetRunTaskHandle(),Task_State_ST);//���������л�
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
		osTaskSwitchConfig(OSCoreTaskHandle,osTaskGetRunTaskHandle(),Task_State_RB);//���������л�
		return (OK);//����OK

	}else{
		TaskHandle -> Addr = NewTA;
		TaskHandle -> Config = Task_State_RB;//
		return (OK);//����OK
	}

}

#if (SIRQ_Config > 0)
/*
 *
 * @��������: osTaskSIRQInit
 *
 * @��������: ���жϳ�ʼ��
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osTaskSIRQInit(void)
{
	TaskHandle_SIRQ = osTaskLogin(
							osTaskSIRQ,
							SIRQStackSize_Config,
							SIRQPriorityLevel_Config,
							SIRQTimeWheel_Config,
							SIRQPass_Config,
							SIRQName_Config,
							SIRQSet_Config); 
	if(TaskHandle_SIRQ == NULL){
		#if (osTaskLog_Config > 0)
		osLogE("osTaskSIRQInit","SIRQ ���񴴽�ʧ��\n");
		#endif
		return (Error);//����Error
	}
	return (OK);
}
/*
 *
 * @��������: osTaskSIRQ_Enable
 *
 * @��������: ���ж�ʹ��
 *
 * @�������:	SIRQList_Addr	���жϱ��ͷ
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void osTaskSIRQ_Enable(_SIRQList* SIRQList_Addr)
{
	TaskHandle_SIRQ -> Arg = (_TaskArg*)SIRQList_Addr;
	osTaskSwitchConfig(TaskHandle_SIRQ,TaskHandle_SIRQ,Task_State_RE);
}
/*
 *
 * @��������: osTaskSIRQLogin
 *
 * @��������: ���ж�ע��
 *
 * @�������:	SIRQList_Addr	���жϱ��ͷ
 * @�������:	Addr			���ж���Ӧ������ַ	
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

	for(;;){
		//osTaskGetRunTaskHandle() -> Config = Task_State_Up_SI;//��������(����̬) 
		osTaskSwitchConfig(OSCoreTaskHandle,osTaskGetRunTaskHandle(),Task_State_Up_SI);
		SIRQList_Addr = (_SIRQList*)osTaskGetRunTaskHandle() -> Arg;
		for(SIRQList_Count = 1; SIRQList_Count <= *SIRQList_Addr; SIRQList_Count++){
			osLinkJump((uint32_t*)SIRQList_Addr[SIRQList_Count]);
		}
	}
	
}

#endif




