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
uint32_t NULL_Value = 0;
TaskDispatchStateTable TST;//�������״̬��
TaskInfoTable*	RunTask_TIT;//��ǰ���������������Ϣ��
TaskList TL[TaskListLength];//������ѯ��

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
        TL[_tr0].TITA = (TaskInfoTable*)TaskList_NULLValue;
    }

	TST.TISRF = 0;
	TST.TSS = TaskSwitch_Ready;
    /***********************************ϵͳ�����ʼ��**********************************/
#if (osTaskAutoStack_Enable > 0)//��������ջ�Զ�����
	if(osTaskLogin("Main",(void*)0,Default_Stack_Size,TaskTimeWheelDefault,0,(void*)0,Task_Set_Default ) == NULL){

		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("Main ���񴴽�ʧ��\n");
		#endif
		return (Error);//����Error
	}
#else
	if(osTaskLogin( 
	&Main_TaskInfoTable, 	//�����
	"Main",					//��������
	(void*)0,				//�����ַ
	Main_Stack,				//����ջ��ַ
	Default_Stack_Size,		//����ջ����
	TaskTimeWheelDefault,	//����ʱ����Ƭ
	0,						//�������ȼ�
    (void*)0,				//���񴫲�   
    Task_Set_Default    	//��������
	) == Error){
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("Main ���񴴽�ʧ��\n");
		#endif
		return (Error);//����Error
	}
#endif

	TST. TDN = NULL;    
	RunTask_TIT = TL[TST. TDN].TITA;//���������е�������Ϣ���ָ�봫�͸��������������
	TST. TDN = TST. TDN + 1;//����ָ�������һλ     
	osTime.TTWM = RunTask_TIT -> TTW;//����ǰ�����ʱ����Ƭд�뵽ʱ���¼��
	osTASK_START(&RunTask_TIT -> TRS);//������һ������
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


#if (osTaskAutoStack_Enable > 0)//��������ջ�Զ�����
TaskInfoTable* osTaskLogin(
	_TaskName *TN,//��������
	void*  TA,//�����ַ	
	_TaskStackSize  TSS,//����ջ����
	_TaskTimeWheel  TTW,//����ʱ����Ƭ
	_TaskPriorityLevel  TPL,//�������ȼ�
    void*  TPP, //���񴫲�
    _TaskConfig  TC//��������
)
{
	void* TIT;
	void* TH;
	TaskInfoTable* TaskInfoTable_Buf;

	TIT = osMemoryMalloc(sizeof(TaskInfoTable));//Ϊ���������ڴ�
	if(TIT == NULL){//���Ϊ�գ���˵���ڴ����ʧ��
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("ע������ʱ,���������ڴ�ʧ�� %s\n",TN);
		#endif
		return (NULL);//���ش���
	}
	TH = osMemoryMalloc(TSS);//Ϊ����ջ�����ڴ�
	if(TH == NULL){//���Ϊ�գ���˵���ڴ����ʧ��
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("ע������ʱ,����ջ�����ڴ�ʧ�� %s\n",TN);
		#endif
		return (NULL);//���ش���
	}
	TaskInfoTable_Buf = osTaskRegister_Write(TIT,TN,TA,TH,TSS,TTW,TPL,TPP, TC);//���ʱ���ڴ������ɣ��ͽ��н�����ͨע��
	if(TaskInfoTable_Buf == NULL){//���Ϊ����ֵ����˵���ڴ����ʧ��
		#if (osTaskDebug_Enable > 0)
		osTaskErrorDebug("ע������ʱ,����ע��ʧ�� %s\n",TN);
		#endif
		return (NULL);//���ش���
	}
	return (TaskInfoTable_Buf);//
}
/*

 *@��������: osTaskRegister_Write�������Զ�ջ����ʱ�� / osTaskLogin��û�������Զ�ջ����ʱ��

 *@�����汾: 1.0.0

 *@��������: ���񴴽�

 *@�������: 	1.�����
				2.��������
				3.�����ַ
				4.������
				5.����ջ����		
				6.����ʱ����Ƭ
				7.�������ȼ�
				8.���񴫲�
				9.��������
				

 *@�� �� ֵ: -1:�������� / 0: �����ɹ�

 *@ע    ��: ����:

*/
TaskInfoTable* osTaskRegister_Write(
#else 
TaskInfoTable* osTaskLogin(
#endif 
	TaskInfoTable* TIT,//�����
	_TaskName *TN,//��������
	void*  TA,//�����ַ
	_TaskHandle* TH,//������	
	_TaskStackSize  TSS,//����ջ����
	_TaskTimeWheel  TTW,//����ʱ����Ƭ
	_TaskPriorityLevel  TPL,//�������ȼ�
    void*  TPP, //���񴫲�
    _TaskConfig  TC//��������
)
{
	int32_t _tr0,_tr1;
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
    TIT -> TI = (_TaskID)TST.TLMA;//д������ID
	TIT -> TN = TN;//д����������
	TIT -> TA = TA;////д�������ַ
	TIT -> TH = (uint32_t*)(((uint32_t)TH)+ (TSS - 1));//д��������
    TIT -> TRS = (uint32_t)(((uint32_t)TH)+ (TSS - 1));//д������ʵʱջָ��
	TIT -> TSS = TSS;//д������ջ����
    TIT -> TPP = TPP;//д�����񴫲�

	TIT	-> PF = (uint32_t*)NULL_Value;//����������Ϣ��Ϊ��

	#if (osClockTimePeriod > osClockTimePeriodStandard)//��ʱ�����ڴ���1000ʱ������ת��
	TTW = TTW / (osClockTimePeriod / osClockTimePeriodStandard);
	#endif

    if(TTW > 0){//�������ʱ����Ƭ�����㣬��ֱ�Ӵ��䵱ǰʱ����Ƭֵ
        TIT -> TTW = TTW;//д��ʱ����Ƭ
    }
    else{//������ʹ��Ĭ��ֵ
        TIT -> TTW = TaskTimeWheelDefault;//д��Ĭ��ֵʱ����Ƭ
    }
	TIT -> TPL = TPL;//д���������ȼ�
	TIT -> TPLb = TPL;//д�����������ȼ�

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
		if(TL[_tr0].TITA->TPL > TPL || TL[_tr0].TITA == (TaskInfoTable*)TaskList_NULLValue){//�����ǰ�������ȼ����ڱ���������������ȼ������ߣ���ǰָ��ָ��ı�Ϊ�գ������
			break;//�˳�ѭ��
		}
	}
	for(_tr1 = TST.TLMA - 1;_tr1 >= 0; _tr1--){//��������ѯ����з������
		if(TL[_tr1].TITA !=  (TaskInfoTable*)TaskList_NULLValue){//�����ǰָ��ָ��ı�Ϊ�˿գ������
			break;//�˳�ѭ��
		}
	}
	_tr1++;//���䷴�������������м�һ
	for(;_tr1 >= _tr0;_tr1--){//���������ݽ��ж�Ӧ����λ
		TL[_tr1].TITA = TL[_tr1 - 1].TITA;//����
	}
	TL[_tr0].TITA = TIT;//����ǰ����д�����

	TST.TLMA++;//��ָ���һ 

	for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//���¼�������ID
		TL[_tr0].TITA -> TI = _tr0;
	}

	if(TC == Task_Set_Default){//�������ѡ����"��������"ѡ�����Ч
        //TIT -> TC &= TIT_Task_State_TC_RST;//��������ȷ״̬λ
        TIT -> TC = Task_State_RB;//��������Ϊ����̬
    }
    else{
        //TIT -> TC &= TIT_Task_State_TC_RST;//��������ȷ״̬λ
        osTaskSet(TIT,TC);
    }
    //osTASK_Stack_Init(TIT ->TPP,(void* )TIT -> TA,(void* )osTaskExit,&TIT -> TRS);//��������
#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_DISABLE();//�˳�����
#endif
	return (TIT);//����
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

 *@�������: TaskInfoTable* TIT //������Ϣ��ָ��

 *@�� �� ֵ: -1:ע������0: ע���ɹ�

 *@ע    ��: ����������ջ�Զ����������µ������ڲ�

*/
osErrorValue osTaskLogout_Write(TaskInfoTable* TIT)
#else 
/*

 *@��������: osTaskLogout

 *@�����汾: 1.0.0

 *@��������: ����д��ע��д��

 *@�������: TaskInfoTable* TIT //������Ϣ��ָ��

 *@�� �� ֵ: -1:ע������0: ע���ɹ�

 *@ע    ��: �ڲ���������ջ�Զ����������µ��õ�����ע������

*/
osErrorValue	osTaskLogout(TaskInfoTable* TIT)
#endif
{
	int32_t _tr0,_tr1;//�������
    #if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_ENABLE();//���뱣��
    #endif
	//TIT -> TC &= TIT_Task_State_TC_RST;//��������״̬λ
	for(_tr0 = 0;_tr0 < TaskListLength;_tr0++){//����������ѯ���ȣ����б���
		if(TL[_tr0].TITA == TIT){//�����ǰ����ID��������ѯ��ǰ��ָ�������ID��ͬ���ͽ���
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
		if(TL[_tr1].TITA !=  (TaskInfoTable*)TaskList_NULLValue){//�����ǰ������ָ��Ϊ�գ��ͽ���
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
		TL[_tr0].TITA = TL[_tr0 + 1].TITA ;//��������ǰ��
		//ָ���Ӧ������ID���±�ָ���������ֵ�ᱻ��һ��������ֵ���ǵ�
	}
	TL[_tr1].TITA = (TaskInfoTable*)TaskList_NULLValue ;//��������ѯ���β������
	TST.TLMA--;//�����������һ
	
	for(_tr0 = NULL;_tr0 < TST.TLMA;_tr0++){//���¼�������ID
		TL[_tr0].TITA -> TI = _tr0;
	}

  #if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	osProtect_DISABLE();//�˳�����
  #endif
	return (OK);//���쳣������OK
}

/*

 *@��������: osTaskNameToTable

 *@�����汾: 1.0.0

 *@��������: ��������ѯ

 *@�������: _TaskName *TN	- ��������

 *@�� �� ֵ: 0:��ѯ����x: ������

 *@ע    ��: ��

*/
TaskInfoTable* osTaskNameToTable(_TaskName *TN)
{
	uint32_t _var0;
	for(_var0 = 0;_var0 < TST.TLMA;_var0++){//������������������б���
		if(StrComp((int8_t*)TN,(int8_t*)TL[_var0].TITA -> TN)){//
			return (TL[_var0].TITA);//��������ID
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
		//RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//����������������״̬λ
		RunTask_TIT -> TC = Task_State_Up_DT;//���������������״̬��Ϊ��ʱ����(�ȴ�̬)
		RunTask_TIT -> TTF = ms;
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
	osTaskTimeUs(us);
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
    //osTASK_HANGUP(&RunTask_TIT -> TRS);//ͨ����ǰ���������ջָ��,����ǰ������
    while(1){//������һ������
		for(;TST. TDN < TST.TLMA;TST. TDN++){//���б���
			switch(TL[TST. TDN].TITA -> TC){//����״̬�����������������switch���
					case Task_State_RB:
										TL[TST. TDN].TITA -> TRS = (_TaskRealSP)(TL[TST. TDN].TITA -> TH);
										osTASK_Stack_Init(TL[TST. TDN].TITA ->TPP,(void* )TL[TST. TDN].TITA -> TA,(void* )osTaskExit,&TL[TST. TDN].TITA -> TRS);//��������
					case Task_State_Up_IN://�����������������(����̬)
					case Task_State_Up_TD://�����������Ƭ����(����̬)	
					case Task_State_RE:	  //������������
										RunTask_TIT = TL[TST. TDN].TITA;//���������е�������Ϣ���ָ�봫�͸��������������
										TST. TDN = TST. TDN + 1;//����ָ�������һλ  
										osTime.TTWM = RunTask_TIT -> TTW;//����ǰ�����ʱ����Ƭд�뵽ʱ���¼��
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
osErrorValue osTaskSet(TaskInfoTable* TIT,_Task_Set_Pv Pv)
{

	if(TIT != 0){//������
		switch(Pv){
			case Task_Set_Pause://��ͣ����
									//TIT -> TC &= TIT_Task_State_TC_RST;//��λ״̬λ
									TIT -> TC = Task_State_DI;//��Ϊ����̬
									return (OK);//����OK

			case Task_Set_Cont://��������
									//TIT -> TC &= TIT_Task_State_TC_RST;//��λ״̬λ
									TIT -> TC = Task_State_Up_IN;//��Ϊ����̬
									return (OK);//����OK

			case Task_Set_Reboot://��������
									//TIT -> TC &= TIT_Task_State_TC_RST;//��λ״̬λ									
									TIT -> TC = Task_State_RB;//
									return (OK);//����OK
			case Task_Set_Start://������������
									while(TST.TSS != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
									//TIT -> TC &= TIT_Task_State_TC_RST;//��λ״̬λ
									TIT -> TC = Task_State_Up_IN;//��������(����̬)
									TST. TDN = TIT -> TI;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
									osTaskSwitch_Enable();
									return (OK);//����OK
			case Task_Set_Up://��������
								return (OK);

									
		}
	}else{//����
		switch(Pv){
			case Task_Set_Pause://��ͣ����
									//TIT -> TC &= TIT_Task_State_TC_RST;//��λ״̬λ
									while(TST.TSS != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
									RunTask_TIT -> TC = Task_State_DI;//��Ϊ����̬
									osTaskSwitch_Enable();//���������л�
									return (OK);//����OK

			case Task_Set_Cont://��������
									return (OK);//����OK

			case Task_Set_Reboot://��������
									//TIT -> TC &= TIT_Task_State_TC_RST;//��λ״̬λ
									while(TST.TSS != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
									RunTask_TIT -> TC = Task_State_RB;//
									osTaskSwitch_Enable();//���������л�
									return (OK);//����OK
			case Task_Set_Start://������������
									return (OK);//����OK
			case Task_Set_Up://��������
								while(TST.TSS != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
								//RunTask_TIT -> TC &= TIT_Task_State_TC_RST;
								RunTask_TIT -> TC = Task_State_Up_IN;
								osTaskSwitch_Enable();//���������л�
								return (OK);

									
		}
	}
	#if (osTaskDebug_Enable > 0)
	osTaskErrorDebug("��������ʱ������ȷ�������� %s\n" ,RunTask_TIT -> TN);
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
	//RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//��λ״̬λ
	while(true){
		RunTask_TIT -> TC = Task_State_ST;//��Ϊ��ֹ̬
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
osErrorValue osTaskAddrReplace(TaskInfoTable* TIT,void* NewTA)
{
	if(TIT == 0){
		RunTask_TIT -> TA = NewTA;
		while(TST.TSS != TaskSwitch_Ready);//��ѯCPU�Ƿ��Ѿ�����Ϊ����̬
		RunTask_TIT -> TC = Task_State_RB;//
		osTaskSwitch_Enable();//���������л�
		return (OK);//����OK

	}else{
		TIT -> TA = NewTA;
		TIT -> TC = Task_State_RB;//
		return (OK);//����OK
	}

}

osErrorValue osTaskErrorHardFault(uint32_t pc,uint32_t psp)
{
	#if (osTaskRunError_Enable > 0)
	uint8_t Count = 1;
	osTaskEnterISR();
	while(Count--){
		osTaskErrorDebug("\n\n\n����Ϊ%s����������Ӳ�������쳣!!!\n",RunTask_TIT -> TN);
		osTaskErrorDebug("�������ȼ�:%d\n",RunTask_TIT -> TPL);
		osTaskErrorDebug("����ǰʹ����:%d%%\n",RunTask_TIT -> TOR);
		osTaskErrorDebug("������ʱʣ��ʱ��:%d%ms\n���񵥴��������ʱ��:%dms\n",RunTask_TIT -> TTF,RunTask_TIT -> TTW);
		osTaskErrorDebug("������һ��״̬:",0,0);
		switch(RunTask_TIT -> TC){
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
		if(RunTask_TIT -> PF == NULL){
			osTaskErrorDebug("�յ�\n");
		}
		else{
			osTaskErrorDebug("�ǿ�\n");
		}
		osTaskErrorDebug("����ջ�ܴ�С:%d�ֽ�\n����ջʣ��:%d�ֽ�\n",(RunTask_TIT -> TSS - 1),psp - ((uint32_t)RunTask_TIT -> TH - ((RunTask_TIT -> TSS - 1))));
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
	RunTask_TIT -> TC = Task_State_Up_IN;
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
		print("����<%s>��ʹ����Ϊ:ռ��ʱ��:%dms | �������ȼ�:%d | ����״̬:",TL[_tr0].TITA -> TN,TL[_tr0].TITA -> TOR,TL[_tr0].TITA -> TPL);
		if(TL[_tr0].TITA != RunTask_TIT || TST.TSS != TaskSwitch_Ready){
			switch(TL[_tr0].TITA -> TC){
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

