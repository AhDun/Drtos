/*
                                                  FILE-START
*/
/*

 *@文件名称: osMemory.h

 *@文件内容: 无

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@注   释: 无

*/
#ifndef _osMemory_H_
#define _osMemory_H_


/*
                                                  <引用文件区>
*/
//
#include "print.h"
#include "osConfig.h"
/*
                                                  <宏定义区>
*/


#define osMemory_Enable //启用内存 ！这个定义无需手动配置，用于自动标记文件，自动增减功能


//内存块标志{
#define Memory_Occupy 	0x01 //该内存块占用中
#define Memory_Free   	0x02 //该内存块已释放
//}

//内存配置{
#define MemTank_Max 	16 * 1024 //内存池大小配置


#define MemoryProtect_Enable 0 // 内存保护配置 	1:开启保护 0:关闭保护	
								//启用保护申请内存与释放内存所用的时长将会增加
								//内存保护也不一定保证内存块一定不会发生错误!!!,只会降低内存发生错误的概率

#define osMemoryInitReset_Enable 1 //初始化内存时复位内存 1:开启 0:关闭

#define osMemoryFreeReset_Enable 1 //释放内存时复位内存 1:开启 0:关闭

#define osMemoryFreeTest_Enable 1 //释放内存时检查内存 1:开启 0:关闭

#define osMemoryErrorDebug osDebugError//DeBug输出函数

#define osMemoryDebug_Enable 1 //Debug配置 1:开启Debug输出 0:关闭Debug输出

#define osMemorySequence_Enable 0 //内存顺序分配   1：启用 0：禁用

//}


/*
                                                  <数据声明区>
*/


typedef uint8_t	_MemoryUnit;//

//内存信息块{
typedef _MemoryUnit 	_MemoryPoolAddr;
typedef uint32_t 		_MemoryPoolLength;
typedef _MemoryUnit 	_MemoryNextAddr;
typedef  struct
{ 
	_MemoryPoolAddr*			HeadAddr;//内存头地址
	const _MemoryPoolAddr*		TailAddr;//内存尾地址
	_MemoryNextAddr*			NextAddr;//内存

}_MemoryInfo;
//}
typedef	_MemoryInfo*	_MemoryInfoHandle;

//内存块结构{
typedef uint8_t 	_MemoryFlag;
typedef uint16_t 	_MemoryLength;

typedef  struct
{ 
	_MemoryFlag 	MemoryFlag;//内存标志
	_MemoryLength	MemoryLength;//内存长度

}MemoryStruct;
//}

/*
                                                  <函数声明区>
*/
/*

 *@函数名称: osMemoryInit

 *@函数版本: 1.0.0

 *@函数功能: 内存初始化

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
osErrorValue  osMemoryInit(void);
/*

 *@函数名称: osMemoryMalloc

 *@函数版本: 1.0.0

 *@函数功能: 内存申请

 *@输入参数: MemSize	申请长度

 *@返 回 值: 申请返回的内存地址

 *@注    释: 无

*/
void* osMemoryMalloc(uint32_t MemSize);
/*

 *@函数名称: osMemoryReset

 *@函数版本: 1.0.0

 *@函数功能: 内存块复位

 *@输入参数: addr	内存块地址
			 data	复位内容

 *@返 回 值: 与addr变量输入相同的内存块地址

 *@注    释: 无

*/
void* osMemoryReset(void* addr,uint8_t data);
/*

 *@函数名称: osMemoryFree

 *@函数版本: 1.0.0

 *@函数功能: 释放内存

 *@输入参数: 0

 *@返 回 值: 

 *@注    释: 无

*/
osErrorValue osMemoryFree(void* addr);
/*

 *@函数名称: osMemoryGetFreeValue

 *@函数版本: 1.0.0

 *@函数功能: 获取剩余内存的长度

 *@输入参数: 无

 *@返 回 值: 剩余内存的长度

 *@注    释: 无

*/
uint32_t osMemoryGetFreeValue(void);
/*

 *@函数名称: osMemoryGetPassValue

 *@函数版本: 1.0.0

 *@函数功能: 获取可申请内存的长度

 *@输入参数: 无

 *@返 回 值: 可申请内存的长度

 *@注    释: 无

*/
uint32_t osMemoryGetPassValue(void);
/*

 *@函数名称: osMemoryGetAllValue

 *@函数版本: 1.0.0

 *@函数功能: 获取总内存长度

 *@输入参数: 无

 *@返 回 值: 总内存长度

 *@注    释: 无

*/
uint32_t osMemoryGetAllValue(void);
/*

 *@函数名称: osMemorySum

 *@函数版本: 1.0.0

 *@函数功能: 对所有内存块校验

 *@输入参数: 无

 *@返 回 值: 无

 *@注    释: 无

*/
osErrorValue osMemorySum(void);



#endif
/*
                                                  FILE-END
*/


