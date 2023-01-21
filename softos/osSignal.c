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
	
	_uList* uList;
	TaskInfoTable* TIT;
	_uList* TuList;
	TuList = osMemoryMalloc(sizeof(_uList));//Ϊ�ź����ṹ�������ڴ�
	if(TuList == NULL){
		return (Error);
	}else{
		TuList -> Body = (_Body*)RunTask_TIT;
		TuList -> DownAddr = NULL;
		uList = (_uList*)ST -> SP;
		TIT = (TaskInfoTable*)uList -> Body;
		do{
			if(uList -> DownAddr == NULL){
				uList -> DownAddr = (_NextAddr*)TuList;
				RunTask_TIT -> TC = Task_State_Up_SI;//�޸�Ϊ�źŹ���(�ȴ�̬)
				osTaskSwitch_Enable();//�����쳣,���������л�
				return (OK);
			}
			uList = (_uList*)uList -> DownAddr;
			TIT = (TaskInfoTable*)uList -> Body;
		}while(RunTask_TIT -> TPL < TIT -> TPL);
		uLinkListInsert(&ST -> SP,uList,TuList);

		RunTask_TIT -> TC = Task_State_Up_SI;//�޸�Ϊ�źŹ���(�ȴ�̬)
		osTaskSwitch_Enable();//�����쳣,���������л�
		return (OK);
	}
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

osErrorValue osSignalApply_Wait(SemaphoreTable* ST)
{
	TaskInfoTable* TIT;
	_uList* uList;
	switch(ST ->ST){
		case Signal_Binary:	
							if(ST -> SP != NULL){
								return osSignalWaitPost(ST);

							}else{
								return osSignalApplyPost(ST);
							}
		case Signal_Mutual:
							if(ST -> SP != NULL){
								uList = (_uList*)ST -> SP;
								TIT = (TaskInfoTable*)uList -> Body;
								if(RunTask_TIT -> TPL < TIT -> TPL){
									TIT -> TPL = RunTask_TIT -> TPL;//
									return osSignalWaitPost(ST);
								}else{
									return osSignalWaitPost(ST);
								}
							}else{
								return osSignalApplyPost(ST);
							}
		case Signal_Count:
							if(ST -> SV > 0){
								ST -> SV =  ST -> SV - 1;
								return (OK);	
							}else{
								if(ST -> SP != NULL){
									return osSignalWaitPost(ST);
								}else{
									return osSignalApplyPost(ST);
								}
							}
		default:return(Error);
	}
}


/*
osErrorValue osSignalApply_Wait(SemaphoreTable* ST)
{
	 switch(ST ->SP){
#ifdef osSignalMutual_Enable 
        case Signal_Mutual://�����ź��� 
							if(ST -> SV == false){
								if(RunTask_TIT -> TPL < TL[ST -> OTID].TITA -> TPL && ST -> OTID < (_TaskIDMax + 1)){
									TL[ST -> OTID].TITA -> TPL = RunTask_TIT -> TPL;//��ʱ������ȼ�
								}
                                while(TST.TSS != TaskSwitch_Ready);//��ѯ������л�̬,����ǲ����л�,����ѭ��,ֱ�����л�̬
                                //RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//�����״̬λ��λ
                                RunTask_TIT -> TC = Task_State_Up_SI;//�޸�Ϊ�źŹ���(�ȴ�̬)
                                RunTask_TIT -> TS =  &ST->SV;
                                osTaskSwitch_Enable();//�����쳣,���������л�
                            }
							ST -> OTID = RunTask_TIT -> TI;
							ST -> SV = false;
                            return (OK);//����ɹ�!����OK
#endif
#ifdef osSignalBinary_Enable                            
        case Signal_Binary://��ֵ�ź���
                            if(ST -> SV == false){
                                while(TST.TSS != TaskSwitch_Ready);//��ѯ������л�̬,����ǲ����л�,����ѭ��,ֱ�����л�̬
                                //RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//�����״̬λ��λ
                                RunTask_TIT -> TC = Task_State_Up_SI;//�޸�Ϊ�źŹ���(�ȴ�̬)
                                RunTask_TIT -> TS =  &ST->SV;
                                osTaskSwitch_Enable();//�����쳣,���������л�
                            }
							ST -> SV = false;
                            return (OK);//����ɹ�!����OK
                            
#endif
#ifdef osSignalCount_Enable
        case Signal_Count://�����ź���
                           if(ST -> SV == 0){
                                while(TST.TSS != TaskSwitch_Ready);//��ѯ������л�̬,����ǲ����л�,����ѭ��,ֱ�����л�̬
                                //RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//�����״̬λ��λ
                                RunTask_TIT -> TC = Task_State_Up_SI;//�޸�Ϊ�źŹ���(�ȴ�̬)
                                RunTask_TIT -> TS =  &ST->SV;
                                osTaskSwitch_Enable();//�����쳣,���������л�
                            }
							if(ST -> SV > 0){
								ST -> SV = ST -> SV - 1;
							}
                            return (OK);//����ɹ�!����OK
#endif
		case Signal_Logout://��Ч�ź���
							return (OK);
        default:return (Error);//�ź���������,��������,���ش���
    }
}
*/
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
							return osSignalFreePost(ST);
		case Signal_Mutual:
							RunTask_TIT -> TPL = RunTask_TIT -> TPLb;
							return osSignalFreePost(ST);
		case Signal_Count:
							ST -> SV = ST -> SV + 1;
							return osSignalFreePost(ST);
		default:return(Error);
	}
}
/*
osErrorValue osSignalFree(SemaphoreTable* ST)
{
	switch(ST ->ST){
#ifdef osSignalMutual_Enable 
        case Signal_Mutual://�����ź���
							if(ST -> SV == false){
								RunTask_TIT -> TPL = RunTask_TIT -> TPLb;//����ǰ�������е�����ĸ����ȼ����ص������ȼ���
								ST -> SV = true;//���ź�ֵΪ��Чֵ
								ST -> OTID = _TaskIDMax + 1;//��Ϊ����̬
								return (OK);//�ͷųɹ�,����OK
							}
							else{
								return (Error);//�������� 
							}
#endif
#ifdef osSignalBinary_Enable                            
        case Signal_Binary://��ֵ�ź���
							if(ST -> SV == false){
								ST -> SV = true;//���ź�ֵΪ��Чֵ
								return (OK);//�ͷųɹ�,����OK
							}
							else{
								return (Error);//��������
							}
                            
#endif
#ifdef osSignalCount_Enable
        case Signal_Count://�����ź���
							ST -> SV = ST -> SV + 1;//
                            return (OK);//�ͷųɹ�,����OK
#endif
        default:return (Error);//�ź���������,��������,���ش���
    }
}
*/
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
