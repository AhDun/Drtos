### 文件结构说明

```ABAP
 
|-- .gitignore   				 git过滤文件
|-- LICENSE		 				开源协议
|-- readme.md    				 本文件
|- Doc						 	文档
  |-- Drtos.png			     logo
|- Drtos					    系统源码
  |-- osClock.c					系统时钟文件, 提供基本的系统时钟服务
  |-- osMemory.c				系统内存管理文件,提供内存申请、释放
  |-- osPost.c					系统邮箱文件,提供邮箱服务
  |-- osSignal.c				系统信号量文件,提供信号量服务
  |-- osTask.c					系统任务文件, 提供基本的任务管理、调度等服务
  |- include					头文件
    |-- osClock.h				
    |-- osConfig.h
    |-- osLink.h
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
    |- link						连接文件
      |-- M3M4F					 M3与M4F内核
        |-- osLink.c			
        |-- osLink.s			
|- Template						文件模板
  |-- template.s				汇编文件模板
  |-- template.c				C源码文件模板
  |-- template.h				C源码文件模板
|- Tools						工具
  |-- filestruct.py				文件结构生成脚本
  |-- MDK-ARM Clear.bat			MDK-ARM清理批处理文件
```

### 移植


```livescript
具体内容请参考 /softbufosk/ 文件中内容
```

### 版权


```c
/**
 * Copyright 2022-2023 AhDun. All rights reserved.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
```