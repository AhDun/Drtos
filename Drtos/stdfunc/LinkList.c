/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
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





