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

 *

 *@注   释: 无

*/


/*
                                                  <宏定义区>
*/



/*
                                                  <自定数据类型声明区>
*/
typedef	int32_t		_LinkListXError;
typedef	uint8_t		_xLink;
typedef	uint32_t		_NextAddr;
typedef	uint32_t		_Body;
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

/*

 *@函数名称: uLinkListAdd

 *@函数版本: 1.0.0

 *@函数功能: 单向链表增加

 *@输入参数: LinkListHeadAddr	 	链表链头部的地址
			 AdduList			 	要添加的链表的地址
				

 *@返 回 值: _LinkListXError		0.成功添加	1.添加时发生错误	

 *@注    释: 无

*/

_LinkListXError uLinkListAdd(void* LinkListHeadAddr,void*  AdduList);
/*

 *@函数名称: uLinkListRemvoe

 *@函数版本: 1.0.0

 *@函数功能: 单向链表删除

 *@输入参数: LinkListHeadAddr	 	链表链头部的地址
			 ReuList			 	要删除的链表的地址

 *@返 回 值: _LinkListXError		0.删除添加	1.删除时发生错误

 *@注    释: 无

*/
_LinkListXError uLinkListRemvoe(void* LinkListHeadAddr,void*  ReuList);
/*

 *@函数名称: uLinkListHeadRemvoe

 *@函数版本: 1.0.0

 *@函数功能: 单向头部链表删除

 *@输入参数: LinkListHeadAddr	 	链表链头部的地址

 *@返 回 值: _LinkListXError		0.删除添加	1.删除时发生错误

 *@注    释: 无

*/
_LinkListXError uLinkListHeadRemvoe(void* LinkListHeadAddr);
/*

 *@函数名称: uLinkListReadEnd

 *@函数版本: 1.0.0

 *@函数功能: 单向尾部链表删除

 *@输入参数: 	LinkListHeadAddr	链表头部

 *@返 回 值: 	返回尾部链表的地址

 *@注    释: 无

*/
void* uLinkListReadEnd(void* LinkListHeadAddr);
/*

 *@函数名称: uLinkListAdd

 *@函数版本: 1.0.0

 *@函数功能: 单向链表增加

 *@输入参数: LinkListHeadAddr	链表头部

 *@返 回 值: 返回尾部链表的地址

 *@注    释: 无

*/
void* uLinkListReadEndAndRemvoe(void* LinkListHeadAddr);


/*
                                                  <引用文件区>
*/
#include "osConfig.h"

#endif
/*
                                                  FILE-END
*/

