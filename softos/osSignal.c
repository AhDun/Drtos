/*
                                                  FILE-START
*/
/*

 *@�ļ�����: .c

 *@�ļ�����: ϵͳ"�ź���"�ļ�

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע    ��: ��

*/

/*
                                                  <�����ļ���>
*/
#include "osMain.h"
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
	SemaphoreTable* ST = osMemoryMalloc(sizeof(SemaphoreTable));//Ϊ�ź����ṹ�������ڴ�
	if(ST == NULL){//����ڴ����뺯������Ϊ��,˵������ʧ��
		return (NULL);//���ؿ�,��ʾ����
	}
    switch(SP){
#ifdef osSignalMutual_Enable 
        case Signal_Mutual: //�����ź���
                            ST ->SV = false;//���ź�ֵ��Ϊ��
                            ST ->ST = SP;//д���ź�����
							ST -> SP = NULL;
                            return (ST);
#endif
#ifdef osSignalBinary_Enable 
        case Signal_Binary://��ֵ�ź���
                            ST ->SV = false;//���ź�ֵ��Ϊ��
							ST ->ST = SP;//д���ź�����	
							ST -> SP = NULL;
							return (ST);
#endif
#ifdef osSignalCount_Enable
        case Signal_Count://�����ź���
							ST ->SV = 0;//���ź�ֵ��Ϊ��
                            ST ->ST = SP;//д���ź�����
							ST -> SP = NULL;
                            return (ST);
#endif
        default:return (NULL);//break;
    }
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
                            ST ->SP = SP;//д���ź�����
                            return (OK);
#endif
#ifdef osSignalBinary_Enable 
        case Signal_Binary://��ֵ�ź���
                            ST ->SV = false;//���ź�ֵ��Ϊ��
							ST ->SP = SP;//д���ź�����
							return (OK);
#endif
#ifdef osSignalCount_Enable
        case Signal_Count://�����ź���
							ST ->SV = 0;//���ź�ֵ��Ϊ��
                            ST ->SP = SP;//д���ź�����
                            return (OK);
#endif
        default:return (Error);//break;
    }
}
#endif
/*

 *@��������: osSignalWaitPost

 *@�����汾: 1.0.0

 *@��������: ��ȴ������ź�������

 *@�������: SemaphoreTable* ST(�ź����ṹ��)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
osErrorValue osSignalWaitPost(SemaphoreTable* ST)
{
	
//	_uList* uList;
//	TaskInfoTable* TIT;
//	_uList* TuList;
//	TuList = osMemoryMalloc(sizeof(_uList));//Ϊ�ź����ṹ�������ڴ�
//	if(TuList == NULL){
//		return (Error);
//	}else{
//		TuList -> Body = (_Body*)RunTask_TIT;
//		TuList -> DownAddr = NULL;
//		uList = (_uList*)ST -> SP;
//		TIT = (TaskInfoTable*)uList -> Body;
//		do{
//			if(uList -> DownAddr == NULL){
//				uList -> DownAddr = (_NextAddr*)TuList;
//				RunTask_TIT -> TC = Task_State_Up_SI;//�޸�Ϊ�źŹ���(�ȴ�̬)
//				osTaskSwitch_Enable();//�����쳣,���������л�
//				return (OK);
//			}
//			uList = (_uList*)uList -> DownAddr;
//			TIT = (TaskInfoTable*)uList -> Body;
//		}while(RunTask_TIT -> TPL < TIT -> TPL);
//		uLinkListInsert(&ST -> SP,uList,TuList);

//		RunTask_TIT -> TC = Task_State_Up_SI;//�޸�Ϊ�źŹ���(�ȴ�̬)
//		osTaskSwitch_Enable();//�����쳣,���������л�
//		return (OK);
//	}
	return (OK);
}
/*

 *@��������: osSignalApplyPost

 *@�����汾: 1.0.0

 *@��������: ����ȴ������ź�������

 *@�������: SemaphoreTable* ST(�ź����ṹ��)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
osErrorValue osSignalApplyPost(SemaphoreTable* ST)
{
	
	_uList* TuList;
	TuList = osMemoryMalloc(sizeof(_uList));//Ϊ�ź����ṹ�������ڴ�
	if(TuList == NULL){
		return (Error);
	}else{
		TuList -> Body = (_Body*)RunTask_TIT;
		TuList -> DownAddr = NULL;
		ST -> SP = (_SignalPost*)TuList;
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

osErrorValue osSignalApplyToken(SemaphoreTable* ST)
{
	SemaphoreToken* SemaphoreToken_Buf = osMemoryMalloc(sizeof(SemaphoreToken));//Ϊ�ź����ṹ�������ڴ�
	if(SemaphoreToken_Buf == NULL){
		return (Error);
	}else{
		SemaphoreToken_Buf -> DownAddr = NULL;
		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)RunTask_TIT;
		ST -> SP = (_SignalPost*)SemaphoreToken_Buf;
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

osErrorValue osSignalWaitToken(SemaphoreTable* ST)
{
	SemaphoreToken* SemaphoreToken_Buf1;
	SemaphoreToken* SemaphoreToken_Buf2;
	TaskInfoTable*	TaskInfoTable_Buf;
	SemaphoreToken* SemaphoreToken_Buf = osMemoryMalloc(sizeof(SemaphoreToken));//Ϊ�ź����ṹ�������ڴ�
	if(SemaphoreToken_Buf == NULL){
		return (Error);
	}else{

		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)RunTask_TIT;
		SemaphoreToken_Buf -> DownAddr = NULL;

		SemaphoreToken_Buf1 = (SemaphoreToken*)ST -> SP;
		SemaphoreToken_Buf2 = NULL;
		while(1){
			if(SemaphoreToken_Buf1 -> DownAddr == NULL){
				SemaphoreToken_Buf1 -> DownAddr = (_NextAddr*)SemaphoreToken_Buf;
				RunTask_TIT -> TC = Task_State_Up_SI;  //�޸�Ϊ�źŹ���(�ȴ�̬)
				osTaskSwitch_Enable();//�����쳣,���������л�
				return (OK);
			}
			TaskInfoTable_Buf = (TaskInfoTable*)SemaphoreToken_Buf1 -> TaskInfo;
			if(RunTask_TIT -> TPL < TaskInfoTable_Buf -> TPL){
				if(SemaphoreToken_Buf2 == NULL){
					SemaphoreToken_Buf -> DownAddr = (_NextAddr*)ST -> SP;
					ST -> SP = (_SignalPost*)SemaphoreToken_Buf;
				}else{
					SemaphoreToken_Buf -> DownAddr = (_NextAddr*)SemaphoreToken_Buf1;
					SemaphoreToken_Buf2 -> DownAddr = (_NextAddr*)SemaphoreToken_Buf;
				}
				RunTask_TIT -> TC = Task_State_Up_SI;  //�޸�Ϊ�źŹ���(�ȴ�̬)
				osTaskSwitch_Enable();//�����쳣,���������л�
				return (OK);
			}else{
				SemaphoreToken_Buf2 = SemaphoreToken_Buf1;
				SemaphoreToken_Buf1 = (SemaphoreToken*)SemaphoreToken_Buf1 -> DownAddr;
			}
		}
	}
}


osErrorValue osSignalApply_Wait(SemaphoreTable* ST)
{
	TaskInfoTable* TIT;
	_uList* uList;
	switch(ST ->ST){
		case Signal_Binary:	
							if(ST -> SP != NULL){
								return osSignalWaitToken(ST);

							}else{
								return osSignalApplyToken(ST);
							}
		case Signal_Mutual:
							if(ST -> SP != NULL){
								uList = (_uList*)ST -> SP;
								TIT = (TaskInfoTable*)uList -> Body;
								if(RunTask_TIT -> TPL < TIT -> TPL){
									TIT -> TPL = RunTask_TIT -> TPL;//
								}
								return osSignalWaitToken(ST);
							}else{
								return osSignalApplyToken(ST);
							}
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
		default:return(Error);
	}
}

/*

 *@��������: osSignalFreePost

 *@�����汾: 1.0.0

 *@��������: �ͷ��ź�������

 *@�������: SemaphoreTable* ST(�ź����ṹ��)

 *@�� �� ֵ: ��

 *@ע    ��: ��

*/
osErrorValue osSignalFreePost(SemaphoreTable* ST)
{
	TaskInfoTable* TIT;
	_uList* uList;
	_SignalPost* SignalPost;
	if(ST -> SP != NULL){
		uList = (_uList*)ST -> SP;
		SignalPost = (_SignalPost*) uList -> DownAddr;
		if(osMemoryFree((u8*)ST -> SP) == Error){
			return (Error);
		}else{
			ST -> SP = SignalPost;
			if(ST -> SP != NULL){
				uList = (_uList*)ST -> SP;
				TIT = (TaskInfoTable*)uList -> Body;
				if(RunTask_TIT -> TPL > TIT ->TPL){
					TST. TDN = TIT -> TI;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
					TIT -> TC = Task_State_Up_IN;  //��������(����̬)
					osTaskSwitch_Enable();//�����쳣,���������л�
				}else{
					TIT -> TC = Task_State_Up_IN;  //��������(����̬)
				}
			}
			else{
				return (OK);
			}
			return (OK);
		}
	}else{
		return (OK);
	}
}

osErrorValue osSignalFreeToken(SemaphoreTable* ST)
{
	SemaphoreToken* SemaphoreToken_Buf;
	TaskInfoTable*	TaskInfoTable_Buf;


	if(ST -> SP != NULL){
		SemaphoreToken_Buf = (SemaphoreToken*)ST -> SP;
		TaskInfoTable_Buf = (TaskInfoTable*)SemaphoreToken_Buf  -> TaskInfo;
		TaskInfoTable_Buf -> TC = Task_State_Up_IN;  //��������(����̬)
		ST -> SP = (_SignalPost*)SemaphoreToken_Buf -> DownAddr;
		if(osMemoryFree(SemaphoreToken_Buf) != OK){
			return (Error);
		}
		if(TaskInfoTable_Buf -> TPL < RunTask_TIT -> TPL){
			osTaskSwitch_Enable();//�����쳣,���������л�
		}
		return (OK);
	}else{
		return (Error);
	}

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
	switch(ST ->ST){
		case Signal_Binary:
							return osSignalFreeToken(ST);
		case Signal_Mutual:
							RunTask_TIT -> TPL = RunTask_TIT -> TPLb;
							return osSignalFreeToken(ST);
		case Signal_Count:
							ST -> SV = ST -> SV + 1;
							return osSignalFreeToken(ST);
		default:return(Error);
	}
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

#if (osSignalAutoApply_Enable > 0)//�������ź����Զ�����

	if(osMemoryFree((u8*)ST) == Error){//��Ҫ���ź�������ռ�ڴ��ͷ�
		return (Error);//�ͷ��ڴ�ʱ,��������,���ش���
	}

#endif
	switch(ST -> ST){
#ifdef osSignalMutual_Enable
		case Signal_Mutual://�����ź���
#endif
#ifdef osSignalBinary_Enable 
		case Signal_Binary://��ֵ�ź���
#endif
#ifdef osSignalCount_Enable
		case Signal_Count://�����ź���
						ST -> ST = Signal_Logout;//��Ϊ��Ч�ź���
						break;
#endif
		default: return(Error);//�Ҳ�����ǰ�ź�����������,���ش���
	}
	return (OK);//ע���ɹ�!����OK

}


/*
                                                  FILE-END
*/
