#ifndef __LED_H_
#define __LED_H_

#include "main.h"
#include "osConfig.h"

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

extern _TaskHandle*	TaskHandle_Task1;
extern _TaskHandle*	TaskHandle_Task2;
extern _TaskHandle*	TaskHandle_Task3;
extern _TaskHandle*	TaskHandle_Task4;
extern _Signal* timebz;
extern _SIRQList SIRQ_RTC[3];

void LED_Init(void);
void Task1_Func(char* a);
void Task2_Func(void);
void Task3_Func(u32* a);
void Task4_Func(u32* a);
void Task5_Func(u32* a);

void RTC_Func(void);
void Time_Func(void);



#endif
