/**
 * Copyright 2022-2023 AhDun. All rights reserved.
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
/**
 *
 * @file .h
 *
 * @brief ��
 *
 * @note none
 *
 */







typedef	int32_t		_LinkListXError;

typedef	uint32_t		_NextAddr;





/**
 *
 * @name uLinkListTailWrtie
 *
 * @brief ���������βд��
 *
 * @param LinkListHeadAddr ����ͷ��ַ
 * @param uListx 		   д�������ַ
 *
 * @retval -1:д����� / 0:д��ɹ�
 *
 * @note none
 *
 */
_LinkListXError uLinkListTailWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/**
 *
 * @name uLinkListHeadWrtie
 *
 * @brief ���������ͷд��
 *
 * @param LinkListHeadAddr ����ͷ��ַ
 * @param uListx 		   д�������ַ
 *
 * @retval -1:д����� / 0:д��ɹ�
 *
 * @note none
 *
 */
_LinkListXError uLinkListHeadWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/**
 *
 * @name uLinkListDel
 *
 * @brief �����������ɾ��
 *
 * @param LinkListHeadAddr ����ͷ��ַ
 * @param uListx 		   Ҫɾ�������ַ
 *
 * @retval -1д����� / 0:д��ɹ�
 *
 * @note none
 *
 */
_LinkListXError uLinkListDel(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/**
 *
 * @name uLinkListTailRead
 *
 * @brief ���������β��ȡ
 *
 * @param LinkListHeadAddr ����ͷ��ַ
 *
 * @retval β������ĵ�ַ
 *
 * @note none
 *
 */
uint32_t* uLinkListTailRead(uint32_t* LinkListHeadAddr);
/**
 *
 * @name uLinkListHeadRead
 *
 * @brief ���������ͷ��ȡ
 *
 * @param LinkListHeadAddr ����ͷ��ַ
 *
 * @retval ͷ������ĵ�ַ
 *
 * @note none
 *
 */
uint32_t* uLinkListHeadRead(uint32_t* LinkListHeadAddr);



#endif


