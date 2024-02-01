/*********************************************************************************************************
* 文件名称：StepperMotor.h
* 摘    要：步进电机控制
* 当前版本：1.0.0
* 作    者：阿顿
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
#ifndef __StepperMotor_h_
#define __StepperMotor_h_

#define Step1 0x00//步1
#define Step2 0x01//步2
#define Step3 0x02//步3
#define Step4 0x03//步4
#define Step5 0x04//步5
#define Step6 0x05//步6
#define Step7 0x06//步7
#define Step8 0x07//步8

#define S4 0x00//单4拍
#define D4 0x01//双4拍
#define S8 0x02//8拍

sbit MOTO42A = P0^0;//四线双极性进电机A端
sbit MOTO42B = P0^1;//四线双极性进电机B端
sbit MOTO42C = P0^2;//四线双极性进电机C端
sbit MOTO42D = P0^3;//四线双极性进电机D端

sbit MOTO54A = P0^0;//五线四极性进电机A端
sbit MOTO54B = P0^1;//五线四极性进电机B端
sbit MOTO54C = P0^2;//五线四极性进电机C端
sbit MOTO54D = P0^3;//五线四极性进电机D端

void MOTO42r42(u8 AB);
void Motor54(u8 AB,u8 TW);

#endif
