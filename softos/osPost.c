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
	_PostForm* PostForm;

	PostForm = osMemoryMalloc(sizeof(_PostForm));//�����ڴ�
	if(PostForm == NULL){//�������Ϊ��,˵������ʧ��
		#if (osPostDebugError_Enable > 0)
		osPostDebugError("�����ʼ�ʱ�����ڴ�ʧ�� %s\n",RunTask_TIT -> TN);
		#endif
		return (Error);//���ش���
	}else{
		PostForm -> PB = PB;
		PostForm -> DownAddr = NULL;

		uLinkListTailWrtie(&TIT -> PF,(uint32_t*)PostForm);
	}
	if(TIT -> TC == Task_State_Up_PT){
		if(TIT -> TPL <  RunTask_TIT -> TPL){//������������ڵ�ǰ�������������������ȼ�����ռ��
			TIT -> TC = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
			RunTask_TIT -> TC = Task_State_Up_TD;//���������������״̬��Ϊ��Ƭ����(����̬)
			if(TST.TSS == TaskSwitch_Ready){
				TST. TDN = TIT -> TI;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
				osTaskSwitch_Enable();//���������л�
			} 
		}else{
			TIT -> TC = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
		}
	}
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
	_PostForm* PostForm;
	uint32_t*	Buf;

	if(RunTask_TIT -> PF != NULL){
		#if (osPostHead > 0)
		PostForm = (_PostForm*)uLinkListHeadRead(&RunTask_TIT -> PF);
		#else
		PostForm  =  (_PostForm*)uLinkListTailRead(&RunTask_TIT -> PF);
		#endif
		Buf = PostForm -> PB;
		if(osMemoryFree(PostForm) != OK){
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
