#include "stm32f10x.h"
#include "delay.h"
#include "Distance.h"
int distance_mm=0,distance_mm_1=0;
int time_us=0,time_us_1=0;
int counter =0,counter_1=0;
int ReadValue=0, ReadValue_1=0;
float T = 15;//�¶�
int hu=0,rui=0;
void Interrupt_init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;   
	//ʹ��PA�˿�ʱ�ӣ�����������ʱ�ӹ��� ��ʹ���ⲿ�ж� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//����IO��Ϊ������������ģʽ�� ����������Ϊ50M 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//��ʼ��PA0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
  	GPIO_Init(GPIOA, &GPIO_InitStructure);			       
	//ѡ��PA0��Ϊ�ⲿ�жϴ���Դ 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);  
	//ʧ��STM32 JTAG��д���� 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);	
}
 void Interrupt_init_1(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;   
	//ʹ��PA�˿�ʱ�ӣ�����������ʱ�ӹ��� ��ʹ���ⲿ�ж� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//����IO��Ϊ������������ģʽ�� ����������Ϊ50M 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//��ʼ��PA0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
  	GPIO_Init(GPIOA, &GPIO_InitStructure);			       
	//ѡ��PA0��Ϊ�ⲿ�жϴ���Դ 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);  
	//ʧ��STM32 JTAG��д���� 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);	
}

void Output_init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;   
	//ʹ��PB�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	//����IO��Ϊ�������ģʽ�� ����������Ϊ50M 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//��ʼ��PB0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
  	GPIO_Init(GPIOB, &GPIO_InitStructure);			       
}
void Output_init_1(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;   
	//ʹ��PB�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	//����IO��Ϊ�������ģʽ�� ����������Ϊ50M 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//��ʼ��PB0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
  	GPIO_Init(GPIOB, &GPIO_InitStructure);			       
}
 

void exti_init(void)
{
	//����һ�жϱ�����һ���ȼ����� 
	EXTI_InitTypeDef EXTI_InitStructure; 		
	NVIC_InitTypeDef NVIC_InitStructure;		 
	
 	//�����ж�Դ��������ʽ 
		EXTI_InitStructure.EXTI_Line = EXTI_Line0;               //�����ж���·Ϊ0 
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//����Ϊ�ж�ģʽ      
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //����Ϊ�����غ��½������ж� 
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;              
  	EXTI_Init(&EXTI_InitStructure);                     
	
	//�ж����ȼ�����  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn ;//�ⲿ�ж���0�ж� 
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //������ȼ� 1 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//��Ӧ���ȼ�0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  	NVIC_Init(&NVIC_InitStructure);							
	
}
 
void exti_init_1(void)
{
	//����һ�жϱ�����һ���ȼ����� 
	EXTI_InitTypeDef EXTI_InitStructure; 		
	NVIC_InitTypeDef NVIC_InitStructure;		 
	
 	//�����ж�Դ��������ʽ 
		EXTI_InitStructure.EXTI_Line = EXTI_Line1;               //�����ж���·Ϊ0 
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//����Ϊ�ж�ģʽ      
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //����Ϊ�����غ��½������ж� 
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;              
  	EXTI_Init(&EXTI_InitStructure);                     
	
	//�ж����ȼ�����  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn ;//�ⲿ�ж���0�ж� 
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //������ȼ� 1 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//��Ӧ���ȼ�0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  	NVIC_Init(&NVIC_InitStructure);							
	
}

void EXTI0_IRQHandler(void)
{							  
   if(EXTI_GetITStatus(EXTI_Line0) != RESET)	
   {
		EXTI_ClearITPendingBit(EXTI_Line0);
   	
		ReadValue = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0); //��ȡ����˿�PA0�ĵ�ƽ 
		
		if(ReadValue==1)
   	{
			hu++;
			counter = 0;
			TIM2->CNT = 0;
			TIM_Cmd(TIM2, ENABLE);  		
		}
		else
		{
		//ʧ��ʱ�ӣ���ȡʱ��
			rui++;
		time_us = 10*TIM_GetCounter(TIM2)+10000*(counter) ;
		distance_mm = time_us*331.45*(1+T/273.15)/2000;

		TIM_Cmd(TIM2, DISABLE);  
	
		} 
   }
	 
}
void EXTI1_IRQHandler(void)
{							  
   if(EXTI_GetITStatus(EXTI_Line1) != RESET)	
   {
		EXTI_ClearITPendingBit(EXTI_Line1);
   
		ReadValue_1 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1); //��ȡ����˿�PA0�ĵ�ƽ 
		
		if(ReadValue_1==1)
   	{
				hu++;//Ceshi
			counter = 0;
			TIM2->CNT = 0;
			TIM_Cmd(TIM2, ENABLE);  		
		}
		else
		{
		//ʧ��ʱ�ӣ���ȡʱ��
			rui++;
		time_us_1 = 10*TIM_GetCounter(TIM2)+10000*(counter) ;
		distance_mm_1= time_us_1*331.45*(1+T/273.15)/2000;

		TIM_Cmd(TIM2, DISABLE);  
	
		} 
   }
	 
}

void timer2_init(u16 arr,u16 psc)
{
	
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//���ö�ʱ��TIM3 
	TIM_TimeBaseStructure.TIM_Period = arr; //������ֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ  
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update); 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); 
}
 
void timer2_IRQ_init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //������ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //��Ӧ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	
}

void TIM2_IRQHandler(void)	  
{
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	counter++;
}

void DIS_A_INT(void){
	Interrupt_init();
	Output_init();
	exti_init();
	//10us����һ�Σ�10ms��������ж�
	timer2_init(999,719);
	timer2_IRQ_init();
}
void DIS_A_INT_1(void){
	Interrupt_init_1();
	Output_init_1();
	exti_init_1();
	//10us����һ�Σ�10ms��������ж�
	timer2_init(999,719);
	timer2_IRQ_init();
}
float GetDistance_A(void){
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	delay_nus(40);
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);	
  return distance_mm;
}
float GetDistance_B(void){
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	delay_nus(40);
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);	
  return distance_mm_1;
}