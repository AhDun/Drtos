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
/*

 @ͷ�ļ�����: ��

 @ͷ�ļ�����: ��

 @ע      ��: ��

*/

/*
                                                  <���ݳ�ʼ��>
*/


_MemoryUnit*    MemoryNextAddr;//�ڴ��µ�ַ
_MemoryUnit 	MemoryPool[MemTank_Max];//�ڴ��

/*
                                                  <������>
*/
osErrorValue  osMemoryInit(void)
{
	u32 addr;
	MemoryNextAddr = &MemoryPool[0];//��ʼ���ڴ��ַ
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

	#if (MemoryProtect_Enable > 0)//�������ڴ汣������
		#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
		osProtect_ENABLE();//�����ٽ籣��
		#endif
		if(osMemorySum() == Error){
			return (NULL);
		}
	#endif

	MemSize += sizeof(MemoryStruct);
	if((MemoryNextAddr  + MemSize) <= (&MemoryPool[MemTank_Max])){//����ڴ���Ƿ�����

		_MemoryStruct = (MemoryStruct*)MemoryNextAddr;
		_MemoryStruct -> MemoryFlag = Memory_Occupy;//��Ϊռ��̬
		_MemoryStruct -> MemoryLength = (_MemoryLength)MemSize;//����鳤��
		
		MemoryNewAddr = (void *)(MemoryNextAddr + sizeof(MemoryStruct));
		MemoryNextAddr = (u8* )( MemoryNextAddr + MemSize);
		#if (MemoryProtect_Enable > 0)//�������ڴ汣������
			#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		return osMemoryReset(MemoryNewAddr,0x00);//�������뵽��ַ�������ڴ渴λ����
		 
	}else{//�ڴ������
		Length = 0;
		MemoryAddr1 = &MemoryPool[Head];//��ȡ�ڴ��ͷ����ַ
		MemoryAddr2 = NULL;
		do{
			_MemoryStruct = (MemoryStruct*)MemoryAddr1;
			if(_MemoryStruct -> MemoryFlag == Memory_Free){
				if(Length == 0){//ֻ���ڳ���Ϊ��ʱ,�ż�¼
					MemoryAddr2 = MemoryAddr1;//��¼��ͷ��ĵ�ַ
				}
				Length += _MemoryStruct -> MemoryLength;
				if( Length >= MemSize){
					if((Length - MemSize) > 4){//�����п����
						MemoryAddr1 = MemoryAddr2;
						MemoryAddr1 += MemSize;//����Ҫ���볤��,����ƫ��
						_MemoryStruct = (MemoryStruct*)MemoryAddr1;	
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
					return osMemoryReset(MemoryAddr2 + sizeof(MemoryStruct),0x00);//�������뵽��ַ�������ڴ渴λ����
				}
				
			}else if(_MemoryStruct -> MemoryFlag == Memory_Occupy){//����ڴ汻ռ��
				Length = 0;
			}else{//����������֮������
				Length = 0;
			}
			MemoryAddr1 += _MemoryStruct -> MemoryLength;
		}while(MemoryAddr1 < MemoryNextAddr);//
		if((Length + ( &MemoryPool[MemTank_Max] - MemoryNextAddr)) >= MemSize){
			_MemoryStruct = (MemoryStruct*)MemoryAddr2;
			_MemoryStruct -> MemoryLength  = (_MemoryLength)MemSize;
			_MemoryStruct -> MemoryFlag = Memory_Occupy;//��Ϊռ��̬

			MemoryNextAddr += MemSize;
			#if (MemoryProtect_Enable > 0)//�������ڴ汣������
				#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
				osProtect_DISABLE();//�˳��ٽ籣��
				#endif
			#endif
			return osMemoryReset(MemoryAddr2 + sizeof(MemoryStruct),0x00); //�������뵽��ַ�������ڴ渴λ����
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
void* osMemoryReset(void* addr,u8 data)
{
	
	MemoryStruct* _MemoryStruct1 = (MemoryStruct*)((u8*)addr - sizeof(MemoryStruct));
	s32 Length = (_MemoryStruct1 -> MemoryLength) - sizeof(MemoryStruct);
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
	MemoryStruct* _MemoryStruct1 = (MemoryStruct*)((u8*)addr - sizeof(MemoryStruct));
	MemoryStruct* _MemoryStruct2 = _MemoryStruct1 + _MemoryStruct1 -> MemoryLength;;
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
	}else if(_MemoryStruct2 -> MemoryFlag == Memory_Occupy || _MemoryStruct2 -> MemoryFlag == Memory_Free || (_MemoryUnit*)_MemoryStruct2 > MemoryNextAddr){
			 //������Ҫ�ͷŵĿ�,��ָ����һ�����״̬�Ƿ�Ϊ�ͷ�̬��ռ��̬,�ٻ������Ҫ�ͷŵĿ��β��ַ�����µ�ַ,�����ſ��Ա��ͷ�
		_MemoryStruct1 -> MemoryFlag = Memory_Free;//��Ϊ�ͷ�̬
		#if (MemoryProtect_Enable > 0)//�������ڴ汣������
			#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		return (OK);//��������
	}
	else{
		#if (osMemoryDebug_Enable > 0)
		osMemoryErrorDebug("�ڴ��ͷ�ʧ��! �ڴ��ַ����ȷ %X\n",addr);
		#endif
		#if (MemoryProtect_Enable > 0)//�������ڴ汣������
			#if (osCriticalToProtect_Enable > 0)//�������ٽ籣��
			osProtect_DISABLE();//�˳��ٽ籣��
			#endif
		#endif
		return (Error);//���ش���
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
