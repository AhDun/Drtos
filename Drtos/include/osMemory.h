/**
 * Copyright 2022-2023 AhDun. All rights reserved.
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

/**
 *
 * @file osMemory.h
 *
 * @brief 无
 *
 * @note none
 *
 */
#ifndef _osMemory_H_
#define _osMemory_H_



//
#include "print.h"
#include "osConfig.h"




//内存块标志{
#define Memory_Occupy 					0x01 //该内存块占用中
#define Memory_Free   					0x02 //该内存块已释放
//}

#define MemoryStructLength				sizeof(MemoryStruct)

typedef uint8_t	_MemoryUnit;//

//内存信息块{
typedef _MemoryUnit 	_MemoryPoolAddr;
typedef uint32_t 		_MemoryPoolLength;
typedef _MemoryUnit 	_MemoryNextAddr;
typedef  struct
{ 
	_MemoryPoolAddr*			HeadAddr;//内存头地址
	_MemoryNextAddr*			NextAddr;//内存可分配的地址
	const _MemoryPoolAddr*		TailAddr;//内存尾地址

}_MemoryInfo;
typedef	_MemoryInfo*	_MemoryInfoHandle;
extern _MemoryInfoHandle	MemoryInfoHandle;
//}
//结构内存信息块{
#if (osMemoryStatic_Config > 0)
typedef  struct
{ 
	uint32_t*			HeadAddr;//内存头地址
	const uint32_t*		TailAddr;//内存尾地址
	const uint8_t		Byte;
	const uint8_t		Size;

}_MemoryInfoStatic;
typedef	_MemoryInfoStatic*	_MemoryInfoStaticHandle;
extern _MemoryInfoStaticHandle	MemoryInfoStaticHandle;
#endif
//}


#if (osMemorySequence_Config == 0)
//内存块结构{
typedef uint8_t 	_MemoryFlag;
typedef uint16_t 	_MemoryLength;

typedef  struct
{ 
	_MemoryLength	MemoryLength;//内存长度
	_MemoryFlag 	MemoryFlag;//内存标志

}MemoryStruct;
#endif
//}
/**
 *
 * @name osMemorySwitch
 *
 * @brief 内存池切换
 *
 * @param a 内存信息句柄
 *
 * @retval none
 *
 * @note none
 *
 */
#define osMemoryInstall(a) MemoryInfoHandle = a
/**
 *
 * @name osMemoryInit
 *
 * @brief 内存初始化
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
_MemoryInfo*  osMemoryInit(_MemoryInfo* MemoryInfo);
/**
 *
 * @name osMemoryMalloc
 *
 * @brief 内存申请
 *
 * @param MemSize	申请长度
 *
 * @retval 申请返回的内存地址
 *
 * @note none
 *
 */
void* osMemoryMalloc(uint32_t MemSize);
/**
 *
 * @name osMemoryReset
 *
 * @brief 内存块复位
 *
 * @param Addr	内存块地址
			 Data	复位内容
 *
 * @retval 与Addr变量输入相同的内存块地址
 *
 * @note none
 *
 */
void* osMemoryReset(void* Addr,uint8_t Data);
/**
 *
 * @name osMemoryFree
 *
 * @brief 释放内存
 *
 * @param 0
 *
 * @retval 
 *
 * @note none
 *
 */
OsErrorValue osMemoryFree(void* Addr);
/**
 *
 * @name osMemoryGetFreeValue
 *
 * @brief 获取剩余内存的长度
 *
 * @param none
 *
 * @retval 剩余内存的长度
 *
 * @note none
 *
 */
uint32_t osMemoryGetFreeValue(void);
/**
 *
 * @name osMemoryGetPassValue
 *
 * @brief 获取可申请内存的长度
 *
 * @param none
 *
 * @retval 可申请内存的长度
 *
 * @note none
 *
 */
uint32_t osMemoryGetPassValue(void);
/**
 *
 * @name osMemoryGetAllValue
 *
 * @brief 获取总内存长度
 *
 * @param none
 *
 * @retval 总内存长度
 *
 * @note none
 *
 */
uint32_t osMemoryGetAllValue(void);
/**
 *
 * @name osMemorySum
 *
 * @brief 对所有内存块校验
 *
 * @param none
 *
 * @retval none
 *
 * @note none
 *
 */
OsErrorValue osMemorySum(void);
/**
 *
 * @name osMemoryGetAllValue
 *
 * @brief 获取总内存长度
 *
 * @param none
 *
 * @retval 总内存长度
 *
 * @note none
 *
 */
_MemoryInfoStatic* osMemoryInitStatic(_MemoryInfoStatic* MemoryInfoStatic);
/**
 *
 * @name osMemorySwitchoverStatic
 *
 * @brief 静态内存切换
 *
 * @param none
 *
 * @retval 总内存长度
 *
 * @note none
 *
 */
#define osMemoryInstallStatic(a) MemoryInfoStaticHandle = a;
/**
 *
 * @name osMemoryMallocStatic
 *
 * @brief 申请静态内存
 *
 * @param MemSize 要要申请的字节数
 *
 * @retval 申请到可用的内存地址
 *
 * @note none
 *
 */
void* osMemoryMallocStatic(int32_t MemSize);
/**
 *
 * @name osMemoryFreeStatic
 *
 * @brief 静态内存释放
 *
 * @param none
 *
 * @retval 总内存长度
 *
 * @note none
 *
 */
OsErrorValue osMemoryFreeStatic(void* Addr);
/**
 *
 * @name osMemoryStaticGetPassValue
 *
 * @brief 获取静态内存可申请字节数
 *
 * @param none
 *
 * @retval 总内存长度
 *
 * @note none
 *
 */
uint32_t osMemoryStaticGetPassValue(void);
/**
 *
 * @name osMemoryStaticGetAllValue
 *
 * @brief 获取静态内存容量字节数
 *
 * @param none
 *
 * @retval 总内存长度
 *
 * @note none
 *
 */
uint32_t osMemoryStaticGetAllValue(void);

#endif



