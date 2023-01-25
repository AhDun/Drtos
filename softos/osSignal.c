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
	#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
		SemaphoreTable* ST = osMemoryMalloc(sizeof(SemaphoreTable));//Ϊ�ź����ṹ�������ڴ�
		if(ST == NULL){//����ڴ����뺯������Ϊ��,˵������ʧ��
			return (NULL);//���ؿ�,��ʾ����
		}
		ST -> SV = 0;//���ź�ֵ��Ϊ��
		ST -> ST = SP;//д���ź�����
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
        default:return (Error);//break;
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
		return (Error);
	}else{
		SemaphoreToken_Buf -> DownAddr = NULL;
		SemaphoreToken_Buf -> TaskInfo = (_TaskInfo*)RunTask_TIT;
		ST -> SP = (SemaphoreToken*)SemaphoreToken_Buf;
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
					ST -> SP = (SemaphoreToken*)SemaphoreToken_Buf;
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


osErrorValue osSignalUseWait(SemaphoreTable* ST)
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


static osErrorValue osSignalFreeToken(SemaphoreTable* ST)
{
	SemaphoreToken* SemaphoreToken_Buf;
	TaskInfoTable*	TaskInfoTable_Buf;


	if(ST -> SP != NULL){
		SemaphoreToken_Buf = (SemaphoreToken*)ST -> SP;
		TaskInfoTable_Buf = (TaskInfoTable*)SemaphoreToken_Buf  -> TaskInfo;
		TaskInfoTable_Buf -> TC = Task_State_Up_IN;  //��������(����̬)
		ST -> SP = (SemaphoreToken*)SemaphoreToken_Buf -> DownAddr;
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
	#if defined osSignalMutual_Enable || defined osSignalBinary_Enable || defined osSignalCount_Enable
	#if (osSignalAutoApply_Enable > 0)//�������ź����Զ�����

	if(osMemoryFree((u8*)ST) == Error){//��Ҫ���ź�������ռ�ڴ��ͷ�
		return (Error);//�ͷ��ڴ�ʱ,��������,���ش���
	}
	
	#endif


	ST -> SV = 0;//���ź�ֵ��Ϊ��
	ST -> ST = 0;//д���ź�����
	ST -> SP = 0;
	return (OK);//ע���ɹ�!����OK
	#else 
	return (Error);//ע���ɹ�!����OK
	#endif

}


/*
                                                  FILE-END
*/
