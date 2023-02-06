/*********************************************************************************************************
* 文件名称：ADApp.h
* 摘    要：读取AD数值/读取单片机上ADC数值
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
#ifndef __ADApp_h_
#define __ADApp_h_

#define SPIIFCON 0 //硬件SPI
//#define SPIFCON 1//软件SPI

/*
0x94//   AIN0 电位器
0xD4//   AIN1 热敏电阻
0xA4//   AIN2 光敏电阻
0xE4//   AIN3 外部输入
*/
void delay_AD();
u16 in_AD(u8 cmd);
u16 SAD_Read(u8 ADCType);

#endif
