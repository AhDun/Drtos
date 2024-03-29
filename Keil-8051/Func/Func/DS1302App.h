/*********************************************************************************************************
* 文件名称：DS1302App.h
* 摘    要：DS1302初始化/读取DS130
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
#ifndef __DS1302App_h_
#define __DS1302App_h_

u8 code ReadRtcAddr[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
u8 code WriteRtcAddr[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
/*存储顺序是            秒    分    时    日    月    周    年   存储格式:是用BCD码*/
u8 xdata RtcTime[7] = {0x00, 0x00, 0x00, 0x01, 0x08, 0x01, 0x20};

void Ds1302_Init();
void in_Ds1302();

#endif 
