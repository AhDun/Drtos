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
 * @file osMemory.c
 *
 * @brief ϵͳ"�ڴ�"�ļ�
 *
 * @note none
 *
 */


#include "Main.h"
#include "osMemory.h"


_MemoryInfoHandle	MemoryInfoHandle;
_MemoryInfoStaticHandle	MemoryInfoStaticHandle;

_MemoryInfo*  osMemoryInit(_MemoryInfo* MemoryInfo)
{
	#if (osMemoryInitReset_Config > 0)
	uint32_t Addr;
	for(Addr = 0;(MemoryInfoHandle -> HeadAddr + Addr) < MemoryInfoHandle -> TailAddr;Addr++){
		*(MemoryInfoHandle -> HeadAddr + Addr) = 0x00;
	}
	#endif
	return (MemoryInfo);
}



#if( osMemorySequence_Config > 0)
void* osMemoryMalloc(uint32_t MemSize)
{
	void*  MemoryNewAddr  = (void *)(MemoryInfoHandle -> NextAddr);
	if((MemoryInfoHandle -> NextAddr  + MemSize) <= MemoryInfoHandle -> TailAddr){//����ڴ���Ƿ�����
		MemoryInfoHandle -> NextAddr = (uint8_t* )( MemoryInfoHandle -> NextAddr + MemSize);
	}else{
		#if (osMemoryLog_Config > 0)//�������ڴ汣������
		osLogE("osMemoryMalloc","�ڴ�����ʧ��! ʣ��������ڴ�Ϊ%d�ֽ�\n",osMemoryGetPassValue());
		#endif
		return (NULL);
	}

	return (MemoryNewAddr);
}
void* osMemoryReset(void* Addr,uint8_t Data)
{
//	while(Length--){
//		*addr_Buf =  Data;
//		addr_Buf++;
//	}
	return Addr;
}

uint32_t osMemoryGetFreeValue(void)
{
	return (MemoryInfoHandle -> TailAddr - MemoryInfoHandle -> NextAddr);
}

uint32_t osMemoryGetPassValue(void)
{
	return osMemoryGetFreeValue();
}
OsErrorValue osMemoryFree(void* Addr)
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

	#if (MemoryProtect_Config > 0)//�������ڴ汣������
		#if (osCriticalToProtect_Config > 0)//�������ٽ籣��
		osProtect_ENABLE();//�����ٽ籣��
		#endif
		if(osMemorySum() == Error){
			return (NULL);
		}
	#endif

	MemSize += MemoryStructLength;
	if((MemoryInfoHandle -> NextAddr  + MemSize) <= MemoryInfoHandle -> TailAddr){//����ڴ���Ƿ�����

		_MemoryStruct = (MemoryStruct*)MemoryInfoHandle -> NextAddr;
		_MemoryStruct -> MemoryFlag = Memory_Occupy;//��Ϊռ��̬
		_MemoryStruct -> MemoryLength = (_MemoryLength)MemSize;//����鳤��
		
		MemoryNewAddr = (void *)(MemoryInfoHandle -> NextAddr + MemoryStructLength);
		MemoryInfoHandle -> NextAddr = (uint8_t* )( MemoryInfoHandle -> NextAddr + MemSize);
		#if (MemoryProtect_Config > 0)//�������ڴ汣������
			#if (osCriticalToProtect_Config > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		return MemoryNewAddr;//�������뵽��ַ�������ڴ渴λ����
		 
	}else{//�ڴ������
		Length = 0;
		MemoryAddr1 = MemoryInfoHandle -> HeadAddr;//��ȡ�ڴ��ͷ����ַ
		MemoryAddr2 = NULL;
		do{
			_MemoryStruct = (MemoryStruct*)MemoryAddr1;
			if(_MemoryStruct -> MemoryFlag == Memory_Free){
				#if( osMemoryMerge_Config > 0)
				if(Length == 0){//ֻ���ڳ���Ϊ��ʱ,�ż�¼
					MemoryAddr2 = MemoryAddr1;//��¼��ͷ��ĵ�ַ
				}
				Length += _MemoryStruct -> MemoryLength;
				#else
				MemoryAddr2 = MemoryAddr1;//��¼��ͷ��ĵ�ַ
				Length = _MemoryStruct -> MemoryLength;
				#endif
				if( Length >= MemSize){
					#if (osMemoryPart_Config > 0)
					if((Length - MemSize) > MemoryStructLength){//�����п����
						_MemoryStruct = (MemoryStruct*)(MemoryAddr2 + MemSize);	
						_MemoryStruct -> MemoryFlag = Memory_Free;//��Ϊ�ͷ�̬
						_MemoryStruct -> MemoryLength = Length - MemSize;//����鳤��

						Length = MemSize;
					}
					#endif
					_MemoryStruct = (MemoryStruct*)MemoryAddr2;
					_MemoryStruct -> MemoryLength  = (_MemoryLength)Length;//����鳤��
					_MemoryStruct -> MemoryFlag = Memory_Occupy;//��Ϊռ��̬
					#if (MemoryProtect_Config > 0)//�������ڴ汣������
						#if (osCriticalToProtect_Config > 0)//�������ٽ籣��
						osProtect_DISABLE();//�˳��ٽ籣��
						#endif
					#endif
					return MemoryAddr2 + MemoryStructLength;//�������뵽��ַ�������ڴ渴λ����
				}
				
			}else if(_MemoryStruct -> MemoryFlag == Memory_Occupy){//����ڴ汻ռ��
				Length = 0;
			}
			MemoryAddr1 += _MemoryStruct -> MemoryLength;
		}while(MemoryAddr1 < MemoryInfoHandle -> NextAddr);//
		#if( osMemoryMerge_Config > 0)
		if((Length + ( MemoryInfoHandle -> TailAddr - MemoryInfoHandle -> NextAddr)) >= MemSize){
			_MemoryStruct = (MemoryStruct*)MemoryAddr2;
			_MemoryStruct -> MemoryLength  = (_MemoryLength)MemSize;
			_MemoryStruct -> MemoryFlag = Memory_Occupy;//��Ϊռ��̬

			MemoryInfoHandle -> NextAddr += MemSize;
			#if (MemoryProtect_Config > 0)//�������ڴ汣������
				#if (osCriticalToProtect_Config > 0)//�������ٽ籣��
				osProtect_DISABLE();//�˳��ٽ籣��
				#endif
			#endif
			return MemoryAddr2 + MemoryStructLength; //�������뵽��ַ�������ڴ渴λ����
		}
		#endif
		#if (osMemoryLog_Config > 0)//�������ڴ汣������
		osLogE("osMemoryMalloc","�ڴ�����ʧ��! ʣ��������ڴ�Ϊ%d�ֽ�\n",osMemoryGetPassValue());
		#endif
		#if (MemoryProtect_Config > 0)
			#if (osCriticalToProtect_Config > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		return (NULL);//
	}

}
void* osMemoryReset(void* Addr,uint8_t Data)
{
	
	MemoryStruct* _MemoryStruct1 = (MemoryStruct*)((uint8_t*)Addr - MemoryStructLength);
	int32_t Length = (_MemoryStruct1 -> MemoryLength) - MemoryStructLength;
	_MemoryUnit* addr_Buf = (_MemoryUnit*)Addr;

	#if (MemoryProtect_Config > 0)//�������ڴ汣������
		if(osMemorySum() == Error){
			return (NULL);
		}
	#endif
	if(_MemoryStruct1 -> MemoryFlag == Memory_Free || _MemoryStruct1 -> MemoryFlag == Memory_Occupy){
		while(Length--){
			*addr_Buf =  Data;
			addr_Buf++;
		}
		return Addr;
	}
	else{
		return (NULL);
	}

}


OsErrorValue osMemoryFree(void* Addr)
{
	MemoryStruct* _MemoryStruct1 = (MemoryStruct*)((uint8_t*)Addr - MemoryStructLength);
	#if( osMemoryFreeTest_Config > 0)
	MemoryStruct* _MemoryStruct2 = (MemoryStruct*)((uint8_t*)Addr - MemoryStructLength + _MemoryStruct1 -> MemoryLength);
	#if (MemoryProtect_Config > 0)//�������ڴ汣������
		#if (osCriticalToProtect_Config > 0)//�������ٽ籣��
		osProtect_ENABLE();//�����ٽ籣��
		#endif
		if(osMemorySum() == Error){
			return (Error);
		}
	#endif
	if(_MemoryStruct1 -> MemoryFlag == Memory_Free){//������Ҫ�ͷŵĿ�״̬,����Ѿ��ͷ�,�ͻ᷵�ش���
		#if (osMemoryLog_Config > 0)
		osLogE("osMemoryMalloc","�ڴ����ͷ�! ���ظ��ͷ� %X\n",Addr);
		#endif
		#if (MemoryProtect_Config > 0)//�������ڴ汣������
			#if (osCriticalToProtect_Config > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		return (Error - 1);//���ش���
	}else if( (_MemoryUnit*)_MemoryStruct2 >= MemoryInfoHandle -> NextAddr || _MemoryStruct2 -> MemoryFlag == Memory_Occupy || _MemoryStruct2 -> MemoryFlag == Memory_Free){
			 //������Ҫ�ͷŵĿ�,��ָ����һ�����״̬�Ƿ�Ϊ�ͷ�̬��ռ��̬,�ٻ������Ҫ�ͷŵĿ��β��ַ�����µ�ַ,�����ſ��Ա��ͷ�
		_MemoryStruct1 -> MemoryFlag = Memory_Free;//��Ϊ�ͷ�̬
		#if (MemoryProtect_Config > 0)//�������ڴ汣������
			#if (osCriticalToProtect_Config > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		#if (osMemoryFreeReset_Config > 0)
		osMemoryReset(Addr,0x00);
		#endif
		return (OK);//��������
	}
	else{
		#if (osMemoryLog_Config > 0)
		osLogE("osMemoryFree","�ڴ��ͷ�ʧ��! �ڴ��ַ����ȷ %X\n",Addr);
		#endif
		#if (MemoryProtect_Config > 0)//�������ڴ汣������
			#if (osCriticalToProtect_Config > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		return (Error);//���ش���
	}
	#else
	_MemoryStruct1 -> MemoryFlag = Memory_Free;//��Ϊ�ͷ�̬
	#if (osMemoryFreeReset_Config > 0)
	osMemoryReset(Addr,0x00);
	#endif
	return (OK);//��������
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
			osLogE("osMemorySum","�ڴ���쳣! %X\n",_MemoryStruct);
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

#if (osMemoryStatic_Config > 0)

_MemoryInfoStatic* osMemoryInitStatic(_MemoryInfoStatic* MemoryInfoStatic)
{
	uint32_t* NextAddr;
	NextAddr = MemoryInfoStaticHandle -> HeadAddr;
	while( NextAddr < MemoryInfoStaticHandle -> TailAddr){
		*NextAddr = NULL;
		NextAddr++;
	}
	return (MemoryInfoStatic);
}


void* osMemoryMallocStatic(int32_t MemSize)
{
	uint32_t* NextAddr = MemoryInfoStaticHandle -> HeadAddr;
	while( NextAddr < MemoryInfoStaticHandle -> TailAddr){
		if(NextAddr[MemoryInfoStaticHandle -> Byte] == 0){
			return NextAddr;
		}else{
			NextAddr += MemoryInfoStaticHandle -> Size;
		}
	}
	return (NULL);
}
OsErrorValue osMemoryFreeStatic(void* Addr)
{
	uint32_t size = 0;
	uint32_t* AddrBuf = (uint32_t*)Addr;
	for(size = 0 ; size < MemoryInfoStaticHandle -> Size ; size++){
		AddrBuf[size] = 0x00;
	}
	return (OK);
}

uint32_t osMemoryStaticGetPassValue(void)
{
	uint32_t* NextAddr = MemoryInfoStaticHandle -> HeadAddr;
	uint32_t size = 0;
	while( NextAddr < MemoryInfoStaticHandle -> TailAddr){
		if(NextAddr[MemoryInfoStaticHandle -> Byte] == 0){
			size += MemoryInfoStaticHandle -> Size;
		}
		NextAddr += MemoryInfoStaticHandle -> Size;

	}
	return (size);
}

uint32_t osMemoryStaticGetAllValue(void)
{
	return MemoryInfoStaticHandle -> TailAddr - MemoryInfoStaticHandle -> HeadAddr;
}
#endif