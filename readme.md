
                             __ _            
                            / _| |           
                  ___  ___ | |_| |_ ___  ___ 
                 / __|/ _ \|  _| __/ _ \/ __|
                 \__ \ (_) | | | || (_) \__ \
                 |___/\___/|_|  \__\___/|___/
                            
						softos v1.0.0
					  全中文注释、轻量RTOS

---------------------------------欢迎----------------------------------------------
	1.感谢您softos arm的支持，希望softos arm对于您的学习上或者开发上有所帮助
	2.本程序使用Apache License 2.0开源协议
	3.本系统稳定性尚不明确，请勿用到重要的开发上！！！
	4.所有源码均使用GB2312编码

---------------------------------文件夹说明----------------------------------------------
文件结构说明: 
	
	OS	-- 	- 系统源代码
		|-- disable				- 已停止开发的源码
			|--
		|--	stdfunc				- 标准的功能库
			|-- print.c/.h/	- 重写的print函数，与标准的printf函数无异
			|--	str.c/.h		- 字符串处理库
		|--	readme
			|-- readme.md		- 当前文件
		|-- DHS_Main.c/.h		- 系统的主要文件,提供系统初始化、系统控制等服务
		|-- DHS_Clock.h/.c      - 系统时钟文件, 提供基本的系统时钟服务
		|-- DHS_CPU.c/.h		- 系统CPU内核文件 
		|-- DHS_CPUa.asm		- 系统CPU内核汇编文件
		|-- DHS_Post.c/.h		- 系统邮箱与队列文件,提供邮箱与队列服务
		|-- DHS_Signal.c/.h		- 系统信号量文件,提供信号量服务
		|-- DHS_Task.c/.h		- 系统任务文件, 提供基本的任务管理、调度等服务
		|-- DHS_Memory.c/.h		- 系统内存管理文件,提供内存申请、释放
		|-- DHS_Error.c/.h		- 系统错误处理文件
	
---------------------------------移植----------------------------------------------

M3:
	PendSV_Handler函数用于任务上下文切换
	
	



	
	
	