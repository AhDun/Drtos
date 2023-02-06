/*********************************************************************************************************
* 文件名称：I2C.h
* 摘    要：硬件I2C初始化/硬件I2C中断响应/硬件I2C起始信号/硬件I2C终止信号/通过硬件I2C发送应答信号
			/通过硬件I2C发送非应答信号/通过硬件I2C发送一字节/通过硬件I2C读取一字节
			/软件I2C专用延时/软件I2C起始信号/软件I2C终止信号/通过软件I2C发送应答信号
			/通过软件I2C发送非应答信号/通过软件I2C发送一字节/通过软件I2C读取一字节
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
#ifndef __I2C_h_
#define __I2C_h_

sbit SDA = P1^4;
sbit SCL = P1^5;

void I2CAppMain();

extern u8 xdata I2CBusy;

void delay_I2C();
void I2cStart();
void I2cStop();
void I2cSendOk();
void I2cSendOn();
u2 I2cSendByte(u8 dat);
u8 I2cReadByte();

void SI2CInit();
//void SI2CInterrupt() interrupt 24;
u8 SI2cReadByte();
u2 SI2cSendByte(u8 dat);
void SI2cSendOn();
void SI2cSendOk();
void SI2cStop();
void SI2cStart();

#endif
