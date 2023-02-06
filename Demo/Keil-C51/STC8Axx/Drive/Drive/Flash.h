/*********************************************************************************************************
* 文件名称：Flash.h
* 摘    要：开启Flash锁/Flash字节读/Flash字节写/Flash扇区擦除
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
#ifndef __Flash_h_
#define __Flash_h_ 

/*宏定义*/
#define IAP_CONTR_Data 0x81//定义IAP控制寄存器状态
#define IAP_CMD_Read 0x01
#define IAP_CMD_Write 0x02
#define IAP_CMD_Erase 0x03

void Flash_Locked();
void Flash_UnLock();
u8 Flash_read(u16 addr); 
void Flash_write(u16 addr,u8 dat);
void Flash_erase(u16 addr);

#endif
