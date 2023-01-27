/*
                                                  FILE-START
*/
/*

 *@文件名称: osMemory.c

 *@文件内容: 系统"内存"文件

 *@文件版本: 1.0.0

 *@文件作者: AhDun (mail: ahdunxx@163.com)

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
		_MemoryStruct -> MemoryFlag = Memory_Occupy;//设为占用态
		_MemoryStruct -> MemoryLength = (_MemoryLength)MemSize;//输入块长度
		
		MemoryNewAddr = (void *)(MemoryNextAddr + sizeof(MemoryStruct));
		MemoryNextAddr = (u8* )( MemoryNextAddr + MemSize);
		#if (MemoryProtect_Enable > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Enable > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return osMemoryReset(MemoryNewAddr,0x00);//返回申请到地址并进行内存复位操作
		 
	}else{//内存池已满
		Length = 0;
		MemoryAddr1 = &MemoryPool[Head];//获取内存池头部地址
		MemoryAddr2 = NULL;
		do{
			_MemoryStruct = (MemoryStruct*)MemoryAddr1;
			if(_MemoryStruct -> MemoryFlag == Memory_Free){
				if(Length == 0){//只有在长度为零时,才记录
					MemoryAddr2 = MemoryAddr1;//记录邻头块的地址
				}
				Length += _MemoryStruct -> MemoryLength;
				if( Length >= MemSize){
					if((Length - MemSize) > 4){//进行切块操作
						MemoryAddr1 = MemoryAddr2;
						MemoryAddr1 += MemSize;//根据要申请长度,向下偏移
						_MemoryStruct = (MemoryStruct*)MemoryAddr1;	
						_MemoryStruct -> MemoryFlag = Memory_Free;//设为释放态
						_MemoryStruct -> MemoryLength = Length - MemSize;//输入块长度

						Length = MemSize;
					}
					_MemoryStruct = (MemoryStruct*)MemoryAddr2;
					_MemoryStruct -> MemoryLength  = (_MemoryLength)Length;//输入块长度
					_MemoryStruct -> MemoryFlag = Memory_Occupy;//设为占用态
					#if (MemoryProtect_Enable > 0)//开启了内存保护配置
						#if (osCriticalToProtect_Enable > 0)//启用了临界保护
						osProtect_DISABLE();//退出临界保护
						#endif
					#endif
					return osMemoryReset(MemoryAddr2 + sizeof(MemoryStruct),0x00);//返回申请到地址并进行内存复位操作
				}
				
			}else if(_MemoryStruct -> MemoryFlag == Memory_Occupy){//这块内存被占用
				Length = 0;
			}else{//发生了意料之外的情况
				Length = 0;
			}
			MemoryAddr1 += _MemoryStruct -> MemoryLength;
		}while(MemoryAddr1 < MemoryNextAddr);//
		if((Length + ( &MemoryPool[MemTank_Max] - MemoryNextAddr)) >= MemSize){
			_MemoryStruct = (MemoryStruct*)MemoryAddr2;
			_MemoryStruct -> MemoryLength  = (_MemoryLength)MemSize;
			_MemoryStruct -> MemoryFlag = Memory_Occupy;//设为占用态

			MemoryNextAddr += MemSize;
			#if (MemoryProtect_Enable > 0)//开启了内存保护配置
				#if (osCriticalToProtect_Enable > 0)//启用了临界保护
				osProtect_DISABLE();//退出临界保护
				#endif
			#endif
			return osMemoryReset(MemoryAddr2 + sizeof(MemoryStruct),0x00); //返回申请到地址并进行内存复位操作
		}
		#if (osMemoryDebug_Enable > 0)//开启了内存保护配置
		osMemoryErrorDebug("内存申请失败! 剩余可申请内存为%d字节\n",osMemoryGetPassValue());
		#endif
		#if (MemoryProtect_Enable > 0)
			#if (osCriticalToProtect_Enable > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return (NULL);//
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
	if(_MemoryStruct1 -> MemoryFlag == Memory_Free){//检查这个要释放的块状态,如果已经释放,就会返回错误
		#if (osMemoryDebug_Enable > 0)
		osMemoryErrorDebug("内存已释放! 勿重复释放 %X\n",addr);
		#endif
		#if (MemoryProtect_Enable > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Enable > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return (Error - 1);//返回错误
	}else if(_MemoryStruct2 -> MemoryFlag == Memory_Occupy || _MemoryStruct2 -> MemoryFlag == Memory_Free || (_MemoryUnit*)_MemoryStruct2 > MemoryNextAddr){
			 //检查这个要释放的块,所指向下一个块的状态是否为释放态或占用态,再或者这个要释放的块的尾地址大于新地址,这个块才可以被释放
		_MemoryStruct1 -> MemoryFlag = Memory_Free;//设为释放态
		#if (MemoryProtect_Enable > 0)//开启了内存保护配置
			#if (osCriticalToProtect_Enable > 0)//启用了临界保护
			osProtect_DISABLE();//退出临界保护
			#endif
		#endif
		return (OK);//返回正常
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
		return (Error);//返回错误
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
			Length = 0;
		}
		if(Length > Vaule){
			Vaule = Length;
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
