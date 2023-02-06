/*********************************************************************************************************
* 文件名称：Flash.c
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

#include"Basic.h"
#include"Flash.h"

/********************************
函数名称:Flash_Locked
函数功能:开启Flash锁
输入参数:
输    入:
输出参数:
输    出:
********************************/ 
void Flash_Locked()
{
	 IAP_CONTR = 0;//禁止IAP/IAP操作
     IAP_CMD = 0x00;//去除IAP/IAP命令
	 IAP_TRIG = 0x00;//防止IAP/IAP命令无触发
}
/********************************
函数名称:Flash_UnLock
函数功能:解除Flash锁
输入参数:
输    入:
输出参数:
输    出:
********************************/ 
void Flash_UnLock()
{
	IAP_TRIG = 0x5A;  //先送0x5A，再送B9h到IAP/IAP触发寄存器，每次都需如此
	IAP_TRIG = 0xA5;  //送完0x5A后，IAP/IAP命令立即被触发启动
}
/********************************
函数名称:Flash_read
函数功能:Flash字节读
输入参数:addr(Flash地址)
输    入:
输出参数:Flash对应地址的字节数据
输    出:
********************************/
u8 Flash_read(u16 addr)
{
	 IAP_CONTR = IAP_CONTR_Data;//打开IAP/IAP功能
	 IAP_ADDRH = addr >> 8;//送地址高字节
	 IAP_ADDRL = addr ; //送地址低字节
	 IAP_CMD   = IAP_CMD_Read;//写入读数据命令
	 Flash_UnLock();//解除Flash锁
	 _nop_();//等待Flash完成操作
	 addr = IAP_DATA;//将IAP_DATA寄存器中的数据保存起来
     Flash_Locked();//开启Flash锁 
	 return addr; //返回读到的数据
}
/********************************
函数名称:Flash_write
函数功能:Flash字节写
输入参数:addr(Flash地址)dat(写入字节数据)
输    入:
输出参数:
输    出:
********************************/ 
void Flash_write(u16 addr,u8 dat)
{
	 IAP_CONTR = IAP_CONTR_Data;//打开IAP/IAP功能
	 IAP_ADDRH = addr >> 8;//送地址高字节
	 IAP_ADDRL = addr;//送地址低字节
	 IAP_CMD  = IAP_CMD_Write;//写入写数据命令 
	 IAP_DATA = dat;//写入数据到IAP_DATA寄存器
	 Flash_UnLock();//解除Flash锁
	 _nop_();//等待Flash完成操作
	 Flash_Locked();//开启Flash锁
}
/********************************
函数名称:Flash_erase
函数功能:Flash扇区擦除
输入参数:addr(Flash地址)
输    入:
输出参数:
输    出:
********************************/
void Flash_erase(u16 addr)
{
	 IAP_CONTR = IAP_CONTR_Data;//打开IAP/IAP功能	 
	 IAP_ADDRH = addr >> 8; //送擦除地址高字节
	 IAP_ADDRL = addr; //送擦除地址低字节
	 IAP_CMD = IAP_CMD_Erase;//写入擦除数据命令
	 Flash_UnLock();//解除Flash锁
	 _nop_();//等待Flash完成操作
	 Flash_Locked();//开启Flash锁
}
