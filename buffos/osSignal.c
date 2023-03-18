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
 * @�ļ�����: .c
 *
 * @�ļ�����: ϵͳ"�ź���"�ļ�
 *
 * @ע    ��: ��
 *
 */


#include "osConfig.h"
#include "osSignal.h"
/*

 @ͷ�ļ�����: ��

 @ͷ�ļ�����: ��

 @ע      ��: ��
 *
 */


/*

 @��������: ��

 @��������: ��
 *
 * @ע    ��: ��
 *
 */


/*
 *
 * @��������: osSignalRegister
 *
 * @��������: ע���ź���
 *
 * @�������: _SignalType SP(�ź���������)
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
#if (osSignalAutoApply_Config > 0)//�������ź����Զ�����
_SignalHandle* osSignalLogin(_SignalType SP)
{
	#if defined osSignalMutual_Config || defined osSignalBinary_Config || defined osSignalCount_Config
		_SignalHandle* ST = osSignalMemoryMalloc(sizeof(_SignalHandle));//Ϊ�ź����ṹ�������ڴ�
		if(ST == NULL){//����ڴ����뺯������Ϊ��,˵������ʧ��
			#if (osSignalLog_Config > 0)
			osLog(osLogClass_Error,"osSignalLogin","ע���ź���ʱ�ڴ�����ʧ��");
			#endif
			return (NULL);//���ؿ�,��ʾ����
		}
		ST -> Value = 0;//���ź�ֵ��Ϊ��
		if(SP == Signal_Mutual || SP == Signal_Binary || SP == Signal_Count){
			ST -> Type = SP;//д���ź�����
		}else{
			#if (osSignalLog_Config > 0)
			osLog(osLogClass_Error,"osSignalLogin","ע���ź���ʱ����δ֪����");
			#endif
			return (NULL);
		}
		ST -> NextAddr = NULL;
		return (ST);
	#else
		return (NULL);
	#endif 
}
#else
/*
 *
 * @��������: osSignalRegister
 *
 * @��������: ע���ź���
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osSignalLogin(_SignalHandle* ST,_SignalType SP)
{
    switch(SP){
#ifdef osSignalMutual_Config 
        case Signal_Mutual://�����ź���
                            ST ->SV = false;//���ź�ֵ��Ϊ��
                            ST ->SP = NULL;//д���ź�����
                            return (OK);
#endif
#ifdef osSignalBinary_Config 
        case Signal_Binary://��ֵ�ź���
                            ST ->SV = false;//���ź�ֵ��Ϊ��
							ST ->SP = NULL;//д���ź�����
							return (OK);
#endif
#ifdef osSignalCount_Config
        case Signal_Count://�����ź���
							ST ->SV = 0;//���ź�ֵ��Ϊ��
                            ST ->SP = NULL;//д���ź�����
                            return (OK);
#endif
        default:
				#if (osSignalLog_Config > 0)
				osLog(osLogClass_Error,"osSignalLogin","ע���ź���ʱ����δ֪����");
				#endif
				return (Error);//break;
    }
}
#endif

/*
 *
 * @��������: osSignalApply_Wait
 *
 * @��������: �ź�������
 *
 * @�������: _SignalHandle* ST(�ź����ṹ��)
 *
 * @�� �� ֵ: -1:�������� / 0:����ɹ�
 *
 * @ע    ��: ��
 *
 */

static OsErrorValue osSignalApplyToken(_SignalHandle* ST)
{
	_SignalToken* SemaphoreToken_Buf = osSignalMemoryMalloc(sizeof(_SignalToken));//Ϊ�ź����ṹ�������ڴ�
	if(SemaphoreToken_Buf == NULL){
		#if (osSignalLog_Config > 0)
		osLog(osLogClass_Error,"osSignalApplyToken","����ռ���ź�������ʱ�ڴ�����ʧ��");
		#endif
		return (Error);
	}else{
		SemaphoreToken_Buf -> DownAddr = NULL;
		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)osTaskGetRunTaskHandle();
		ST -> NextAddr = (uint32_t)SemaphoreToken_Buf;
		return (OK);
	}
}


/*
 *
 * @��������: osSignalApply_Wait
 *
 * @��������: �ź�������
 *
 * @�������: _SignalHandle* ST(�ź����ṹ��)
 *
 * @�� �� ֵ: -1:�������� / 0:����ɹ�
 *
 * @ע    ��: ��
 *
 */

static OsErrorValue osSignalWaitToken(_SignalHandle* ST)
{
	_NextAddr* NextAddr_Buf;
	_NextAddr NextAddr_Buf1;
	_SignalToken* SemaphoreToken_Buf1;
	_TaskHandle*	TaskInfoTable_Buf;
	_SignalToken* SemaphoreToken_Buf = osSignalMemoryMalloc(sizeof(_SignalToken));//Ϊ�ź����ṹ�������ڴ�
	if(SemaphoreToken_Buf == NULL){
		#if (osSignalLog_Config > 0)
		osLog(osLogClass_Error,"osSignalWaitToken","����ȴ��ź�������ʱ�ڴ�����ʧ��");
		#endif
		return (Error);
	}else{
		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)osTaskGetRunTaskHandle();
		SemaphoreToken_Buf -> DownAddr = NULL;
	
		NextAddr_Buf = &ST -> NextAddr;
		
		while(*NextAddr_Buf != NULL){
			SemaphoreToken_Buf1 = (_SignalToken*)*NextAddr_Buf;
			TaskInfoTable_Buf = (_TaskHandle*)SemaphoreToken_Buf1 -> TaskInfo;
			if(osTaskGetRunTaskHandle() -> Level < TaskInfoTable_Buf -> Level){
				NextAddr_Buf1 = (_NextAddr)*NextAddr_Buf;
				*NextAddr_Buf = (_NextAddr)SemaphoreToken_Buf;
				SemaphoreToken_Buf -> DownAddr = NextAddr_Buf1;
				if(NextAddr_Buf == &ST -> NextAddr){
					TaskInfoTable_Buf -> Config = Task_State_Up_SI;
					return (OK);
				}
				osTaskSwitchConfig_Config(osTaskGetRunTaskHandle(),Task_State_Up_SI);//�����쳣,���������л� //�޸�Ϊ�źŹ���(�ȴ�̬)
				return (OK);
			}
			NextAddr_Buf = (_NextAddr*)*NextAddr_Buf;
		}
		*NextAddr_Buf = (_NextAddr)SemaphoreToken_Buf;
		osTaskSwitchConfig_Config(osTaskGetRunTaskHandle(),Task_State_Up_SI);//�����쳣,���������л� //�޸�Ϊ�źŹ���(�ȴ�̬)
		return(OK);
	}
}


OsErrorValue osSignalUseWait(_SignalHandle* ST)
{
#if defined osSignalMutual_Config || defined osSignalBinary_Config || defined osSignalCount_Config
	_TaskHandle* TaskHandle;
	_SignalToken* SemaphoreToken_Buf;
	switch(ST -> Type){
#ifdef osSignalBinary_Config 
		case Signal_Binary:	
							if(ST -> NextAddr != NULL){
								return osSignalWaitToken(ST);

							}else{
								return osSignalApplyToken(ST);
							}
#endif
#ifdef osSignalMutual_Config 
		case Signal_Mutual:
							if(ST -> NextAddr != NULL){
								SemaphoreToken_Buf = (_SignalToken*)ST -> NextAddr;
								TaskHandle = (_TaskHandle*)SemaphoreToken_Buf -> TaskInfo;
								if(osTaskGetRunTaskHandle() -> Level < TaskHandle -> Level){
									TaskHandle -> Level = osTaskGetRunTaskHandle() -> Level;//
								}
								return osSignalWaitToken(ST);
							}else{
								return osSignalApplyToken(ST);
							}
#endif
#ifdef osSignalCount_Config
		case Signal_Count:
							if(ST -> Value > 0){
								ST -> Value =  ST -> Value - 1;
								return (OK);	
							}else{
								if(ST -> NextAddr != NULL){
									return osSignalWaitToken(ST);
								}else{
									return osSignalApplyToken(ST);
								}
							}
#endif
		default:
				#if (osSignalLog_Config > 0)
				osLog(osLogClass_Error,"osSignalUseWait","ռ���ź���ʱ����δ֪����");
				#endif
				return(Error);
	}
#endif
}


OsErrorValue osSignalUse(_SignalHandle* ST)
{
	if(ST -> NextAddr != NULL){
		return (Error);

	}else{
		return osSignalApplyToken(ST);
	}
}

/*
 *
 * @��������: osSignalFree
 *
 * @��������: �ͷ��ź���
 *
 * @�������: _SignalHandle* ST(�ź����ṹ��)
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osSignalFree(_SignalHandle* ST)
{
#if defined osSignalMutual_Config || defined osSignalBinary_Config || defined osSignalCount_Config
	_SignalToken* SemaphoreToken_Buf;
	_TaskHandle*	TaskInfoTable_Buf;

	switch(ST -> Type){
#ifdef osSignalBinary_Config
		case Signal_Binary:
							break;
#endif
#ifdef osSignalMutual_Config
		case Signal_Mutual:
							osTaskGetRunTaskHandle() -> Level = osTaskGetRunTaskHandle() -> Levelb;
							break;
#endif
#ifdef osSignalCount_Config
		case Signal_Count:	
							if(ST -> NextAddr == NULL){
								ST -> Value = ST -> Value + 1;
								return (OK);
							}
							break;
#endif
		default:
				#if (osSignalLog_Config > 0)
				osLog(osLogClass_Error,"osSignalFree","�ͷ��ź���ʱ���ʹ���");
				#endif
				return(Error);
	}
	if(ST -> NextAddr != NULL){
		SemaphoreToken_Buf = (_SignalToken*)uLinkListHeadRead(&ST -> NextAddr);
		TaskInfoTable_Buf = (_TaskHandle*)SemaphoreToken_Buf  -> TaskInfo;
		TaskInfoTable_Buf -> Config = Task_State_RE;  //��������(����̬)
		if(osSignalMemoryFree(SemaphoreToken_Buf) != OK){
			#if (osSignalLog_Config > 0)
			osLog(osLogClass_Error,"osSignalFree","�ͷ��ź���ʱ�ͷ��ڴ����");
			#endif
			return (Error);
		}
		if(TaskInfoTable_Buf -> Level < osTaskGetRunTaskHandle() -> Level){
			osTaskSwitch_Config();//�����쳣,���������л�
		}
		return (OK);
	}else{
		#if (osSignalLog_Config > 0)
		osLog(osLogClass_Warn,"osSignalFree","�ͷ��ź���ʱ�Ѿ�Ϊ��");
		#endif
		return (Error);
	}
	#endif
}

/*
 *
 * @��������: osSignalLogout
 *
 * @��������: �ź���ע��
 *
 * @�������: _SignalHandle* ST(�ź����ṹ��)
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osSignalLogout(_SignalHandle* ST)
{
	#if defined osSignalMutual_Config || defined osSignalBinary_Config || defined osSignalCount_Config
	ST -> NextAddr =  ST -> Type =  ST -> Value = 0;
	#if (osSignalAutoApply_Config > 0)//�������ź����Զ�����

	if(osSignalMemoryFree((uint8_t*)ST) == Error){//��Ҫ���ź�������ռ�ڴ��ͷ�
		#if (osSignalLog_Config > 0)
		osLog(osLogClass_Error,"osSignalLogout","ע���ź���ʱ�ͷ��ڴ����");
		#endif
		return (Error);//�ͷ��ڴ�ʱ,��������,���ش���
	}
	return (OK);//ע���ɹ�!����OK
	#endif
	#else 
	return (Error);//ע���ɹ�!����OK
	#endif

}



