/*********************************************************************************************************
* 文件名称：At24c02App.h
* 摘    要：写AT24c02/读AT24c02/AT24c02读字符串/AT24c02写字符串/删除AT24c02所有数据
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
#ifndef __At24c02App_h_
#define __At24c02App_h_

#define I2CIFCON 0 //硬件I2C
//#define I2CIFCON//软件I2C


#define At24c02Address 0xA0

#if I2CIFCON
	/*软件I2C*/
	#define Start  I2cStart
	#define Stop   I2cStop
	#define SendByte I2cSendByte
	#define ReadByte I2cReadByte
	#define SendOk  I2cSendOk
#else
	/*硬件I2C*/
	#define Start  SI2cStart
	#define Stop   SI2cStop
	#define SendByte SI2cSendByte
	#define ReadByte SI2cReadByte
	#define SendOk  SI2cSendOk
#endif
void delay_At24c02();
void At24c02Write(u8 addr,u8 dat);
u8 At24c02Read(u8 addr);
void outs_At24c02(u8 Flash_p,u8 *fp,u8 n);
void ins_At24c02(u8 Flash_p,u8 *fp,u8 n);
void Del_AT24c02();

#endif
