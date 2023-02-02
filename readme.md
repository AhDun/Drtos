```c++
                         __ _            
                        / _| |           
              ___  ___ | |_| |_ ___  ___ 
             / __|/ _ \|  _| __/ _ \/ __|
             \__ \ (_) | | | || (_) \__ \
             |___/\___/|_|  \__\___/|___/
  					softos v1.1.0
				  全中文注释、轻量RTOS
```

### 欢迎

```c
     
  	1.感谢您softos arm的支持
​	2.本程序使用Apache License 2.0开源协议
​	3.本系统稳定性尚不明确，请勿用到重要的开发上！！！
​	4.所有源码均使用GB2312编码
```

### 文件结构说明

```c
 
|-- .gitignore   				git过滤文件
|-- LICENSE		 				开源协议
|-- readme.md    				本文件
|- Doc							文档
  |-- AhDun.png					logo
  |-- DHS_logo.png				logo
  |-- DHS_logo_r.png			logo
|- softos						系统源码
  |-- osClock.c					系统时钟文件, 提供基本的系统时钟服务
  |-- osCPU.s					系统CPU内核汇编文件
  |-- osCPU.c					系统CPU内核文件 
  |-- osMemory.c				系统内存管理文件,提供内存申请、释放
  |-- osPost.c					系统邮箱文件,提供邮箱服务
  |-- osSignal.c				系统信号量文件,提供信号量服务
  |-- osTask.c					系统任务文件, 提供基本的任务管理、调度等服务
  |- include					头文件
    |-- osClock.h				
    |-- osConfig.h
    |-- osCPU.h
    |-- osMemory.h
    |-- osPost.h
    |-- osSignal.h
    |-- osTask.h
  |- stdfunc					标准的功能库						
    |-- LinkList.c				单向链表,双向链表
    |-- print.c					重写的print函数，与标准的printf函数无异
    |-- str.c					字符串处理
    |- include
      |-- LinkList.h
      |-- print.h
      |-- str.h
|- Template						文件模板
  |-- template.s				汇编文件模板
  |-- template.c				C源码文件模板
  |-- template.h				C源码文件模板
|- Tools						工具
  |-- filestruct.py				文件结构生成脚本
  |-- MDK-ARM Clear.bat			MDK-ARM清理批处理文件
```

### 移植