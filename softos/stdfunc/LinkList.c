/*
                                                  FILE-START
*/
/*

 *@�ļ�����: .c

 *@�ļ�����: ��

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *

 *@ע    ��: ��

*/

/*
                                                  <�����ļ���>
*/
#include "osConfig.h"
#include "LinkList.h"

/*
                                                  <���ݳ�ʼ��>
*/
/*
                                                  <������>
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
