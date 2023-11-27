/*------------------------------------------------------------------------------------------------------------------------
 * 文件名称：System_Uart.h

 * 文件内容：系统串口内核

 * 文件版本：1.0.0

 * 文件作者：麦特实验室

 * 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5 

 * 注    意：
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  防重复编译宏配置区
------------------------------------------------------------------------------------------------------------------------*/
#ifndef __System_Uart_h_
#define __System_Uart_h_

/*------------------------------------------------------------------------------------------------------------------------
                                                  宏定义区
------------------------------------------------------------------------------------------------------------------------*/
#define UART_DAT_Max 128//串口缓冲区的数据最大长度
#define UART_TIMES 5//响应时间（ms）
/*------------------------------------------------------------------------------------------------------------------------
                                                  变量声明区
------------------------------------------------------------------------------------------------------------------------*/
extern u8 xdata UART_DAT[UART_DAT_Max];//串口缓冲区
extern u8 xdata UART_XDAT_SP;//UART_DAT_SP指针
extern u8 xdata UART_SKL;

/*------------------------------------------------------------------------------------------------------------------------
                                                  函数声明区
------------------------------------------------------------------------------------------------------------------------*/
extern void SUARTAppMain();
extern void AUARTAppMain();
extern void Systme_UART_Handle();
extern void Systme_UART_Input();

extern s16 CMD_COMP(const char* a,const char *b);
extern void UARTCMD_Help(const u8 *a);
extern void UARTSystemCmd();
extern void UARTCMD_OUTUART1();
extern void UARTCMD_QueryRunTime();
extern void UARTCMD_INFO();
extern void UARTCMD_ISP();
extern void UARTCMD_RST();
extern void UARTCMD_OPENTU();
extern void UARTCMD_OFFTU();
extern void UARTCMDError();
extern void UARTCMD_OFFTASK();
extern void UARTCMD_POWERIDL();
extern void UARTCMD_POWERPD();
extern void UARTCMD_POWERLOW();
extern void UARTCMD_POWERHIGH();
extern void UARTCMD_OFFWDT();
extern void UARTCMD_OPENWDT();
extern void UARTCMD_OPENTASKAPP();
extern void UARTCMD_OPENAPP();
extern void UARTCMD_SAU();
extern void UARTCMD_PQueryTask();
extern void UARTCMD_QuerySystemTime();
extern void MonitorOutUART();

#endif
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/