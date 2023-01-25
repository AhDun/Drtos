/*
                                                  FILE-START
*/
/*

 *@文件名称: osMemory.h

 *@文件内容: 无

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注   释: 无

*/
#ifndef _osMemory_H_
#define _osMemory_H_


/*
                                                  <引用文件区>
*/
//#include "osError.h"
#include "print.h"
#include "osMain.h"
/*
                                                  <宏定义区>
*/


#define osMemory_Enable //启用内存 ！这个定义无需手动配置，用于自动标记文件，自动增减功能


//内存块标志{
#define Memory_Occupy 	0x01 //该内存块占用中
#define Memory_Free   	0x02 //该内存块已释放
//}

//内存配置{
#define MemTank_Max 	32 * 1024 //内存池大小配置


#define MemoryProtect_Enable 1 // 内存保护配置 	1:开启保护 0:关闭保护	
								//启用保护申请内存与释放内存所用的时长将会增加
								//内存保护也不一定保证内存块一定不会发生错误!!!,只会降低内存发生错误的概率

#define osMemoryErrorDebug print//DeBug输出函数

#define osMemoryDebug_Enable 1 //Debug配置 1:开启Debug输出 0:关闭Debug输出


#define osMemorySequence_Enable 0 //内存顺序分配   1：启用 0：禁用

#if (osMemorySequence_Enable == 0)
#define osMemoryMerge_Enable   1 //内存块合并 1：启用 0：禁用
#endif
//}



/*
                                                  <数据声明区>
*/



typedef u8	_MemoryUnit;

extern _MemoryUnit*    MemoryNextAddr;//内存新地址
extern _MemoryUnit 	MemoryPool[MemTank_Max];//内存池

//内存块结构{
typedef u8 	_MemoryFlag;
typedef u16 _MemoryLength;

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
void* osMemoryMalloc(u32 MemSize);
/*

 *@函数名称: osMemoryReset

 *@函数版本: 1.0.0

 *@函数功能: 内存块复位

 *@输入参数: addr	内存块地址
			 data	复位内容

 *@返 回 值: 与addr变量输入相同的内存块地址

 *@注    释: 无

*/
void* osMemoryReset(void* addr,u8 data);
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
u32 osMemoryGetFreeValue(void);
/*

 *@函数名称: osMemoryGetPassValue

 *@函数版本: 1.0.0

 *@函数功能: 获取可申请内存的长度

 *@输入参数: 无

 *@返 回 值: 可申请内存的长度

 *@注    释: 无

*/
u32 osMemoryGetPassValue(void);
/*

 *@函数名称: osMemoryGetAllValue

 *@函数版本: 1.0.0

 *@函数功能: 获取总内存长度

 *@输入参数: 无

 *@返 回 值: 总内存长度

 *@注    释: 无

*/
u32 osMemoryGetAllValue(void);
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


