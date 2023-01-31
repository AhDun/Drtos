/*
                                                  FILE-START
*/
#ifndef __osTaskH_
#define __osTaskH_
/*

 *@�ļ�����: osTask.h

 *@�ļ�����: 

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@ע    ��: 

*/

/*
                                                  <�����ļ���>
*/
/*
                                                  <�궨����>
*/

#define osTask_Enable 	//�������� ��������������ֶ����ã������Զ�����ļ����Զ���������

#define TaskListLength 		osMaximumTask 	//������ѯ���ȣ������ζ������������


//����״̬{
#define Task_State_Up_TD  0x05u//��Ƭ����(����̬)
/*
	�ڳ�ʱ����ִ���ʱ���񣬻ᱻ��Ƭ���𣬲���Ϊ��Ƭ����
*/
#define Task_State_Up_IN  0x06u//��������(����̬)
/*
	����ͨ����ͣ����������Ϊ��������
*/
#define Task_State_Up_DT  0x07u//��ʱ����(�ȴ�̬)
/*
	����ͨ����ʱ����������Ϊ��ʱ����
*/
#define Task_State_Up_SI  0x08u//�źŹ���(�ȴ�̬)
/*
	������Ϊ�ȴ��ź����������𣬻���Ϊ�źŹ���
*/
#define Task_State_Up_PT  0x09u//�ʼ�����(�ȴ�̬)
/*
	������Ϊ�ȴ��ʼ��������𣬻���Ϊ�ʼ�����
*/
/*
	��������Ϊ�ȴ�̬ʱ������������ᱻϵͳ�ָ�����
	��������Ϊ����̬ʱ��ֻ��ͨ��ͳһ���Ȼָ�����
*/
#define Task_State_DI 	  0x00u //����̬
/*
����̬: 
���������Զ���ᱻ���ȣ�����Ȼռ���ڴ�������ID
*/
#define Task_State_ST	  0x02u//��ֹ̬
/*
��ֹ̬: 
��������������й��������Ժ���������
*/
#define Task_State_RB	  0x01u//����̬
/*
����̬: 
����������ڵȴ�������
*/
#define Task_State_OP	  0x03u//����̬
/*
����̬: 
������������������У�����ռ��CPU
*/
#define Task_State_Up     0x04u//����̬
/*
����̬: 
������������������У�����ռ��CPU
*/
#define Task_State_RE     0x0Au//����̬
/*
����̬: 
*
*/
//}


//��������{
#define Task_Set_Default	0x00 //Ĭ�ϣ��������κζ���
#define Task_Set_Pause 		0x01u//��ͣ����
#define Task_Set_Cont  		0x02u//��������
#define Task_Set_Reboot 	0x03u//��������
#define Task_Set_Start  	0x04u//������������
#define Task_Set_Up  		0x05u//��������
//}

//����״̬{
#define TaskSwitch_Ready  		0x00u//����
#define TaskSwitch_Wait   		0x01u//�ȴ�
#define TaskSwitch_Run    		0x02u//����
//}



//------------------------Ĭ����Ƭʱ��-----------------------------
#define TaskTimeWheelDefault        100u//Ĭ����Ƭʱ��(��λms)

//--------------------------Ĭ��ջ��С------------------
#define Default_Stack_Size             1000u//Ĭ��ջ��С
     
//--------------------------�����滻----------------------
#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
	#define osProtect_DISABLE() 			INTX_ENABLE()//�˳��ٽ籣��
	#define osProtect_ENABLE() 				INTX_DISABLE()//�����ٽ籣��
#endif
#define osTaskSwitch_Enable() 			do{TaskSwitchState.SwitchState = TaskSwitch_Wait; CPU_PendSV();}while(0);//���������л�
#if (osTaskAutoStack_Enable > 0)//��������ջ�Զ�����
#define osTaskLogout(TN) 	osTaskLogout_Write(osTaskNameToTable(TN))
#endif

#define osTaskErrorDebug 		osDebugError

#define osTaskDebug_Enable 1 //Debug���� 1:����Debug��� 0:�ر�Debug���


#define osTaskRunError_Enable 1 //��������ʱ������������ 1:����Debug��� 0:�ر�Debug���

#define osTaskEnterISR()			TaskSwitchState.ISRFlag += 1;//���� �ж�

#define osTaskExitISR()				TaskSwitchState.ISRFlag -= 1;//�˳� �ж�


/*
                                                  �������ͱ���������
*/

typedef 	uint8_t 	_TaskID;//����ID
typedef 	uint8_t 	_TaskName;//��������
typedef 	uint8_t 	_TaskConfig;//���������
typedef 	uint32_t 	_TaskStackSize;//����ջ����
typedef 	uint32_t 	_TaskSemaphore;//�����ź���
typedef 	uint32_t 	_TaskTimeWheel;//����ʱ����Ƭ
typedef 	int8_t 		_TaskPriorityLevel;//�������ȼ�
typedef		uint32_t	_PostFormT;
typedef 	uint32_t 	_TaskAddr;
typedef		uint32_t	_TaskRealSP;
typedef		uint32_t	_TaskTimeFlag;
typedef     uint32_t     _TaskParameterPass;//���񴫲�
#if (osPerformanceStatistics_Enable > 0) //����������ͳ��
typedef     uint16_t     _TaskOccupyTime;//����ռ��ʱ��
typedef     uint16_t      _TaskOccupyRatio;//����ռ�ñ�
#endif


typedef struct
{
	_TaskRealSP			RealSP;	//����ʵʱջָ��
	_TaskRealSP			RealSPb;	//����ʵʱջָ��
	_TaskID				ID;		//����ID
	_TaskName*			Name; 	//��������
	_TaskConfig 		Config;  	//���������	
#ifdef osSignalMutual_Enable
	_TaskPriorityLevel	PriorityLevelb;   //���������ȼ�
#endif
//#ifdef osPost_Enable
	_PostFormT			PF;		//��������
//#endif
	_TaskTimeWheel 		TaskTimeWheel;	//����ʱ����Ƭ
	_TaskPriorityLevel 	PriorityLevel;	//�������ȼ�
	_TaskAddr*			Addr;		//�����ַ
	_TaskTimeFlag		TimeFlag;	//����ʱ���־
#if (osPerformanceStatistics_Enable > 0) //����������ͳ��
    _TaskOccupyTime      OccupyTime;    //����ռ��ʱ��
    _TaskOccupyRatio     OccupyRatio;    //����ռ�ñ�
	_TaskParameterPass*  ParameterPass;    //���񴫲�	
#endif				
} _TaskHandle;
//}

//������ѯ��{
typedef struct
{
	_TaskHandle*		TaskHandle;	  //������Ϣ�� ��ַ(������)
} _TaskList;
//}

//�������״̬��{
typedef		uint8_t		_TaskListMaximumActivity;//���������
typedef 	uint8_t		_TaskDispatchNum;//�������״̬
typedef     uint8_t      _SwitchState;//������ȼ���
typedef		uint8_t		_TaskISRFlag;
typedef struct
{
	_SwitchState	    		SwitchState;//�������״̬
	_TaskDispatchNum			DispatchNum;//������ȼ���
    _TaskListMaximumActivity	TaskListMax;//���������
	_TaskISRFlag				ISRFlag;//�ж�״̬

    
}_TaskSwitchState;
//}

/*
                                                  <����������>
*/
extern _TaskHandle*	RunTaskHandle;//��ǰ�������е������ָ��
extern _TaskList TaskList[TaskListLength];//������ѯ��
extern _TaskSwitchState TaskSwitchState;//�������״̬��


/*
                                                  <����������>
*/	
/*

 *@��������: osTaskInit

 *@�����汾: 1.0.0

 *@��������: �����������Ʋ�ѯ������ַ

 *@�������: ��	

 *@�� �� ֵ: osErrorValue - �������󷵻�ֵ (0:��ʾ��ʼ���ɹ���-1:��ʾ��ʼ���ɹ�)

 *@ע    ��: ��
*/
osErrorValue osTaskInit(void);	

/*

 *@��������: osTaskNameToTable

 *@�����汾: 1.0.0

 *@��������: �����������Ʋ�ѯ������ַ

 *@�������: TN		��������	
			 TA		�����ַ
			 TSS  	����ջ����
			 TTW  	����ʱ����Ƭ
			 TPL    �������ȼ�
			 TPP 	���񴫲�
			 TC 	�������ã�����������ο� - Task_Set_Default - ����궨�壩
	
 *@�� �� ֵ: 0:ע��ʧ��		������ֵ:ע��ɹ�
			 
 *@ע    ��: ��
*/
_TaskHandle* osTaskLogin(
	_TaskName *TN,
	void*  TA,	
	_TaskStackSize  TSS,
	_TaskTimeWheel  TTW,
	_TaskPriorityLevel  TPL,
    void*  TPP, 
    _TaskConfig  TC
);

_TaskHandle* osTaskLogin_Static(

	_TaskHandle* TaskHandle,
	_TaskName *TN,
	void*  TA,
	_TaskStackSize  TSS,
	_TaskTimeWheel  TTW,
	_TaskPriorityLevel  TPL,
    void*  TPP, 
    _TaskConfig  TC
);



#if (osTaskAutoStack_Enable > 0)//��������ջ�Զ�����
//osErrorValue osTaskLogout(_TaskName *TN);
osErrorValue osTaskLogout_Write(_TaskHandle* TaskHandle);
#else 							//����������ջ�Զ�����
osErrorValue	osTaskLogout(_TaskHandle* TaskHandle);
#endif
/*

 *@��������: osTaskNameToTable

 *@�����汾: 1.0.0

 *@��������: �����������Ʋ�ѯ������ַ

 *@�������: *TN	-	��������	

 *@�� �� ֵ: _TaskHandle* - ������ַ

 *@ע    ��: ��
*/
_TaskHandle* osTaskNameToTable(_TaskName *TN);
/*

 *@��������: osTaskNext

 *@�����汾: 1.0.0

 *@��������: ������һ��Ҫ���е�����

 *@�������: ��	

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
void osTaskNext(void);
/*

 *@��������: osTaskDelayMs

 *@�����汾: 1.0.0

 *@��������: ������뼶������ʱ

 *@�������: ms	-	Ҫ��ʱ��ʱ��	

 *@�� �� ֵ: 0: �����ʱ

 *@ע    ��: ��

*/
osErrorValue osTaskDelayMs(uint32_t ms);
/*

 *@��������: osTaskDelayUs

 *@�����汾: 1.0.0

 *@��������: ����΢�뼶������ʱ

 *@�������: us	-	Ҫ��ʱ��ʱ��

 *@�� �� ֵ: 0: �����ʱ

 *@ע    ��: ��

*/
osErrorValue osTaskDelayUs(uint32_t us);

//extern osErrorValue osTaskSwitch_State(void);
///*

// *@��������: osTaskAddrReplace

// *@�����汾: 1.0.0

// *@��������: ��������

// *@�������: ��	

// *@�� �� ֵ: -1:����ʱ���ִ���0: ���óɹ�

// *@ע    ��: ��

//*/
//extern osErrorValue osTaskISR(_TaskHandle* TaskHandle);
/*

 *@��������: osTaskAddrReplace

 *@�����汾: 1.0.0

 *@��������: ��������

 *@�������: ��	

 *@�� �� ֵ: -1:����ʱ���ִ���0: ���óɹ�

 *@ע    ��: ��

*/
osErrorValue osTaskSet(_TaskHandle* TaskHandle,uint8_t Pv);
/*

 *@��������: osTaskAddrReplace

 *@�����汾: 1.0.0

 *@��������: �����ַ�滻

 *@�������: ��	

 *@�� �� ֵ: -1:��������0: �����ɹ�

 *@ע    ��: ��

*/
osErrorValue osTaskAddrReplace(_TaskHandle* TaskHandle,void* NewTA);
/*

 *@��������: osTaskExit

 *@�����汾: 1.0.0

 *@��������: �������

 *@�������: ��	

 *@�� �� ֵ: 0: �ɹ�����

 *@ע    ��: ��

*/
osErrorValue osTaskExit(void);

osErrorValue osTaskErrorHardFault(uint32_t pc,uint32_t psp);


osErrorValue osTaskSpeedTest(void);

osErrorValue osTaskMonitor(void);

#endif

/*
                                                  FILE-END
*/


