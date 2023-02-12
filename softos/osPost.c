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
 * @�ļ�����: osPost.c
 *
 * @�ļ�����: ϵͳ"����������"�ļ�
 *
 * @ע    ��: ��
 *
 */


#include "osPost.h"






/*
 *
 * @��������: osPostSend
 *
 * @��������: �����ʼ�
 *
 * @�������: ��
 *
 * @�� �� ֵ: -1:�������� / 0:���ͳɹ�
 *
 * @ע   ��: ��
 *
 */
OsErrorValue osPostSend(void* PB,_TaskHandle* TaskHandle)
{
	_Post* PostForm;

	PostForm = osMemoryMalloc(sizeof(_Post));//�����ڴ�
	if(PostForm == NULL){//�������Ϊ��,˵������ʧ��
		#if (osPostDebugError_Enable > 0)
		osPostDebugError("�����ʼ�ʱ�����ڴ�ʧ�� %s\n",osTaskGetRunTaskHandle() -> Name);
		#endif
		return (Error);//���ش���
	}else{
		PostForm -> Body = PB;
		PostForm -> DownAddr = NULL;

		uLinkListTailWrtie(&TaskHandle -> PF,(uint32_t*)PostForm);
	}
	if(TaskHandle -> Config == Task_State_Up_PT){
		if(TaskHandle -> PriorityLevel <  osTaskGetRunTaskHandle() -> PriorityLevel){//������������ڵ�ǰ�������������������ȼ�����ռ��
			TaskHandle -> Config = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
			osTaskGetRunTaskHandle() -> Config = Task_State_Up_TD;//���������������״̬��Ϊ��Ƭ����(����̬)
			if(osTaskGetSwitchState() == TaskSwitch_Ready){
				osTaskGetNextTaskHandle() = TaskHandle;//���������ID���ص�������ȼ����У�����������Ȳ���ʶ������񣬷��򽫻����µ���
				osTaskSwitch_Enable();//���������л�
			} 
		}else{
			TaskHandle -> Config = Task_State_Up_TD;//����������״̬��Ϊ��Ƭ����(����̬)
		}
	}
	return (OK);//���ͳɹ�������OK
}


/*
 *
 * @��������: osPostRead
 *
 * @��������: ��ȡ�ʼ�
 *
 * @�������: uint8_t* ResiduePost(����ָ��)
 *
 * @�� �� ֵ: �ʼ�����
 *
 * @ע   ��: ��
 *
 */
uint32_t* osPostRead(void)
{
	_Post* PostForm;
	uint32_t*	Buf;

	if(osTaskGetRunTaskHandle() -> PF != NULL){
		#if (osPostHead > 0)
		PostForm = (_Post*)uLinkListHeadRead(&osTaskGetRunTaskHandle() -> PF);
		#else
		PostForm  =  (_Post*)uLinkListTailRead(&osTaskGetRunTaskHandle() -> PF);
		#endif
		Buf = PostForm -> Body;
		if(osMemoryFree(PostForm) != OK){
			#if (osPostDebugError_Enable > 0)
			osPostDebugError("��ȡ�ʼ�ʱ�ͷ��ڴ�ʧ�� %s\n",osTaskGetRunTaskHandle() -> Name);
			#endif
			return (Buf);
		}
		return (Buf);
		
	}else{
		return (NULL);//û���ʼ������ؿ�
	}
}
/*
 *
 * @��������: osPostRead_Wait
 *
 * @��������: ����ʽ��ȡ�ʼ�
 *
 * @�������: ��
 *
 * @�� �� ֵ: �ʼ�����
 *
 * @ע   ��: ��
 *
 */
uint32_t* osPostReadWait(void)
{
	if(osTaskGetRunTaskHandle() -> PF == 0){//û���ʼ�,���еȴ�
		while(osTaskGetSwitchState() != TaskSwitch_Ready);//��ѯ������л�̬,����ǲ����л�,����ѭ��,ֱ�����л�̬
		osTaskSwitchConfig_Enable(osTaskGetRunTaskHandle(),Task_State_Up_PT);//�����쳣,���������л�
	}
	return (osPostRead());//ͨ��������ʽ��ȡ�ʼ�
}


