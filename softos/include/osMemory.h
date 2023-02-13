/*
 * Copyright (c) 2022-2023 AhDun
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */
/*
 *
 * @文件名称: osMemory.h
 *
 * @文件内容: 无
 *
 * @注   释: 无
 *
 */
#ifndef _osMemory_H_
#define _osMemory_H_



//
#include "print.h"
#include "osConfig.h"



#define osMemory_Enable //启用内存 ！这个定义无需手动配置，用于自动标记文件，自动增减功能


//内存块标志{
#define Memory_Occupy 					0x01 //该内存块占用中
#define Memory_Free   					0x02 //该内存块已释放
//}



typedef uint8_t	_MemoryUnit;//

//内存信息块{
typedef _MemoryUnit 	_MemoryPoolAddr;
typedef uint32_t 		_MemoryPoolLength;
typedef _MemoryUnit 	_MemoryNextAddr;
typedef  struct
{ 
	_MemoryPoolAddr*			HeadAddr;//内存头地址
	_MemoryNextAddr*			NextAddr;//内存
	const _MemoryPoolAddr*		TailAddr;//内存尾地址

}_MemoryInfo;
//}
typedef	_MemoryInfo*	_MemoryInfoHandle;
extern _MemoryInfoHandle	MemoryInfoHandle;
#if (osMemorySequence_Enable == 0)
//内存块结构{
typedef uint8_t 	_MemoryFlag;
typedef uint16_t 	_MemoryLength;

typedef  struct
{ 
	_MemoryFlag 	MemoryFlag;//内存标志
	_MemoryLength	MemoryLength;//内存长度

}MemoryStruct;
#endif
//}
/*
 *
 * @函数名称: osMemorySwitch
 *
 * @函数功能: 内存池切换
 *
 * @输入参数: a 内存信息句柄
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
#define osMemorySwitch(a) MemoryInfoHandle = a
/*
 *
 * @函数名称: osMemoryInit
 *
 * @函数功能: 内存初始化
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
OsErrorValue  osMemoryInit(_MemoryInfo* MemoryInfo);
/*
 *
 * @函数名称: osMemoryMalloc
 *
 * @函数功能: 内存申请
 *
 * @输入参数: MemSize	申请长度
 *
 * @返 回 值: 申请返回的内存地址
 *
 * @注    释: 无
 *
 */
void* osMemoryMalloc(uint32_t MemSize);
/*
 *
 * @函数名称: osMemoryReset
 *
 * @函数功能: 内存块复位
 *
 * @输入参数: addr	内存块地址
			 data	复位内容
 *
 * @返 回 值: 与addr变量输入相同的内存块地址
 *
 * @注    释: 无
 *
 */
void* osMemoryReset(void* addr,uint8_t data);
/*
 *
 * @函数名称: osMemoryFree
 *
 * @函数功能: 释放内存
 *
 * @输入参数: 0
 *
 * @返 回 值: 
 *
 * @注    释: 无
 *
 */
OsErrorValue osMemoryFree(void* addr);
/*
 *
 * @函数名称: osMemoryGetFreeValue
 *
 * @函数功能: 获取剩余内存的长度
 *
 * @输入参数: 无
 *
 * @返 回 值: 剩余内存的长度
 *
 * @注    释: 无
 *
 */
uint32_t osMemoryGetFreeValue(void);
/*
 *
 * @函数名称: osMemoryGetPassValue
 *
 * @函数功能: 获取可申请内存的长度
 *
 * @输入参数: 无
 *
 * @返 回 值: 可申请内存的长度
 *
 * @注    释: 无
 *
 */
uint32_t osMemoryGetPassValue(void);
/*
 *
 * @函数名称: osMemoryGetAllValue
 *
 * @函数功能: 获取总内存长度
 *
 * @输入参数: 无
 *
 * @返 回 值: 总内存长度
 *
 * @注    释: 无
 *
 */
uint32_t osMemoryGetAllValue(void);
/*
 *
 * @函数名称: osMemorySum
 *
 * @函数功能: 对所有内存块校验
 *
 * @输入参数: 无
 *
 * @返 回 值: 无
 *
 * @注    释: 无
 *
 */
OsErrorValue osMemorySum(void);



#endif



