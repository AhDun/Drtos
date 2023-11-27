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
 * @brief 无
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
 * @brief 单向链表从尾写入
 *
 * @param LinkListHeadAddr 链表头地址
 * @param uListx 		   写入链表地址
 *
 * @retval -1:写入错误 / 0:写入成功
 *
 * @note none
 *
 */
_LinkListXError uLinkListTailWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/**
 *
 * @name uLinkListHeadWrtie
 *
 * @brief 单向链表从头写入
 *
 * @param LinkListHeadAddr 链表头地址
 * @param uListx 		   写入链表地址
 *
 * @retval -1:写入错误 / 0:写入成功
 *
 * @note none
 *
 */
_LinkListXError uLinkListHeadWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/**
 *
 * @name uLinkListDel
 *
 * @brief 单向从链表中删除
 *
 * @param LinkListHeadAddr 链表头地址
 * @param uListx 		   要删除链表地址
 *
 * @retval -1写入错误 / 0:写入成功
 *
 * @note none
 *
 */
_LinkListXError uLinkListDel(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/**
 *
 * @name uLinkListTailRead
 *
 * @brief 单向链表从尾读取
 *
 * @param LinkListHeadAddr 链表头地址
 *
 * @retval 尾部链表的地址
 *
 * @note none
 *
 */
uint32_t* uLinkListTailRead(uint32_t* LinkListHeadAddr);
/**
 *
 * @name uLinkListHeadRead
 *
 * @brief 单向链表从头读取
 *
 * @param LinkListHeadAddr 链表头地址
 *
 * @retval 头部链表的地址
 *
 * @note none
 *
 */
uint32_t* uLinkListHeadRead(uint32_t* LinkListHeadAddr);



#endif


