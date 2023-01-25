/*
                                                  FILE-START
*/
/*

 *@�ļ�����: .c

 *@�ļ�����: ��

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע    ��: ��

*/

/*
                                                  <�����ļ���>
*/
#include "osMain.h"
#include "LinkList.h"

/*
                                                  <���ݳ�ʼ��>
*/
/*
                                                  <������>
*/

/*

 *@��������: uLinkListAdd

 *@�����汾: 1.0.0

 *@��������: ������������

 *@�������: 	1.LinkListHeadAddr		-void*		-����ͷ��
				2.LinkListAddr			-void*		-Ҫ��ӵ�����

 *@�� �� ֵ: 	_LinkListXError		0.���쳣	-1.��������	

 *@ע    ��: ��

*/
_LinkListXError uLinkListAdd(void* LinkListHeadAddr,void*  AdduList)
{
	_uList* uList_Buf;
	u32* LinkListHeadAddr_Buf = (u32*)LinkListHeadAddr;

	while(*LinkListHeadAddr_Buf != NULL){
		uList_Buf = (_uList*)LinkListHeadAddr_Buf;
		LinkListHeadAddr_Buf = uList_Buf -> DownAddr;
	}
	*LinkListHeadAddr_Buf = (u32)AdduList;
	return (OK);
}


_LinkListXError uLinkListRemvoe(void* LinkListHeadAddr,void*  ReuList)
{
	_uList* uList_Buf;
	_uList* uList_Buf1;
	u32* LinkListHeadAddr_Buf = (u32*)LinkListHeadAddr;

	if(*LinkListHeadAddr_Buf != NULL){
		uList_Buf = (_uList*)LinkListHeadAddr_Buf;
		uList_Buf1 = (_uList*)LinkListHeadAddr_Buf;
		while(uList_Buf != ReuList){
			uList_Buf1 = uList_Buf;
			uList_Buf = (_uList*)uList_Buf -> DownAddr;
			if(uList_Buf == NULL){
				return (Error);
			}
		}
		if(uList_Buf == uList_Buf1){
			*LinkListHeadAddr_Buf = (u32)uList_Buf -> DownAddr;
		}else{
			uList_Buf1 -> DownAddr = uList_Buf -> DownAddr;
		}
		return (OK);
	}
	else{
		return (Error);
	}
}

_LinkListXError uLinkListHeadRemvoe(void* LinkListHeadAddr)
{
	return uLinkListRemvoe(LinkListHeadAddr,LinkListHeadAddr);
}

void* uLinkListReadEnd(void* LinkListHeadAddr)
{
	_uList* uList_Buf;
	u32* LinkListHeadAddr_Buf = (u32*)LinkListHeadAddr;

	if(*LinkListHeadAddr_Buf != NULL){
		uList_Buf = (_uList*)LinkListHeadAddr_Buf;
		while(uList_Buf -> DownAddr != NULL){
			uList_Buf = (_uList*)uList_Buf -> DownAddr;
		}
		return ((void*)uList_Buf);
	}
	else{
		return (NULL);
	}


}

void* uLinkListReadEndAndRemvoe(void* LinkListHeadAddr)
{
	_uList* uList_Buf;
	_uList* uList_Buf1;
	u32* LinkListHeadAddr_Buf = (u32*)LinkListHeadAddr;

	if(*LinkListHeadAddr_Buf != NULL){
		uList_Buf = (_uList*)LinkListHeadAddr_Buf;
		uList_Buf1 = (_uList*)LinkListHeadAddr_Buf;
		while(uList_Buf -> DownAddr != NULL){
			uList_Buf1 = uList_Buf;
			uList_Buf = (_uList*)uList_Buf -> DownAddr;
		}
		if(uList_Buf == uList_Buf1){
			*LinkListHeadAddr_Buf = NULL;
		}else{
			uList_Buf1 -> DownAddr = NULL;
		}
		return ((void*)uList_Buf);
	}
	else{
		return (NULL);
	}


}



/*
                                                  FILE-END
*/
