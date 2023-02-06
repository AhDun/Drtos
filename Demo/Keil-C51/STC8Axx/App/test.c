/*--------------------------------------------------------------------------
文件:test.c
说明:
芯片:STC8A8K64S4A12@22.1184MHz
编写:麦特实验室
--------------------------------------------------------------------------*/

#include "System_Task.h"
#include "test.h"


void led1()
{
	P04 = !P04;
}

void led2()
{
	P01 = !P01;
}

void  ledoff()
{
	P04 = P01 = 1;
	TaskRemove(11);
}

void Step0()
{
	P05 = 0;
	P00 = 0;
	TaskLoad(10,Task_Time,1,1000,Step1);
}
void Step1()
{
	TaskLoad(10,Task_Time,1,3000,Step2);
	TaskLoad(11,Task_Time,1,500,led1);
	P0 = 0xFF;
	P04 = 0;
	P00 = 0;
}
void Step2()
{
	TaskLoad(10,Task_Time,1,5000,Step3);	
	TaskLoad(11,Task_Time,1,10,ledoff);
	P0 = 0xFF;
	P03 = 0;
	P02 = 0;	
}
void Step3()
{
	TaskLoad(10,Task_Time,1,3000,Step4);	
	TaskLoad(11,Task_Time,1,500,led2);
	P0 = 0xFF;
	P01 = 0;
	P03 = 0;	
}
void Step4()
{
	TaskLoad(10,Task_Time,1,5000,Step1);
	TaskLoad(11,Task_Time,1,10,ledoff);
	P0 = 0xFF;
	P00 = 0;
	P05 = 0;
}
