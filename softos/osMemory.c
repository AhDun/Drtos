/*
                                                  FILE-START
*/
/*
 *
 * @�ļ�����: osMemory.c
 *
 * @�ļ�����: ϵͳ"�ڴ�"�ļ�
 *
 * @�ļ�����: AhDun (mail: ahdunxx@163.com)
 *
 * @ע    ��: ��
 *
 */

/*
                                                  <�����ļ���>
*/
#include "Main.h"
#include "osMemory.h"
#include "sram.h"

/*
                                                  <���ݳ�ʼ��>
*/

uint8_t CCRAM[MemTank_Max] __attribute__((at(0x10000000)));

_MemoryInfo 	Memory_CCRAM = {&CCRAM[0],&CCRAM[MemTank_Max],&CCRAM[0]};

_MemoryInfoHandle	MemoryInfoHandle;
/*
                                                  <������>
*/



osErrorValue  osMemoryInit(void)
{
	#if (osMemoryInitReset_Enable > 0)
	uint32_t addr;
	MemoryInfoHandle = &Memory_CCRAM; 
	for(addr = 0;(MemoryInfoHandle -> HeadAddr + addr) < MemoryInfoHandle -> TailAddr;addr++){
		*(MemoryInfoHandle -> HeadAddr + addr) = 0x00;
	}
	#else
	MemoryInfoHandle = &Memory_CCRAM; 
	#endif
	return (OK);
}

#if( osMemorySequence_Enable > 0)
void* osMemoryMalloc(uint32_t MemSize)
{
	void*  MemoryNewAddr  = (void *)(MemoryInfoHandle -> NextAddr);
	if((MemoryInfoHandle -> NextAddr  + MemSize) <= MemoryInfoHandle -> TailAddr){//����ڴ���Ƿ�����
		MemoryInfoHandle -> NextAddr = (uint8_t* )( MemoryInfoHandle -> NextAddr + MemSize);
	}else{
		#if (osMemoryDebug_Enable > 0)//�������ڴ汣������
		osMemoryErrorDebug("�ڴ�����ʧ��! ʣ��������ڴ�Ϊ%d�ֽ�\n",osMemoryGetPassValue());
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
osErrorValue osMemoryFree(void* addr)
{
	return (OK);
}

osErrorValue osMemorySum(void)
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

	#if (MemoryProtect_Enable > 0)//�������ڴ汣������
		#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
		osProtect_ENABLE();//�����ٽ籣��
		#endif
		if(osMemorySum() == Error){
			return (NULL);
		}
	#endif

	MemSize += sizeof(MemoryStruct);
	if((MemoryInfoHandle -> NextAddr  + MemSize) <= MemoryInfoHandle -> TailAddr){//����ڴ���Ƿ�����

		_MemoryStruct = (MemoryStruct*)MemoryInfoHandle -> NextAddr;
		_MemoryStruct -> MemoryFlag = Memory_Occupy;//��Ϊռ��̬
		_MemoryStruct -> MemoryLength = (_MemoryLength)MemSize;//����鳤��
		
		MemoryNewAddr = (void *)(MemoryInfoHandle -> NextAddr + sizeof(MemoryStruct));
		MemoryInfoHandle -> NextAddr = (uint8_t* )( MemoryInfoHandle -> NextAddr + MemSize);
		#if (MemoryProtect_Enable > 0)//�������ڴ汣������
			#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
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
				#if( osMemoryMerge_Enable > 0)
				if(Length == 0){//ֻ���ڳ���Ϊ��ʱ,�ż�¼
					MemoryAddr2 = MemoryAddr1;//��¼��ͷ��ĵ�ַ
				}
				Length += _MemoryStruct -> MemoryLength;
				#else
				MemoryAddr2 = MemoryAddr1;//��¼��ͷ��ĵ�ַ
				Length = _MemoryStruct -> MemoryLength;
				#endif
				if( Length >= MemSize){
					#if (osMemoryPart_Enable > 0)
					if((Length - MemSize) > sizeof(MemoryStruct)){//�����п����
						_MemoryStruct = (MemoryStruct*)(MemoryAddr2 + MemSize);	
						_MemoryStruct -> MemoryFlag = Memory_Free;//��Ϊ�ͷ�̬
						_MemoryStruct -> MemoryLength = Length - MemSize;//����鳤��

						Length = MemSize;
					}
					#endif
					_MemoryStruct = (MemoryStruct*)MemoryAddr2;
					_MemoryStruct -> MemoryLength  = (_MemoryLength)Length;//����鳤��
					_MemoryStruct -> MemoryFlag = Memory_Occupy;//��Ϊռ��̬
					#if (MemoryProtect_Enable > 0)//�������ڴ汣������
						#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
						osProtect_DISABLE();//�˳��ٽ籣��
						#endif
					#endif
					return MemoryAddr2 + sizeof(MemoryStruct);//�������뵽��ַ�������ڴ渴λ����
				}
				
			}else if(_MemoryStruct -> MemoryFlag == Memory_Occupy){//����ڴ汻ռ��
				Length = 0;
			}
			MemoryAddr1 += _MemoryStruct -> MemoryLength;
		}while(MemoryAddr1 < MemoryInfoHandle -> NextAddr);//
		#if( osMemoryMerge_Enable > 0)
		if((Length + ( MemoryInfoHandle -> TailAddr - MemoryInfoHandle -> NextAddr)) >= MemSize){
			_MemoryStruct = (MemoryStruct*)MemoryAddr2;
			_MemoryStruct -> MemoryLength  = (_MemoryLength)MemSize;
			_MemoryStruct -> MemoryFlag = Memory_Occupy;//��Ϊռ��̬

			MemoryInfoHandle -> NextAddr += MemSize;
			#if (MemoryProtect_Enable > 0)//�������ڴ汣������
				#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
				osProtect_DISABLE();//�˳��ٽ籣��
				#endif
			#endif
			return MemoryAddr2 + sizeof(MemoryStruct); //�������뵽��ַ�������ڴ渴λ����
		}
		#endif
		#if (osMemoryDebug_Enable > 0)//�������ڴ汣������
		osMemoryErrorDebug("�ڴ�����ʧ��! ʣ��������ڴ�Ϊ%d�ֽ�\n",osMemoryGetPassValue());
		#endif
		#if (MemoryProtect_Enable > 0)
			#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		return (NULL);//
	}

}
void* osMemoryReset(void* addr,uint8_t data)
{
	
	MemoryStruct* _MemoryStruct1 = (MemoryStruct*)((uint8_t*)addr - sizeof(MemoryStruct));
	int32_t Length = (_MemoryStruct1 -> MemoryLength) - sizeof(MemoryStruct);
	_MemoryUnit* addr_Buf = (_MemoryUnit*)addr;

	#if (MemoryProtect_Enable > 0)//�������ڴ汣������
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


osErrorValue osMemoryFree(void* addr)
{
	MemoryStruct* _MemoryStruct1 = (MemoryStruct*)((uint8_t*)addr - sizeof(MemoryStruct));
	#if( osMemoryFreeTest_Enable > 0)
	MemoryStruct* _MemoryStruct2 = (MemoryStruct*)((uint8_t*)addr - sizeof(MemoryStruct) + _MemoryStruct1 -> MemoryLength);
	#if (MemoryProtect_Enable > 0)//�������ڴ汣������
		#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
		osProtect_ENABLE();//�����ٽ籣��
		#endif
		if(osMemorySum() == Error){
			return (Error);
		}
	#endif
	if(_MemoryStruct1 -> MemoryFlag == Memory_Free){//������Ҫ�ͷŵĿ�״̬,����Ѿ��ͷ�,�ͻ᷵�ش���
		#if (osMemoryDebug_Enable > 0)
		osMemoryErrorDebug("�ڴ����ͷ�! ���ظ��ͷ� %X\n",addr);
		#endif
		#if (MemoryProtect_Enable > 0)//�������ڴ汣������
			#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		return (Error - 1);//���ش���
	}else if( (_MemoryUnit*)_MemoryStruct2 >= MemoryInfoHandle -> NextAddr || _MemoryStruct2 -> MemoryFlag == Memory_Occupy || _MemoryStruct2 -> MemoryFlag == Memory_Free){
			 //������Ҫ�ͷŵĿ�,��ָ����һ�����״̬�Ƿ�Ϊ�ͷ�̬��ռ��̬,�ٻ������Ҫ�ͷŵĿ��β��ַ�����µ�ַ,�����ſ��Ա��ͷ�
		_MemoryStruct1 -> MemoryFlag = Memory_Free;//��Ϊ�ͷ�̬
		#if (MemoryProtect_Enable > 0)//�������ڴ汣������
			#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		#if (osMemoryFreeReset_Enable > 0)
		osMemoryReset(addr,0x00);
		#endif
		return (OK);//��������
	}
	else{
		#if (osMemoryDebug_Enable > 0)
		osMemoryErrorDebug("�ڴ��ͷ�ʧ��! �ڴ��ַ����ȷ %X,%d\n",addr,_MemoryStruct2 -> MemoryLength );
		#endif
		#if (MemoryProtect_Enable > 0)//�������ڴ汣������
			#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		return (Error);//���ش���
	}
	#else
	_MemoryStruct1 -> MemoryFlag = Memory_Free;//��Ϊ�ͷ�̬
	#if (osMemoryFreeReset_Enable > 0)
	osMemoryReset(addr,0x00);
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
	return (Vaule >= sizeof(MemoryStruct)? Vaule - sizeof(MemoryStruct) : NULL);
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
	return (Vaule >= sizeof(MemoryStruct)? Vaule - sizeof(MemoryStruct) : NULL);
}

osErrorValue osMemorySum(void)
{
	_MemoryUnit* MemoryAddr = MemoryInfoHandle -> HeadAddr;
	MemoryStruct* _MemoryStruct;
	uint32_t Count = 0;
	while(MemoryAddr < MemoryInfoHandle -> NextAddr){
		_MemoryStruct = (MemoryStruct*)MemoryAddr;
		if(_MemoryStruct -> MemoryFlag == Memory_Occupy || _MemoryStruct -> MemoryFlag == Memory_Free){
			Count += 1;
		}else{
			#if (osMemoryDebug_Enable > 0)
			osMemoryErrorDebug("�ڴ���쳣! %X\n",_MemoryStruct);
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


/*
                                                  FILE-END
*/
