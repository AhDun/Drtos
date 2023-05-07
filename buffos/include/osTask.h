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
#ifndef __osTask_H_
#define __osTask_H_
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

#define Task_Set_OSCore		0x0Fu//

#define Task_Set_StopAutoFree	0x80
//}


//װ������{
#define Load_Only	0x00
#define Load_Create	0x01
#define Load_Stack	0x02
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
#define osProtect_DISABLE() 			osLinkISREnable()
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
#define osProtect_ENABLE() 				osLinkISRDisable()
#endif
/*
 *
 * @��������: osTaskSwitch
 *
 * @��������: ���������������л�
 *
 * @�������: ��	
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
*/
//#define osTaskSwitch() 			do{osTaskGetSwitchQueue()++; ISR_Touch();}while(0);
#define osTaskSwitch(a)				do{OsTaskNextTaskHandle = a;OsTimeTaskTimeWheel = OsTaskNextTaskHandle -> Wheel;ISR_Touch();}while(0);
//#define osTaskSwitchChock()			do{osTaskNext();}while(0);
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
#define osTaskSwitchConfig(a,b,c)			do{b -> Config = c;OsTaskNextTaskHandle = a;OsTimeTaskTimeWheel = OsTaskNextTaskHandle -> Wheel;ISR_Touch();}while(0);
//#define osTaskSwitchChockConfig(a,b)		do{a -> Config = b;OsTaskNextTaskHandle = a;osTaskNext();}while(0);
//#define osTaskSwitchConfig(a,b)  do{a -> Config = b;osTaskGetSwitchQueue()++; ISR_Touch();}while(0);


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


//#define osTaskGetSwitchQueue()			OsTaskSwitchQueue//��������������


/*
 *
 * @��������: osTaskGetOIRQFlag
 *
 * @��������: ��ȡ�ж�״̬
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
 * @��������: ��ȡ����������ͷ��ָ��
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
typedef		uint32_t	_TaskDelay;//����ʱ���־
typedef		uint32_t	_NextTaskHandle;//����ʱ���־
#if (osTaskArg_Config > 0)
typedef     uint32_t     _TaskArg;//���񴫲�
#endif
#if (osPerf_Config > 0) //����������ͳ��
typedef     uint16_t     _TaskOccupyTime;//����ռ��ʱ��
typedef     uint16_t     _TaskOccupyRatio;//����ռ�ñ�
#endif

typedef struct
{
	/*����*/
	_TaskRealSP			RealSP;//����ʵʱջָ��
	_NextTaskHandle*	NextTaskHandle;
	_TaskAddr*			Addr;//�����ַ
	_TaskConfig 		Config;//���������
	/*��չ*/
	_TaskRealSP			Length;//����ʵʱջָ��
	_TaskLevel 			Level;//�������ȼ�
	_TaskWheel 			Wheel;//����ʱ����Ƭ
	_TaskDelay			Delay;//��ʱʱ���־
#if (osTaskName_Config > 0)
	_TaskName*			Name;//��������
#endif	
#if (osSignal_Config & Signal_Mutual)
	_TaskLevel			Levelb;//���������ȼ�
#endif
#if (osTaskArg_Config > 0)
	_TaskArg*  			Arg;//���񴫲�	
#endif
#if (osPost_Config > 0)
	_TaskArg			Arg1;//��������
#endif
#if (osPerf_Config > 0)//����������ͳ��
    _TaskOccupyTime      OccupyTime;//����ռ��ʱ��
    _TaskOccupyRatio     OccupyRatio;//����ռ�ñ�
#endif				
} _TaskHandle;
//}


typedef     uint8_t     _SwitchState;//������ȼ���
typedef		uint8_t		_TaskISRFlag;
typedef		uint8_t 	_TaskSwitchQueue;


extern 	_TaskHandle*	OSCoreTaskHandle;//Main������
extern  _TaskHandle* 	volatile OsTaskRunTaskHandle;//�������е�������
extern  _TaskHandle* 	volatile OsTaskNextTaskHandle;//��һ��Ҫ���е�������
extern  _TaskSwitchQueue	OsTaskSwitchQueue;//��������������
extern _TaskISRFlag		OsTaskISRFlag;//�ж�״̬
extern _TaskHandle* 	OsTaskTaskHandleListHead;//�����������ͷ
extern uint16_t		OsTaskIdle;

typedef _TaskAddr 		_SIRQList;

	
/*
 *
 * @��������: osTaskInit
 *
 * @��������: �����������Ʋ�ѯ��������ַ
 *
 * @�������: ��	
 *
 * @�� �� ֵ: OsErrorValue - �������󷵻�ֵ (0:��ʾ��ʼ���ɹ���-1:��ʾ��ʼ���ɹ�)
 *
 * @ע    ��: ��
*/
OsErrorValue osTaskInit(void);	

OsErrorValue osTaskSIRQInit(void);	

void osTaskStart(void);

_TaskHandle* osTaskLoad(_TaskHandle* TaskHandle,uint8_t Config);

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
);
/*
 *
 * @��������: osTaskLoginStatic
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
 * @��������: osTaskLogoutStatic
 *
 * @��������: ����ע��(���ͷ��ڴ�)
 *
 * @�������: TaskHandle ������
 *
 * @�� �� ֵ: 0:ע��ʧ��		������ֵ:ע��ɹ�
 *
 * @ע    ��: ��
 */

OsErrorValue  osTaskLogoutStatic(_TaskHandle* TaskHandle);

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
void osTaskSIRQ_Enable(_SIRQList* SIRQList_Addr);
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
OsErrorValue osTaskSIRQLogin(_SIRQList* SIRQList_Addr,void* Addr);
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
void osTaskSIRQ(void);


#endif




