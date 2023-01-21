#ifndef __LED_H_
#define __LED_H_

#include "main.h"
#include "osMain.h"

#define delay_ms(a)  osTaskDelayMs(a)

#define Task1_Stack_size 1000
#define Task2_Stack_size 1000 
#define Task3_Stack_size 1000
#define Task4_Stack_size 1000
#define Task5_Stack_size 1000


#define LED1_PORT 			GPIOF   
#define LED1_PIN 			GPIO_Pin_9
#define LED1_PORT_RCC		RCC_AHB1Periph_GPIOF

#define LED2_PORT 			GPIOF   
#define LED2_PIN 			GPIO_Pin_10
#define LED2_PORT_RCC		RCC_AHB1Periph_GPIOF


#define LED1 PFout(9)  	
#define LED2 PFout(10) 



void LED_Init(void);
void Task1_Func(char* a);
void Task2_Func(void);
void Task3_Func(u32* a);
void Task4_Func(u32* a);
void Task5_Func(u32* a);



#endif
