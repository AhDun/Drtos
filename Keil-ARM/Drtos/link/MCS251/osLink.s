PUBLIC        INT0_ISR_Handler?_

; line 1: /*
; line 2:  * Copyright (c) 2022-2023 AhDun
; line 3:  * 
; line 4:  * Licensed under the Apache License, Version 2.0 (the "License");
; line 5:  * you may not use this file except in compliance with the License.
; line 6:  * You may obtain a copy of the License at
; line 7:  * 
; line 8:  *     http://www.apache.org/licenses/LICENSE-2.0
; line 9:  * 
; line 10:  * Unless required by applicable law or agreed to in writing, software
; line 11:  * distributed under the License is distributed on an "AS IS" BASIS,
; line 12:  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; line 13:  * See the License for the specific language governing permissions and
; line 14:  * limitations under the License.
; line 15:  * 
; line 16:  */
; line 17: /*
; line 18:  *
; line 19:  * @file osLink.c
; line 20:  *
; line 21:  * @brief 链接(衔接)文件
; line 22:  *
; line 23:  * @note 
; line 24:  *
; line 25:  */
; line 26: 
; line 27: 
; line 28: #include "osConfig.h"
; line 29: #include "osLink.h"
; line 30: #include "STC32G_UART.h"
; line 31: #include "STC32G_Exti.h"
; line 32: /*
; line 33:                                                   变量初始化区
; line 34: */
; line 35: 
; line 36: 
; line 37: 
; line 38: #if (osTaskUseStack_Config > 0)
; line 39: void INT0_ISR_Handler (void) interrupt INT0_VECTOR		
; line 40: {
; line 41: 
; line 42: }
; line 43: #else
; line 44: void INT0_ISR_Handler (void) interrupt INT0_VECTOR	

        RSEG       ?PR?IV?0
        LJMP     INT0_ISR_Handler?_

        RSEG       ?PR?INT0_ISR_HANDLER?_?OSLINK1
        INT0_ISR_Handler?_ PROC
        PUSH     DR28
        PUSH     DR24
        PUSH     DR20
        PUSH     DR16
        PUSH     DR8
        PUSH     DR4
        PUSH     DR0
        PUSH     PSW
        PUSH     DPH                            ; WORD0(DR56)=DPTR
        PUSH     DPL                            ; WORD0(DR56)=DPTR
; line 45: {
; line 46: 
; line 47: 	__asm   { CLR	EA      }
        CLR	EA      
; line 48: 	__asm   { PUSH  DR560    }               
        PUSH  DR560    
; line 49:     __asm   { PUSH  DR28    }               
        PUSH  DR28    
; line 50:     __asm   { PUSH  DR24    }               
        PUSH  DR24    
; line 51:     __asm   { PUSH  DR20    }               
        PUSH  DR20    
; line 52:     __asm   { PUSH  DR16    }               
        PUSH  DR16    
; line 53:     __asm   { PUSH  DR12    }               
        PUSH  DR12    
; line 54:     __asm   { PUSH  DR8     }               
        PUSH  DR8     
; line 55:     __asm   { PUSH  DR4     }               
        PUSH  DR4     
; line 56:     __asm   { PUSH  DR0     }               
        PUSH  DR0     
; line 57:     __asm   { PUSH  PSW     }
        PUSH  PSW     
; line 58:     __asm   { MOV   DR0,DR60}           
        MOV   DR0,DR60
; line 59:     __asm   { MOV   DR4,OsTaskRunTaskHandle}   
        MOV   DR4,OsTaskRunTaskHandle
; line 60:     __asm   { MOV   @WR6,WR2} 
        MOV   @WR6,WR2
; line 61: 	__asm   { SETB  EA    } 
        SETB  EA    
; line 62: 	osTaskNext(); 
        LCALL    osTaskNext?_
; line 63: 	__asm   { CLR	EA      }
        CLR	EA      
; line 64: 	__asm   { MOV   DR4,OsTaskRunTaskHandle}   
        MOV   DR4,OsTaskRunTaskHandle
; line 65:     __asm   { MOV   WR2,@WR6    }   
        MOV   WR2,@WR6    
; line 66:     __asm   { XRL   WR0,WR0     }           
        XRL   WR0,WR0     
; line 67:     __asm   { MOV   DR60,DR0    }           
        MOV   DR60,DR0    
; line 68: 	__asm   { POP   PSW     }               
        POP   PSW     
; line 69:     __asm   { POP   DR0     }               
        POP   DR0     
; line 70:     __asm   { POP   DR4     }               
        POP   DR4     
; line 71:     __asm   { POP   DR8     }               
        POP   DR8     
; line 72:     __asm   { POP   DR12    }               
        POP   DR12    
; line 73:     __asm   { POP   DR16    }               
        POP   DR16    
; line 74:     __asm   { POP   DR20    }               
        POP   DR20    
; line 75:     __asm   { POP   DR24    }               
        POP   DR24    
; line 76:     __asm   { POP   DR28    }               
        POP   DR28    
; line 77:     __asm   { POP   DR56    }  
        POP   DR56    
; line 78:     __asm   { SETB  EA    	} 
        SETB  EA    	
; line 79: 	OsTaskRunTaskHandle;
; line 80: }
        POP      DPL                            ; WORD0(DR56)=DPTR
        POP      DPH                            ; WORD0(DR56)=DPTR
        POP      PSW
        POP      DR0
        POP      DR4
        POP      DR8
        POP      DR16
        POP      DR20
        POP      DR24
        POP      DR28
        RETI     
        ENDP
; line 81: 
; line 82: #endif
; line 83: 
; line 84: 
; line 85: 

        END

