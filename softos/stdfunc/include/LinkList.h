/*
                                                  FILE-START
*/

#ifndef __osLinkList_H_
#define __osLinkList_H_
/*

 *@�ļ�����: .h

 *@�ļ�����: ��

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@��������: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@ע   ��: ��

*/


/*
                                                  <�궨����>
*/



/*
                                                  <�Զ���������������>
*/
typedef	s32		_LinkListXError;
typedef	u8		_xLink;
typedef	u32		_NextAddr;
typedef	u32		_Body;
typedef	struct
{
	_NextAddr*  DownAddr;//��һ����ĵ�ַ
	_Body*		Body;//������

}_uList;//��������
typedef	struct
{
	_NextAddr*  DownAddr;//��һ����ĵ�ַ
	_NextAddr*	UpAddr;//��һ����ĵ�ַ
	_Body*		Body;//������

}_mList;//˫������


/*
                                                  <����������>
*/

/*
                                                  <����������>
*/











extern _LinkListXError uLinkListAdd(void* LinkListHeadAddr,void*  AdduList);
extern _LinkListXError mLinkListAdd(void* LinkListHeadAddr,_mList* LinkListAddr);
extern _LinkListXError uLinkListInsert(void* LinkListHeadAddr,_uList* CLinkListAddr,_uList* LinkListAddr);

extern _LinkListXError uLinkListRemvoe(void* LinkListHeadAddr,void*  ReuList);
extern _LinkListXError mLinkListRemvoe(void* LinkListHeadAddr,_mList* LinkListAddr);
extern _uList* uLinkListEndRead(void* LinkListHeadAddr);






/*
                                                  <�����ļ���>
*/
#include "osMain.h"

#endif
/*
                                                  FILE-END
*/

