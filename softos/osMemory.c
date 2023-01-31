/*
                                                  FILE-START
*/
/*

 *@�ļ�����: osMemory.c

 *@�ļ�����: ϵͳ"�ڴ�"�ļ�

 *@�ļ��汾: 1.0.0

 *@�ļ�����: AhDun (mail: ahdunxx@163.com)

 *@ע    ��: ��

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

uint8_t a[MemTank_Max] __attribute__((at(0x10000000)));

_MemoryInfo 	Memory1 = {&a[0],&a[MemTank_Max],&a[0]};

_MemoryInfoHandle	MemoryInfoHandle;
/*
                                                  <������>
*/



osErrorValue  osMemoryInit(void)
{
	uint32_t addr;


	MemoryInfoHandle = &Memory1; 

	for(addr = 0;(MemoryInfoHandle -> HeadAddr + addr) < MemoryInfoHandle -> TailAddr;addr++){
		*(MemoryInfoHandle -> HeadAddr + addr) = 0x00;
	}
	return (OK);
}


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
				if(Length == 0){//ֻ���ڳ���Ϊ��ʱ,�ż�¼
					MemoryAddr2 = MemoryAddr1;//��¼��ͷ��ĵ�ַ
				}
				Length += _MemoryStruct -> MemoryLength;
				if( Length >= MemSize){
					if((Length - MemSize) > sizeof(MemoryStruct)){//�����п����
						_MemoryStruct = (MemoryStruct*)(MemoryAddr2 + MemSize);	
						_MemoryStruct -> MemoryFlag = Memory_Free;//��Ϊ�ͷ�̬
						_MemoryStruct -> MemoryLength = Length - MemSize;//����鳤��

						Length = MemSize;
					}
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
		#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
		osProtect_ENABLE();//�����ٽ籣��
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
		#if (MemoryProtect_Enable > 0)//�������ڴ汣������
			#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		return addr;
	}
	else{
		#if (MemoryProtect_Enable > 0)//�������ڴ汣������
			#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		return (NULL);
	}

	

}


osErrorValue osMemoryFree(void* addr)
{
	MemoryStruct* _MemoryStruct1 = (MemoryStruct*)((uint8_t*)addr - sizeof(MemoryStruct));
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
		osMemoryReset(addr,0x00);
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

uint32_t osMemoryGetAllValue(void)
{
	return MemoryInfoHandle -> TailAddr - MemoryInfoHandle -> HeadAddr;
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



/*
                                                  FILE-END
*/
