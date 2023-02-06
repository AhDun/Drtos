/*------------------------------------------------------------------------------------------------------------------------
 * 文件名称：ByteApp.h

 * 文件内容：

 * 文件版本：1.0.0

 * 文件作者：麦特实验室

 * 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5 

 * 注    意：
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  防重复编译宏配置区
------------------------------------------------------------------------------------------------------------------------*/
#ifndef __ByteApp_h_
#define __ByteApp_h_
/*------------------------------------------------------------------------------------------------------------------------
                                                  函数声明区
------------------------------------------------------------------------------------------------------------------------*/
extern u8 byte_write(u8 byte_data,u8 byte_address,u2 bit_data);
extern u2 byte_read(u8 byte_data,u8 byte_address);
extern u8 byte_not(u8 byte_data);

#endif
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/