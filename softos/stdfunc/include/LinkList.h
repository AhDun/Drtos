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
 * @文件名称: .h
 *
 * @文件内容: 无
 *
 * @注   释: 无
 *
 */







typedef	int32_t		_LinkListXError;

typedef	uint32_t		_NextAddr;





/*
 *
 * @函数名称: uLinkListTailWrtie
 *
 * @函数功能: 单向链表从尾写入
 *
 * @输入参数: LinkListHeadAddr 链表头地址
 * @输入参数: uListx 		   写入链表地址
 *
 * @返 回 值: -1:写入错误 / 0:写入成功
 *
 * @注   释: 无
 *
 */
_LinkListXError uLinkListTailWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/*
 *
 * @函数名称: uLinkListHeadWrtie
 *
 * @函数功能: 单向链表从头写入
 *
 * @输入参数: LinkListHeadAddr 链表头地址
 * @输入参数: uListx 		   写入链表地址
 *
 * @返 回 值: -1:写入错误 / 0:写入成功
 *
 * @注   释: 无
 *
 */
_LinkListXError uLinkListHeadWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/*
 *
 * @函数名称: uLinkListDel
 *
 * @函数功能: 单向从链表中删除
 *
 * @输入参数: LinkListHeadAddr 链表头地址
 * @输入参数: uListx 		   要删除链表地址
 *
 * @返 回 值: -1写入错误 / 0:写入成功
 *
 * @注   释: 无
 *
 */
_LinkListXError uLinkListDel(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/*
 *
 * @函数名称: uLinkListTailRead
 *
 * @函数功能: 单向链表从尾读取
 *
 * @输入参数: LinkListHeadAddr 链表头地址
 *
 * @返 回 值: 尾部链表的地址
 *
 * @注   释: 无
 *
 */
uint32_t* uLinkListTailRead(uint32_t* LinkListHeadAddr);
/*
 *
 * @函数名称: uLinkListHeadRead
 *
 * @函数功能: 单向链表从头读取
 *
 * @输入参数: LinkListHeadAddr 链表头地址
 *
 * @返 回 值: 头部链表的地址
 *
 * @注   释: 无
 *
 */
uint32_t* uLinkListHeadRead(uint32_t* LinkListHeadAddr);



#endif


