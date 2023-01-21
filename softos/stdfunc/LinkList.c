/*
                                                  FILE-START
*/
/*

 *@文件名称: .c

 *@文件内容: 无

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注    释: 无

*/

/*
                                                  <引用文件区>
*/
#include "osMain.h"
#include "LinkList.h"

/*
                                                  <数据初始区>
*/
/*
                                                  <函数区>
*/

/*

 *@函数名称: uLinkListAdd

 *@函数版本: 1.0.0

 *@函数功能: 单向链表增加

 *@输入参数: 	1.LinkListHeadAddr		-void*		-链表头部
				2.LinkListAddr			-void*		-要添加的链表

 *@返 回 值: 	_LinkListXError		0.无异常	-1.发生错误	

 *@注    释: 无

*/
_LinkListXError uLinkListAdd(void* LinkListHeadAddr,_uList* LinkListAddr)
{
	_uList* uList;
	u32* LinkListHead = (u32*)LinkListHeadAddr;

	LinkListAddr -> DownAddr = NULL;


	if(*LinkListHead == NULL){//表头为空，可以直接写入
		*LinkListHead = (u32)LinkListAddr;
		return (OK);//单向

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

 *@函数名称: uLinkListAdd

 *@函数版本: 1.0.0

 *@函数功能: 单向链表增加

 *@输入参数: 	1.LinkListHeadAddr		-void*		-链表头部
				2.LinkListAddr			-void*		-要添加的链表

 *@返 回 值: 	_LinkListXError		0.无异常	-1.发生错误	

 *@注    释: 无

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

 *@函数名称: mLinkListAdd

 *@函数版本: 1.0.0

 *@函数功能: 双向链表增加

 *@输入参数: 	1.LinkListHeadAddr		-void*		-链表头部
				2.LinkListAddr			-void*		-要添加的链表

 *@返 回 值: 	_LinkListXError		0.无异常	-1.发生错误	

 *@注    释: 无

*/
_LinkListXError mLinkListAdd(void* LinkListHeadAddr,_mList* LinkListAddr)
{
	_mList* mList;
	_mList* mList1;
	u32* LinkListHead = (u32*)LinkListHeadAddr;

	LinkListAddr -> DownAddr = NULL;
	LinkListAddr ->  UpAddr = NULL;

	if(*LinkListHead == NULL){//表头为空，可以直接写入

		*LinkListHead = (u32)LinkListAddr;
		mList = LinkListAddr;
		mList -> UpAddr = NULL;
		return (OK);//双向

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

 *@函数名称: uLinkListRemvoe

 *@函数版本: 1.0.0

 *@函数功能: 单向链表删除

 *@输入参数: 	1.LinkListHeadAddr		-void*		-链表头部
				2.LinkListAddr			-void*		-要删除的链表

 *@返 回 值: 	_LinkListXError		0.无异常	-1.发生错误	

 *@注    释: 无

*/

_LinkListXError uLinkListRemvoe(void* LinkListHeadAddr,_uList* LinkListAddr)
{
	_uList* uList;
	_uList* uList1;
	u32* LinkListHead = (u32*)LinkListHeadAddr;
	if(*LinkListHead == (u32)LinkListAddr){//
		uList = (_uList*)*LinkListHead;
		uList = (_uList*)uList -> DownAddr;//这个表指向的下一个表
		if(uList == NULL){//只有这一张表
			*LinkListHead = NULL;//直接清空
		}else{
			*LinkListHead = (u32)uList;//
		}
		return (OK);
	}else{
		uList = (_uList*) *LinkListHead;
		do{
			uList1 = uList;//备份
			uList = (_uList*)uList -> DownAddr;
		}while(uList != LinkListAddr);
		uList1 -> DownAddr = uList -> DownAddr;
		return (OK);

	}
}
/*

 *@函数名称: mLinkListRemvoe

 *@函数版本: 1.0.0

 *@函数功能: 双向链表删除

 *@输入参数: 	1.LinkListHeadAddr		-void*		-链表头部
				2.LinkListAddr			-void*		-要删除的链表

 *@返 回 值: 	_LinkListXError		0.无异常	-1.发生错误	

 *@注    释: 无

*/
_LinkListXError mLinkListRemvoe(void* LinkListHeadAddr,_mList* LinkListAddr)
{
	_mList* mList;
	_mList* mList1;
	u32* LinkListHead = (u32*)LinkListHeadAddr;
	if(*LinkListHead == (u32)LinkListAddr){//

		mList = (_mList*)*LinkListHead;
		mList = (_mList*)mList -> DownAddr;//这个表指向的下一个表
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
			mList1 = mList;//备份
			mList = (_mList*)mList -> DownAddr;
		}while(mList != (_mList*)LinkListAddr);
		mList1 -> DownAddr = mList -> DownAddr;
		return (OK);

	}
}
/*

 *@函数名称: umLinkListEndRead

 *@函数版本: 1.0.0

 *@函数功能: 单向尾部链表读取

 *@输入参数: 1.LinkListHead		-void*		-链表头部

 *@返 回 值: void*				-链表本体

 *@注    释: 无

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

 *@函数名称: umLinkListEndRead

 *@函数版本: 1.0.0

 *@函数功能: 单向尾部链表读取

 *@输入参数: 1.LinkListHead		-void*		-链表头部

 *@返 回 值: void*				-链表本体

 *@注    释: 无

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

 *@函数名称: uLinkListRead

 *@函数版本: 1.0.0

 *@函数功能: 单向链表读取

 *@输入参数: 1.LinkListHead		-void*		-链表头部

 *@返 回 值: void*				-链表本体

 *@注    释: 无

*/
_uList* uLinkListRead(void* LinkListAddr)
{
	_uList* uList = LinkListAddr;
	return (_uList*)uList -> DownAddr;
}
/*

 *@函数名称: mLinkListDownRead

 *@函数版本: 1.0.0

 *@函数功能: 双向链表向下读取

 *@输入参数: 1.LinkListHead		-void*		-链表头部

 *@返 回 值: void*				-链表本体

 *@注    释: 无

*/
_mList* mLinkListDownRead(void* LinkListAddr)
{
	_mList* mList = LinkListAddr;
	return (_mList*)mList -> DownAddr;
}
/*

 *@函数名称: mLinkListUpRead

 *@函数版本: 1.0.0

 *@函数功能: 单向链表向上读取

 *@输入参数: 1.LinkListHead		-void*		-链表头部

 *@返 回 值: void*				-链表本体

 *@注    释: 无

*/
_mList* mLinkListUpRead(void* LinkListAddr)
{
	_mList* mList = LinkListAddr;
	return (_mList*)mList -> UpAddr;
}

/*
                                                  FILE-END
*/
