#include "stm32f10x.h"
void goforwards(void);          //保持直行
void turn_left(void);           //向左微调
void turn_right(void);          //向右微调
void gobackwards(void);
void turn_back_left(void);
void turn_back_right(void);
void brake();                   //刹车
void back_adjust(void);         //向后倒车（少距离）
void forwards_adjust(void);     //向前倒车（少距离）
void CarGoLeft(void);           //以左轮为圆心向左转弯,7作为中断源
void CarGoRight(void);          //以右轮为圆心向右转弯.6作为中断源
void CircleLeft_R(void);          //以车轴中点为圆心向左旋转，2作为中断源
void CircleRight_R(void);         //以车轴中点为圆心向右旋转，
void CircleLeft_B(void);          //同上，用于蓝方场地
void CircleRight_B(void);         //  
void CarGoRight_1(void);
void CarGoLeft_1(void);
