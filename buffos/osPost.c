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

#if (osPost_Config > 0)

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

	PostForm = osPostMemoryMalloc(sizeof(_Post));//�����ڴ�
	if(PostForm == NULL){//�������Ϊ��,˵������ʧ��
		#if (osPostLog_Config > 0)
		osLogE("osPostSend","�����ʼ�ʱ�����ڴ�ʧ��");
		#endif
		return (Error);//���ش���
	}else{
		PostForm -> Body = PB;
		PostForm -> DownAddr = NULL;

		uLinkListTailWrtie(&TaskHandle -> Arg1,(uint32_t*)PostForm);
	}
	if(TaskHandle -> Config == Task_State_Up_PT){
		if(TaskHandle -> Level <  osTaskGetRunTaskHandle() -> Level){//������������ڵ�ǰ�������������������ȼ�����ռ��
			TaskHandle -> Config = Task_State_RE;//����������״̬��Ϊ��Ƭ����(����̬)
			osTaskSwitchConfig(TaskHandle,osTaskGetRunTaskHandle(),Task_State_RE);//���������л�
		}else{
			TaskHandle -> Config = Task_State_RE;//����������״̬��Ϊ��Ƭ����(����̬)
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

	if(osTaskGetRunTaskHandle() -> Arg1 != NULL){
		#if (osPostHead_Config > 0)
		PostForm = (_Post*)uLinkListHeadRead(&osTaskGetRunTaskHandle() -> Arg1);
		#else
		PostForm  =  (_Post*)uLinkListTailRead(&osTaskGetRunTaskHandle() -> Arg1);
		#endif
		Buf = PostForm -> Body;
		if(osPostMemoryFree(PostForm) != OK){
			#if (osPostLog_Config > 0)
			osLogE("osPostRead","��ȡ�ʼ�ʱ�ͷ��ڴ�ʧ��\n");
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
	if(osTaskGetRunTaskHandle() -> Arg1 == 0){//û���ʼ�,���еȴ�
		osTaskSwitchConfig(OSCoreTaskHandle,osTaskGetRunTaskHandle(),Task_State_Up_PT);//�����쳣,���������л�
	}
	return (osPostRead());//ͨ��������ʽ��ȡ�ʼ�
}

#endif


