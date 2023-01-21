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
_LinkListXError uLinkListAdd(void* LinkListHeadAddr,_uList* LinkListAddr)
{
	_uList* uList;
	u32* LinkListHead = (u32*)LinkListHeadAddr;

	LinkListAddr -> DownAddr = NULL;


	if(*LinkListHead == NULL){//��ͷΪ�գ�����ֱ��д��
		*LinkListHead = (u32)LinkListAddr;
		return (OK);//����

	}else{
		uList = (_uList*) *LinkListHead;
		while(uList -> DownAddr != NULL){
			uList = (_uList*) uList-> DownAddr;
		}
		uList -> DownAddr = (_NextAddr*)LinkListAddr;
		return (OK);

	}
}
/*

 *@��������: uLinkListAdd

 *@�����汾: 1.0.0

 *@��������: ������������

 *@�������: 	1.LinkListHeadAddr		-void*		-����ͷ��
				2.LinkListAddr			-void*		-Ҫ��ӵ�����

 *@�� �� ֵ: 	_LinkListXError		0.���쳣	-1.��������	

 *@ע    ��: ��

*/
_LinkListXError uLinkListInsert(void* LinkListHeadAddr,_uList* CLinkListAddr,_uList* LinkListAddr)
{
	_uList* uList;
	_uList* uList1;
	u32* LinkListHead = (u32*)LinkListHeadAddr;
	if(*LinkListHead != NULL){
		if(*LinkListHead == (u32)CLinkListAddr){
			*LinkListHead = (u32)LinkListAddr;
			LinkListAddr -> DownAddr = (_NextAddr*)CLinkListAddr;
			return (OK);
		}else{
			uList = (_uList*) *LinkListHead;
			while(uList != CLinkListAddr){
				uList1 = uList;
				uList = (_uList*) uList -> DownAddr;
				if(uList == NULL){
					return (Error);
				}
			}
			uList1 -> DownAddr = (_NextAddr*)LinkListAddr;
			LinkListAddr -> DownAddr = (_NextAddr*)CLinkListAddr;
			return (OK);
		}
		
	}else{
		return uLinkListAdd(LinkListHeadAddr,LinkListAddr);
	}
}
/*

 *@��������: mLinkListAdd

 *@�����汾: 1.0.0

 *@��������: ˫����������

 *@�������: 	1.LinkListHeadAddr		-void*		-����ͷ��
				2.LinkListAddr			-void*		-Ҫ��ӵ�����

 *@�� �� ֵ: 	_LinkListXError		0.���쳣	-1.��������	

 *@ע    ��: ��

*/
_LinkListXError mLinkListAdd(void* LinkListHeadAddr,_mList* LinkListAddr)
{
	_mList* mList;
	_mList* mList1;
	u32* LinkListHead = (u32*)LinkListHeadAddr;

	LinkListAddr -> DownAddr = NULL;
	LinkListAddr ->  UpAddr = NULL;

	if(*LinkListHead == NULL){//��ͷΪ�գ�����ֱ��д��

		*LinkListHead = (u32)LinkListAddr;
		mList = LinkListAddr;
		mList -> UpAddr = NULL;
		return (OK);//˫��

	}else{
		mList = (_mList*) *LinkListHead;
		while(mList -> DownAddr != NULL){
			mList1 = mList;
			mList = (_mList*) mList -> DownAddr;
		}
		mList -> DownAddr = (_NextAddr*)LinkListAddr;
		mList1 = LinkListAddr;
		mList1 -> UpAddr = (_NextAddr*)mList;
		return (OK);
	}
}
/*

 *@��������: uLinkListRemvoe

 *@�����汾: 1.0.0

 *@��������: ��������ɾ��

 *@�������: 	1.LinkListHeadAddr		-void*		-����ͷ��
				2.LinkListAddr			-void*		-Ҫɾ��������

 *@�� �� ֵ: 	_LinkListXError		0.���쳣	-1.��������	

 *@ע    ��: ��

*/

_LinkListXError uLinkListRemvoe(void* LinkListHeadAddr,_uList* LinkListAddr)
{
	_uList* uList;
	_uList* uList1;
	u32* LinkListHead = (u32*)LinkListHeadAddr;
	if(*LinkListHead == (u32)LinkListAddr){//
		uList = (_uList*)*LinkListHead;
		uList = (_uList*)uList -> DownAddr;//�����ָ�����һ����
		if(uList == NULL){//ֻ����һ�ű�
			*LinkListHead = NULL;//ֱ�����
		}else{
			*LinkListHead = (u32)uList;//
		}
		return (OK);
	}else{
		uList = (_uList*) *LinkListHead;
		do{
			uList1 = uList;//����
			uList = (_uList*)uList -> DownAddr;
		}while(uList != LinkListAddr);
		uList1 -> DownAddr = uList -> DownAddr;
		return (OK);

	}
}
/*

 *@��������: mLinkListRemvoe

 *@�����汾: 1.0.0

 *@��������: ˫������ɾ��

 *@�������: 	1.LinkListHeadAddr		-void*		-����ͷ��
				2.LinkListAddr			-void*		-Ҫɾ��������

 *@�� �� ֵ: 	_LinkListXError		0.���쳣	-1.��������	

 *@ע    ��: ��

*/
_LinkListXError mLinkListRemvoe(void* LinkListHeadAddr,_mList* LinkListAddr)
{
	_mList* mList;
	_mList* mList1;
	u32* LinkListHead = (u32*)LinkListHeadAddr;
	if(*LinkListHead == (u32)LinkListAddr){//

		mList = (_mList*)*LinkListHead;
		mList = (_mList*)mList -> DownAddr;//�����ָ�����һ����
		if(mList == NULL){
			*LinkListHead = NULL;
		}else{
			*LinkListHead = (u32)mList;//
			mList -> UpAddr = NULL;
		}
		return (OK);
	}else{
		mList = (_mList*) *LinkListHead;
		do{
			mList1 = mList;//����
			mList = (_mList*)mList -> DownAddr;
		}while(mList != (_mList*)LinkListAddr);
		mList1 -> DownAddr = mList -> DownAddr;
		return (OK);

	}
}
/*

 *@��������: umLinkListEndRead

 *@�����汾: 1.0.0

 *@��������: ����β�������ȡ

 *@�������: 1.LinkListHead		-void*		-����ͷ��

 *@�� �� ֵ: void*				-������

 *@ע    ��: ��

*/
_uList* uLinkListEndRead(void* LinkListHeadAddr)
{
	_uList* uList;
	u32* LinkListHead = (u32*)LinkListHeadAddr;
	if(LinkListHead  == NULL){
		return (NULL);
	}else{
		uList = (_uList*)LinkListHead;
		while(uList -> DownAddr != NULL){
			uList = (_uList*)uList -> DownAddr;
		}
		return (uList);
	}
}
/*

 *@��������: umLinkListEndRead

 *@�����汾: 1.0.0

 *@��������: ����β�������ȡ

 *@�������: 1.LinkListHead		-void*		-����ͷ��

 *@�� �� ֵ: void*				-������

 *@ע    ��: ��

*/
_mList* mLinkListEndRead(void* LinkListHeadAddr)
{
	_mList* mList;
	u32* LinkListHead = (u32*)LinkListHeadAddr;
	if(LinkListHead  == NULL){
		return (NULL);
	}else{
		mList = (_mList*)LinkListHead;
		if(mList -> DownAddr == NULL){
			return (mList);
		}else{
			do{
				mList = (_mList*)mList -> DownAddr;
			}while(mList -> DownAddr != NULL);
			return (mList);
		}
	}
}

/*

 *@��������: uLinkListRead

 *@�����汾: 1.0.0

 *@��������: ���������ȡ

 *@�������: 1.LinkListHead		-void*		-����ͷ��

 *@�� �� ֵ: void*				-������

 *@ע    ��: ��

*/
_uList* uLinkListRead(void* LinkListAddr)
{
	_uList* uList = LinkListAddr;
	return (_uList*)uList -> DownAddr;
}
/*

 *@��������: mLinkListDownRead

 *@�����汾: 1.0.0

 *@��������: ˫���������¶�ȡ

 *@�������: 1.LinkListHead		-void*		-����ͷ��

 *@�� �� ֵ: void*				-������

 *@ע    ��: ��

*/
_mList* mLinkListDownRead(void* LinkListAddr)
{
	_mList* mList = LinkListAddr;
	return (_mList*)mList -> DownAddr;
}
/*

 *@��������: mLinkListUpRead

 *@�����汾: 1.0.0

 *@��������: �����������϶�ȡ

 *@�������: 1.LinkListHead		-void*		-����ͷ��

 *@�� �� ֵ: void*				-������

 *@ע    ��: ��

*/
_mList* mLinkListUpRead(void* LinkListAddr)
{
	_mList* mList = LinkListAddr;
	return (_mList*)mList -> UpAddr;
}

/*
                                                  FILE-END
*/
