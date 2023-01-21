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
	MemoryNextAddr = &MemoryPool[0];//初始化内存地址
}


void* osMemoryMalloc(u32 MemSize)
{
	MemoryStruct* _MemoryStruct;
	void*  MemoryNewAddr;
	_MemoryUnit* MemoryAddr1;
	_MemoryUnit* MemoryAddr2;
	s32 Length;

	MemSize += sizeof(MemoryStruct);
	if((MemoryNextAddr  + MemSize) <= (&MemoryPool[MemTank_Max])){//检查内存池是否已满

		_MemoryStruct = (MemoryStruct*)MemoryNextAddr;
		_MemoryStruct -> MemoryFlag = Memory_Occupy;
		_MemoryStruct -> MemoryLength = (_MemoryLength)MemSize;
		
		MemoryNewAddr = (void *)(MemoryNextAddr + sizeof(MemoryStruct));
		MemoryNextAddr = (u8* )( MemoryNextAddr + MemSize);

		return MemoryNewAddr;
		 
	}else{
		Length = 0;
		MemoryAddr1 = &MemoryPool[0];
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
						_MemoryStruct -> MemoryLength = Length - sizeof(MemoryStruct);

						_MemoryStruct = (MemoryStruct*)MemoryAddr2;
						_MemoryStruct -> MemoryLength  = (_MemoryLength)MemSize;
						_MemoryStruct -> MemoryFlag = Memory_Occupy;

					}else{
						_MemoryStruct = (MemoryStruct*)MemoryAddr2;
						_MemoryStruct -> MemoryLength  = (_MemoryLength)Length;
						_MemoryStruct -> MemoryFlag = Memory_Occupy;
					}
	
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

			return (MemoryAddr2 + sizeof(MemoryStruct)); 
		}
		return (NULL);
	}
	return (NULL);
}

osErrorValue osMemoryFree(u8* addr){
	MemoryStruct* _MemoryStruct;
	_MemoryStruct = (MemoryStruct*)(addr - sizeof(MemoryStruct));
	_MemoryStruct -> MemoryFlag = Memory_Free;
	return (OK);
}
void* osMemoryExtend(u8* addr,u32 MemSize){
}
u32 osMemoryMaxMallocValue(void){
}
u32 osMemoryAllSize(void){
}
u32 osMemoryMarginSize(void){
}

/*
                                                  FILE-END
*/
