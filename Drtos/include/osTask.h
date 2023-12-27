/**
 * Copyright 2022-2023 AhDun. All rights reserved.
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
/**
 *
 * @file osTask.h
 *
 * @brief 
 *
 * @note 
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
/**
 *
 * @name osProtect_DISABLE
 *
 * @brief �˳��ٽ籣��
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osProtect_DISABLE() 			osLinkISREnable()
/**
 *
 * @name osProtect_DISABLE
 *
 * @brief �����ٽ籣��
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osProtect_ENABLE() 				osLinkISRDisable()
#endif
/**
 *
 * @name osTaskSwitch
 *
 * @brief ���������������л�
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
//#define osTaskSwitch() 			do{osTaskGetSwitchQueue()++; ISR_Touch();}while(0);
#define osTaskSwitch(a)				do{OsTaskNextTaskHandle = a;OsTimeTaskTimeWheel = OsTaskNextTaskHandle -> Wheel;ISR_Touch();}while(0);
//#define osTaskSwitchChock()			do{osTaskNext();}while(0);
/**
 *
 * @name osTaskSwitchConfig_Config
 *
 * @brief �����ô��������������л�
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osTaskSwitchConfig(a,b,c)			do{b -> Config = c;OsTaskNextTaskHandle = a;OsTimeTaskTimeWheel = OsTaskNextTaskHandle -> Wheel;ISR_Touch();}while(0);
//#define osTaskSwitchChockConfig(a,b)		do{a -> Config = b;OsTaskNextTaskHandle = a;osTaskNext();}while(0);
//#define osTaskSwitchConfig(a,b)  do{a -> Config = b;osTaskGetSwitchQueue()++; ISR_Touch();}while(0);


/**
 *
 * @name osTaskEnterIRQ
 *
 * @brief �����ж�
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osTaskEnterIRQ()			osTaskGetOIRQFlag() += 1;
/**
 *
 * @name osTaskExitIRQ
 *
 * @brief �˳��ж�
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/
#define osTaskExitIRQ()				osTaskGetOIRQFlag() -= 1;
/**
 *
 * @name osTaskGetRunTaskHandle
 *
 * @brief ��ȡ�������е�������
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/

#define osTaskGetRunTaskHandle()		OsTaskRunTaskHandle

/**
 *
 * @name osTaskGetRunTaskHandle
 *
 * @brief ��ȡ���������л�״̬
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/


//#define osTaskGetSwitchQueue()			OsTaskSwitchQueue//��������������


/**
 *
 * @name osTaskGetOIRQFlag
 *
 * @brief ��ȡ�ж�״̬
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/

#define osTaskGetOIRQFlag()			OsTaskISRFlag

/**
 *
 * @name osTaskGetRunTaskHandle
 *
 * @brief ��ȡ���������л�״̬
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
*/

#define osTaskGetNextTaskHandle()			OsTaskNextTaskHandle


/**
 *
 * @name osTaskGetRunTaskHandle
 *
 * @brief ��ȡ����������ͷ��ָ��
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
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

	
/**
 *
 * @name osTaskInit
 *
 * @brief �����������Ʋ�ѯ��������ַ
 *
 * @param none	
 *
 * @retval OsErrorValue - �������󷵻�ֵ (0:��ʾ��ʼ���ɹ���-1:��ʾ��ʼ���ɹ�)
 *
 * @note none
*/
OsErrorValue osTaskInit(void);	

OsErrorValue osTaskSIRQInit(void);	

void osTaskStart(void);

_TaskHandle* osTaskLoad(_TaskHandle* TaskHandle,uint8_t Config);

/**
 *
 * @name osTaskLogin
 *
 * @brief ����ע��(�Զ������ڴ�)
 *
 * @param TN	��������	
 * @param TA	�����ַ
 * @param TSS  	����ջ����
 * @param TTW  	����ʱ����Ƭ
 * @param TPL   �������ȼ�
 * @param TPP 	���񴫲�
 * @param TC 	�������ã�����������ο� - Task_Set_Default - ����궨�壩
 *
 * @retval 0:ע��ʧ��		������ֵ:ע��ɹ�
 *
 * @note none
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
/**
 *
 * @name osTaskLoginStatic
 *
 * @brief ����ע��(�ֶ��ṩ�ڴ�)
 *
 * @param TaskHandle ������(�洢��ַ)
 * @param TN	��������	
 * @param TA	�����ַ
 * @param TSS  	����ջ����
 * @param TTW  	����ʱ����Ƭ
 * @param TPL   �������ȼ�
 * @param TPP 	���񴫲�
 * @param TC 	�������ã�����������ο� - Task_Set_Default - ����궨�壩
 *
 * @retval 0:ע��ʧ��		������ֵ:ע��ɹ�
 *
 * @note none
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

/**
 *
 * @name osTaskLogout
 *
 * @brief ����ע��(�Զ��ͷ��ڴ�)
 *
 * @param TaskHandle ������
 *
 * @retval 0:ע��ʧ��		������ֵ:ע��ɹ�
 *
 * @note none
 */
OsErrorValue  osTaskLogout(_TaskHandle* TaskHandle);
/**
 *
 * @name osTaskLogoutStatic
 *
 * @brief ����ע��(���ͷ��ڴ�)
 *
 * @param TaskHandle ������
 *
 * @retval 0:ע��ʧ��		������ֵ:ע��ɹ�
 *
 * @note none
 */

OsErrorValue  osTaskLogoutStatic(_TaskHandle* TaskHandle);

/**
 *
 * @name osTaskNext
 *
 * @brief ������һ��Ҫ���е�����
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
 *
 */
void osTaskNext(void);
/**
 *
 * @name osTaskDelayMs
 *
 * @brief ������뼶������ʱ
 *
 * @param ms	Ҫ��ʱ��ʱ��	
 *
 * @retval none
 *
 * @note none
 *
 */
void osTaskDelayMs(uint32_t ms);
/**
 *
 * @name osTaskDelayUs
 *
 * @brief ����΢�뼶������ʱ
 *
 * @param us	Ҫ��ʱ��ʱ��
 *
 * @retval none
 *
 * @note none
 *
 */
void osTaskDelayUs(uint32_t us);

/**
 *
 * @name osTaskAddrReplace
 *
 * @brief ��������
 *
 * @param none	
 *
 * @retval -1:����ʱ���ִ���0: ���óɹ�
 *
 * @note none
 *
 */
OsErrorValue osTaskSet(_TaskHandle* TaskHandle,uint8_t Pv);
/**
 *
 * @name osTaskAddrReplace
 *
 * @brief �����ַ�滻
 *
 * @param none	
 *
 * @retval -1:��������0: �����ɹ�
 *
 * @note none
 *
 */
OsErrorValue osTaskAddrReplace(_TaskHandle* TaskHandle,void* NewTA);
/**
 *
 * @name osTaskExit
 *
 * @brief �������
 *
 * @param none	
 *
 * @retval 0: �ɹ�����
 *
 * @note none
 *
 */
OsErrorValue osTaskExit(void);

/**
 *
 * @name osTaskSIRQ_Enable
 *
 * @brief ���ж�ʹ��
 *
 * @param 	SIRQList_Addr	���жϱ��ͷ
 *
 * @retval none
 *
 * @note none
 *
 */
void osTaskSIRQ_Enable(_SIRQList* SIRQList_Addr);
/**
 *
 * @name osTaskSIRQLogin
 *
 * @brief ���ж�ע��
 *
 * @param 	SIRQList_Addr	���жϱ��ͷ
 * @param 	Addr			���ж���Ӧ������ַ	
 *
 * @retval none
 *
 * @note none
 *
 */
OsErrorValue osTaskSIRQLogin(_SIRQList* SIRQList_Addr,void* Addr);
/**
 *
 * @name osTaskSIRQ
 *
 * @brief ���ж���Ӧ
 *
 * @param none	
 *
 * @retval none
 *
 * @note none
 *
 */
void osTaskSIRQ(void);


#endif




