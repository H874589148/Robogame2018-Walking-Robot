#include "stm32f10x.h"
	//������йس�ʼ��
	//��tim4
	/*********
	PB0  �����ƶ�  ��Trig
	PA0  �����ն�  ��Echo
	
	PB1  �����ƶ�  ��Trig
	PA1  �����ն�  ��Echo
	************/
void DIS_A_INT(void);
void DIS_A_INT_1(void);
void Interrupt_init(void);
void Output_init(void);
void exti_init(void);
void timer2_init(u16 arr,u16 psc);
void timer2_IRQ_init(void);
extern float GetDistance_A(void);
extern float GetDistance_B(void);

