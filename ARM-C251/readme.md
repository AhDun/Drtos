### 文件结构说明

```
|-- readme.md    				 本文件
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
    |-- LinkList.c				 单向链表,双向链表
    |-- print.c					 重写的print函数，与标准的printf函数无异
    |-- str.c					 字符串处理
    |- include					 头文件
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
```

### 移植


```
具体内容请参考 /Drtos/link/ 文件中内容
```

