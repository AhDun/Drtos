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
#ifndef __osPOST_H_
#define __osPOST_H_
/*
 *
 * @�ļ�����: osPOST.h
 *
 * @�ļ�����: ��
 *
 * @ע   ��: ��
 *
 */





#include "main.h"
#include "osConfig.h"
#include "osTask.h"


#if (osPost_Config > 0)

typedef		uint32_t		 _PostBody;//�ʼ�����
//�����{
typedef struct 
{
	_NextAddr	  DownAddr;//��һ���ʼ��ĵ�ַ
	_PostBody*	  Body;//�ʼ�����

}_Post;
//}


/*
 *
 * @��������: osPostSend
 *
 * @��������: ��ʼ������
 *
 * @�������: PB - �ʼ�����
			 TaskHandle - Ŀ���������������ַ
 *
 * @�� �� ֵ:  �������󷵻�ֵ (0:��ʾ��ʼ���ɹ���-1:��ʾ��ʼ��ʧ��)
 *
 * @ע   ��: ��
 *
 */
OsErrorValue osPostSend(void* PB,_TaskHandle* TaskHandle);
/*
 *
 * @��������: osPostRead
 *
 * @��������: ��ȡ�ʼ�
 *
 * @�������: ��
 *
 * @�� �� ֵ: �ʼ�����
 *
 * @ע   ��: ��
 *
 */
uint32_t* osPostRead(void);
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
uint32_t* osPostReadWait(void);

#endif

#endif



