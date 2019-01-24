#include "stm32f10x.h"
u8 zhang=0,xue=0;
void TIM_PWM_Init(){
	
	//控制舵机的定时器PWM波输出初始化 
	
	/*********
	标*的为使用到的5个引脚
	TIM4-CH1 PB6     1正转
	     CH2 PB7
	     CH3 PB8      2正转
	     CH4 PB9
	************/
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 99; 	 //
	TIM_TimeBaseStructure.TIM_Prescaler = 71; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  TIM_OCInitStructure.TIM_Pulse = 0; 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
		TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM4, ENABLE); 
  TIM_Cmd(TIM4, ENABLE); 
//	
}


void setWheel(u16 num, u16 dire,u16 v){
	if(num==1)
	{if(dire==1)
		{zhang=1;
		TIM_SetCompare1(TIM4,v);}
		else
		TIM_SetCompare2(TIM4,v);}
else 
{if(dire==1)
		TIM_SetCompare3(TIM4,v);
		else
		TIM_SetCompare4(TIM4,v);}	}
		
	
