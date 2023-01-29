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

 *

 *@ע   ��: ��

*/


/*
                                                  <�궨����>
*/



/*
                                                  <�Զ���������������>
*/
typedef	int32_t		_LinkListXError;
typedef	uint8_t		_xLink;
typedef	uint32_t		_NextAddr;
typedef	uint32_t		_Body;
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

/*

 *@��������: uLinkListAdd

 *@�����汾: 1.0.0

 *@��������: ������������

 *@�������: LinkListHeadAddr	 	������ͷ���ĵ�ַ
			 AdduList			 	Ҫ��ӵ�����ĵ�ַ
				

 *@�� �� ֵ: _LinkListXError		0.�ɹ����	1.���ʱ��������	

 *@ע    ��: ��

*/

_LinkListXError uLinkListAdd(void* LinkListHeadAddr,void*  AdduList);
/*

 *@��������: uLinkListRemvoe

 *@�����汾: 1.0.0

 *@��������: ��������ɾ��

 *@�������: LinkListHeadAddr	 	������ͷ���ĵ�ַ
			 ReuList			 	Ҫɾ��������ĵ�ַ

 *@�� �� ֵ: _LinkListXError		0.ɾ�����	1.ɾ��ʱ��������

 *@ע    ��: ��

*/
_LinkListXError uLinkListRemvoe(void* LinkListHeadAddr,void*  ReuList);
/*

 *@��������: uLinkListHeadRemvoe

 *@�����汾: 1.0.0

 *@��������: ����ͷ������ɾ��

 *@�������: LinkListHeadAddr	 	������ͷ���ĵ�ַ

 *@�� �� ֵ: _LinkListXError		0.ɾ�����	1.ɾ��ʱ��������

 *@ע    ��: ��

*/
_LinkListXError uLinkListHeadRemvoe(void* LinkListHeadAddr);
/*

 *@��������: uLinkListReadEnd

 *@�����汾: 1.0.0

 *@��������: ����β������ɾ��

 *@�������: 	LinkListHeadAddr	����ͷ��

 *@�� �� ֵ: 	����β������ĵ�ַ

 *@ע    ��: ��

*/
void* uLinkListReadEnd(void* LinkListHeadAddr);
/*

 *@��������: uLinkListAdd

 *@�����汾: 1.0.0

 *@��������: ������������

 *@�������: LinkListHeadAddr	����ͷ��

 *@�� �� ֵ: ����β������ĵ�ַ

 *@ע    ��: ��

*/
void* uLinkListReadEndAndRemvoe(void* LinkListHeadAddr);


/*
                                                  <�����ļ���>
*/
#include "osConfig.h"

#endif
/*
                                                  FILE-END
*/

