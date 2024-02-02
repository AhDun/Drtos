/*------------------------------------------------------------------------------------------------------------------------
 * 文件名称：Inc_DataType.h

 * 文件内容：基本数据类型定义

 * 文件版本：1.0.0

 * 文件作者：阿顿

 * 开发环境：STC8A8K64S4A12@22.1184MHz芯片 & Keil uVision 5 

 * 注    意：
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  防重复编译宏配置区
------------------------------------------------------------------------------------------------------------------------*/
#ifndef __Inc_DataType_H_
#define __Inc_DataType_H_
/*------------------------------------------------------------------------------------------------------------------------
                                                  数据类型声明区
------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------布尔型--------------------------------------------*/
typedef bit 								bool;
typedef bit 								u2;
typedef bit 								U2;
typedef bit 								u2_t;

/*----------------------------------无符号字符型---------------------------------------*/
typedef unsigned char 			u8;
typedef unsigned char 			uchar;
typedef unsigned char 			UINT8;
typedef unsigned char 			uint8_t;
/*----------------------------------带符号字符型---------------------------------------*/
typedef signed char 				s8;
typedef signed char 				schar;
typedef signed char 				INT8;
typedef signed char 				int8_t;
/*--------------------------------无符号短整型与整型------------------------------------*/
typedef unsigned short int  u16;
typedef unsigned short int  uint;
typedef unsigned short int  UINT16;	
typedef unsigned short int  uint16_t;	
/*------------------------------带符号短整型与整型-------------------------------------*/
typedef signed  int  				s16;	
typedef signed  int  				sint;	
typedef signed  int  				INT16;
typedef signed  int  				int16_t;
/*----------------------------------无符号长整型---------------------------------------*/
typedef unsigned long int  	u32;	
typedef unsigned long int  	luint;
typedef unsigned long int  	UINT32;	
typedef unsigned long int  	uint32_t;
/*----------------------------------带符号长整型---------------------------------------*/
typedef signed long int  		s32;	
typedef signed long int  		lsint;	
typedef signed long int  		INT32;	
typedef signed long int  		int32_t;
/*----------------------------------单精度浮点型---------------------------------------*/
typedef float  							f32;
typedef float  							float_32;
typedef float  							F32;
typedef float  							f32_t;
/*----------------------------------双精度浮点型---------------------------------------*/
typedef double  						d64;
typedef double  						double_64;
typedef double  						D64;
typedef double  						d64_t;
/*------------------------------------------------------------------------------------------------------------------------
                                                  数据类型宏定义区
------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------布尔型--------------------------------------------*/
#define BOOL_MIN						0
#define BOOL_MAX						1
#define u2_MIN							0
#define u2_MAX							1
#define U2_MIN							0
#define U2_MAX							1
#define u2_t_MIN						0
#define u2_t_MAX						1

/*----------------------------------无符号字符型---------------------------------------*/
#define u8_MIN							0
#define u8_MAX							255
#define uchar_MIN						0
#define uchar_MAX						255
#define UINT8_MIN						0
#define UINT8_MAX						255
#define uint8_t_MIN					0
#define uint8_t_MAX					255

/*----------------------------------带符号字符型---------------------------------------*/
#define s8_MIN						 -128
#define s8_MAX							127
#define schar_MIN					 -128
#define schar_MAX						127
#define INT8_MIN					 -128
#define INT8_MAX						127
#define int8_t_MIN				 -128
#define int8_t_MAX					127
/*--------------------------------无符号短整型与整型------------------------------------*/
#define u16_MIN				 			0
#define u16_MAX							65535
#define uint_MIN				 		0
#define uint_MAX						65535
#define UINT16_MIN				 	0
#define UINT16_MAX					65535
#define uint16_t_MIN				0
#define uint16_t_MAX				65535
/*----------------------------------带符号短整型与整型---------------------------------------*/
#define s16_MIN				 		 -32768
#define s16_MAX							32767
#define sint_MIN				 	 -32768
#define sint_MAX						32767
#define INT16_MIN				 	 -32768
#define INT16_MAX					  32767
#define int16_t_MIN				 -32768
#define int16_t_MAX					32767
/*----------------------------------无符号长整型---------------------------------------*/
#define u32_MIN				 		  0
#define u32_MAX							4294967295
#define luint_MIN				 		0
#define luint_MAX						4294967295
#define UINT32_MIN				 	0
#define UINT32_MAX					4294967295
#define uint32_t_MIN				0
#define uint32_t_MAX				4294967295
/*----------------------------------带符号长整型---------------------------------------*/
#define s32_MIN				 		 -2147483648
#define s32_MAX							2147483647
#define lsint_MIN				 	 -2147483648
#define lsint_MAX						2147483647
#define INT32_MIN				 	 -2147483648
#define INT32_MAX						2147483647
#define int32_t_MIN				 -2147483648
#define int32_t_MAX					2147483647

/*----------------------------------单精度浮点型---------------------------------------*/
#define f32_MIN				 		  10e-37
#define f32_MAX							10e38
#define float_32_MIN				10e-37
#define float_32_MAX				10e38
#define F32_MIN					 		10e-37
#define F32_MAX							10e38
#define f32_t_MIN					 	10e-37
#define f32_t_MAX						10e38


/*----------------------------------双精度浮点型---------------------------------------*/
#define d64_MIN				 		  10e-37
#define d64_MAX							10e308
#define double_64_MIN				10e-37
#define double_64_MAX				10e308
#define D64_MIN				 		  10e-37
#define D64_MAX							10e308
#define d64_t_MIN				 		10e-37
#define d64_t_MAX						10e308

#endif
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/