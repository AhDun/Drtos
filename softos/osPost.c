/*
                                                  FILE-START
*/
/*

 *@�ļ�����: osPost.c

 *@�ļ�����: ϵͳ"����������"�ļ�

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@ע    ��: ��

*/

/*
                                                  <�����ļ���>
*/
#include "osPost.h"

/*
                                                  <���ݳ�ʼ��>
*/
/*
                                                  <������>
*/



/*

 *@��������: osPostSend

 *@�����汾: 1.0.0

 *@��������: �����ʼ�

 *@�������: ��

 *@�� �� ֵ: -1:�������� / 0:���ͳɹ�

 *@ע   ��: ��

*/
osErrorValue osPostSend(void* PB,TaskInfoTable* TIT)
{
	PostForm* PF;

	if(TIT -> TI >= TST.TLMA){//���д������ID���ܴ���������,���򷵻ش���
		return (Error);//���ִ���,����Error
	}else{
		PF = osMemoryMalloc(sizeof(PostForm));//�����ڴ�
		if(PF == NULL){//�������Ϊ��,˵������ʧ��
			#if (osPostDebugError_Enable > 0)
			osPostDebugError("�����ʼ�ʱ�����ڴ�ʧ�� %s\n",RunTask_TIT -> TN);
			#endif
			return (Error);//���ش���
		}else{
			PF -> PB = PB;
			PF -> DownAddr = NULL;

			uLinkListAdd(&TIT -> PF,&PF -> DownAddr);
		}
		if(TIT -> TPL <  RunTask_TIT -> TPL && TIT -> TC == Task_State_Up_PT){//������������ڵ�ǰ�������������������ȼ�����ռ��
			//TL[_tr0].TITA -> TC &= TIT_Task_State_TC_RST;//�����������״̬λ
			TIT -> TC = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
			//RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//����������������״̬λ
			RunTask_TIT -> TC = Task_State_Up_TD;//���������������״̬��Ϊ��Ƭ����(����̬)
			if(TST.TSS == TaskSwitch_Ready){
				TST. TDN = TIT -> TI;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
				osTaskSwitch_Enable();//���������л�
			} 
		}else if(TIT -> TC == Task_State_Up_PT){
			TIT -> TC = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
		}
	}
	//TIT -> TC = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
	return (OK);//���ͳɹ�������OK
}


/*

 *@��������: osPostRead

 *@�����汾: 1.0.0

 *@��������: ��ȡ�ʼ�

 *@�������: uint8_t* ResiduePost(����ָ��)

 *@�� �� ֵ: �ʼ�����

 *@ע   ��: ��

*/
uint32_t* osPostRead(void)
{
	PostForm* PF;
	uint32_t*	Buf;

	if(RunTask_TIT -> PF != NULL){
		#if (osPostHead > 0)
		PF = (PostForm*)RunTask_TIT -> PF;
		Buf = PF -> PB;
		RunTask_TIT -> PF = PF -> DownAddr;
		#else
		PF  =  uLinkListReadEndAndRemvoe(&RunTask_TIT -> PF);
		Buf = PF -> PB;
		#endif
		if(osMemoryFree(PF) == Error){
			#if (osPostDebugError_Enable > 0)
			osPostDebugError("��ȡ�ʼ�ʱ�ͷ��ڴ�ʧ�� %s\n",RunTask_TIT -> TN);
			#endif
			return (Buf);
		}
		return (Buf);
		
	}else{
		return (NULL);//û���ʼ������ؿ�
	}
}
/*

 *@��������: osPostRead_Wait

 *@�����汾: 1.0.0

 *@��������: ����ʽ��ȡ�ʼ�

 *@�������: ��

 *@�� �� ֵ: �ʼ�����

 *@ע   ��: ��

*/
uint32_t* osPostReadWait(void)
{
	if(RunTask_TIT -> PF == 0){//û���ʼ�,���еȴ�
		while(TST.TSS != TaskSwitch_Ready);//��ѯ������л�̬,����ǲ����л�,����ѭ��,ֱ�����л�̬
		//RunTask_TIT -> TC &= TIT_Task_State_TC_RST;//�����״̬λ��λ
		RunTask_TIT -> TC = Task_State_Up_PT;//�޸�Ϊ�ʼ�����(�ȴ�̬)
		osTaskSwitch_Enable();//�����쳣,���������л�
	}
	return (osPostRead());//ͨ��������ʽ��ȡ�ʼ�
}

/*
                                                  FILE-END
*/
