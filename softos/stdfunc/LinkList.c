/*
                                                  FILE-START
*/
/*

 *@文件名称: .c

 *@文件内容: 无

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *

 *@注    释: 无

*/

/*
                                                  <引用文件区>
*/
#include "osConfig.h"
#include "LinkList.h"

/*
                                                  <数据初始区>
*/
/*
                                                  <函数区>
*/


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




/*
                                                  FILE-END
*/
