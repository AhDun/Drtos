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
#ifndef __osTaskH_
#define __osTaskH_
/*
 *
 * @�ļ�����: osTask.h
 *
 * @�ļ�����: 
 *
 * @ע    ��: 
 *
 */








//����״̬{
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







     

#if (osCriticalToProtect_Config > 0)//�������ٽ籣��
/*
 *
 * @��������: osProtect_DISABLE
 *
 * @��������: �˳��ٽ籣��
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osProtect_DISABLE() 			ISR_Config()
/*
 *
 * @��������: osProtect_DISABLE
 *
 * @��������: �����ٽ籣��
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osProtect_ENABLE() 				ISR_Disable()
#endif
/*
 *
 * @��������: osTaskSwitch_Config
 *
 * @��������: ���������������л�
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osTaskSwitch_Config() 			do{osTaskGetSwitchState() = TaskSwitch_Wait; ISR_Touch();}while(0);
/*
 *
 * @��������: osTaskSwitchConfig_Config
 *
 * @��������: �����ô��������������л�
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osTaskSwitchConfig_Config(a,b)  do{a -> Config = b;osTaskGetSwitchState() = TaskSwitch_Wait; ISR_Touch();}while(0);
/*
 *
 * @��������: osTaskEnterIRQ
 *
 * @��������: �����ж�
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osTaskEnterIRQ()			osTaskGetOIRQFlag() += 1;
/*
 *
 * @��������: osTaskExitIRQ
 *
 * @��������: �˳��ж�
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
#define osTaskExitIRQ()				osTaskGetOIRQFlag() -= 1;
/*
 *
 * @��������: osTaskErrorDebug
 *
 * @��������: �����ж�
 *
 * @�������: 	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/

#define osTaskErrorDebug 		osDebugError
/*
 *
 * @��������: osTaskGetRunTaskHandle
 *
 * @��������: ��ȡ�������е�������
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/

#define osTaskGetRunTaskHandle()		OsTaskRunTaskHandle

/*
 *
 * @��������: osTaskGetRunTaskHandle
 *
 * @��������: ��ȡ���������л�״̬
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/

#define osTaskGetSwitchState()			OsTaskSwitchState


/*
 *
 * @��������: osTaskGetRunTaskHandle
 *
 * @��������: ��ȡ���������л�״̬
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/

#define osTaskGetOIRQFlag()			OsTaskISRFlag

/*
 *
 * @��������: osTaskGetRunTaskHandle
 *
 * @��������: ��ȡ���������л�״̬
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/

#define osTaskGetNextTaskHandle()			OsTaskNextTaskHandle


/*
 *
 * @��������: osTaskGetRunTaskHandle
 *
 * @��������: ��ȡ���������л�״̬
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/

#define osTaskGetTaskHandleListHead()			OsTaskTaskHandleListHead





//������{
#if (osTaskName_Config > 0)
typedef 	uint8_t 	_TaskName;//��������
#endif
typedef 	uint8_t 	_TaskConfig;//���������
typedef 	uint32_t 	_TaskStackSize;//����ջ����
typedef 	uint32_t 	_TaskSemaphore;//�����ź���
typedef 	uint32_t 	_TaskWheel;//����ʱ����Ƭ
typedef 	int8_t 		_TaskLevel;//�������ȼ�
typedef		uint32_t	_PostFormT;//��������
typedef 	uint32_t 	_TaskAddr;//�����ַ
typedef		uint32_t	_TaskRealSP;//����ʵʱջָ��
typedef		uint32_t	_TaskTimeFlag;//����ʱ���־
typedef		uint32_t	_NextTaskHandle;//����ʱ���־
#if (osTaskArg_Config > 0)
typedef     uint32_t     _TaskArg;//���񴫲�
#endif
#if (osPerformanceStatistics_Config > 0) //����������ͳ��
typedef     uint16_t     _TaskOccupyTime;//����ռ��ʱ��
typedef     uint16_t      _TaskOccupyRatio;//����ռ�ñ�
#endif

typedef struct
{
	_TaskRealSP			RealSP;				//����ʵʱջָ��
	_NextTaskHandle*	NextTaskHandle;
	_TaskConfig 		Config;  			//���������
	_TaskWheel 			TaskWheel;			//����ʱ����Ƭ
	_TaskLevel 			Level;			//�������ȼ�
	_TaskAddr*			Addr;					//�����ַ
	_TaskRealSP			RealSPb;			//����ʵʱջָ��
	_TaskTimeFlag		TimeFlag;			//����ʱ���־
#if (osTaskName_Config > 0)
	_TaskName*			Name; 				//��������
#endif	
#ifdef osSignalMutual_Config
	_TaskLevel			Levelb;   	//���������ȼ�
#endif
#if (osTaskArg_Config > 0)
	_TaskArg*  			Arg;    //���񴫲�	
#endif
#if (osPost_Config > 0)
	_TaskArg			Arg1;					//��������
#endif
#if (osPerformanceStatistics_Config > 0) //����������ͳ��
    _TaskOccupyTime      OccupyTime;    //����ռ��ʱ��
    _TaskOccupyRatio     OccupyRatio;    //����ռ�ñ�
#endif				
} _TaskHandle;

typedef struct
{
	_TaskRealSP			RealSP;				//����ʵʱջָ��
	_NextTaskHandle*	NextTaskHandle;
	_TaskConfig 		Config;  			//���������
	_TaskWheel 			TaskWheel;			//����ʱ����Ƭ
	_TaskLevel 			Level;			//�������ȼ�
	_TaskAddr*			Addr;					//�����ַ
	_TaskRealSP			RealSPb;			//����ʵʱջָ��
	_TaskTimeFlag		TimeFlag;			//����ʱ���־
#if (osTaskName_Config > 0)
	_TaskName*			Name; 				//��������
#endif	
#ifdef osSignalMutual_Config
	_TaskLevel			Levelb;   	//���������ȼ�
#endif
#if (osTaskArg_Config > 0)
	_TaskArg*  			Arg;    //���񴫲�	
#endif
#if (osPost_Config > 0)
	_TaskArg			Arg1;					//��������
#endif
#if (osPerformanceStatistics_Config > 0) //����������ͳ��
    _TaskOccupyTime      OccupyTime;    //����ռ��ʱ��
    _TaskOccupyRatio     OccupyRatio;    //����ռ�ñ�
#endif				
} _QuickTaskHandle;

//}

typedef		uint8_t		_TaskListMaximumActivity;//���������
typedef 	uint8_t		_TaskDispatchNum;//�������״̬
typedef     uint8_t      _SwitchState;//������ȼ���
typedef		uint8_t		_TaskISRFlag;



extern _TaskHandle*		TaskHandle_Main;//Main������

extern _TaskHandle* 	OsTaskRunTaskHandle;//�������е�������
extern _SwitchState	    OsTaskSwitchState;//�������״̬
extern _TaskISRFlag		OsTaskISRFlag;//�ж�״̬
extern _TaskHandle* 	OsTaskNextTaskHandle;//��һ��Ҫ���е�������
extern _TaskHandle* 	OsTaskTaskHandleListHead;//�����������ͷ



typedef _TaskAddr 		_SIRQList;

	
/*
 *
 * @��������: osTaskInit
 *
 * @��������: �����������Ʋ�ѯ������ַ
 *
 * @�������: ��	
 *
 * @�� �� ֵ: OsErrorValue - �������󷵻�ֵ (0:��ʾ��ʼ���ɹ���-1:��ʾ��ʼ���ɹ�)
 *
 * @ע    ��: ��
*/
OsErrorValue osTaskInit(void);	

OsErrorValue osTaskSIRQInit(void);	

/*
 *
 * @��������: osTaskLogin
 *
 * @��������: ����ע��(�Զ������ڴ�)
 *
 * @�������: TN	��������	
 * @�������: TA	�����ַ
 * @�������: TSS  	����ջ����
 * @�������: TTW  	����ʱ����Ƭ
 * @�������: TPL   �������ȼ�
 * @�������: TPP 	���񴫲�
 * @�������: TC 	�������ã�����������ο� - Task_Set_Default - ����궨�壩
 *
 * @�� �� ֵ: 0:ע��ʧ��		������ֵ:ע��ɹ�
 *
 * @ע    ��: ��
 */
_TaskHandle* osTaskLogin(
#if (osTaskName_Config > 0)
	_TaskName *TN,
#endif
	void*  TA,	
	_TaskStackSize  TSS,
	_TaskWheel  TTW,
	_TaskLevel  TPL,
	#if (osTaskArg_Config > 0)
    void*  TPP, 
	#endif
    _TaskConfig  TC
);
/*
 *
 * @��������: osTaskLogin_Static
 *
 * @��������: ����ע��(�ֶ��ṩ�ڴ�)
 *
 * @�������: TaskHandle ������(�洢��ַ)
 * @�������: TN	��������	
 * @�������: TA	�����ַ
 * @�������: TSS  	����ջ����
 * @�������: TTW  	����ʱ����Ƭ
 * @�������: TPL   �������ȼ�
 * @�������: TPP 	���񴫲�
 * @�������: TC 	�������ã�����������ο� - Task_Set_Default - ����궨�壩
 *
 * @�� �� ֵ: 0:ע��ʧ��		������ֵ:ע��ɹ�
 *
 * @ע    ��: ��
 */

_TaskHandle* osTaskLogin_Static(

	_TaskHandle* TaskHandle,
#if (osTaskName_Config > 0)
	_TaskName *TN,
#endif
	void*  TA,
	_TaskStackSize  TSS,
	_TaskWheel  TTW,
	_TaskLevel  TPL,
#if (osTaskArg_Config > 0)
    void*  TPP, 
#endif
    _TaskConfig  TC
);

/*
 *
 * @��������: osTaskLogout
 *
 * @��������: ����ע��(�Զ��ͷ��ڴ�)
 *
 * @�������: TaskHandle ������
 *
 * @�� �� ֵ: 0:ע��ʧ��		������ֵ:ע��ɹ�
 *
 * @ע    ��: ��
 */
OsErrorValue  osTaskLogout(_TaskHandle* TaskHandle);
/*
 *
 * @��������: osTaskLogout_Static
 *
 * @��������: ����ע��(���ͷ��ڴ�)
 *
 * @�������: TaskHandle ������
 *
 * @�� �� ֵ: 0:ע��ʧ��		������ֵ:ע��ɹ�
 *
 * @ע    ��: ��
 */

OsErrorValue  osTaskLogout_Static(_TaskHandle* TaskHandle);

/*
 *
 * @��������: osTaskNext
 *
 * @��������: ������һ��Ҫ���е�����
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void osTaskNext(void);
/*
 *
 * @��������: osTaskDelayMs
 *
 * @��������: ������뼶������ʱ
 *
 * @�������: ms	Ҫ��ʱ��ʱ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void osTaskDelayMs(uint32_t ms);
/*
 *
 * @��������: osTaskDelayUs
 *
 * @��������: ����΢�뼶������ʱ
 *
 * @�������: us	Ҫ��ʱ��ʱ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
void osTaskDelayUs(uint32_t us);

/*
 *
 * @��������: osTaskAddrReplace
 *
 * @��������: ��������
 *
 * @�������: ��	
 *
 * @�� �� ֵ: -1:����ʱ���ִ���0: ���óɹ�
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osTaskSet(_TaskHandle* TaskHandle,uint8_t Pv);
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
OsErrorValue osTaskAddrReplace(_TaskHandle* TaskHandle,void* NewTA);
/*
 *
 * @��������: osTaskExit
 *
 * @��������: �������
 *
 * @�������: ��	
 *
 * @�� �� ֵ: 0: �ɹ�����
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osTaskExit(void);

OsErrorValue osTaskErrorHardFault(uint32_t pc,uint32_t psp);


OsErrorValue osTaskSpeedTest(void);

OsErrorValue osTaskMonitor(void);


void osTaskSIRQ_Config(_SIRQList* SIRQList_Addr);

OsErrorValue osTaskSIRQLogin(_SIRQList* SIRQList_Addr,void* Addr);

void osTaskSIRQ(void);
#endif




