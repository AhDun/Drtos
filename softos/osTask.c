/*
                                                  FILE-START
*/
/*

 *@�ļ�����: osTask.c

 *@�ļ�����: ϵͳ"����"�ļ�

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@ע    ��: 

*/

/*
                                                  <�����ļ���>
*/
#include "osConfig.h"
#include "osTask.h"
/*
                                                  <���ݳ�ʼ��>
*/
_TaskDispatchStateTable TST;//�������״̬��
_TaskHandle*	RunTaskHandle;//��ǰ���������������Ϣ��
_TaskList TaskList[TaskListLength];//������ѯ��

/*
                                                  <������>
*/
/*

 *@��������: osTaskInit

 *@�����汾: 1.0.0

 *@��������: ����ϵͳ��ʼ��

 *@�������: ��

 *@�� �� ֵ: -1:�������� / 0: ��ʼ���ɹ�

 *@ע    ��: ��

*/
osErrorValue osTaskInit(void)
{
    uint32_t _tr0;
    /***********************************������ѯ���ʼ��*********************************/
    TST.TLMA = NULL;
    for(_tr0 = 0;_tr0 < TaskListLength;_tr0++){
        TaskList[_tr0].TaskHandle = (_TaskHandle*)TaskList_NULLValue;
    }

	TST.TISRF = 0;
	TST.TSS = TaskSwitch_Ready;
    /***********************************ϵͳ�����ʼ��**********************************/
	if(osTaskLogin("Main",(void*)0,Default_Stack_Size,TaskTimeWheelDefault,0,(void*)0,Task_Set_Default ) == NULL){

		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("Main ���񴴽�ʧ��\n");
		#endif
		return (Error);//����Error
	}

	TST. TDN = NULL;    
	RunTaskHandle = TaskList[TST. TDN].TaskHandle;//���������е�������Ϣ���ָ�봫�͸��������������
	TST. TDN = TST. TDN + 1;//����ָ�������һλ     
	osTime.TTWM = RunTaskHandle -> TaskTimeWheel;//����ǰ�����ʱ����Ƭд�뵽ʱ���¼��
	osTASK_START(&RunTaskHandle -> RealSP);//������һ������
    return (OK);//����OK
}		
/*

 *@��������: osTaskLogin

 *@�����汾: 1.0.0

 *@��������: ���񴴽����Զ������ڴ棩

 *@�������:  	1.�������� 
				2.�����ַ
				3.����ջ����		
				4.����ʱ����Ƭ
				5.�������ȼ�
				6.���񴫲�
				7.��������

 *@�� �� ֵ: -1:�������� / 0: �����ɹ�

 *@ע    ��:

*/	


_TaskHandle* osTaskLogin(
	_TaskName *TN,//��������
	void*  TA,//�����ַ	
	_TaskStackSize  TSS,//����ջ����
	_TaskTimeWheel  TTW,//����ʱ����Ƭ
	_TaskPriorityLevel  TPL,//�������ȼ�
    void*  TPP, //���񴫲�
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

 *@��������: 

 *@�����汾: 1.0.0

 *@��������: ���񴴽�

 *@�������: 	1.�����
				2.��������
				3.�����ַ
				5.����ջ����		
				6.����ʱ����Ƭ
				7.�������ȼ�
				8.���񴫲�
				9.��������
				

 *@�� �� ֵ: -1:�������� / 0: �����ɹ�

 *@ע    ��: ����:

*/
_TaskHandle* osTaskLogin_Static(
 
	_TaskHandle* TaskHandle,//�����
	_TaskName *TN,//��������
	void*  TA,//�����ַ
	_TaskStackSize  TSS,//����ջ����
	_TaskTimeWheel  TTW,//����ʱ����Ƭ
	_TaskPriorityLevel  TPL,//�������ȼ�
    void*  TPP, //���񴫲�
    _TaskConfig  TC//��������
)
{
	int32_t _tr0,_tr1;
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
    TaskHandle -> ID = (_TaskID)TST.TLMA;//д������ID
	TaskHandle -> Name = TN;//д����������
	TaskHandle -> Addr = TA;////д�������ַ
	TSS -= 1;
    TaskHandle -> RealSPb = TaskHandle -> RealSP = (uint32_t)((uint32_t)StackAddr + TSS);//д������ʵʱջָ��
    TaskHandle -> ParameterPass = TPP;//д�����񴫲�
	TaskHandle -> PriorityLevel = TPL;//д���������ȼ�
	TaskHandle -> PriorityLevelb = TPL;//д�����������ȼ�

	if(TC == Task_Set_Default){//�������ѡ����"��������"ѡ�����Ч
        TaskHandle -> Config = Task_State_RB;//��������Ϊ����̬
    }
    else{
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


	if(TST.TLMA > (TaskListLength - 1)){//���������ѯ��ָ���Ƿ����������ѯ��ĳ��ȣ�������������
#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
		osProtect_DISABLE();//�˳�����
#endif
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("ע������ʱ,��������������� %s\n",TN);
		#endif
		return (NULL);//���ش���
	}
	for(_tr0 = 0;_tr0 < TST.TLMA;_tr0++){//��������ѯ������������
		if(TaskList[_tr0].TaskHandle -> PriorityLevel > TPL || TaskList[_tr0].TaskHandle == (_TaskHandle*)TaskList_NULLValue){//�����ǰ�������ȼ����ڱ���������������ȼ������ߣ���ǰָ��ָ��ı�Ϊ�գ������
			break;//�˳�ѭ��
		}
	}
	for(_tr1 = TST.TLMA - 1;_tr1 >= 0; _tr1--){//��������ѯ����з������
		if(TaskList[_tr1].TaskHandle !=  (_TaskHandle*)TaskList_NULLValue){//�����ǰָ��ָ��ı�Ϊ�˿գ������
			break;//�˳�ѭ��
		}
	}
	_tr1++;//���䷴�������������м�һ
	for(;_tr1 >= _tr0;_tr1--){//���������ݽ��ж�Ӧ����λ
		TaskList[_tr1].TaskHandle = TaskList[_tr1 - 1].TaskHandle;//����
	}
	TaskList[_tr0].TaskHandle = TaskHandle;//����ǰ����д�����

	TST.TLMA++;//��ָ���һ 

	for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//���¼�������ID
		TaskList[_tr0].TaskHandle -> ID = _tr0;
	}


#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_DISABLE();//�˳�����
#endif
	return (TaskHandle);//����
}
	

#if (osTaskAutoStack_Enable > 0)//��������ջ�Զ�����
/*

 *@��������: osTaskLogout

 *@�����汾: 1.0.0

 *@��������: ����ע��

 *@�������: _TaskName *TN //��������	

 *@�� �� ֵ: -1:ע������0: ע���ɹ�

 *@ע    ��: ����������ջ�Զ����������µ��õ�����ע������

*/
//osErrorValue osTaskLogout(_TaskName *TN)
/*

 *@��������: osTaskLogout_Write

 *@�����汾: 1.0.0

 *@��������: ����д��ע��д��

 *@�������: _TaskHandle* TaskHandle //������Ϣ��ָ��

 *@�� �� ֵ: -1:ע������0: ע���ɹ�

 *@ע    ��: ����������ջ�Զ����������µ������ڲ�

*/
osErrorValue osTaskLogout_Write(_TaskHandle* TaskHandle)
#else 
/*

 *@��������: osTaskLogout

 *@�����汾: 1.0.0

 *@��������: ����д��ע��д��

 *@�������: _TaskHandle* TaskHandle //������Ϣ��ָ��

 *@�� �� ֵ: -1:ע������0: ע���ɹ�

 *@ע    ��: �ڲ���������ջ�Զ����������µ��õ�����ע������

*/
osErrorValue	osTaskLogout(_TaskHandle* TaskHandle)
#endif
{
	int32_t _tr0,_tr1;//�������
    #if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_ENABLE();//���뱣��
    #endif
	//TaskHandle -> Config &= TIT_Task_State_TC_RST;//��������״̬λ
	for(_tr0 = 0;_tr0 < TaskListLength;_tr0++){//����������ѯ���ȣ����б���
		if(TaskList[_tr0].TaskHandle == TaskHandle){//�����ǰ����ID��������ѯ��ǰ��ָ�������ID��ͬ���ͽ���
			break;//�˳���ǰѭ��
		}
	}
	if(_tr0 == TaskListLength || TST.TLMA == 0){//���_tr0��ֵ��������ѯ���ȣ��������������Ϊ��ʱ���ͽ���
		#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
		osProtect_DISABLE();//�˳�����
		#endif
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("�ͷ�����: δ֪\n");
		#endif
		return (Error);//�������󣬷��ش���
	}
	for(_tr1 = TST.TLMA;_tr1 >= 0; _tr1--){//������������������б���
		if(TaskList[_tr1].TaskHandle !=  (_TaskHandle*)TaskList_NULLValue){//�����ǰ������ָ��Ϊ�գ��ͽ���
			break;//�˳���ǰѭ��
		}
	}
	/*
	���ʱ��
	_tr0 = ָ���Ӧ������ID���±�ֵ
	_tr1 = ������ѯ���β��
	*/
	for(;_tr0 + 1 != (_tr1 + 1);_tr0++){//����ָ���Ӧ������ID���±�ֵ��������ѯ���β�ˣ����б���
		//ָ���Ӧ������ID���±�ֵ����һ�����ݿ�ʼ
		TaskList[_tr0].TaskHandle = TaskList[_tr0 + 1].TaskHandle ;//��������ǰ��
		//ָ���Ӧ������ID���±�ָ���������ֵ�ᱻ��һ��������ֵ���ǵ�
	}
	TaskList[_tr1].TaskHandle = (_TaskHandle*)TaskList_NULLValue ;//��������ѯ���β������
	TST.TLMA--;//�����������һ
	
	for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//���¼�������ID
		TaskList[_tr0].TaskHandle -> ID = _tr0;
	}

  #if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_DISABLE();//�˳�����
  #endif
	return (OK);//���쳣������OK
}

/*

 *@��������: osTaskNameToTable

 *@�����汾: 1.0.0

 *@��������: �����������Ʋ�ѯ���

 *@�������: _TaskName *TN	- ��������

 *@�� �� ֵ: 0:��ѯ����x: ������

 *@ע    ��: ��

*/
_TaskHandle* osTaskNameToTable(_TaskName *TN)
{
	uint32_t _var0;
	for(_var0 = 0;_var0 < TST.TLMA;_var0++){//������������������б���
		if(StrComp((int8_t*)TN,(int8_t*)TaskList[_var0].TaskHandle -> Name)){//
			return (TaskList[_var0].TaskHandle);//��������ID
		}
	}
	#if (osTaskDebug_Enable > 0)
	osTaskErrorDebug("��ѯ����ʱû���ҵ���Ӧ�������� %s\n",TN);
	#endif
	return (NULL);//û�ж�Ӧ������ID,���ش���
}
/*

 *@��������: osTaskTime_Choke_ms

 *@�����汾: 1.0.0

 *@��������: ���뼶������ʱ

 *@�������: ms(��ʱʱ������λ����)	

 *@�� �� ֵ: 0: ʱ�������ɹ�

 *@ע    ��: ��

*/	
osErrorValue osTaskDelayMs(uint32_t ms)
{
    if(ms > 0){//���ر�
		#if (osClockTimePeriod > osClockTimePeriodStandard)
		ms = ms /(osClockTimePeriod / osClockTimePeriodStandard);	
		#endif
		while(TST.TSS != TaskSwitch_Ready);//����ѯCPU�Ƿ��Ѿ�����Ϊ����̬
		//��������ˣ��ͻ᷵����ֵ����whileѭ����ֱ��δ������
		//RunTaskHandle -> Config &= TIT_Task_State_TC_RST;//����������������״̬λ
		RunTaskHandle -> Config = Task_State_Up_DT;//���������������״̬��Ϊ��ʱ����(�ȴ�̬)
		RunTaskHandle -> TimeFlag = ms;
		osTaskSwitch_Enable();
    }
	return (OK);
}
/*

 *@��������: osTaskDelayUs

 *@�����汾: 1.0.0

 *@��������: ΢�뼶������ʱ

 *@�������: ms(��ʱʱ������λ΢��)	

 *@�� �� ֵ: 0: ʱ�������ɹ�

 *@ע    ��: ��

*/	
osErrorValue osTaskDelayUs(uint32_t us)
{
	osTime.TTWM = osTime.TTWM + 1;
	osTaskTimeUs(
);
	return (OK);
}


/*

 *@��������: osTaskSwitch_State

 *@�����汾: 1.0.0

 *@��������: ��ѯ������л�̬

 *@�������: ��	

 *@�� �� ֵ: -1:��������0: �����ɹ�

 *@ע    ��: ��

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

 *@��������: osTaskNext

 *@�����汾: 1.0.0

 *@��������: �����л�

 *@�������: ��	

 *@�� �� ֵ: -1:��������0: �����ɹ�

 *@ע    ��: ��

*/	
void osTaskNext(void)
{  
    TST.TSS = TaskSwitch_Run;
    //osTASK_HANGUP(&RunTaskHandle -> RealSP);//ͨ����ǰ���������ջָ��,����ǰ������
    while(1){//������һ������
		for(;TST. TDN < TST.TLMA;TST. TDN++){//���б���
			switch(TaskList[TST. TDN].TaskHandle -> Config){//����״̬�����������������switch���
					case Task_State_RB:
										TaskList[TST. TDN].TaskHandle -> RealSP = TaskList[TST. TDN].TaskHandle -> RealSPb;
										osTASK_Stack_Init(TaskList[TST. TDN].TaskHandle -> ParameterPass,(void* )TaskList[TST. TDN].TaskHandle -> Addr,(void* )osTaskExit,&TaskList[TST. TDN].TaskHandle -> RealSP);//��������
					case Task_State_Up_IN://�����������������(����̬)
					case Task_State_Up_TD://�����������Ƭ����(����̬)	
					case Task_State_RE:	  //������������
										RunTaskHandle = TaskList[TST. TDN].TaskHandle;//���������е�������Ϣ���ָ�봫�͸��������������
										TST. TDN = TST. TDN + 1;//����ָ�������һλ  
										osTime.TTWM = RunTaskHandle -> TaskTimeWheel;//����ǰ�����ʱ����Ƭд�뵽ʱ���¼��
										TST.TSS = TaskSwitch_Ready;//������״̬��Ϊ"δ����"
										#if (osPerformanceStatistics_Enable > 0)
										PS.TSC += 1;
										#endif
										return;//�˳�����

					default:break;//����֮��!
				}
		}
		TST.TDN = NULL;//���������ȼ���
    }
}
/*

 *@��������: osTaskSet

 *@�����汾: 1.0.0

 *@��������: ��������

 *@�������: ��	

 *@�� �� ֵ: -1:��������0: �����ɹ�

 *@ע    ��: ��

*/
osErrorValue osTaskSet(_TaskHandle* TaskHandle,uint8_t Pv)
{

	if(TaskHandle != 0){//������
		switch(Pv){
			case Task_Set_Pause://��ͣ����
									//TaskHandle -> Config &= TIT_Task_State_TC_RST;//��λ״̬λ
									TaskHandle -> Config = Task_State_DI;//��Ϊ����̬
									return (OK);//����OK

			case Task_Set_Cont://��������
									//TaskHandle -> Config &= TIT_Task_State_TC_RST;//��λ״̬λ
									TaskHandle -> Config = Task_State_Up_IN;//��Ϊ����̬
									return (OK);//����OK

			case Task_Set_Reboot://��������
									//TaskHandle -> Config &= TIT_Task_State_TC_RST;//��λ״̬λ									
									TaskHandle -> Config = Task_State_RB;//
									return (OK);//����OK
			case Task_Set_Start://������������
									while(TST.TSS != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
									//TaskHandle -> Config &= TIT_Task_State_TC_RST;//��λ״̬λ
									TaskHandle -> Config = Task_State_Up_IN;//��������(����̬)
									TST. TDN = TaskHandle -> ID;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
									osTaskSwitch_Enable();
									return (OK);//����OK
			case Task_Set_Up://��������
								return (OK);

									
		}
	}else{//����
		switch(Pv){
			case Task_Set_Pause://��ͣ����
									//TaskHandle -> Config &= TIT_Task_State_TC_RST;//��λ״̬λ
									while(TST.TSS != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
									RunTaskHandle -> Config = Task_State_DI;//��Ϊ����̬
									osTaskSwitch_Enable();//���������л�
									return (OK);//����OK

			case Task_Set_Cont://��������
									return (OK);//����OK

			case Task_Set_Reboot://��������
									//TaskHandle -> Config &= TIT_Task_State_TC_RST;//��λ״̬λ
									while(TST.TSS != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
									RunTaskHandle -> Config = Task_State_RB;//
									osTaskSwitch_Enable();//���������л�
									return (OK);//����OK
			case Task_Set_Start://������������
									return (OK);//����OK
			case Task_Set_Up://��������
								while(TST.TSS != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
								//RunTaskHandle -> Config &= TIT_Task_State_TC_RST;
								RunTaskHandle -> Config = Task_State_Up_IN;
								osTaskSwitch_Enable();//���������л�
								return (OK);

									
		}
	}
	#if (osTaskDebug_Enable > 0)
	osTaskErrorDebug("��������ʱ������ȷ�������� %s\n" ,RunTaskHandle -> Name);
	#endif
	return (Error);
}
/*

 *@��������: osTaskEnd

 *@�����汾: 1.0.0

 *@��������: �������

 *@�������: ��	

 *@�� �� ֵ: -1:��������0: �����ɹ�

 *@ע    ��: ��

*/
osErrorValue osTaskExit(void)
{
	//RunTaskHandle -> Config &= TIT_Task_State_TC_RST;//��λ״̬λ
	while(true){
		RunTaskHandle -> Config = Task_State_ST;//��Ϊ��ֹ̬
		osTaskSwitch_Enable();//���������л�
	}
}
/*

 *@��������: osTaskAddrReplace

 *@�����汾: 1.0.0

 *@��������: �����ַ�滻

 *@�������: ��	

 *@�� �� ֵ: -1:��������0: �����ɹ�

 *@ע    ��: ��

*/
osErrorValue osTaskAddrReplace(_TaskHandle* TaskHandle,void* NewTA)
{
	if(TaskHandle == 0){
		RunTaskHandle -> Addr = NewTA;
		while(TST.TSS != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
		RunTaskHandle -> Config = Task_State_RB;//
		osTaskSwitch_Enable();//���������л�
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
	osTaskEnterISR();
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
		osTaskErrorDebug("����ջ�ܴ�С:%d�ֽ�\n����ջʣ��:%d�ֽ�\n",(1),psp - ((uint32_t)RunTaskHandle -> RealSPb - (1)));
		osTaskErrorDebug("�����쳣��:%X\n",pc);
		osTaskErrorDebug("�ڴ�����:%d�ֽ�\n�ڴ�����:%d�ֽ�",osMemoryGetAllValue(),osMemoryGetFreeValue());
	}
	#endif
	#if (osTaskErrorSet == 1)
	osTaskSet(NULL,Task_Set_Reboot);
	#elif(osTaskErrorSet == 0)
	osTaskSet(NULL,Task_Set_Pause);
	#endif
	osTaskExitISR();
	return (OK);
}
/*

 *@��������: osTaskSpeedTest

 *@�����汾: 1.0.0

 *@��������: �����л��ٶȲ���

 *@�������: ��	

 *@�� �� ֵ: -1:��������0: �����ɹ�

 *@ע    ��: ��

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
	uint8_t _tr0;
	for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//��ÿһ��������б���
		print("����<%s>��ʹ����Ϊ:ռ��ʱ��:%dms | �������ȼ�:%d | ����״̬:",TaskList[_tr0].TaskHandle -> Name,TaskList[_tr0].TaskHandle -> OccupyRatio,TaskList[_tr0].TaskHandle -> PriorityLevel);
		if(TaskList[_tr0].TaskHandle != RunTaskHandle || TST.TSS != TaskSwitch_Ready){
			switch(TaskList[_tr0].TaskHandle -> Config){
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
	}
	
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
                                                  FILE-END
*/

