/*
                                                  FILE-START
*/

#ifndef __osLinkList_H_
#define __osLinkList_H_
/*
 *
 * @�ļ�����: .h
 *
 * @�ļ�����: ��
 *
 * @�ļ�����: AhDun (mail: ahdunxx@163.com)
 *
 *
 *
 * @ע   ��: ��
 *
 */


/*
                                                  <�궨����>
*/



/*
                                                  <�Զ���������������>
*/
typedef	int32_t		_LinkListXError;

typedef	uint32_t		_NextAddr;


/*
                                                  <����������>
*/

/*
                                                  <����������>
*/
/*
 *
 * @��������: uLinkListTailWrtie
 *
 * @��������: ���������βд��
 *
 * @�������: ��
 *
 * @�� �� ֵ: ��
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
 * @�������: ��
 *
 * @�� �� ֵ: -1:�������� / 0:���ͳɹ�
 *
 * @ע   ��: ��
 *
 */
_LinkListXError uLinkListHeadWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/*
 *
 * @��������: uLinkListTailRead
 *
 * @��������: ���������β��ȡ
 *
 * @�������: ��
 *
 * @�� �� ֵ: -1:�������� / 0:���ͳɹ�
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
 * @�������: ��
 *
 * @�� �� ֵ: -1:�������� / 0:���ͳɹ�
 *
 * @ע   ��: ��
 *
 */
uint32_t* uLinkListHeadRead(uint32_t* LinkListHeadAddr);

/*
                                                  <�����ļ���>
*/

#endif
/*
                                                  FILE-END
*/

