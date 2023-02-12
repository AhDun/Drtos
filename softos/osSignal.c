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
#if (osSignalAutoApply_Enable > 0)//�������ź����Զ�����
_Signal* osSignalLogin(_SignalType SP)
{
	#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
		_Signal* ST = osMemoryMalloc(sizeof(_Signal));//Ϊ�ź����ṹ�������ڴ�
		if(ST == NULL){//����ڴ����뺯������Ϊ��,˵������ʧ��
			#if (osSignalDebugError_Enable > 0)
			osSignalDebugError("ע���ź���ʱ�ڴ�����ʧ�� %s\n",osTaskGetRunTaskHandle() -> Name);
			#endif
			return (NULL);//���ؿ�,��ʾ����
		}
		ST -> Value = 0;//���ź�ֵ��Ϊ��
		if(SP == Signal_Mutual || SP == Signal_Binary || SP == Signal_Count){
			ST -> Type = SP;//д���ź�����
		}else{
			#if (osSignalDebugError_Enable > 0)
			osSignalDebugError("ע���ź���ʱ���ʹ��� %s\n",osTaskGetRunTaskHandle() -> Name);
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
OsErrorValue osSignalLogin(_Signal* ST,_SignalType SP)
{
    switch(SP){
#ifdef osSignalMutual_Enable 
        case Signal_Mutual://�����ź���
                            ST ->SV = false;//���ź�ֵ��Ϊ��
                            ST ->SP = NULL;//д���ź�����
                            return (OK);
#endif
#ifdef osSignalBinary_Enable 
        case Signal_Binary://��ֵ�ź���
                            ST ->SV = false;//���ź�ֵ��Ϊ��
							ST ->SP = NULL;//д���ź�����
							return (OK);
#endif
#ifdef osSignalCount_Enable
        case Signal_Count://�����ź���
							ST ->SV = 0;//���ź�ֵ��Ϊ��
                            ST ->SP = NULL;//д���ź�����
                            return (OK);
#endif
        default:
				#if (osSignalDebugError_Enable > 0)
				osSignalDebugError("ע���ź���ʱ���ʹ��� %s\n",osTaskGetRunTaskHandle() -> Name);
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
 * @�������: _Signal* ST(�ź����ṹ��)
 *
 * @�� �� ֵ: -1:�������� / 0:����ɹ�
 *
 * @ע    ��: ��
 *
 */

static OsErrorValue osSignalApplyToken(_Signal* ST)
{
	_SignalToken* SemaphoreToken_Buf = osMemoryMalloc(sizeof(_SignalToken));//Ϊ�ź����ṹ�������ڴ�
	if(SemaphoreToken_Buf == NULL){
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("����ռ���ź�������ʱ�ڴ�����ʧ�� %s\n",osTaskGetRunTaskHandle() -> Name);
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
 * @�������: _Signal* ST(�ź����ṹ��)
 *
 * @�� �� ֵ: -1:�������� / 0:����ɹ�
 *
 * @ע    ��: ��
 *
 */

static OsErrorValue osSignalWaitToken(_Signal* ST)
{
	_NextAddr* NextAddr_Buf;
	_NextAddr NextAddr_Buf1;
	_SignalToken* SemaphoreToken_Buf1;
	_TaskHandle*	TaskInfoTable_Buf;
	_SignalToken* SemaphoreToken_Buf = osMemoryMalloc(sizeof(_SignalToken));//Ϊ�ź����ṹ�������ڴ�
	if(SemaphoreToken_Buf == NULL){
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("����ȴ��ź�������ʱ�ڴ�����ʧ�� %s\n",osTaskGetRunTaskHandle() -> Name);
		#endif
		return (Error);
	}else{
		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)osTaskGetRunTaskHandle();
		SemaphoreToken_Buf -> DownAddr = NULL;
	
		NextAddr_Buf = &ST -> NextAddr;
		
		while(*NextAddr_Buf != NULL){
			SemaphoreToken_Buf1 = (_SignalToken*)*NextAddr_Buf;
			TaskInfoTable_Buf = (_TaskHandle*)SemaphoreToken_Buf1 -> TaskInfo;
			if(osTaskGetRunTaskHandle() -> PriorityLevel < TaskInfoTable_Buf -> PriorityLevel){
				NextAddr_Buf1 = (_NextAddr)*NextAddr_Buf;
				*NextAddr_Buf = (_NextAddr)SemaphoreToken_Buf;
				SemaphoreToken_Buf -> DownAddr = NextAddr_Buf1;
				if(NextAddr_Buf == &ST -> NextAddr){
					TaskInfoTable_Buf -> Config = Task_State_Up_SI;
					return (OK);
				}
				osTaskSwitchConfig_Enable(osTaskGetRunTaskHandle(),Task_State_Up_SI);//�����쳣,���������л� //�޸�Ϊ�źŹ���(�ȴ�̬)
				return (OK);
			}
			NextAddr_Buf = (_NextAddr*)*NextAddr_Buf;
		}
		*NextAddr_Buf = (_NextAddr)SemaphoreToken_Buf;
		osTaskSwitchConfig_Enable(osTaskGetRunTaskHandle(),Task_State_Up_SI);//�����쳣,���������л� //�޸�Ϊ�źŹ���(�ȴ�̬)
		return(OK);
	}
}


OsErrorValue osSignalUseWait(_Signal* ST)
{
#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
	_TaskHandle* TaskHandle;
	_SignalToken* SemaphoreToken_Buf;
	switch(ST -> Type){
#ifdef osSignalBinary_Enable 
		case Signal_Binary:	
							if(ST -> NextAddr != NULL){
								return osSignalWaitToken(ST);

							}else{
								return osSignalApplyToken(ST);
							}
#endif
#ifdef osSignalMutual_Enable 
		case Signal_Mutual:
							if(ST -> NextAddr != NULL){
								SemaphoreToken_Buf = (_SignalToken*)ST -> NextAddr;
								TaskHandle = (_TaskHandle*)SemaphoreToken_Buf -> TaskInfo;
								if(osTaskGetRunTaskHandle() -> PriorityLevel < TaskHandle -> PriorityLevel){
									TaskHandle -> PriorityLevel = osTaskGetRunTaskHandle() -> PriorityLevel;//
								}
								return osSignalWaitToken(ST);
							}else{
								return osSignalApplyToken(ST);
							}
#endif
#ifdef osSignalCount_Enable
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
				#if (osSignalDebugError_Enable > 0)
				osSignalDebugError("ռ���ź���ʱ�������ʹ��� %s\n",osTaskGetRunTaskHandle() -> Name);
				#endif
				return(Error);
	}
#endif
}

/*
 *
 * @��������: osSignalFree
 *
 * @��������: �ͷ��ź���
 *
 * @�������: _Signal* ST(�ź����ṹ��)
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osSignalFree(_Signal* ST)
{
#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
	_SignalToken* SemaphoreToken_Buf;
	_TaskHandle*	TaskInfoTable_Buf;

	switch(ST -> Type){
#ifdef osSignalBinary_Enable
		case Signal_Binary:
							break;
#endif
#ifdef osSignalMutual_Enable
		case Signal_Mutual:
							osTaskGetRunTaskHandle() -> PriorityLevel = osTaskGetRunTaskHandle() -> PriorityLevelb;
							break;
#endif
#ifdef osSignalCount_Enable
		case Signal_Count:	
							if(ST -> NextAddr == NULL){
								ST -> Value = ST -> Value + 1;
								return (OK);
							}
							break;
#endif
		default:
				#if (osSignalDebugError_Enable > 0)
				osSignalDebugError("�ͷ��ź���ʱ���ʹ��� %s\n",osTaskGetRunTaskHandle() -> Name);
				#endif
				return(Error);
	}
	if(ST -> NextAddr != NULL){
		SemaphoreToken_Buf = (_SignalToken*)uLinkListHeadRead(&ST -> NextAddr);
		TaskInfoTable_Buf = (_TaskHandle*)SemaphoreToken_Buf  -> TaskInfo;
		TaskInfoTable_Buf -> Config = Task_State_Up_IN;  //��������(����̬)
		if(osMemoryFree(SemaphoreToken_Buf) != OK){
			#if (osSignalDebugError_Enable > 0)
			osSignalDebugError("�ͷ��ź���ʱ�ͷ��ڴ���� %s\n",osTaskGetRunTaskHandle() -> Name);
			#endif
			return (Error);
		}
		if(TaskInfoTable_Buf -> PriorityLevel < osTaskGetRunTaskHandle() -> PriorityLevel){
			osTaskSwitch_Enable();//�����쳣,���������л�
		}
		return (OK);
	}else{
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("�ͷ��ź���ʱ�Ѿ�Ϊ�� %s\n",osTaskGetRunTaskHandle() -> Name);
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
 * @�������: _Signal* ST(�ź����ṹ��)
 *
 * @�� �� ֵ: ��
 *
 * @ע    ��: ��
 *
 */
OsErrorValue osSignalLogout(_Signal* ST)
{
	#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
	ST -> NextAddr =  ST -> Type =  ST -> Value = 0;
	#if (osSignalAutoApply_Enable > 0)//�������ź����Զ�����

	if(osMemoryFree((uint8_t*)ST) == Error){//��Ҫ���ź�������ռ�ڴ��ͷ�
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("ע���ź���ʱ�ͷ��ڴ���� %s\n",osTaskGetRunTaskHandle() -> Name);
		#endif
		return (Error);//�ͷ��ڴ�ʱ,��������,���ش���
	}
	return (OK);//ע���ɹ�!����OK
	#endif
	#else 
	return (Error);//ע���ɹ�!����OK
	#endif

}



