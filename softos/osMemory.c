/*
                                                  FILE-START
*/
/*

 *@文件名称: osMemory.c

 *@文件内容: 系统"内存"文件

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

 *@开发环境: STM32F407ZGT6@168MHz & MDK-ARM Version: 5.27.1.0

 *@注    释: 无

*/

/*
                                                  <引用文件区>
*/
#include "Main.h"
#include "osMemory.h"
/*

 @头文件名称: 无

 @头文件功能: 无

 @注      释: 无

*/

/*
                                                  <数据初始区>
*/


_MemoryUnit*    MemoryNextAddr;//内存新地址
_MemoryUnit 	MemoryPool[MemTank_Max];//内存池

/*
                                                  <函数区>
*/
osErrorValue  osMemoryInit(void)
{
	u32 addr;
	MemoryNextAddr = &MemoryPool[0];//初始化内存地址
	for(addr = 0;addr < MemTank_Max;addr++){
		MemoryPool[addr] = 0x00;
	}
	return (OK);
}


void* osMemoryMalloc(u32 MemSize)
{
	MemoryStruct* _MemoryStruct;
	void*  MemoryNewAddr;
	_MemoryUnit* MemoryAddr1;
	_MemoryUnit* MemoryAddr2;
	s32 Length;

	#if (MemoryProtect_Enable > 0)//开启了内存保护配置
		#if (osCriticalToProtect_Enable > 0)//启用了临界保护
		osProtect_ENABLE();//进入临界保护
		#endif
		if(osMemorySum() == Error){
			return (NULL);
		}
	#endif

	MemSize += sizeof(MemoryStruct);
	if((MemoryNextAddr  + MemSize) <= (&MemoryPool[MemTank_Max])){//检查内存池是否已满

		_MemoryStruct = (MemoryStruct*)MemoryNextAddr;
		_MemoryStruct -> MemoryFlag = Memory_Occupy;
		_MemoryStruct -> MemoryLength = (_MemoryLength)MemSize;
		
		MemoryNewAddr = (void *)(MemoryNextAddr + sizeof(MemoryStruct));
		MemoryNextAddr = (u8* )( MemoryNextAddr + MemSize);
		#if (MemoryProtect_Enable > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Enable > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return MemoryNewAddr;
		 
	}else{
		Length = 0;
		MemoryAddr1 = &MemoryPool[Head];
		MemoryAddr2 = NULL;
		do{
			_MemoryStruct = (MemoryStruct*)MemoryAddr1;
			if(_MemoryStruct -> MemoryFlag == Memory_Free){
				if(Length == 0){
					MemoryAddr2 = MemoryAddr1;
				}
				Length += _MemoryStruct -> MemoryLength;
				if( Length >= MemSize){
					if((Length - MemSize) > 4){
						MemoryAddr1 = MemoryAddr2;
						MemoryAddr1 += MemSize;
						_MemoryStruct = (MemoryStruct*)MemoryAddr1;	
						_MemoryStruct -> MemoryFlag = Memory_Free;
						_MemoryStruct -> MemoryLength = Length - MemSize;

						_MemoryStruct = (MemoryStruct*)MemoryAddr2;
						_MemoryStruct -> MemoryLength  = (_MemoryLength)MemSize;
						_MemoryStruct -> MemoryFlag = Memory_Occupy;

					}else{
						_MemoryStruct = (MemoryStruct*)MemoryAddr2;
						_MemoryStruct -> MemoryLength  = (_MemoryLength)Length;
						_MemoryStruct -> MemoryFlag = Memory_Occupy;
					}
					#if (MemoryProtect_Enable > 0)//开启了内存保护配置
						#if (osCriticalToProtect_Enable > 0)//启用了临界保护
						osProtect_DISABLE();//退出临界保护
						#endif
					#endif
					return (MemoryAddr2 + sizeof(MemoryStruct)); 
				}
				
			}else if(_MemoryStruct -> MemoryFlag == Memory_Occupy){
				Length = 0;
			}else{
				Length = 0;
			}
			MemoryAddr1 += _MemoryStruct -> MemoryLength;
		}while(MemoryAddr1 < MemoryNextAddr);
		if((Length + ( &MemoryPool[MemTank_Max] - MemoryNextAddr)) >= MemSize){
			_MemoryStruct = (MemoryStruct*)MemoryAddr2;
			_MemoryStruct -> MemoryLength  = (_MemoryLength)MemSize;
			_MemoryStruct -> MemoryFlag = Memory_Occupy;

			MemoryNextAddr += MemSize;
			#if (MemoryProtect_Enable > 0)//开启了内存保护配置
				#if (osCriticalToProtect_Enable > 0)//启用了临界保护
				osProtect_DISABLE();//退出临界保护
				#endif
			#endif
			return (MemoryAddr2 + sizeof(MemoryStruct)); 
		}
		#if (osMemoryDebug_Enable > 0)//开启了内存保护配置
		osMemoryErrorDebug("内存申请失败! 剩余可申请内存为%d字节\n",osMemoryGetPassValue());
		#endif
		#if (MemoryProtect_Enable > 0)
			#if (osCriticalToProtect_Enable > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return (NULL);
	}

}
void* osMemoryReset(void* addr,u8 data)
{
	
	MemoryStruct* _MemoryStruct1 = (MemoryStruct*)((u8*)addr - sizeof(MemoryStruct));
	s32 Length = (_MemoryStruct1 -> MemoryLength) - sizeof(MemoryStruct);
	_MemoryUnit* addr_Buf = (_MemoryUnit*)addr;

	#if (MemoryProtect_Enable > 0)//开启了内存保护配置
		#if (osCriticalToProtect_Enable > 0)//启用了临界保护
		osProtect_ENABLE();//进入临界保护
		#endif
		if(osMemorySum() == Error){
			return (NULL);
		}
	#endif
	if(_MemoryStruct1 -> MemoryFlag == Memory_Free || _MemoryStruct1 -> MemoryFlag == Memory_Occupy){
		while(Length--){
			*addr_Buf =  data;
			addr_Buf++;
		}
		#if (MemoryProtect_Enable > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Enable > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return addr;
	}
	else{
		#if (MemoryProtect_Enable > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Enable > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return (NULL);
	}

	

}
void* osMemoryMallocAndReset(u32 MemSize)
{
	return osMemoryReset(osMemoryMalloc(MemSize),0x00);
}

osErrorValue osMemoryFree(void* addr)
{
	MemoryStruct* _MemoryStruct1 = (MemoryStruct*)((u8*)addr - sizeof(MemoryStruct));
	MemoryStruct* _MemoryStruct2 = _MemoryStruct1 + _MemoryStruct1 -> MemoryLength;;
	#if (MemoryProtect_Enable > 0)//开启了内存保护配置
		#if (osCriticalToProtect_Enable > 0)//启用了临界保护
		osProtect_ENABLE();//进入临界保护
		#endif
		if(osMemorySum() == Error){
			return (Error);
		}
	#endif
	if(_MemoryStruct1 -> MemoryFlag == Memory_Free){
		#if (osMemoryDebug_Enable > 0)
		osMemoryErrorDebug("内存已释放! 勿重复释放 %X\n",addr);
		#endif
		#if (MemoryProtect_Enable > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Enable > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return (Error - 1);
	}else if(_MemoryStruct2 -> MemoryFlag == Memory_Occupy || _MemoryStruct2 -> MemoryFlag == Memory_Free){
		_MemoryStruct1 -> MemoryFlag = Memory_Free;
		osMemoryReset(addr,0x00);
		#if (MemoryProtect_Enable > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Enable > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return (OK);
	}else if((_MemoryUnit*)_MemoryStruct2 >= MemoryNextAddr){
		_MemoryStruct1 -> MemoryFlag = Memory_Free;
		osMemoryReset(addr,0x00);
		#if (MemoryProtect_Enable > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Enable > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return (OK);
	}
	else{
		#if (osMemoryDebug_Enable > 0)
		osMemoryErrorDebug("内存释放失败! 内存地址不正确 %X\n",addr);
		#endif
		#if (MemoryProtect_Enable > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Enable > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return (Error);
	}
	
}

u32 osMemoryGetFreeValue(void)
{
	_MemoryUnit* MemoryAddr = &MemoryPool[Head];
	MemoryStruct* _MemoryStruct;
	u32 Vaule = 0;
	while(MemoryAddr < MemoryNextAddr){
		_MemoryStruct = (MemoryStruct*)MemoryAddr;
		if(_MemoryStruct -> MemoryFlag == Memory_Free){
			Vaule += _MemoryStruct -> MemoryLength;
		}
		MemoryAddr += _MemoryStruct -> MemoryLength;
	}
	Vaule += (&MemoryPool[MemTank_Max] - MemoryNextAddr);
	return (Vaule >= sizeof(MemoryStruct)? Vaule - sizeof(MemoryStruct) : NULL);
}

u32 osMemoryGetPassValue(void)
{
	_MemoryUnit* MemoryAddr = &MemoryPool[Head];
	MemoryStruct* _MemoryStruct;
	u32 Vaule = 0;
	s32 Length = 0;
	while(MemoryAddr < MemoryNextAddr){
		_MemoryStruct = (MemoryStruct*)MemoryAddr;
		if(_MemoryStruct -> MemoryFlag == Memory_Free){
			Length += _MemoryStruct -> MemoryLength;
		}else{
			if(Length > Vaule){
				Vaule = Length;
			}
			Length = 0;
		}
		MemoryAddr += _MemoryStruct -> MemoryLength;
	}
	if((&MemoryPool[MemTank_Max] - MemoryNextAddr) > Vaule){
		Vaule = &MemoryPool[MemTank_Max] - MemoryNextAddr;
	}
	return (Vaule >= sizeof(MemoryStruct)? Vaule - sizeof(MemoryStruct) : NULL);
}

u32 osMemoryGetAllValue(void)
{
	return (&MemoryPool[MemTank_Max] - &MemoryPool[Head]);
}

osErrorValue osMemorySum(void)
{
	_MemoryUnit* MemoryAddr = &MemoryPool[Head];
	MemoryStruct* _MemoryStruct;
	u32 Count = 0;
	while(MemoryAddr < MemoryNextAddr){
		_MemoryStruct = (MemoryStruct*)MemoryAddr;
		if(_MemoryStruct -> MemoryFlag == Memory_Occupy || _MemoryStruct -> MemoryFlag == Memory_Free){
			Count += 1;
		}else{
			#if (osMemoryDebug_Enable > 0)
			osMemoryErrorDebug("内存块异常! %X\n",_MemoryStruct);
			#endif
			return (Error);
		}
		MemoryAddr += _MemoryStruct -> MemoryLength;
	}
	return (Count);
}



/*
                                                  FILE-END
*/
