#include "stm32f10x.h"

void stepper_Init(u16 divNum, double round){
	
	//divNum��ϸ�������ı�ϸ����ҲҪ����ϵ��ڵ�����Ŀǰȡ16
	//������� ÿ��5Ȧ�Ѿ������
	//ת�ٽϿ�ʱ������𽥼��٣���3-5-6�����粻��ֱ�Ӵ�0��5
	//round: ÿ���Ȧ����������Ҫ�ı����
	
	/*******
	����˵����
	PA0-PUL+
	PA1-DIR+
	PUL-��DIR-��GND�뵥Ƭ��������
	����Vcc�ӵ�Դ��9-12V����
	********/
	
	u32	pulseNum = (u32)divNum*200*round;
  u32 arr = 1000000/pulseNum;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);		//����ʱ�� 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);										//��ʼ��IO�� 

	TIM_TimeBaseStructure.TIM_Period = arr-1;	 
	TIM_TimeBaseStructure.TIM_Prescaler =72-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);								//��ʼ����ʱ�� 

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;					//���ö�ʱ������ģʽ 

	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM2, ENABLE); 
	
	TIM_Cmd(TIM2, ENABLE);
	
	TIM_SetCompare1(TIM2,5);						//����5us 
}

void stepper_direction(u8 direction){
	
	//������� 
	//������ת�ٽϿ�ʱ����
	
	if(direction == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
}

void stepper_enable(u8 status){
	
	//�����Ƿ�ת
	//0 ��ת, 1 ת
	
	if(status == 0)
	{
		TIM_Cmd(TIM2, DISABLE);
		
	}
	else
	{
		TIM_Cmd(TIM2, ENABLE);
	}
}
