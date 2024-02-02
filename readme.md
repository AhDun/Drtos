<img src="./Drtos.png" alt="buffos" style="zoom:70%;" />



### 文件结构

```
|-- .gitignore  --  git过滤文件
|-- LICENSE  --  开源协议
|-- readme.md  --  本文件
|-- Drtos.png  --  logo
|- Tools  --  工具
|- Keil-8051  --  8051内核RTOS
|- Keil-ARM  --  ARM内核RTOS
  |-- filestruct.py  --  文件结构生成脚本
  |-- MDK-ARM Clear.bat  --  MDK-ARM清理批处理文件
  |-- MDK-C51 Clear.bat  --  MDK-C51清理批处理文件
```

### 支持程度

|          |                 8051                 |   ARM   |
| :------: | :----------------------------------: | :-----: |
| 任务调度 |                 支持                 |  支持   |
| 内存管理 |                不支持                |  支持   |
|  信号量  |                不支持                |  支持   |
|   邮箱   |                不支持                |  支持   |
|  软中断  |                不支持                |  支持   |
|  软延时  |                不支持                |  支持   |
| 软定时器 |                不支持                |  支持   |
| 性能统计 |                不支持                |  支持   |
| 电源管理 |                不支持                | 不支持  |
|  栈检查  |                不支持                |  支持   |
| 临界保护 |                 支持                 |  支持   |
|  额外库  | 字节库、字符串库、延时库、串口命令库 | print库 |
|   注释   |                全中文                | 全中文  |
| 技术文档 |                 部分                 |   无    |

#### 任务调度支持程度

|          |   8051   |        ARM         |
| :------: | :------: | :----------------: |
| 调度方式 |  队列式  |       链表式       |
|  优先级  |   16级   |       254级        |
| 最大数量 |   32个   |       无限制       |
| 时间调度 |   支持   |        支持        |
| 中断调度 |   支持   |        支持        |
| 单次运行 |  不支持  |        支持        |
|  栈分配  | 手动分配 | 手动分配、自动分配 |

#### 内存管理支持程度

|          | 8051 |  ARM   |
| :------: | :--: | :----: |
| 管理方式 |  -   | 链表式 |
|   结构   |  -   | 块结构 |
| 碎片整理 |  -   |  支持  |
| 安全释放 |  -   |  支持  |
| 顺序分配 |  -   |  支持  |

#### 信号量支持程度

|                | 8051 |     ARM      |
| :------------: | :--: | :----------: |
|   互斥信号量   |  -   |     支持     |
|   二值信号量   |  -   |     支持     |
|   计数信号量   |  -   |     支持     |
|   信号量广播   |  -   |     支持     |
|     优先级     |  -   | 同任务优先级 |
| 内存分配与释放 |  -   |     自动     |

#### 邮箱信号量支持程度
|                | 8051 |     ARM      |
| :------------: | :--: | :----------: |
|     优先级     |  -   | 同任务优先级 |
| 内存分配与释放 |  -   |     自动     |



### 开源协议


```c
/**
 * Copyright 2020-2024 AhDun. All rights reserved.
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
### 其他

|          |               C51                |               ARM                |
| :------: | :------------------------------: | :------------------------------: |
| 开发周期 | 2020年08月29日 到 2022年03月17日 | 2022年04月18日 到 2023年09月02日 |
|   版本   |              v1.6.8              |              v1.1.0              |
| 实验芯片 |            STC8A8Kxx             |            STM32f4xx             |
|   IDE    |          Keil5(MDK-C51)          |          Keil5(MDK-ARM)          |