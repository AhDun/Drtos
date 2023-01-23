/*
                                                  FILE-START
*/

#ifndef __osLinkList_H_
#define __osLinkList_H_
/*

 *@文件名称: .h

 *@文件内容: 无

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注   释: 无

*/


/*
                                                  <宏定义区>
*/



/*
                                                  <自定数据类型声明区>
*/
typedef	s32		_LinkListXError;
typedef	u8		_xLink;
typedef	u32		_NextAddr;
typedef	u32		_Body;
typedef	struct
{
	_NextAddr*  DownAddr;//下一个表的地址
	_Body*		Body;//表内容

}_uList;//单向链表
typedef	struct
{
	_NextAddr*  DownAddr;//下一个表的地址
	_NextAddr*	UpAddr;//上一个表的地址
	_Body*		Body;//表内容

}_mList;//双向链表


/*
                                                  <数据声明区>
*/

/*
                                                  <函数声明区>
*/











extern _LinkListXError uLinkListAdd(void* LinkListHeadAddr,void*  AdduList);
extern _LinkListXError mLinkListAdd(void* LinkListHeadAddr,_mList* LinkListAddr);
extern _LinkListXError uLinkListInsert(void* LinkListHeadAddr,_uList* CLinkListAddr,_uList* LinkListAddr);

extern _LinkListXError uLinkListRemvoe(void* LinkListHeadAddr,void*  ReuList);
extern _LinkListXError mLinkListRemvoe(void* LinkListHeadAddr,_mList* LinkListAddr);
extern _uList* uLinkListEndRead(void* LinkListHeadAddr);






/*
                                                  <引用文件区>
*/
#include "osMain.h"

#endif
/*
                                                  FILE-END
*/

