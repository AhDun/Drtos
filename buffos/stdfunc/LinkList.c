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
 * @文件名称: .c
 *
 * @文件内容: 无
 *
 * @注    释: 无
 *
 */


#include "osConfig.h"
#include "LinkList.h"





_LinkListXError uLinkListTailWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx)
{
	while(*LinkListHeadAddr != NULL){
		LinkListHeadAddr = (uint32_t*)*LinkListHeadAddr;
	}
	*LinkListHeadAddr = (uint32_t)uListx;
	return (OK);
}

_LinkListXError uLinkListHeadWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx)
{
	if(*LinkListHeadAddr == NULL){
		*LinkListHeadAddr = (uint32_t) uListx;
	}else{
		*uListx = (uint32_t)*LinkListHeadAddr;
		*LinkListHeadAddr = (uint32_t)uListx;
	}
	return (OK);
}
_LinkListXError uLinkListDel(uint32_t* LinkListHeadAddr,uint32_t*  uListx)
{
	uint32_t* LinkListHeadAddr_Buf = (uint32_t*)*LinkListHeadAddr;
	uint32_t* LinkListHeadAddr_Buf1 = LinkListHeadAddr_Buf;
	if(*LinkListHeadAddr == (uint32_t)uListx){
		*LinkListHeadAddr = (uint32_t)*LinkListHeadAddr_Buf;
		return (OK);
	}
	LinkListHeadAddr_Buf = (uint32_t*)*LinkListHeadAddr_Buf;
	while(LinkListHeadAddr_Buf != uListx){
		LinkListHeadAddr_Buf1 = LinkListHeadAddr_Buf;
		LinkListHeadAddr_Buf = (uint32_t*)*LinkListHeadAddr_Buf;
	}
	*LinkListHeadAddr_Buf1 = *LinkListHeadAddr_Buf;
	return (OK);
}

uint32_t* uLinkListTailRead(uint32_t* LinkListHeadAddr)
{
	uint32_t* LinkListHeadAddr_Buf;
	while(*LinkListHeadAddr != NULL){
		LinkListHeadAddr_Buf = LinkListHeadAddr;
		LinkListHeadAddr = (uint32_t*)*LinkListHeadAddr;
		if(*LinkListHeadAddr == NULL){
			*LinkListHeadAddr_Buf = NULL;
			return (LinkListHeadAddr);
		}
	}
	return (NULL);
}

uint32_t* uLinkListHeadRead(uint32_t* LinkListHeadAddr)
{
	uint32_t* LinkListAddr_Buf;
	if(*LinkListHeadAddr == NULL){
		return(NULL);
	}else{
		LinkListAddr_Buf = (uint32_t*)*LinkListHeadAddr;
		*LinkListHeadAddr = (uint32_t)*LinkListAddr_Buf;
		return(LinkListAddr_Buf);
	}
}





