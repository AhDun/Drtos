/*
                                                  FILE-START
*/

#ifndef __osLinkList_H_
#define __osLinkList_H_
/*
 *
 * @文件名称: .h
 *
 * @文件内容: 无
 *
 * @文件作者: AhDun (mail: ahdunxx@163.com)
 *
 *
 *
 * @注   释: 无
 *
 */


/*
                                                  <宏定义区>
*/



/*
                                                  <自定数据类型声明区>
*/
typedef	int32_t		_LinkListXError;

typedef	uint32_t		_NextAddr;


/*
                                                  <数据声明区>
*/

/*
                                                  <函数声明区>
*/
/*
 *
 * @函数名称: uLinkListTailWrtie
 *
 * @函数功能: 单向链表从尾写入
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注   释: 无
 *
 */
_LinkListXError uLinkListTailWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/*
 *
 * @函数名称: uLinkListHeadWrtie
 *
 * @函数功能: 单向链表从头写入
 *
 * @输入参数: 无
 *
 * @返 回 值: -1:发生错误 / 0:发送成功
 *
 * @注   释: 无
 *
 */
_LinkListXError uLinkListHeadWrtie(uint32_t* LinkListHeadAddr,uint32_t*  uListx);
/*
 *
 * @函数名称: uLinkListTailRead
 *
 * @函数功能: 单向链表从尾读取
 *
 * @输入参数: 无
 *
 * @返 回 值: -1:发生错误 / 0:发送成功
 *
 * @注   释: 无
 *
 */
uint32_t* uLinkListTailRead(uint32_t* LinkListHeadAddr);
/*
 *
 * @函数名称: uLinkListHeadRead
 *
 * @函数功能: 单向链表从头读取
 *
 * @输入参数: 无
 *
 * @返 回 值: -1:发生错误 / 0:发送成功
 *
 * @注   释: 无
 *
 */
uint32_t* uLinkListHeadRead(uint32_t* LinkListHeadAddr);

/*
                                                  <引用文件区>
*/

#endif
/*
                                                  FILE-END
*/

