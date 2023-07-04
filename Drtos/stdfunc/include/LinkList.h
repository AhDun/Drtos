/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
 */

#ifndef __osLinkList_H_
#define __osLinkList_H_
/*
 *
 * @�ļ�����: .h
 *
 * @�ļ�����: ��
 *
 * @ע   ��: ��
 *
 */







typedef	int32_t		_LinkListXError;

typedef	uint32_t		_NextAddr;





/*
 *
 * @��������: uLinkListTailWrtie
 *
 * @��������: ���������βд��
 *
 * @�������: LinkListHeadAddr ����ͷ��ַ
 * @�������: uListx 		   д�������ַ
 *
 * @�� �� ֵ: -1:д����� / 0:д��ɹ�
 *
 * @ע   ��: ��
 *
 */
_LinkListXError uLinkListTailWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/*
 *
 * @��������: uLinkListHeadWrtie
 *
 * @��������: ���������ͷд��
 *
 * @�������: LinkListHeadAddr ����ͷ��ַ
 * @�������: uListx 		   д�������ַ
 *
 * @�� �� ֵ: -1:д����� / 0:д��ɹ�
 *
 * @ע   ��: ��
 *
 */
_LinkListXError uLinkListHeadWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/*
 *
 * @��������: uLinkListDel
 *
 * @��������: �����������ɾ��
 *
 * @�������: LinkListHeadAddr ����ͷ��ַ
 * @�������: uListx 		   Ҫɾ�������ַ
 *
 * @�� �� ֵ: -1д����� / 0:д��ɹ�
 *
 * @ע   ��: ��
 *
 */
_LinkListXError uLinkListDel(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/*
 *
 * @��������: uLinkListTailRead
 *
 * @��������: ���������β��ȡ
 *
 * @�������: LinkListHeadAddr ����ͷ��ַ
 *
 * @�� �� ֵ: β������ĵ�ַ
 *
 * @ע   ��: ��
 *
 */
uint32_t* uLinkListTailRead(uint32_t* LinkListHeadAddr);
/*
 *
 * @��������: uLinkListHeadRead
 *
 * @��������: ���������ͷ��ȡ
 *
 * @�������: LinkListHeadAddr ����ͷ��ַ
 *
 * @�� �� ֵ: ͷ������ĵ�ַ
 *
 * @ע   ��: ��
 *
 */
uint32_t* uLinkListHeadRead(uint32_t* LinkListHeadAddr);



#endif


