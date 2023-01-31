/*
                                                  FILE-START
*/
/*

 *@文件名称: .h

 *@文件内容: 无

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@注    释: 无

*/
/*
                                                  防重复编译宏配置区
*/
#ifndef __osSignalH_
#define __osSignalH_

/*
                                                  <引用文件区>
*/
#include "main.h"
#include "osConfig.h"
/*
                                                  <宏定义区>
*/
#define osSignal_Enable //启用队列 ！这个定义无需手动配置，用于自动标记文件，自动增减功能

#define Signal_Mutual       0x01u//互斥信号量
//什么是互斥信号量?
//
#define Signal_Binary       0x02u//二值信号量
//什么是二值信号量?

#define Signal_Count        0x03u//计数信号量
//什么是互斥信号量?
#define Signal_Logout		0x04u//无效信号量


#define osSignalMutual_Enable //启用互斥信号量
#define osSignalBinary_Enable //启用二值信号量
#define osSignalCount_Enable  //启用计数信号量

#define osSignalDebugError_Enable 1 //信号量错误DeBug  1:开启Debug输出 0:关闭Debug输出

#define osSignalDebugError	osDebugError 


/*
                                                  数据类型别名声明区
*/

/*
                                                  结构式数据类型别名声明区
*/
//信号量令牌{
typedef		uint32_t		_TaskInfo;
typedef struct
{
	_NextAddr  DownAddr;//下一个表的地址
	_TaskInfo*	TaskInfo;//任务句柄
}_SignalToken;
//}

//信号量{
typedef     uint8_t     _SignalValue;
typedef     uint8_t     _SignalType;
typedef struct
{
    _SignalValue 	 Value;//信号值
    _SignalType   	 Type;//信号的类型
	_NextAddr		 NextAddr;//信号量令牌链头
}_Signal;
//}

/*
                                                  <数据声明区>
*/

/*
                                                  <函数声明区>
*/
#if (osSignalAutoApply_Enable > 0)//启用了信号量自动分配

/*

 *@函数名称: osSignalLogin

 *@函数版本: 1.0.0

 *@函数功能: 信号量注册

 *@输入参数: _Signal* ST(信号量结构体)

 *@返 回 值: 无

 *@注    释: 无

*/
_Signal* osSignalLogin(_SignalType SP);
#else
osErrorValue osSignalLogin(_Signal* ST,_SignalType SP);
#endif

osErrorValue osSignalUseWait(_Signal* ST);
osErrorValue osSignalFree(_Signal* ST);

/*
                                                  FILE-END
*/
#endif
