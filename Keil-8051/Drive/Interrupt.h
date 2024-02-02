/*------------------------------------------------------------------------------------------------------------------------
 * �ļ����ƣ�Interrupt.h

 * �ļ����ݣ�

 * �ļ��汾��1.0.0

 * �ļ����ߣ�����

 * ����������STC8A8K64S4A12@22.1184MHzоƬ & Keil uVision 5 

 * ע    �⣺
------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------
                                                  ���ظ������������
------------------------------------------------------------------------------------------------------------------------*/
#ifndef __Interrupt_h_
#define __Interrupt_h_
/*------------------------------------------------------------------------------------------------------------------------
                                                  �궨����
------------------------------------------------------------------------------------------------------------------------*/
#define TINT0 0x00//�ⲿ�ж�0
#define TTIMER0 0x01//��ʱ��0
#define TINT1 0x02//�ⲿ�ж�1
#define TTIMER1 0x03//��ʱ��1
#define TUART1 0x04//����1
#define TADC 0x05//ADC
#define TLVD 0x06//��ѹ���
#define TPCA 0x07//CCP/PCA/PWM
#define TUART2 0x08//����2
#define TSPI 0x09//SPI
#define TPWM 0x0A//��ǿ��PWM
#define TPWMFD 0x0B//��ǿ��PWM�쳣���
#define TINT4 0x0C//�ⲿ�ж�4
#define TCMP 0x0D//�Ƚ���
#define TI2C 0x0E//I2C
#define Tclass1 0x00//�ȼ�1
#define Tclass2 0x01//�ȼ�2
#define Tclass3 0x02//�ȼ�3
#define Tclass4 0x03//�ȼ�4
/*------------------------------------------------------------------------------------------------------------------------
                                                  ����������
------------------------------------------------------------------------------------------------------------------------*/
extern void InterruptTp(u8 Itype,u8 class);

#endif
/*------------------------------------------------------------------------------------------------------------------------
                                                  END
------------------------------------------------------------------------------------------------------------------------*/