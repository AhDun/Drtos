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
osErrorValue osPostSend(void* PB,_TaskHandle* TaskHandle)
{
	_PostForm* PostForm;

	PostForm = osMemoryMalloc(sizeof(_PostForm));//�����ڴ�
	if(PostForm == NULL){//�������Ϊ��,˵������ʧ��
		#if (osPostDebugError_Enable > 0)
		osPostDebugError("�����ʼ�ʱ�����ڴ�ʧ�� %s\n",RunTaskHandle -> Name);
		#endif
		return (Error);//���ش���
	}else{
		PostForm -> PB = PB;
		PostForm -> DownAddr = NULL;

		uLinkListTailWrtie(&TaskHandle -> PF,(uint32_t*)PostForm);
	}
	if(TaskHandle -> Config == Task_State_Up_PT){
		if(TaskHandle -> PriorityLevel <  RunTaskHandle -> PriorityLevel){//������������ڵ�ǰ�������������������ȼ�����ռ��
			TaskHandle -> Config = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
			RunTaskHandle -> Config = Task_State_Up_TD;//���������������״̬��Ϊ��Ƭ����(����̬)
			if(TST.TSS == TaskSwitch_Ready){
				TST. TDN = TaskHandle -> ID;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
				osTaskSwitch_Enable();//���������л�
			} 
		}else{
			TaskHandle -> Config = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
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

	if(RunTaskHandle -> PF != NULL){
		#if (osPostHead > 0)
		PostForm = (_PostForm*)uLinkListHeadRead(&RunTaskHandle -> PF);
		#else
		PostForm  =  (_PostForm*)uLinkListTailRead(&RunTaskHandle -> PF);
		#endif
		Buf = PostForm -> PB;
		if(osMemoryFree(PostForm) != OK){
			#if (osPostDebugError_Enable > 0)
			osPostDebugError("��ȡ�ʼ�ʱ�ͷ��ڴ�ʧ�� %s\n",RunTaskHandle -> Name);
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
	if(RunTaskHandle -> PF == 0){//û���ʼ�,���еȴ�
		while(TST.TSS != TaskSwitch_Ready);//��ѯ������л�̬,����ǲ����л�,����ѭ��,ֱ�����л�̬
		//RunTaskHandle -> Config &= TIT_Task_State_TC_RST;//�����״̬λ��λ
		RunTaskHandle -> Config = Task_State_Up_PT;//�޸�Ϊ�ʼ�����(�ȴ�̬)
		osTaskSwitch_Enable();//�����쳣,���������л�
	}
	return (osPostRead());//ͨ��������ʽ��ȡ�ʼ�
}

/*
                                                  FILE-END
*/
