/*********************************************************************************************************
* 文件名称：FlasdApp.h
* 摘    要：Flash写字符串/Flash读字符串/Flash续写字符串
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
#ifndef __FlashApp_h_
#define __FlashApp_h_

void outs_Flash(u16 Flash_p,u8 *fp,u8 n);
void ins_Flash(u16 Flash_p,u8 *fp,u8 n);
void outsa_Flash(u16 Flash_p,u8 *fp,u8 n);
u8 inchar_Flash(u16 Flash_p);
void outchar_Flash(u16 Flash_p,u8 sdata);
void DelErase_Flash(u16 Flash_p);

#endif	
