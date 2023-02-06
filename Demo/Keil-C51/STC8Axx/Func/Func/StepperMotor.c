/*********************************************************************************************************
* 文件名称：StepperMotor.c
* 摘    要：步进电机控制
* 当前版本：1.0.0
* 作    者：麦特实验室
* 完成日期：
* 内    容：
* 注    意：
* 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5                                                                 
**********************************************************************************************************
* 取代版本：
* 作    者：
* 完成日期：
* 修改内容：
* 修改文件：
*********************************************************************************************************/

#include"Basic.h"
#include"StepperMotor.h"

/********************************
函数名称:Motor42
函数功能:步进电机控制
输入参数:AB(方向)
输入:
输出参数:
输出:
说明:四线双极性进电机
********************************/
void MOTO42r42(u8 AB)
{
 	switch(AB)
	{
 		case 0:MOTO42A = 1;MOTO42B = 0;MOTO42C = 1;MOTO42D = 1;break;
		case 1:MOTO42A = 1;MOTO42B = 1;MOTO42C = 1;MOTO42D = 0;break;
		case 2:MOTO42A = 0;MOTO42B = 1;MOTO42C = 1;MOTO42D = 1;break;
		case 3:MOTO42A = 1;MOTO42B = 1;MOTO42C = 0;MOTO42D = 1;break;
	}
}
/********************************
函数名称:SMotor
函数功能:步进电机控制
输入参数:AB(方向)TW(工作模式)
输入:
输出参数:
输出:
说明:五线四极性进电机
********************************/
void Motor54(u8 AB,u8 TW)
{
 	switch(TW)
	{
	   case 0://单4拍
			switch(AB)
			{
				case 0:MOTO54A = 1;MOTO54B = 0;MOTO54C = 0;MOTO54D = 0;break;
				case 1:MOTO54A = 0;MOTO54B = 1;MOTO54C = 0;MOTO54D = 0;break;
				case 2:MOTO54A = 0;MOTO54B = 0;MOTO54C = 1;MOTO54D = 0;break;
				case 3:MOTO54A = 0;MOTO54B = 0;MOTO54C = 0;MOTO54D = 1;break;
			}
			break;
		case 1://双4拍
			switch(AB)
			{
				case 0:MOTO54A = 1;MOTO54B = 1;MOTO54C = 0;MOTO54D = 0;break;
				case 1:MOTO54A = 0;MOTO54B = 1;MOTO54C = 1;MOTO54D = 0;break;
				case 2:MOTO54A = 0;MOTO54B = 0;MOTO54C = 1;MOTO54D = 1;break;
				case 3:MOTO54A = 1;MOTO54B = 0;MOTO54C = 0;MOTO54D = 1;break;
			}
			break;
		case 2://8拍
			switch(AB)
			{
				case 0:MOTO54A = 1;MOTO54B = 0;MOTO54C = 0;MOTO54D = 0;break;
				case 1:MOTO54A = 1;MOTO54B = 1;MOTO54C = 0;MOTO54D = 0;break;
				case 2:MOTO54A = 0;MOTO54B = 1;MOTO54C = 0;MOTO54D = 0;break;
				case 3:MOTO54A = 0;MOTO54B = 1;MOTO54C = 1;MOTO54D = 0;break;
				case 4:MOTO54A = 0;MOTO54B = 0;MOTO54C = 1;MOTO54D = 0;break;
				case 5:MOTO54A = 0;MOTO54B = 0;MOTO54C = 1;MOTO54D = 1;break;
				case 6:MOTO54A = 0;MOTO54B = 0;MOTO54C = 0;MOTO54D = 1;break;
				case 7:MOTO54A = 1;MOTO54B = 0;MOTO54C = 0;MOTO54D = 1;break;
			}
			break;
	}
}
