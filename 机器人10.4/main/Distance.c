#include "stm32f10x.h"
#include "delay.h"
#include "Distance.h"
int distance_mm=0,distance_mm_1=0;
int time_us=0,time_us_1=0;
int counter =0,counter_1=0;
int ReadValue=0, ReadValue_1=0;
float T = 15;//温度
int hu=0,rui=0;
void Interrupt_init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;   
	//使能PA端口时钟，并开启复用时钟功能 ，使用外部中断 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//配置IO口为？？下拉输入模式， 最高输出速率为50M 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//初始化PA0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
  	GPIO_Init(GPIOA, &GPIO_InitStructure);			       
	//选定PA0作为外部中断触发源 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);  
	//失能STM32 JTAG烧写功能 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);	
}
 void Interrupt_init_1(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;   
	//使能PA端口时钟，并开启复用时钟功能 ，使用外部中断 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//配置IO口为？？下拉输入模式， 最高输出速率为50M 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//初始化PA0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
  	GPIO_Init(GPIOA, &GPIO_InitStructure);			       
	//选定PA0作为外部中断触发源 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);  
	//失能STM32 JTAG烧写功能 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);	
}

void Output_init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;   
	//使能PB端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	//配置IO口为推挽输出模式， 最高输出速率为50M 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//初始化PB0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
  	GPIO_Init(GPIOB, &GPIO_InitStructure);			       
}
void Output_init_1(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;   
	//使能PB端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	//配置IO口为推挽输出模式， 最高输出速率为50M 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//初始化PB0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
  	GPIO_Init(GPIOB, &GPIO_InitStructure);			       
}
 

void exti_init(void)
{
	//命名一中断变量，一优先级变量 
	EXTI_InitTypeDef EXTI_InitStructure; 		
	NVIC_InitTypeDef NVIC_InitStructure;		 
	
 	//配置中断源及触发方式 
		EXTI_InitStructure.EXTI_Line = EXTI_Line0;               //配置中断线路为0 
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//配置为中断模式      
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //配置为上升沿和下降触发中断 
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;              
  	EXTI_Init(&EXTI_InitStructure);                     
	
	//中断优先级设置  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn ;//外部中断线0中断 
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //打断优先级 1 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//响应优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  	NVIC_Init(&NVIC_InitStructure);							
	
}
 
void exti_init_1(void)
{
	//命名一中断变量，一优先级变量 
	EXTI_InitTypeDef EXTI_InitStructure; 		
	NVIC_InitTypeDef NVIC_InitStructure;		 
	
 	//配置中断源及触发方式 
		EXTI_InitStructure.EXTI_Line = EXTI_Line1;               //配置中断线路为0 
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//配置为中断模式      
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //配置为上升沿和下降触发中断 
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;              
  	EXTI_Init(&EXTI_InitStructure);                     
	
	//中断优先级设置  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn ;//外部中断线0中断 
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //打断优先级 1 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//响应优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  	NVIC_Init(&NVIC_InitStructure);							
	
}

void EXTI0_IRQHandler(void)
{							  
   if(EXTI_GetITStatus(EXTI_Line0) != RESET)	
   {
		EXTI_ClearITPendingBit(EXTI_Line0);
   	
		ReadValue = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0); //读取输入端口PA0的电平 
		
		if(ReadValue==1)
   	{
			hu++;
			counter = 0;
			TIM2->CNT = 0;
			TIM_Cmd(TIM2, ENABLE);  		
		}
		else
		{
		//失能时钟，读取时间
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
   
		ReadValue_1 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1); //读取输入端口PA0的电平 
		
		if(ReadValue_1==1)
   	{
				hu++;//Ceshi
			counter = 0;
			TIM2->CNT = 0;
			TIM_Cmd(TIM2, ENABLE);  		
		}
		else
		{
		//失能时钟，读取时间
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
	
	//配置定时器TIM3 
	TIM_TimeBaseStructure.TIM_Period = arr; //计数阈值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式  
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update); 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); 
}
 
void timer2_IRQ_init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //打断优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应优先级1级
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
	//10us计数一次，10ms触发溢出中断
	timer2_init(999,719);
	timer2_IRQ_init();
}
void DIS_A_INT_1(void){
	Interrupt_init_1();
	Output_init_1();
	exti_init_1();
	//10us计数一次，10ms触发溢出中断
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