/*********************************************************************************************************
* ÎÄ¼þÃû³Æ£ºSPI.c
* Õª    Òª£ºSPI×¨ÓÃÑÓÊ±/SPIÐ­Òé·¢ËÍÊý¾Ý/SPIÐ­Òé¶ÁÈ¡Êý¾Ý
* µ±Ç°°æ±¾£º1.0.0
* ×÷    Õß£ºÂóÌØÊµÑéÊÒ
* Íê³ÉÈÕÆÚ£º
* ÄÚ    ÈÝ£º
* ×¢    Òâ£º
* ¿ª·¢»·¾³£ºSTC8A8K64S4A12@22.1184MHzÐ¾Æ¬ & Keil uVision 5                                                                 
**********************************************************************************************************
* È¡´ú°æ±¾£º
* ×÷    Õß£º
* Íê³ÉÈÕÆÚ£º
* ÐÞ¸ÄÄÚÈÝ£º
* ÐÞ¸ÄÎÄ¼þ£º
*********************************************************************************************************/

#include"Basic.h"
#include"SPI.h"
#include"ADApp.h"
#include"Sdelay.h"

u8 xdata SPIBusy;

#if SPIIFCON
/**********************************************************************************
							      Èí¼þSPI								  	   
**********************************************************************************/
/********************************
º¯ÊýÃû³Æ:SPI_Write
º¯Êý¹¦ÄÜ:SPIÐ­Òé·¢ËÍÊý¾Ý
ÊäÈë²ÎÊý:Êý¾Ý
Êä    Èë:
Êä³ö²ÎÊý:
Êä    ³ö:
********************************/
void SPI_Write(u8 dat)
{
 	u8 a;
	CLK = 0;
	for(a = 0; a < 8; a++)//·¢ËÍÊý¾Ý
	{
	 	if(dat & 0x80)//´Ó×î¸ßÎ»¿ªÊ¼·¢ËÍÊý¾Ý
			DIN = 1;
		else
			DIN = 0;
		dat <<= 1;//×óÒÆÒ»Î»
		CLK = 0;//²úÉúÉÏÉýÑØ£¬Ð´Êý¾Ý
		CLK = 1;
	} 	
}
/********************************
º¯ÊýÃû³Æ: SPI_Rea
º¯Êý¹¦ÄÜ:SPIÐ­Òé¶ÁÈ¡Êý¾Ý
ÊäÈë²ÎÊý:
Êä    Èë:
Êä³ö²ÎÊý:Êý¾Ý
Êä    ³ö:
********************************/
u8 SPI_Read()
{
 	u8 a;
	u8 dat;
	CLK = 0;
	for(a = 0; a < 8; a++)//½ÓÊÕÊý¾Ý
	{
	  	dat <<= 1;//×óÒÆÒ»Î»
		CLK = 1;//²úÉúÏÂ½µÑØ£¬Ð´Êý¾Ý
		CLK = 0;	
		dat |= DOUT;//´Ó×î¸ßÎ»¿ªÊ¼·¢ËÍÊý¾Ý
	}
	return dat;
}
#else


/**********************************************************************************
							      Ó²¼þSPI								  	   
**********************************************************************************/
void SSPI_Init()
{
 	/*SPSTAT  - SPI ×´Ì¬¼Ä´æÆ÷*/
	//bit7
//	SPSTAT &= 0x7F;//SPI ÖÐ¶Ï±êÖ¾Î»

//	SPSTAT |= 0x80;//SPI ÖÐ¶Ï±êÖ¾Î»

	//bit6
//	SPSTAT &= 0xBF;//SPI Ð´³åÍ»±êÖ¾Î»
//	SPSTAT |= 0x40;//SPI Ð´³åÍ»±êÖ¾Î»
    /*SPCTL  - SPI ¿ØÖÆ¼Ä´æÆ÷*/
	//bit7
	SPCTL  &= 0x7F;//SS Òý½ÅÈ·¶¨Æ÷¼þÊÇÖ÷»ú»¹ÊÇ´Ó»ú
//	SPCTL  |= 0x80;//ºöÂÔ SS Òý½Å¹¦ÄÜ£¬Ê¹ÓÃ MSTR È·¶¨Æ÷¼þÊÇÖ÷»ú»¹ÊÇ´Ó»ú
	//bit6
//	SPCTL  &= 0xBF;//¹Ø±Õ SPI ¹¦ÄÜ
	SPCTL  |= 0x40;//Ê¹ÄÜ SPI ¹¦ÄÜ
	//bit5
	SPCTL  &= 0xDF;//ÏÈ·¢ËÍ/½ÓÊÕÊý¾ÝµÄ¸ßÎ»£¨MSB£©

//	SPCTL  |= 0x20;//ÏÈ·¢ËÍ/½ÓÊÕÊý¾ÝµÄµÍÎ»£¨LSB£©
	/*
		bit4
		ÉèÖÃÖ÷»úÄ£Ê½£º
		Èô SSIG£½0£¬Ôò SS ¹Ü½Å±ØÐëÎª¸ßµçÆ½ÇÒÉèÖÃ MSTR Îª 1
		Èô SSIG£½1£¬ÔòÖ»ÐèÒªÉèÖÃ MSTR Îª 1£¨ºöÂÔ SS ¹Ü½ÅµÄµçÆ½£©
		ÉèÖÃ´Ó»úÄ£Ê½£º
		Èô SSIG£½0£¬Ôò SS ¹Ü½Å±ØÐëÎªµÍµçÆ½£¨Óë MSTR Î»ÎÞ¹Ø£©
		Èô SSIG£½1£¬ÔòÖ»ÐèÒªÉèÖÃ MSTR Îª 0£¨ºöÂÔ SS ¹Ü½ÅµÄµçÆ½©
	*/
	//bit4
	SPCTL  &= 0xEF;//Ö÷´ÓÄ£Ê½
//	SPCTL  |= 0x10;//Ö÷´ÓÄ£Ê½
	//bit3
	SPCTL  &= 0xF7;//SCLK ¿ÕÏÐÊ±ÎªµÍµçÆ½£¬SCLK µÄÇ°Ê±ÖÓÑØÎªÉÏÉýÑØ£¬ºóÊ±ÖÓÑØÎªÏÂ½µÑØ
//	SPCTL  |= 0x08;//SCLK ¿ÕÏÐÊ±Îª¸ßµçÆ½£¬SCLK µÄÇ°Ê±ÖÓÑØÎªÏÂ½µÑØ£¬ºóÊ±ÖÓÑØÎªÉÏÉýÑØ
	//bit2
//	SPCTL  &= 0xFB;//Êý¾Ý SS ¹Ü½ÅÎªµÍµçÆ½Çý¶¯µÚÒ»Î»Êý¾Ý²¢ÔÚ SCLK µÄºóÊ±ÖÓÑØ¸Ä±äÊý¾Ý£¬Ç°Ê±ÖÓÑØ²ÉÑùÊý¾Ý£¨±ØSSIG£½0£©
	SPCTL  |= 0x04;//Êý¾ÝÔÚ SCLK µÄÇ°Ê±ÖÓÑØÇý¶¯£¬ºóÊ±ÖÓÑØ²ÉÑù
	/*
	SPR[1:0] | SCLK ÆµÂÊ
	00 		   SYSclk/4
	01 		   SYSclk/8
	10 		   SYSclk/16
	11 		   SYSclk/32 
	*/
	//bit1 - bit0 SPI Ê±ÖÓÆµÂÊÑ¡Ôñ 
	SPCTL  |= 0x00;

	IE2  |= 0x02;//¿ªÆôSPIÖÐ¶Ï
	EA = 1;//¿ªÆô×ÜÖÐ¶Ï
}
void SPIInterrupt() interrupt 9
{
 	SPIBusy = 1;
	SPSTAT &= 0x7F;
}
/********************************
º¯ÊýÃû³Æ:SSPI_Write
º¯Êý¹¦ÄÜ:Ó²¼þSPIÐ­Òé·¢ËÍÊý¾Ý
ÊäÈë²ÎÊý:Êý¾Ý
Êä    Èë:
Êä³ö²ÎÊý:
Êä    ³ö:
********************************/
void SSPI_Write(u8 dat)
{
 	SPIBusy = 0;
	SPCTL |= 0x40;
	delay_us(100); 
	SPDAT = dat;
	while(!SPIBusy);
	SPCTL &= 0xBF;
}
/********************************
º¯ÊýÃû³Æ:SSPI_Rea
º¯Êý¹¦ÄÜ:Ó²¼þSPIÐ­Òé¶ÁÈ¡Êý¾Ý
ÊäÈë²ÎÊý:
Êä    Èë:
Êä³ö²ÎÊý:Êý¾Ý
Êä    ³ö:
********************************/
u8 SSPI_Read()
{
	SPIBusy = 0;
	SPCTL |= 0x40;
	delay_us(100); 
	while(!SPIBusy);
	SPCTL &= 0xBF;
	return SPDAT;
}
#endif

