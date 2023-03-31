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
 * @文件名称: osMemory.c
 *
 * @文件内容: 系统"内存"文件
 *
 * @注    释: 无
 *
 */


#include "Main.h"
#include "osMemory.h"
#include "sram.h"

uint32_t abc[128];

_MemoryInfoHandle	MemoryInfoHandle;
_MemoryInfoStaticHandle	MemoryInfoStaticHandle;

OsErrorValue  osMemoryInit(_MemoryInfo* MemoryInfo)
{
	#if (osMemoryInitReset_Config > 0)
	uint32_t addr;
	osMemorySwitch(MemoryInfo); 
	for(addr = 0;(MemoryInfoHandle -> HeadAddr + addr) < MemoryInfoHandle -> TailAddr;addr++){
		*(MemoryInfoHandle -> HeadAddr + addr) = 0x00;
	}
	#else
	osMemorySwitch(MemoryInfo);
	#endif
	return (OK);
}



#if( osMemorySequence_Config > 0)
void* osMemoryMalloc(uint32_t MemSize)
{
	void*  MemoryNewAddr  = (void *)(MemoryInfoHandle -> NextAddr);
	if((MemoryInfoHandle -> NextAddr  + MemSize) <= MemoryInfoHandle -> TailAddr){//检查内存池是否已满
		MemoryInfoHandle -> NextAddr = (uint8_t* )( MemoryInfoHandle -> NextAddr + MemSize);
	}else{
		#if (osMemoryLog_Config > 0)//开启了内存保护配置
		osLogE("osMemoryMalloc","内存申请失败! 剩余可申请内存为%d字节\n",osMemoryGetPassValue());
		#endif
		return (NULL);
	}

	return (MemoryNewAddr);
}
void* osMemoryReset(void* addr,uint8_t data)
{
//	while(Length--){
//		*addr_Buf =  data;
//		addr_Buf++;
//	}
	return addr;
}

uint32_t osMemoryGetFreeValue(void)
{
	return (MemoryInfoHandle -> TailAddr - MemoryInfoHandle -> NextAddr);
}

uint32_t osMemoryGetPassValue(void)
{
	return osMemoryGetFreeValue();
}
OsErrorValue osMemoryFree(void* addr)
{
	return (OK);
}

OsErrorValue osMemorySum(void)
{
	return (100);
}

#else
void* osMemoryMalloc(uint32_t MemSize)
{
	MemoryStruct* _MemoryStruct;
	void*  MemoryNewAddr;
	_MemoryUnit* MemoryAddr1;
	_MemoryUnit* MemoryAddr2;
	int32_t Length;

	#if (MemoryProtect_Config > 0)//开启了内存保护配置
		#if (osCriticalToProtect_Config > 0)//启用了临界保护
		osProtect_ENABLE();//进入临界保护
		#endif
		if(osMemorySum() == Error){
			return (NULL);
		}
	#endif

	MemSize += MemoryStructLength;
	if((MemoryInfoHandle -> NextAddr  + MemSize) <= MemoryInfoHandle -> TailAddr){//检查内存池是否已满

		_MemoryStruct = (MemoryStruct*)MemoryInfoHandle -> NextAddr;
		_MemoryStruct -> MemoryFlag = Memory_Occupy;//设为占用态
		_MemoryStruct -> MemoryLength = (_MemoryLength)MemSize;//输入块长度
		
		MemoryNewAddr = (void *)(MemoryInfoHandle -> NextAddr + MemoryStructLength);
		MemoryInfoHandle -> NextAddr = (uint8_t* )( MemoryInfoHandle -> NextAddr + MemSize);
		#if (MemoryProtect_Config > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Config > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return MemoryNewAddr;//返回申请到地址并进行内存复位操作
		 
	}else{//内存池已满
		Length = 0;
		MemoryAddr1 = MemoryInfoHandle -> HeadAddr;//获取内存池头部地址
		MemoryAddr2 = NULL;
		do{
			_MemoryStruct = (MemoryStruct*)MemoryAddr1;
			if(_MemoryStruct -> MemoryFlag == Memory_Free){
				#if( osMemoryMerge_Config > 0)
				if(Length == 0){//只有在长度为零时,才记录
					MemoryAddr2 = MemoryAddr1;//记录邻头块的地址
				}
				Length += _MemoryStruct -> MemoryLength;
				#else
				MemoryAddr2 = MemoryAddr1;//记录邻头块的地址
				Length = _MemoryStruct -> MemoryLength;
				#endif
				if( Length >= MemSize){
					#if (osMemoryPart_Config > 0)
					if((Length - MemSize) > MemoryStructLength){//进行切块操作
						_MemoryStruct = (MemoryStruct*)(MemoryAddr2 + MemSize);	
						_MemoryStruct -> MemoryFlag = Memory_Free;//设为释放态
						_MemoryStruct -> MemoryLength = Length - MemSize;//输入块长度

						Length = MemSize;
					}
					#endif
					_MemoryStruct = (MemoryStruct*)MemoryAddr2;
					_MemoryStruct -> MemoryLength  = (_MemoryLength)Length;//输入块长度
					_MemoryStruct -> MemoryFlag = Memory_Occupy;//设为占用态
					#if (MemoryProtect_Config > 0)//开启了内存保护配置
						#if (osCriticalToProtect_Config > 0)//启用了临界保护
						osProtect_DISABLE();//退出临界保护
						#endif
					#endif
					return MemoryAddr2 + MemoryStructLength;//返回申请到地址并进行内存复位操作
				}
				
			}else if(_MemoryStruct -> MemoryFlag == Memory_Occupy){//这块内存被占用
				Length = 0;
			}
			MemoryAddr1 += _MemoryStruct -> MemoryLength;
		}while(MemoryAddr1 < MemoryInfoHandle -> NextAddr);//
		#if( osMemoryMerge_Config > 0)
		if((Length + ( MemoryInfoHandle -> TailAddr - MemoryInfoHandle -> NextAddr)) >= MemSize){
			_MemoryStruct = (MemoryStruct*)MemoryAddr2;
			_MemoryStruct -> MemoryLength  = (_MemoryLength)MemSize;
			_MemoryStruct -> MemoryFlag = Memory_Occupy;//设为占用态

			MemoryInfoHandle -> NextAddr += MemSize;
			#if (MemoryProtect_Config > 0)//开启了内存保护配置
				#if (osCriticalToProtect_Config > 0)//启用了临界保护
				osProtect_DISABLE();//退出临界保护
				#endif
			#endif
			return MemoryAddr2 + MemoryStructLength; //返回申请到地址并进行内存复位操作
		}
		#endif
		#if (osMemoryLog_Config > 0)//开启了内存保护配置
		osLogE("osMemoryMalloc","内存申请失败! 剩余可申请内存为%d字节\n",osMemoryGetPassValue());
		#endif
		#if (MemoryProtect_Config > 0)
			#if (osCriticalToProtect_Config > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return (NULL);//
	}

}
void* osMemoryReset(void* addr,uint8_t data)
{
	
	MemoryStruct* _MemoryStruct1 = (MemoryStruct*)((uint8_t*)addr - MemoryStructLength);
	int32_t Length = (_MemoryStruct1 -> MemoryLength) - MemoryStructLength;
	_MemoryUnit* addr_Buf = (_MemoryUnit*)addr;

	#if (MemoryProtect_Config > 0)//开启了内存保护配置
		if(osMemorySum() == Error){
			return (NULL);
		}
	#endif
	if(_MemoryStruct1 -> MemoryFlag == Memory_Free || _MemoryStruct1 -> MemoryFlag == Memory_Occupy){
		while(Length--){
			*addr_Buf =  data;
			addr_Buf++;
		}
		return addr;
	}
	else{
		return (NULL);
	}

}


OsErrorValue osMemoryFree(void* addr)
{
	MemoryStruct* _MemoryStruct1 = (MemoryStruct*)((uint8_t*)addr - MemoryStructLength);
	#if( osMemoryFreeTest_Config > 0)
	MemoryStruct* _MemoryStruct2 = (MemoryStruct*)((uint8_t*)addr - MemoryStructLength + _MemoryStruct1 -> MemoryLength);
	#if (MemoryProtect_Config > 0)//开启了内存保护配置
		#if (osCriticalToProtect_Config > 0)//启用了临界保护
		osProtect_ENABLE();//进入临界保护
		#endif
		if(osMemorySum() == Error){
			return (Error);
		}
	#endif
	if(_MemoryStruct1 -> MemoryFlag == Memory_Free){//检查这个要释放的块状态,如果已经释放,就会返回错误
		#if (osMemoryLog_Config > 0)
		osLogE("osMemoryMalloc","内存已释放! 勿重复释放 %X\n",addr);
		#endif
		#if (MemoryProtect_Config > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Config > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return (Error - 1);//返回错误
	}else if( (_MemoryUnit*)_MemoryStruct2 >= MemoryInfoHandle -> NextAddr || _MemoryStruct2 -> MemoryFlag == Memory_Occupy || _MemoryStruct2 -> MemoryFlag == Memory_Free){
			 //检查这个要释放的块,所指向下一个块的状态是否为释放态或占用态,再或者这个要释放的块的尾地址大于新地址,这个块才可以被释放
		_MemoryStruct1 -> MemoryFlag = Memory_Free;//设为释放态
		#if (MemoryProtect_Config > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Config > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		#if (osMemoryFreeReset_Config > 0)
		osMemoryReset(addr,0x00);
		#endif
		return (OK);//返回正常
	}
	else{
		#if (osMemoryLog_Config > 0)
		osLogE("osMemoryFree","内存释放失败! 内存地址不正确 %X\n",addr);
		#endif
		#if (MemoryProtect_Config > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Config > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return (Error);//返回错误
	}
	#else
	_MemoryStruct1 -> MemoryFlag = Memory_Free;//设为释放态
	#if (osMemoryFreeReset_Config > 0)
	osMemoryReset(addr,0x00);
	#endif
	return (OK);//返回正常
	#endif
	
}

uint32_t osMemoryGetFreeValue(void)
{
	_MemoryUnit* MemoryAddr = MemoryInfoHandle -> HeadAddr;
	MemoryStruct* _MemoryStruct;
	uint32_t Vaule = 0;
	while(MemoryAddr < MemoryInfoHandle -> NextAddr){
		_MemoryStruct = (MemoryStruct*)MemoryAddr;
		if(_MemoryStruct -> MemoryFlag == Memory_Free){
			Vaule += _MemoryStruct -> MemoryLength;
		}
		MemoryAddr += _MemoryStruct -> MemoryLength;
	}
	Vaule += (MemoryInfoHandle -> TailAddr - MemoryInfoHandle -> NextAddr);
	return (Vaule >= MemoryStructLength? Vaule - MemoryStructLength : NULL);
}

uint32_t osMemoryGetPassValue(void)
{
	_MemoryUnit* MemoryAddr = MemoryInfoHandle -> HeadAddr;
	MemoryStruct* _MemoryStruct;
	uint32_t Vaule = 0;
	int32_t Length = 0;
	while(MemoryAddr < MemoryInfoHandle -> NextAddr){
		_MemoryStruct = (MemoryStruct*)MemoryAddr;
		if(_MemoryStruct -> MemoryFlag == Memory_Free){
			Length += _MemoryStruct -> MemoryLength;
		}else{
			Length = 0;
		}
		if(Length > Vaule){
			Vaule = Length;
		}
		MemoryAddr += _MemoryStruct -> MemoryLength;
	}
	if((MemoryInfoHandle -> TailAddr - MemoryInfoHandle -> NextAddr) > Vaule){
		Vaule = MemoryInfoHandle -> TailAddr - MemoryInfoHandle -> NextAddr;
	}
	return (Vaule >= MemoryStructLength? Vaule - MemoryStructLength : NULL);
}

OsErrorValue osMemorySum(void)
{
	_MemoryUnit* MemoryAddr = MemoryInfoHandle -> HeadAddr;
	MemoryStruct* _MemoryStruct;
	uint32_t Count = 0;
	while(MemoryAddr < MemoryInfoHandle -> NextAddr){
		_MemoryStruct = (MemoryStruct*)MemoryAddr;
		if(_MemoryStruct -> MemoryFlag == Memory_Occupy || _MemoryStruct -> MemoryFlag == Memory_Free){
			Count += 1;
		}else{
			#if (osMemoryLog_Config > 0)
			osLogE("osMemorySum","内存块异常! %X\n",_MemoryStruct);
			#endif
			return (Error);
		}
		MemoryAddr += _MemoryStruct -> MemoryLength;
	}
	return (Count);
}
#endif

uint32_t osMemoryGetAllValue(void)
{
	return MemoryInfoHandle -> TailAddr - MemoryInfoHandle -> HeadAddr;
}

OsErrorValue osMemoryInitStatic(_MemoryInfoStatic* MemoryInfoStatic)
{
	uint32_t* NextAddr;
	MemoryInfoStaticHandle = MemoryInfoStatic;
	NextAddr = MemoryInfoStaticHandle -> HeadAddr;
	while( NextAddr < MemoryInfoStaticHandle -> TailAddr){
		*NextAddr = NULL;
		NextAddr++;
	}
	return (OK);
}


void* osMemoryMallocStatic(int32_t MemSize)
{
	uint32_t* NextAddr = MemoryInfoStaticHandle -> HeadAddr;
	while( NextAddr < MemoryInfoStaticHandle -> TailAddr){
		if(NextAddr[osMemoryByteStatic_Config] == 0){
			return NextAddr;
		}else{
			NextAddr += osMemorySizeStatic_Config;
		}
	}
	return (NULL);
}
OsErrorValue osMemoryFreeStatic(void* addr)
{
	uint32_t size = 0;
	uint32_t* AddrBuf = (uint32_t*)addr;
	for(size = 0 ; size < osMemorySizeStatic_Config ; size++){
		AddrBuf[size] = 0x00;
	}
	return (OK);
}

uint32_t osMemoryStaticGetPassValue(void)
{
	uint32_t* NextAddr = MemoryInfoStaticHandle -> HeadAddr;
	uint32_t size = 0;
	while( NextAddr < MemoryInfoStaticHandle -> TailAddr){
		if(NextAddr[osMemoryByteStatic_Config] == 0){
			size += osMemorySizeStatic_Config;
		}
		NextAddr += osMemorySizeStatic_Config;

	}
	return (size);
}

uint32_t osMemoryStaticGetAllValue(void)
{
	return MemoryInfoStaticHandle -> TailAddr - MemoryInfoStaticHandle -> HeadAddr;
}
