#include "stm32f10x.h"
#include "delay.h"
#include "Tracking.h"
#include "SteeringEngine.h"
#include "Configuration1.h"
extern u8 sign;
u8 exti1_sign;
//直走
void goforwards(void){
	setWheel(1,2,40);
	setWheel(2,2,40);
}
//左转
void turn_left(void){
	setWheel(1,2,10);
	setWheel(2,2,70);
}
//右转
void turn_right(void){
	setWheel(1,2,70);
	setWheel(2,2,10);
}

void gobackwards(void){
	setWheel(1,1,40);
	setWheel(2,1,40);
}
void turn_back_left(void){
	setWheel(1,2,70);
	setWheel(2,2,10);
}
void turn_back_right(void){
	setWheel(1,2,10);
	setWheel(2,2,70);
}
//停止
void brake(void){
	setWheel(2,1,0);
	setWheel(1,1,0);
	setWheel(2,2,0);
	setWheel(1,2,0);
}
/*
void back_adjust(void){
	setWheel(1,2,20);
	setWheel(2,2,20);
}
void forwards_adjust(void){
	setWheel(1,1,20);
	setWheel(2,1,20);
}*/
void CarGoLeft(void){
    setWheel(1,1,0);
	 setWheel(2,2,40);
}
void CarGoLeft_1(void){
    setWheel(1,2,40);
	 setWheel(2,1,0);
}
void CarGoRight(void){
	  setWheel(1,1,0);
		setWheel(2,2,40);
	 
}
void CarGoRight_1(void){
 setWheel(1,2,40);
		setWheel(2,2,0);}
/*void CircleLeft_R(void){
   setWheel(1,2,40);
	 setWheel(2,1,40);
	 NVIC_EXTI1_Configuration();
	 while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_1)==0);
	 exti1_sign=1;*/

void CircleRight_R(void){
	setWheel(1,1,40);
	setWheel(2,2,40);
}
void CircleLeft_R(void){
	 setWheel(1,2,40);
	 setWheel(2,1,40);

}
void CircleLeft_B(void){
	setWheel(1,1,40);
	setWheel(2,2,40);

}
