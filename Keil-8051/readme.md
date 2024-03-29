### 说明

	在开发之前，你要知道以下几点
	1.我们已经完全适配了STC8A8K64S4A12@22.1184MHz*
	2.你的单片机至少要有11KByte的程序空间和至少50Byte的RAM以及2200Byte的SRAM，只有这样系统才能正常运行**
	3.你的单片机最好支持1T或者更快***
	4.请使用keil5来开发
	5.关于系统的详细内容请参考Readme文件夹下的《DRTOS开发指南》
	
	注释：
	*目前只适配了STC8A8K64S4A12@22.1184MHz，不保证STC8A8K64S4A12的库正确性、稳定性、完整性
	**以上的硬件配置只能保证系统正常运行，不预留用户程序的空间
	***6T/12T单片机也可以运行系统，速度和稳定性可能较低
	
	感谢您DRTOS的支持，也希望DRTOS对于您的学习或者开发有所帮助
	
	注意：虽然本程序相对稳定，但是实用性尚不明确，请勿用到重要的开发上！！

### 文件夹说明

	listing	-keil5信息(.M51 .lst等)
	Objects	-目标文件(.Hex .obj等)
	Uvproj	-keil5工程文件(. uvproj . uvport等)
	Readme  -参考文档、手册资料(.ppt .word等)
	User  	-用户层 	-主要用来放置Main.c文件
	App   	-应用层 	-用户自己开发的通过系统来运行的程序
			|-- App 	-未启用应用层文件
	OS    	-操作系统层 -为操作系统程序 (DRTOS  主要文件就在这)
			|-- OS 		-未启用操作系统层文件
	Func  	-功能层 	-通过软件或者硬件（再或者是软硬结合）实现一些功能的程序
			|-- Func 	-未启用功能层文件
	Drive 	-驱动层 	-直接驱动硬件(寄存器、IO口等)的程序
			|-- Drive 	-未启用驱动层文件
	ASM   	-汇编语言 	-内核启动、任务调度的程序
			|-- ASM 	-未启用汇编语言 文件

### 系统的主要文件

	System_Clock.h/.c 	- 系统时钟文件 , 提供基本的系统时钟服务
	System_Control.h/.c - 系统管理文件 , 提供系统初始化、系统控制等服务
	System_Task.h/.c 	- 系统任务文件 , 提供基本的任务管理、调度等服务
	System_Uart.h/.c 	- 系统串口通信文件 , 提供系统的串口通信服务
	CPU.h/.c			- 任务系统内核，提供系统任务上下文切换

### 基本的外设支持

	必备的：
		Timer_x : 提供系统时钟
	可选的:	
		UART_x 	: 提供串口通信
		WDT 	: 提供看门狗
		Power 	: 提供硬件系统电源管理

### 支持的任务类型

	1.定时任务
	2.条件任务
	3.空任务

