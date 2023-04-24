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


#if (osSignal_Config > 0)
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
	_SignalHandle* ST;
	_SignalHandleValue* STV;
	if(SP >= Signal_Mutual && SP <= Signal_OrGroup){
		if(SP >=Signal_Count){
			STV = osSignalMemoryMalloc(sizeof(_SignalHandleValue));//Ϊ�ź����ṹ�������ڴ�
		}else{
			ST = osSignalMemoryMalloc(sizeof(_SignalHandle));//Ϊ�ź����ṹ�������ڴ�
		}
		if(ST == NULL && STV == NULL){//����ڴ����뺯������Ϊ��,˵������ʧ��
			#if (osSignalLog_Config > 0)
			osLogE("osSignalLogin","ע���ź���ʱ�ڴ�����ʧ��\n");
			#endif
			return (NULL);//���ؿ�,��ʾ����
		}
		if(SP >=Signal_Count){
			STV -> Value = 0;//���ź�ֵ��Ϊ��
			STV -> Type = SP;//д���ź�����
			STV -> NextAddr = NULL;
			return (_SignalHandle*)STV;
		}else{
			ST -> Type = SP;//д���ź�����
			ST -> NextAddr = NULL;
			return (ST);
		}
		
	}else{
		#if (osSignalLog_Config > 0)
		osLogE("osSignalLogin","ע���ź���ʱ����δ֪����\n");
		#endif
		return (NULL);
	}
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
#if	(osSignal_Config & Signal_Mutual) 
        case Signal_Mutual://�����ź���
                            ST ->SV = false;//���ź�ֵ��Ϊ��
                            ST ->SP = NULL;//д���ź�����
                            return (OK);
#endif
#if	(osSignal_Config & Signal_Binary)
        case Signal_Binary://��ֵ�ź���
                            ST ->SV = false;//���ź�ֵ��Ϊ��
							ST ->SP = NULL;//д���ź�����
							return (OK);
#endif
#if	(osSignal_Config & Signal_Count)
        case Signal_Count://�����ź���
							ST ->SV = 0;//���ź�ֵ��Ϊ��
                            ST ->SP = NULL;//д���ź�����
                            return (OK);
#endif
        default:
				#if (osSignalLog_Config > 0)
				osLogE("osSignalLogin","ע���ź���ʱ����δ֪����\n");
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
		osLogE("osSignalApplyToken","����ռ���ź�������ʱ�ڴ�����ʧ��\n");
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
		osLogE("osSignalWaitToken","����ȴ��ź�������ʱ�ڴ�����ʧ��\n");
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
	_TaskHandle* TaskHandle;
	_SignalToken* SemaphoreToken_Buf;
	_SignalHandleValue* STV = (_SignalHandleValue*)ST;
	switch(ST -> Type){
#if	(osSignal_Config & Signal_Binary) 
		case Signal_Binary:	
							if(ST -> NextAddr != NULL){
								return osSignalWaitToken(ST);

							}else{
								return osSignalApplyToken(ST);
							}
#endif
#if	(osSignal_Config & Signal_Mutual) 
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
#if	(osSignal_Config & Signal_Count)
		case Signal_Count:
							if(STV -> Value > 0){
								STV -> Value =  STV -> Value - 1;
								return (OK);	
							}else{
								if(STV -> NextAddr != NULL){
									return osSignalWaitToken(ST);
								}else{
									return osSignalApplyToken(ST);
								}
							}
#endif
		default:
				#if (osSignalLog_Config > 0)
				osLogE("osSignalUseWait","ռ���ź���ʱ����δ֪����\n");
				#endif
				return(Error);
	}
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
	_SignalToken* 	SemaphoreToken_Buf;
	_TaskHandle*	TaskInfoTable_Buf;
	_SignalHandleValue* STV = (_SignalHandleValue*)ST;
	switch(ST -> Type){
#if	(osSignal_Config & Signal_Binary)
		case Signal_Binary:
							break;
#endif
#if	(osSignal_Config & Signal_Mutual)
		case Signal_Mutual:
							osTaskGetRunTaskHandle() -> Level = osTaskGetRunTaskHandle() -> Levelb;
							break;
#endif
#if	(osSignal_Config & Signal_Count)
		case Signal_Count:	
							if(STV -> NextAddr == NULL){
								STV -> Value = STV -> Value + 1;
								return (OK);
							}
		case Signal_AndGroup:
		case Signal_OrGroup:
							break;
#endif
		default:
				#if (osSignalLog_Config > 0)
				osLogE("osSignalFree","�ͷ��ź���ʱ���ʹ���\n");
				#endif
				return(Error);
	}
	if(ST -> NextAddr != NULL){
		SemaphoreToken_Buf = (_SignalToken*)uLinkListHeadRead(&ST -> NextAddr);
		TaskInfoTable_Buf = (_TaskHandle*)SemaphoreToken_Buf  -> TaskInfo;
		TaskInfoTable_Buf -> Config = Task_State_RE;  //��������(����̬)
		if(osSignalMemoryFree(SemaphoreToken_Buf) != OK){
			#if (osSignalLog_Config > 0)
			osLogE("osSignalFree","�ͷ��ź���ʱ�ͷ��ڴ����\n");
			#endif
			return (Error);
		}
		if(TaskInfoTable_Buf -> Level < osTaskGetRunTaskHandle() -> Level){
			osTaskSwitch_Config();//�����쳣,���������л�
		}
		return (OK);
	}else{
		#if (osSignalLog_Config > 0)
		osLogW("osSignalFree","�ͷ��ź���ʱ�Ѿ�Ϊ��\n");
		#endif
		return (Error);
	}
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
	ST -> NextAddr =  ST -> Type = 0;
	#if (osSignalAutoApply_Config > 0)//�������ź����Զ�����

	if(osSignalMemoryFree((uint8_t*)ST) == Error){//��Ҫ���ź�������ռ�ڴ��ͷ�
		#if (osSignalLog_Config > 0)
		osLogE("osSignalLogout","ע���ź���ʱ�ͷ��ڴ����\n");
		#endif
		return (Error);//�ͷ��ڴ�ʱ,��������,���ش���
	}
	return (OK);//ע���ɹ�!����OK
	#endif

}
OsErrorValue osSignalSetGroup(_SignalHandle* ST,uint8_t Bits,uint8_t SetBit,uint8_t SetValue)
{
	_SignalHandleValue* STV = (_SignalHandleValue*)ST;
	uint32_t Bit,Precision;
	if(ST -> Type >= Signal_AndGroup && ST -> Type <= Signal_AndGroup){
		Bit = 0x00000001;
		for(Precision = 32 / Bits;Precision > 1;Precision--){
			Bit = (Bit << 1) | 0x01;
		}
		Bit <<= (32 / Bits) * (SetBit - 1);
		if(SetValue){
			STV -> Value |=  Bit;
		}else{
			STV -> Value &= ~Bit;
		}
		switch(STV -> Type){
			case Signal_AndGroup:
				 if(STV -> Value != 0xFFFFFFFF){
					return (OK);
				 }
				 break;
			case Signal_OrGroup:
				 if(STV -> Value == 0x00000000){
					return (OK);
				 }
				 break;
			default:
				break;
			
		}
		STV -> Value = 0x00000000;
		osSignalFree(ST);
		return (OK);

	}else{
		#if (osSignalLog_Config > 0)
		osLogE("osSignalSetAndGroup","δ֪����\n");
		#endif
		return (Error);
	}

}

#endif

