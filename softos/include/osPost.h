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

 *@注   释: 无

*/


/*
                                                  <引用文件区>
*/
#include "main.h"
#include "osConfig.h"
#include "osTask.h"
/*
                                                  <宏定义区>
*/
#define osPost_Enable 		//启用邮箱 ！这个定义无需手动配置，用于自动标记文件，自动增减功能

#define osPostHead		1	 //读邮件顺序  1：正序 0：倒序

#define osPostDebugError_Enable 1 //邮箱错误DeBug  1:开启Debug输出 0:关闭Debug输出

#define osPostDebugError	osDebugError 

/*
                                                  <数据声明区>
*/

typedef		uint32_t		 _PostBody;//邮件主体
//邮箱表单{
typedef struct 
{
	_NextAddr	  DownAddr;//下一个邮件的地址
	_PostBody*	  Body;//邮件主体

}_Post;
//}

/*
                                                  <函数声明区>
*/
/*

 *@函数名称: osPostSend

 *@函数版本: 1.0.0

 *@函数功能: 初始化邮箱

 *@输入参数: PB - 邮件内容
			 TaskHandle - 目标任务的任务表地址

 *@返 回 值:  函数错误返回值 (0:表示初始化成功，-1:表示初始化失败)

 *@注   释: 无

*/
osErrorValue osPostSend(void* PB,_TaskHandle* TaskHandle);
/*

 *@函数名称: osPostRead

 *@函数版本: 1.0.0

 *@函数功能: 读取邮件

 *@输入参数: 无

 *@返 回 值: 邮件内容

 *@注   释: 无

*/
uint32_t* osPostRead(void);
/*

 *@函数名称: osPostRead_Wait

 *@函数版本: 1.0.0

 *@函数功能: 阻塞式读取邮件

 *@输入参数: 无

 *@返 回 值: 邮件内容

 *@注   释: 无

*/
uint32_t* osPostReadWait(void);

#endif
/*
                                                  FILE-END
*/


