/*********************************************************************************************************
* 文件名称：Keyboard.c
* 摘    要：矩阵键盘驱动程序
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
#include"Keyboard.h"
#include"Sdelay.h"

/********************************
函数名称:Keyboarddriver
函数功能:矩阵键盘驱动程序
输入参数:
输    入:
输出参数:键值
输    出:
********************************/
u8 Keyboarddriver()
{
	u8 keyvalue = 0xFF;
	keyboardIO = 0xF0;//列扫描
	if(keyboardIO != 0xF0)
	{
		delay_ms(20);
		if(keyboardIO != 0xF0)//判断按键是否被按下
		{
			switch(keyboardIO) //判断那一列被按下
			{
				case 0xe0:	keyvalue = 0;break;//第一列被按下
				case 0xd0:	keyvalue = 1;break;//第二列被按下	
				case 0xb0:	keyvalue = 2;break;//第三列被按下	
				case 0x70:	keyvalue = 3;break;//第四列被按下 
			}
			keyboardIO = 0x0F;//行扫描
			switch(keyboardIO) //判断那一行被按下
			{
				case 0x0E:	keyvalue = keyvalue;break;//第一行被按下
				case 0x0D:	keyvalue = keyvalue + 4;break;//第二行被按下		
				case 0x0B:	keyvalue = keyvalue + 8;break;//第三行被按下		
				case 0x07:	keyvalue = keyvalue + 12;break;//第四行被按下	 
			}
		}
	}
	return keyvalue;
}
