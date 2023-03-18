
/*
 * FreeRTOS STC port V1.0.2
 * 
 * STC32G12K128���ܼ�飺
 *    2�� CAN, 3��Lin, USB, 32λ 8051, RMB5,
 *    �߾�׼12λADC, DMA ֧��(TFT����, ADC, 4�鴮��, SPI, I2C )
 *  
 *  ��λ�û��ں�����ʹ�ù����У���������в���ȷ�ĵط�����
 *  �пɸ��Ƶĵط������STC��ϵ����STC�ٷ�����ͳһ�޸Ĳ����°汾
 *
 *  �����Ĵ������������Ҫ���ñ�������еĲ�����ֲ���룬��������
 *  �����������ע���ο���ʹ����STC��FreeRTOS����ֲ����
*/

#include "FreeRTOS.h"
#include "task.h"
#include "System_init.h"

#include "display.h"
#include "rtc.h"
#include "ntc.h"
#include "adckey.h"
#include "uart2_3.h"
#include "MatrixKey.h"
#include "i2c_ps.h"
#include "pwmb.h"

#include "STC32G_GPIO.h"
#include "STC32G_ADC.h"
#include "STC32G_Exti.h"
#include "STC32G_I2C.h"
#include "STC32G_SPI.h"
#include "STC32G_Timer.h"
#include "STC32G_UART.h"
#include "STC32G_Compare.h"
#include "STC32G_Delay.h"
#include "STC32G_Switch.h"
#include "STC32G_WDT.h"
#include "STC32G_NVIC.h"

void vSystemInit( void );

void delay(unsigned int t)
{
	unsigned long i;

	_nop_();
	i = t * 8293UL;
	while (i) i--;
}




void main( void )
{
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����
    /* ϵͳ��ʼ�� */
    vSystemInit();
	EA = 1;
	ES = 1;

	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2, ���Բ���ѡ��)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		    //��ʼ������2 UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_3);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
	
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			//ѡ�����ʷ�����, BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2, ���Բ���ѡ��)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	UART_Configuration(UART2, &COMx_InitStructure);		    //��ʼ������2 UART1,UART2,UART3,UART4
	NVIC_UART2_Init(ENABLE,Priority_3);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	SBUF = 0x12;
	S2BUF = 0x10;
	while(1){
//		if(SBUF != 0x00){
//			P0 = 0x00;
//		}
	}

	/* �������� */
    xTaskCreate((TaskFunction_t )vDisplayTask,
                (const char*    )"DISPLAY",
                (uint16_t       )configDEFAULT_STACK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )(configDEFAULT_PRIORITIES + 1),
                (TaskHandle_t*  )NULL);
    xTaskCreate((TaskFunction_t )vRtcTask,
                (const char*    )"RTC",
                (uint16_t       )configDEFAULT_STACK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )(configDEFAULT_PRIORITIES + 1),
                (TaskHandle_t*  )NULL);
    xTaskCreate((TaskFunction_t )vAdcKeyTask,
                (const char*    )"ADCKEY",
                (uint16_t       )configDEFAULT_STACK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )(configDEFAULT_PRIORITIES),
                (TaskHandle_t*  )NULL);
    xTaskCreate((TaskFunction_t )vNtcTask,
                (const char*    )"NTC",
                (uint16_t       )configDEFAULT_STACK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )(configDEFAULT_PRIORITIES),
                (TaskHandle_t*  )NULL);
    xTaskCreate((TaskFunction_t )vUart2_3Task,
                (const char*    )"UART2_3",
                (uint16_t       )configDEFAULT_STACK_SIZE,
                (void*          )1000,  //ע��pvParameters��������ַ����������ʱֻ�е�24λ����Чλ�����8λ����ʱ���Զ���0. ��ͨ���������߳�������32�ֽ�����.
                (UBaseType_t    )(configDEFAULT_PRIORITIES),
                (TaskHandle_t*  )NULL);
    xTaskCreate((TaskFunction_t )vMatrixKeyTask,
                (const char*    )"MatrixKey",
                (uint16_t       )configDEFAULT_STACK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )(configDEFAULT_PRIORITIES),
                (TaskHandle_t*  )NULL);
    xTaskCreate((TaskFunction_t )vI2C_PsTask,
                (const char*    )"I2C_PS",
                (uint16_t       )configDEFAULT_STACK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )(configDEFAULT_PRIORITIES),
                (TaskHandle_t*  )NULL);
    xTaskCreate((TaskFunction_t )vPWMB_LedTask,
                (const char*    )"PWMB_LED",
                (uint16_t       )configDEFAULT_STACK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )(configDEFAULT_PRIORITIES),
                (TaskHandle_t*  )NULL);

    /* ���������������ʼ������� */
    vTaskStartScheduler();

    /* ��������²������е��˴� */
    while (1);
}
