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

#ifndef __osLinkList_H_
#define __osLinkList_H_
/*
 *
 * @�ļ�����: .h
 *
 * @�ļ�����: ��
 *
 * @ע   ��: ��
 *
 */







typedef	int32_t		_LinkListXError;

typedef	uint32_t		_NextAddr;





/*
 *
 * @��������: uLinkListTailWrtie
 *
 * @��������: ���������βд��
 *
 * @�������: LinkListHeadAddr ����ͷ��ַ
 * @�������: uListx 		   д�������ַ
 *
 * @�� �� ֵ: -1:д����� / 0:д��ɹ�
 *
 * @ע   ��: ��
 *
 */
_LinkListXError uLinkListTailWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/*
 *
 * @��������: uLinkListHeadWrtie
 *
 * @��������: ���������ͷд��
 *
 * @�������: LinkListHeadAddr ����ͷ��ַ
 * @�������: uListx 		   д�������ַ
 *
 * @�� �� ֵ: -1:д����� / 0:д��ɹ�
 *
 * @ע   ��: ��
 *
 */
_LinkListXError uLinkListHeadWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/*
 *
 * @��������: uLinkListDel
 *
 * @��������: �����������ɾ��
 *
 * @�������: LinkListHeadAddr ����ͷ��ַ
 * @�������: uListx 		   Ҫɾ�������ַ
 *
 * @�� �� ֵ: -1д����� / 0:д��ɹ�
 *
 * @ע   ��: ��
 *
 */
_LinkListXError uLinkListDel(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/*
 *
 * @��������: uLinkListTailRead
 *
 * @��������: ���������β��ȡ
 *
 * @�������: LinkListHeadAddr ����ͷ��ַ
 *
 * @�� �� ֵ: β������ĵ�ַ
 *
 * @ע   ��: ��
 *
 */
uint32_t* uLinkListTailRead(uint32_t* LinkListHeadAddr);
/*
 *
 * @��������: uLinkListHeadRead
 *
 * @��������: ���������ͷ��ȡ
 *
 * @�������: LinkListHeadAddr ����ͷ��ַ
 *
 * @�� �� ֵ: ͷ������ĵ�ַ
 *
 * @ע   ��: ��
 *
 */
uint32_t* uLinkListHeadRead(uint32_t* LinkListHeadAddr);



#endif


