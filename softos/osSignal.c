/*
                                                  FILE-START
*/
/*

 *@�ļ�����: .c

 *@�ļ�����: ϵͳ"�ź���"�ļ�

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@ע    ��: ��

*/

/*
                                                  <�����ļ���>
*/
#include "osConfig.h"
#include "osSignal.h"
/*

 @ͷ�ļ�����: ��

 @ͷ�ļ�����: ��

 @ע      ��: ��

*/

/*
                                                  <���ݳ�ʼ��>
*/
/*

 @��������: ��

 @��������: ��

 *@ע    ��: ��

*/
/*
                                                  <������>
*/

/*

 *@��������: osSignalRegister

 *@�����汾: 1.0.0

 *@��������: ע���ź���

 *@�������: _SemaphoreType SP(�ź���������)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
#if (osSignalAutoApply_Enable > 0)//�������ź����Զ�����
SemaphoreTable* osSignalLogin(_SemaphoreType SP)
{
	#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
		SemaphoreTable* ST = osMemoryMalloc(sizeof(SemaphoreTable));//Ϊ�ź����ṹ�������ڴ�
		if(ST == NULL){//����ڴ����뺯������Ϊ��,˵������ʧ��
			#if (osSignalDebugError_Enable > 0)
			osSignalDebugError("ע���ź���ʱ�ڴ�����ʧ�� %s\n",RunTaskHandle -> Name);
			#endif
			return (NULL);//���ؿ�,��ʾ����
		}
		ST -> SV = 0;//���ź�ֵ��Ϊ��
		if(SP == Signal_Mutual || SP == Signal_Binary || SP == Signal_Count){
			ST -> ST = SP;//д���ź�����
		}else{
			#if (osSignalDebugError_Enable > 0)
			osSignalDebugError("ע���ź���ʱ���ʹ��� %s\n",RunTaskHandle -> Name);
			#endif
			return (NULL);
		}
		ST -> SP = NULL;
		return (ST);
	#else
		return (NULL);
	#endif 
}
#else
/*

 *@��������: osSignalRegister

 *@�����汾: 1.0.0

 *@��������: ע���ź���

 *@�������: ��

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
osErrorValue osSignalLogin(SemaphoreTable* ST,_SemaphoreType SP)
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
				osSignalDebugError("ע���ź���ʱ���ʹ��� %s\n",RunTaskHandle -> Name);
				#endif
				return (Error);//break;
    }
}
#endif

/*

 *@��������: osSignalApply_Wait

 *@�����汾: 1.0.0

 *@��������: �ź�������

 *@�������: SemaphoreTable* ST(�ź����ṹ��)

 *@�� �� ֵ: -1:�������� / 0:����ɹ�

 *@ע    ��: ��

*/

static osErrorValue osSignalApplyToken(SemaphoreTable* ST)
{
	SemaphoreToken* SemaphoreToken_Buf = osMemoryMalloc(sizeof(SemaphoreToken));//Ϊ�ź����ṹ�������ڴ�
	if(SemaphoreToken_Buf == NULL){
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("����ռ���ź�������ʱ�ڴ�����ʧ�� %s\n",RunTaskHandle -> Name);
		#endif
		return (Error);
	}else{
		SemaphoreToken_Buf -> DownAddr = NULL;
		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)RunTaskHandle;
		ST -> SP = (uint32_t)SemaphoreToken_Buf;
		return (OK);
	}
}


/*

 *@��������: osSignalApply_Wait

 *@�����汾: 1.0.0

 *@��������: �ź�������

 *@�������: SemaphoreTable* ST(�ź����ṹ��)

 *@�� �� ֵ: -1:�������� / 0:����ɹ�

 *@ע    ��: ��

*/

static osErrorValue osSignalWaitToken(SemaphoreTable* ST)
{
	_NextAddr* NextAddr_Buf;
	_NextAddr NextAddr_Buf1;
	SemaphoreToken* SemaphoreToken_Buf1;
	_TaskHandle*	TaskInfoTable_Buf;
	SemaphoreToken* SemaphoreToken_Buf = osMemoryMalloc(sizeof(SemaphoreToken));//Ϊ�ź����ṹ�������ڴ�
	if(SemaphoreToken_Buf == NULL){
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("����ȴ��ź�������ʱ�ڴ�����ʧ�� %s\n",RunTaskHandle -> Name);
		#endif
		return (Error);
	}else{
		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)RunTaskHandle;
		SemaphoreToken_Buf -> DownAddr = NULL;
	
		NextAddr_Buf = &ST -> SP;
		
		while(*NextAddr_Buf != NULL){
			SemaphoreToken_Buf1 = (SemaphoreToken*)*NextAddr_Buf;
			TaskInfoTable_Buf = (_TaskHandle*)SemaphoreToken_Buf1 -> TaskInfo;
			if(RunTaskHandle -> PriorityLevel < TaskInfoTable_Buf -> PriorityLevel){
				NextAddr_Buf1 = (_NextAddr)*NextAddr_Buf;
				*NextAddr_Buf = (_NextAddr)SemaphoreToken_Buf;
				SemaphoreToken_Buf -> DownAddr = NextAddr_Buf1;
				if(NextAddr_Buf == &ST -> SP){
					TaskInfoTable_Buf -> Config = Task_State_Up_SI;
					return (OK);
				}
				RunTaskHandle -> Config = Task_State_Up_SI;  //�޸�Ϊ�źŹ���(�ȴ�̬)
				osTaskSwitch_Enable();//�����쳣,���������л�
				return (OK);
			}
			NextAddr_Buf = (_NextAddr*)*NextAddr_Buf;
		}
		*NextAddr_Buf = (_NextAddr)SemaphoreToken_Buf;
		RunTaskHandle -> Config = Task_State_Up_SI;  //�޸�Ϊ�źŹ���(�ȴ�̬)
		osTaskSwitch_Enable();//�����쳣,���������л�
		return(OK);
	}
}


osErrorValue osSignalUseWait(SemaphoreTable* ST)
{
#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
	_TaskHandle* TaskHandle;
	SemaphoreToken* SemaphoreToken_Buf;
	switch(ST ->ST){
#ifdef osSignalBinary_Enable 
		case Signal_Binary:	
							if(ST -> SP != NULL){
								return osSignalWaitToken(ST);

							}else{
								return osSignalApplyToken(ST);
							}
#endif
#ifdef osSignalMutual_Enable 
		case Signal_Mutual:
							if(ST -> SP != NULL){
								SemaphoreToken_Buf = (SemaphoreToken*)ST -> SP;
								TaskHandle = (_TaskHandle*)SemaphoreToken_Buf -> TaskInfo;
								if(RunTaskHandle -> PriorityLevel < TaskHandle -> PriorityLevel){
									TaskHandle -> PriorityLevel = RunTaskHandle -> PriorityLevel;//
								}
								return osSignalWaitToken(ST);
							}else{
								return osSignalApplyToken(ST);
							}
#endif
#ifdef osSignalCount_Enable
		case Signal_Count:
							if(ST -> SV > 0){
								ST -> SV =  ST -> SV - 1;
								return (OK);	
							}else{
								if(ST -> SP != NULL){
									return osSignalWaitToken(ST);
								}else{
									return osSignalApplyToken(ST);
								}
							}
#endif
		default:
				#if (osSignalDebugError_Enable > 0)
				osSignalDebugError("ռ���ź���ʱ�������ʹ��� %s\n",RunTaskHandle -> Name);
				#endif
				return(Error);
	}
#endif
}

/*

 *@��������: osSignalFree

 *@�����汾: 1.0.0

 *@��������: �ͷ��ź���

 *@�������: SemaphoreTable* ST(�ź����ṹ��)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
osErrorValue osSignalFree(SemaphoreTable* ST)
{
#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
	SemaphoreToken* SemaphoreToken_Buf;
	_TaskHandle*	TaskInfoTable_Buf;

	switch(ST ->ST){
#ifdef osSignalBinary_Enable
		case Signal_Binary:
							break;
#endif
#ifdef osSignalMutual_Enable
		case Signal_Mutual:
							RunTaskHandle -> PriorityLevel = RunTaskHandle -> PriorityLevelb;
							break;
#endif
#ifdef osSignalCount_Enable
		case Signal_Count:
							ST -> SV = ST -> SV + 1;
							break;
#endif
		default:
				#if (osSignalDebugError_Enable > 0)
				osSignalDebugError("�ͷ��ź���ʱ���ʹ��� %s\n",RunTaskHandle -> Name);
				#endif
				return(Error);
	}
	if(ST -> SP != NULL){
		SemaphoreToken_Buf = (SemaphoreToken*)uLinkListHeadRead(&ST -> SP);
		TaskInfoTable_Buf = (_TaskHandle*)SemaphoreToken_Buf  -> TaskInfo;
		TaskInfoTable_Buf -> Config = Task_State_Up_IN;  //��������(����̬)
		if(osMemoryFree(SemaphoreToken_Buf) != OK){
			#if (osSignalDebugError_Enable > 0)
			osSignalDebugError("�ͷ��ź���ʱ�ͷ��ڴ���� %s\n",RunTaskHandle -> Name);
			#endif
			return (Error);
		}
		if(TaskInfoTable_Buf -> PriorityLevel < RunTaskHandle -> PriorityLevel){
			osTaskSwitch_Enable();//�����쳣,���������л�
		}
		return (OK);
	}else{
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("�ͷ��ź���ʱ�Ѿ�Ϊ�� %s\n",RunTaskHandle -> Name);
		#endif
		return (Error);
	}
	#endif
}

/*

 *@��������: osSignalLogout

 *@�����汾: 1.0.0

 *@��������: �ź���ע��

 *@�������: SemaphoreTable* ST(�ź����ṹ��)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
osErrorValue osSignalLogout(SemaphoreTable* ST)
{
	#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
	ST -> SV = 0;//���ź�ֵ��Ϊ��
	ST -> ST = 0;//д���ź�����
	ST -> SP = 0;
	#if (osSignalAutoApply_Enable > 0)//�������ź����Զ�����

	if(osMemoryFree((uint8_t*)ST) == Error){//��Ҫ���ź�������ռ�ڴ��ͷ�
		#if (osSignalDebugError_Enable > 0)
		osSignalDebugError("ע���ź���ʱ�ͷ��ڴ���� %s\n",RunTaskHandle -> Name);
		#endif
		return (Error);//�ͷ��ڴ�ʱ,��������,���ش���
	}
	return (OK);//ע���ɹ�!����OK
	#endif
	#else 
	return (Error);//ע���ɹ�!����OK
	#endif

}


/*
                                                  FILE-END
*/
