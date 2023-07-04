/*
 * Copyright (c) 2022-2023 AhDun. All rights reserved.
 */
/*
 *
 * @�ļ�����: osLink.c
 *
 * @�ļ�����: ����(�ν�)�ļ�
 *
 * @ע    ��: 
 *
 */


#include "osConfig.h"
#include "osLink.h"
#include "STC32G_UART.h"
#include "STC32G_Exti.h"
/*
                                                  ������ʼ����
*/



#if (osTaskUseStack_Config > 0)
void INT0_ISR_Handler (void) interrupt INT0_VECTOR		
{

}
#else
void INT0_ISR_Handler (void) interrupt INT0_VECTOR	
{

	__asm   { CLR	EA      }
	__asm   { PUSH  DR560    }               
    __asm   { PUSH  DR28    }               
    __asm   { PUSH  DR24    }               
    __asm   { PUSH  DR20    }               
    __asm   { PUSH  DR16    }               
    __asm   { PUSH  DR12    }               
    __asm   { PUSH  DR8     }               
    __asm   { PUSH  DR4     }               
    __asm   { PUSH  DR0     }               
    __asm   { PUSH  PSW     }
    __asm   { MOV   DR0,DR60}           
    __asm   { MOV   DR4,OsTaskRunTaskHandle}   
    __asm   { MOV   @WR6,WR2} 
	__asm   { SETB  EA    } 
	osTaskNext(); 
	__asm   { CLR	EA      }
	__asm   { MOV   DR4,OsTaskRunTaskHandle}   
    __asm   { MOV   WR2,@WR6    }   
    __asm   { XRL   WR0,WR0     }           
    __asm   { MOV   DR60,DR0    }           
	__asm   { POP   PSW     }               
    __asm   { POP   DR0     }               
    __asm   { POP   DR4     }               
    __asm   { POP   DR8     }               
    __asm   { POP   DR12    }               
    __asm   { POP   DR16    }               
    __asm   { POP   DR20    }               
    __asm   { POP   DR24    }               
    __asm   { POP   DR28    }               
    __asm   { POP   DR56    }  
    __asm   { SETB  EA    	} 
	OsTaskRunTaskHandle;
}

#endif



