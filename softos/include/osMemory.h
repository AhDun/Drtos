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


//内存块状态{
#define Memory_Occupy 	0x01 //该内存块占用中
#define Memory_Free   	0x02 //该内存块已释放
//}

//内存配置{
#define MemTank_Max 	4 * 900 //32KB//内存池大小

#define osMemoryDebug print//DeBug输出函数
#define osMemoryDebug_Enable 1 //Debug配置 1:开启Debug输出 0:关闭Debug输出
#define osMemoryMarginSizeOut(a) print("\nosMemory: 剩余内存大小 %d 字节\n",a)//DeBug输出函数
#define osMemoryMarginSizeOut_Enable 1//配置 1:开启Debug输出 0:关闭Debug输出
#define osMemorySequence_Enable 0 //内存顺序分配   1：启用 0：禁用
#define osMemTankSur_Enable 	1 //内存余量记录   1：启用 0：禁用
#if (osMemorySequence_Enable == 0)
#define osMemoryMerge_Enable   1 //内存块合并 1：启用 0：禁用
#endif
//}



/*
                                                  <数据声明区>
*/

typedef u8 	_MemoryFlag;
typedef u16 _MemoryLength;

typedef u8	_MemoryUnit;

typedef u32 	MemTankSur;

extern _MemoryUnit*    MemoryNextAddr;//内存新地址
extern _MemoryUnit 	MemoryPool[MemTank_Max];//内存池

typedef  struct
{ 
	_MemoryFlag 	MemoryFlag;
	_MemoryLength	MemoryLength;

}MemoryStruct;


/*
                                                  <函数声明区>
*/
osErrorValue  osMemoryInit(void);
void* osMemoryMalloc(u32 MemSize);

osErrorValue osMemoryFree(void* addr);

u32 osMemoryGetFreeValue(void);
u32 osMemoryGetPassValue(void);

u32 osMemoryGetAllValue(void);

osErrorValue osMemorySum(void);



#endif
/*
                                                  FILE-END
*/


