#include "stm32f10x.h"
	//跟测距有关初始化
	//用tim4
	/*********
	PB0  作控制端  接Trig
	PA0  作接收端  接Echo
	
	PB1  作控制端  接Trig
	PA1  作接收端  接Echo
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

