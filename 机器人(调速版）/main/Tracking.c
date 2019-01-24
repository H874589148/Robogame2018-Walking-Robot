#include "stm32f10x.h"
#include "delay.h"
#include "Tracking.h"
#include "SteeringEngine.h"
#include "Configuration1.h"
extern u16 speed_l,speed_r,speed_high,speed_low;
//直走
void goforwards(void){
	setWheel(1,2,speed_r);
	setWheel(2,2,speed_l);
}
//左转
void turn_left(void){
	setWheel(1,2,speed_low);
	setWheel(2,2,speed_high);
}
//右转
void turn_right(void){
	setWheel(1,2,speed_high);
	setWheel(2,2,speed_low);
}

void gobackwards(void){
	setWheel(1,1,speed_l);
	setWheel(2,1,speed_l);
}
void turn_back_left(void){
	setWheel(1,1,40);
	setWheel(2,1,0);
}
void turn_back_right(void){
	setWheel(1,1,0);
	setWheel(2,1,40);
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
	 setWheel(2,2,speed_l);
}
void CarGoLeft_1(void){
    setWheel(1,2,speed_r);
	 setWheel(2,1,0);
}
void CarGoRight(void){
	  setWheel(1,1,0);
		setWheel(2,2,speed_l);
	 
}
void CarGoRight_1(void){
 setWheel(1,2,speed_r);
		setWheel(2,2,0);}

void CircleRight_R(void){
	setWheel(1,1,speed_l);
	setWheel(2,2,speed_l);
}
void CircleLeft_R(void){
	 setWheel(1,2,speed_l);
	 setWheel(2,1,speed_l);

}
void CircleLeft_B(void){
	setWheel(1,1,speed_l);
	setWheel(2,2,speed_l);

}
