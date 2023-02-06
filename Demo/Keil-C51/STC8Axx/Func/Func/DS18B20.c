/*********************************************************************************************************
* 文件名称：DS18B20.c
* 摘    要：
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
#include"DS18B20.h"
#include"Sdelay.h"

/********************************
函数名称:DS_Init
函数功能:单总线初始化时序
输入参数:
输    入:
输出参数:
输    出:
********************************/
u2 DS_Init() reentrant 
{
	u8 i;
	DS = 1;
	delay_us(1);
	DS = 0;
	delay_us(500); //拉低总线499.45us 挂接在总线上的18B20将会全部被复位
	DS = 1; //释放总线
	delay_us(38); //延时37.95us 等待18B20发回存在信号
	i = DS;
	delay_us(142); //141.95us
	DS = 1;
	delay_us(1);
	return i;
}
/********************************
函数名称:DS_Write
函数功能:单总线写字节数据
输入参数:dat(字节数据)
输    入:
输出参数:
输    出:
********************************/
void DS_Write(u8 dat)
{
	u8 a;
	for(a = 0;a < 8; a++)
	{
		DS = 0;
		delay_us(1);//产生些时序
		DS = dat & 0x01;
		delay_us(77);//76.95us
		DS = 1; //释放总线准备下一次数据写入
		delay_us(1);
		dat >>= 1;
	}
}
/********************************
函数名称:DS_DS_Read
函数功能:单总线读字节数据
输入参数:
输    入:
输出参数:读取字节数据
输    出:
********************************/
u8 DS_Read()
{
	u8 a,dat;
	for(a = 0;a < 8; a++)
	{
		DS = 0;
		delay_us(1);//产生读时序
		DS = 1;
		dat >>= 1;
		delay_us(1);//释放总线
		if(DS)
			dat |= 0x80;
		delay_us(77);//76.95us
		DS = 1;
		delay_us(1);
	}
	return dat;
}
