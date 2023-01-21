/*
                                                  FILE-START
*/
#ifndef _osPOST_H_
#define _osPOST_H_
/*

 *@文件名称: osPOST.h

 *@文件内容: 无

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注   释: 无

*/


/*
                                                  <引用文件区>
*/
#include "main.h"
#include "osMain.h"
#include "osTask.h"
/*
                                                  <宏定义区>
*/
#define osPost_Enable 		//启用邮箱 ！这个定义无需手动配置，用于自动标记文件，自动增减功能

#define osPostHead		1	 //读邮件顺序  1：正序 0：倒序

/*
                                                  <数据声明区>
*/

typedef		u32		 _PostBody;//邮件主体
//邮箱表单{
typedef struct 
{
	_PostBody*				PB;//邮件主体
	_uList					uList;//单向链表

}PostForm;
//}

/*
                                                  <函数声明区>
*/
/*

 *@函数名称: osPostInit

 *@函数版本: 1.0.0

 *@函数功能: 初始化邮箱

 *@输入参数: 无

 *@返 回 值: 函数错误返回值 (0:表示初始化成功，-1:表示初始化失败)

 *@注   释: 无

*/
extern osErrorValue osPostInit(void);
/*

 *@函数名称: osPostSend

 *@函数版本: 1.0.0

 *@函数功能: 初始化邮箱

 *@输入参数: PB - 邮件内容
			 TIT - 目标任务的任务表地址

 *@返 回 值:  函数错误返回值 (0:表示初始化成功，-1:表示初始化失败)

 *@注   释: 无

*/
extern osErrorValue osPostSend(void* PB,TaskInfoTable* TIT);
/*

 *@函数名称: osPostRead

 *@函数版本: 1.0.0

 *@函数功能: 读取邮件

 *@输入参数: 无

 *@返 回 值: 邮件内容

 *@注   释: 无

*/
extern u32* osPostRead(void);
/*

 *@函数名称: osPostRead_Wait

 *@函数版本: 1.0.0

 *@函数功能: 阻塞式读取邮件

 *@输入参数: 无

 *@返 回 值: 邮件内容

 *@注   释: 无

*/
extern u32* osPostReadWait(void);

#endif
/*
                                                  FILE-END
*/


