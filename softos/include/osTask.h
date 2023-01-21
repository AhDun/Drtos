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

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע    ��: 

*/

/*
                                                  <�����ļ���>
*/
/*
                                                  <�궨����>
*/

#define TaskListLength 		osMaximumTask 	//������ѯ���ȣ������ζ������������

#if TaskListLength <= 255 //��������С��255ʱ


//---------------------�������ȼ�--------------------
	#define _TaskPriorityLevelMin   	-127		//������С���ȼ� 
	#define _TaskPriorityLevelMax 		126		//����������ȼ�
	/*
	��������ȼ�: 
	-127~126
	*/
//����ID��Χ{
	#define _TaskIDMin 					0u		//����ID��Сֵ
	#define _TaskIDMax 					253u	//����ID���ֵ
	/*
		����ID�ķ�Χ: 0~253
		����������: 254��
	*/
//}
#endif

#define TaskList_NULLValue	0u	    //������ѯ���ֵ

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
#define osTaskSwitch_Enable() 			do{TST.TSS = TaskSwitch_Wait; CPU_PendSV();}while(0);//���������л�
//#define osTaskSwitch_Strong_Enable() 	CPU_SVC()//����ǿ�������л�

#define osTaskDebug(a,b) print("\nosTask: %s:%s\n",a,b)//DeBug�������
#define osTaskInfoPrintOut	 print
#define osTaskDebug_Enable 1 //Debug���� 1:����Debug��� 0:�ر�Debug���




/*
                                                  �������ͱ���������
*/

typedef     u8		_Task_Set_Pv;//


//�����{
#if _TaskIDMax<= 253
	typedef 	u8 	_TaskID;//����ID
#endif
typedef 	u8 		_TaskName;//��������
typedef 	u8 		_TaskConfig;//���������
typedef 	u32 	_TaskHandle;//����ջ��ַ
typedef 	u32 	_TaskStackSize;//����ջ����
typedef 	u32 	_TaskSemaphore;//�����ź���
typedef 	u32 	_TaskTimeWheel;//����ʱ����Ƭ
#if _TaskPriorityLevelMax <= 126 && _TaskPriorityLevelMin >= -127
	typedef 	s8 		_TaskPriorityLevel;//�������ȼ�
#endif
typedef		u32		_PostForm;
typedef 	u32 	_TaskAddr;
typedef		u32		_TaskRealSP;
typedef		u32		_TaskTimeFlag;
#if (osPerformanceStatistics_Enable > 0) //����������ͳ��
typedef     u16     _TaskOccupyTime;//����ռ��ʱ��
typedef     u16      _TaskOccupyRatio;//����ռ�ñ�
#endif
typedef     u32     _TaskParameterPass;//���񴫲�


typedef struct
{
	_TaskRealSP			TRS;	//����ʵʱջָ��
	_TaskID				TI;		//����ID
	_TaskName*			TN; 	//��������
	_TaskConfig 		TC;  	//���������	
	_TaskHandle* 		TH;  	//����ջ��ַ
	_TaskStackSize 	TSS;   	//����ջ����
#if defined osSignalMutual_Enable ||  defined osSignalBinary_Enable || define osSignalCount_Enable
	_TaskPriorityLevel	TPLb;   //���������ȼ�
#endif
//#ifdef osPost_Enable
	_PostForm*			PF;
//#endif
	_TaskTimeWheel 		TTW;	//����ʱ����Ƭ
	_TaskPriorityLevel 	TPL;	//�������ȼ�
	_TaskAddr*			TA;		//�����ַ
	_TaskTimeFlag		TTF;	//����ʱ���־
#if (osPerformanceStatistics_Enable > 0) //����������ͳ��
    _TaskOccupyTime      TOT;    //����ռ��ʱ��
    _TaskOccupyRatio     TOR;    //����ռ�ñ�
#endif
    _TaskParameterPass*  TPP;    //���񴫲�					
} TaskInfoTable;
//}

//������ѯ��{
typedef struct
{
	TaskInfoTable*		TITA;	  //������Ϣ�� ��ַ(������)
} TaskList;
//}

//�������״̬��{
typedef		u8		_TaskListMaximumActivity;//���������
typedef 	u8		_TaskDispatchNum;//�������״̬
typedef     u8      _TaskSwitchState;//������ȼ���
#if (osTaskUsePrint  > 0)
typedef		u32		_TaskSwitchConut;//������ȴ���
typedef		u8		_TaskSwitchSpeedUs;//�����л��ٶȲ���
#endif
typedef struct
{
	_TaskSwitchState	    TSS;//�������״̬
	_TaskDispatchNum		TDN;//������ȼ���
    _TaskListMaximumActivity	TLMA;//���������
	#if (osTaskUsePrint  > 0)
	_TaskSwitchConut			TSC;//������ȴ���
	_TaskSwitchSpeedUs			TSSU;//�����л��ٶȲ���
	#endif
    
} TaskDispatchStateTable;
//}

/*
                                                  <����������>
*/
extern u32 NULL_Value;//һ����ֵ
extern TaskInfoTable*	RunTask_TIT;//��ǰ�������е������ָ��

extern TaskList TL[TaskListLength];//������ѯ��
extern TaskDispatchStateTable TST;//�������״̬��


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
extern osErrorValue osTaskInit(void);	


#if (osTaskAutoStack_Enable > 0)//��������ջ�Զ�����
/*

 *@��������: osTaskNameToTable

 *@�����汾: 1.0.0

 *@��������: �����������Ʋ�ѯ������ַ

 *@�������: TN	-	��������	
			 TA	-	�����ַ
			 TSS - 	����ջ����
			 TTW - 	����ʱ����Ƭ
			 TPL -  �������ȼ�
			 TPP -	���񴫲�
			 TC -	�������ã�����������ο� - Task_Set_Default - ����궨�壩
	
 *@�� �� ֵ: osErrorValue -		�������󷵻�ֵ (-1: ��ʾ��������������,> - 1: ע�������ID����ʾ�����ע��)
			 
 *@ע    ��: ��
*/
extern osErrorValue osTaskLogin(
	_TaskName *TN,
	void*  TA,	
	_TaskStackSize  TSS,
	_TaskTimeWheel  TTW,
	_TaskPriorityLevel  TPL,
    void*  TPP, 
    _TaskConfig  TC
);
extern osErrorValue osTaskRegister_Write(
#else //����������ջ�Զ�����
extern osErrorValue osTaskLogin(
#endif 
	TaskInfoTable* TIT,
	_TaskName *TN,
	void*  TA,
	_TaskHandle* TH,
	_TaskStackSize  TSS,
	_TaskTimeWheel  TTW,
	_TaskPriorityLevel  TPL,
    void*  TPP, 
    _TaskConfig  TC
);

#if (osTaskAutoStack_Enable > 0)//��������ջ�Զ�����
osErrorValue osTaskLogout(_TaskName *TN);
osErrorValue osTaskLogout_Write(TaskInfoTable* TIT);
#else 							//����������ջ�Զ�����
osErrorValue	osTaskLogout(TaskInfoTable* TIT);
#endif
/*

 *@��������: osTaskNameToTable

 *@�����汾: 1.0.0

 *@��������: �����������Ʋ�ѯ������ַ

 *@�������: *TN	-	��������	

 *@�� �� ֵ: TaskInfoTable* - ������ַ

 *@ע    ��: ��
*/
extern TaskInfoTable* osTaskNameToTable(_TaskName *TN);
/*

 *@��������: osTaskNext

 *@�����汾: 1.0.0

 *@��������: ������һ��Ҫ���е�����

 *@�������: ��	

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
extern void osTaskNext(void);
/*

 *@��������: osTaskDelayMs

 *@�����汾: 1.0.0

 *@��������: ������뼶������ʱ

 *@�������: ms	-	Ҫ��ʱ��ʱ��	

 *@�� �� ֵ: 0: �����ʱ

 *@ע    ��: ��

*/
extern osErrorValue osTaskDelayMs(u32 ms);
/*

 *@��������: osTaskDelayUs

 *@�����汾: 1.0.0

 *@��������: ����΢�뼶������ʱ

 *@�������: us	-	Ҫ��ʱ��ʱ��

 *@�� �� ֵ: 0: �����ʱ

 *@ע    ��: ��

*/
extern osErrorValue osTaskDelayUs(u32 us);

//extern osErrorValue osTaskSwitch_State(void);
///*

// *@��������: osTaskAddrReplace

// *@�����汾: 1.0.0

// *@��������: ��������

// *@�������: ��	

// *@�� �� ֵ: -1:����ʱ���ִ���0: ���óɹ�

// *@ע    ��: ��

//*/
//extern osErrorValue osTaskISR(TaskInfoTable* TIT);
/*

 *@��������: osTaskAddrReplace

 *@�����汾: 1.0.0

 *@��������: ��������

 *@�������: ��	

 *@�� �� ֵ: -1:����ʱ���ִ���0: ���óɹ�

 *@ע    ��: ��

*/
extern osErrorValue osTaskSet(TaskInfoTable* TIT,_Task_Set_Pv Pv);
/*

 *@��������: osTaskAddrReplace

 *@�����汾: 1.0.0

 *@��������: �����ַ�滻

 *@�������: ��	

 *@�� �� ֵ: -1:��������0: �����ɹ�

 *@ע    ��: ��

*/
extern osErrorValue osTaskAddrReplace(TaskInfoTable* TIT,void* NewTA);
/*

 *@��������: osTaskExit

 *@�����汾: 1.0.0

 *@��������: �������

 *@�������: ��	

 *@�� �� ֵ: 0: �ɹ�����

 *@ע    ��: ��

*/
extern osErrorValue osTaskExit(void);


#endif

/*
                                                  FILE-END
*/


