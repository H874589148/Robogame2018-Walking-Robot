//STLINK PA13 PA14
#include "stm32f10x.h"
#include "math.h"
#include "stdio.h"
#include "delay.h"
#include "SteeringEngine.h"
#include "Distance.h"
#include "sys.h"
#include "usart.h"
#include "rfid.h"
#include "Configuration1.h"
#include "Tracking.h"
//ALIENTEKÕ½½¢STM32¿ª·¢°åÊµÑé4
//´®¿ÚÊµÑé  
//¼¼ÊõÖ§³Ö£ºwww.openedv.com
//¹ãÖİÊĞĞÇÒíµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾ 

void delay_nus(u32);           //72MÊ±ÖÓÏÂ£¬Ô¼ÑÓÊ±us
void delay_nms(u32);            //72MÊ±ÖÓÏÂ£¬Ô¼ÑÓÊ±ms
 void detect(u8 num);              //Ñ°ÕÒÏàÓ¦±ê¼Ç
u8 read1(void);               //¶Á³ö±àºÅÎª1µÄRFIDÊı¾İPA9£¬PA10£¬×ó²àrfid¶Á¿¨Æ÷
u8 read2(void);               //¶Á³ö±àºÅÎª2µÄRFIDÊı¾İPA2£¬PA3£¬×ßÓÒ²à¶Á¿¨Æ÷
void USART3_Configuration(void);
void TIM3_Init(void){
		
	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	  //¶¨Òå¸ñÊ½ÎªTIM_TimeBaseInitTypeDefµÄ½á¹¹ÌåµÄÃû×ÖÎªTIM_TimeBaseStructure  

  	TIM_TimeBaseStructure.TIM_Period =9999;		  // ÅäÖÃ¼ÆÊıãĞÖµÎª9999£¬³¬¹ıÊ±£¬×Ô¶¯ÇåÁã£¬²¢1ms´¥·¢ÖĞ¶Ï
  	TIM_TimeBaseStructure.TIM_Prescaler =71;		 //	 Ê±ÖÓÔ¤·ÖÆµÖµ£¬³ıÒÔ¶àÉÙ
  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	// Ê±ÖÓ·ÖÆµ±¶Êı
  	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// ¼ÆÊı·½Ê½ÎªÏòÉÏ¼ÆÊı

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);		 //	 ³õÊ¼»¯tim3
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //Çå³ıTIM3Òç³öÖĞ¶Ï±êÖ¾
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);   //  Ê¹ÄÜTIM3µÄÒç³ö¸üĞÂÖĞ¶Ï
    TIM_Cmd(TIM3,DISABLE);				 //		   Ê¹ÄÜTIM3
}
int i=0;
u8 success=0;
u8 duoji_success=0;
u8 RxData;
u8 j=0,k=0,b=0;
u8 mission=0;//0±íÊ¾ºì·½³¡µØ£¬1±íÊ¾À¶·½³¡µØ£¬²âÊÔÆÚ¼ä¾ùÄ¬ÈÏÎª0
u8 direction=1;
float dis_1=0,dis_11=0,dis_12=0,disA=0;
int t;
u8 f1,f2;//ºìÍâ¶Ô¹ÜµÄout
u8 f3,f4,f5,f6,f11,f7,f8,f9,f10,f12;
u8 t1,t2,t3,t4;
u8 a=0x00;//¶Á³öµÄRFIDµÚÒ»¿éÊı¾İ
u8 num1;
u8 carpos=0;//¼ÇÂ¼³µËùÔÚµÄÎ»Ö
u8 flag_count=0;
u8 temp;
u8 high_flag1,high_flag2,temp1=0,temp2=0;
u16 speed_low,speed_l,speed_r,speed_high;
int flag1=0,ok=0,chen=0,ii=0,jj=0,ruo=0,xi=0,wu=0,shuang=0;
void assert_failed(uint8_t* file, uint32_t line)
{
 printf("Wrong parameters value: file %s on line %d\r\n", file, line);
 while(1);
}
void abitslower(void){
	speed_l=30;
	speed_r=32;
	speed_low=0;
	speed_high=60;
}
void normal(void){
 speed_low=10;
 speed_l=40;
 speed_r=43;
 speed_high=70;
}
void abitfaster(void){
	speed_l=60;
	speed_r=67;
	speed_high=90;
	speed_low=30;
}
void track0(){
	f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_1);
		f2=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2);
		if(f1==1&&f2==1){
			 gobackwards(); 
		 }
		 else if(f1==0&&f2==1){
		   turn_back_left();
		 }
		 else if(f1==1&&f2==0){
			  turn_back_right();
		 }
		 else{
		    gobackwards();
		 }
}

	
void track1(){
	  f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_1);
		f2=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2);
		if(f1==1&&f2==1){
			 goforwards(); 
		 }
		 else if(f1==0&&f2==1){
		   turn_left();
		 }
		 else if(f1==1&&f2==0){
			  turn_right();
		 }
		 else{
		    goforwards();
		 }
}
void track2_A(){
	f3=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_3);
//		 f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);
//		 f5=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11);
		 f6=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);
		 if(f3==1&&f6==1){
			 goforwards();
		 }
		 else if((f3==0)&&(f6==1)){
			 turn_right();
		 }
		 else if((f3==1)&&(f6==0)){
			 turn_left();
		 }
		 else{
			 goforwards();
		 }
}	

void track2(){ 
		 f3=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_3);
		 f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);
		 f5=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11);
		 f6=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);
		 if(f3==1&&f4==1&&f5==1&&f6==1){
			 goforwards();
		 }
		 else if((f3==0||f5==0)&&(f4==1||f6==1)){
			 turn_right();
		 }
		 else if((f3==1||f5==1)&&(f4==0||f6==0)){
			 turn_left();
		 }
		 else{
			 goforwards();
		 }
}	
void track3(){
	f3=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_3);//7
		 f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//8
		 f5=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11);//6
		 f6=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);//5
		 if(f3==1&&f4==1&&f5==1&&f6==1){
			 gobackwards();
		 }
		 else if((f3==0||f5==0)&&(f4==1||f6==1)){
			 turn_back_left();
		 }
		 else if((f3==1||f5==1)&&(f4==0||f6==0)){
			 turn_back_right();
		 }
		 else{
			 gobackwards();
		 }
}	
void go_n_step(u8 m){
	  f11=0;
	while(m){
		while(!f11){
			goforwards();
			f11=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_7);
		  f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
		  f6=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);//5
			if(wu==0){
			  if(f4==1&&f6==0){
					setWheel(2,2,0);
		      setWheel(1,2,40);
				  delay_nus(500);}
			else if(f4==0&&f6==1){
				   setWheel(2,2,40);
				   setWheel(1,2,0);
				   delay_nus(500);}
			else if(f4==1&&f6==1){
					wu=1;
			    goforwards();
			}
			else 
			delay_nms(1);
			}
		else 
			delay_nms(1);}
		while(f11){
			goforwards();
			f11=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_7);
			delay_nms(1);
		}
		m--;
		wu=0;
	}
		brake();
}
void back_n_step(u8 m){
	  f11=0;
	while(m){
		while(!f11){
			gobackwards();
			f11=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_8);
			f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
		  f6=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);//5
			if(shuang==0){
			  if(f4==1&&f6==0){
					
		      setWheel(2,1,0);
					setWheel(1,1,40);
				  delay_nus(500);}
			  else if(f4==0&&f6==1){
					setWheel(2,1,40);
		      setWheel(1,1,0);
				  delay_nus(500);
				}
				else if(f4==1&&f6==1)
					shuang=1;
			  else 
			    delay_nms(1);
			}
		 else 
			  delay_nms(1);
		}
		while(f11){
			gobackwards();
			f11=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_8);
			delay_nms(5);
		}
	m--;
		shuang=0;
	}
		  brake();
}
void go_n_step_1(u8 m){
	  f11=0;
	while(m){
		while(!f11){
			goforwards();
			f11=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_5);
		  f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
		  f6=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);//5
			if(wu==0){
			  if(f4==1&&f6==0){
					
					setWheel(2,2,0);
		      setWheel(1,2,40);
				  delay_nus(500);}
			else if(f4==0&&f6==1){
				   setWheel(2,2,40);
				   setWheel(1,2,0);
				   delay_nus(500);}
			else if(f4==1&&f6==1){
					wu=1;
				goforwards();
			}
			else 
			delay_nms(5);
			}
		else 
			delay_nms(5);}
		while(f11){
			goforwards();
			f11=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_5);
			delay_nms(5);
		}
		m--;
		wu=0;
	}
		brake();
}
void back_n_step_1(u8 m){
	  f11=0;
	while(m){
		while(!f11){
			gobackwards();
			f11=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_6);
			f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
		  f6=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);//5
			if(shuang==0){
			  if(f4==1&&f6==0){
					
		      setWheel(2,1,40);
					setWheel(1,1,0);
				  delay_nus(500);}
			  else if(f4==0&&f6==1){
					setWheel(2,1,0);
		      setWheel(1,1,40);
				  delay_nus(500);
				}
				else if(f4==1&&f6==1)
					shuang=1;
			  else 
			    delay_nms(5);
			}
		 else 
			  delay_nms(5);
		}
		while(f11){
			gobackwards();
			f11=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_6);
			delay_nms(5);
		}
	m--;
		shuang=0;
	}
		  brake();
}
void go_back_1(){
	  f12=0;
		while(!f12){
      gobackwards();
			f12=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_13);
			delay_nms(10);
		}
		while(f12){
			gobackwards();
			f12=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_13);
			delay_nms(10);
		}
		brake();
}
void turn_0(){
   f11=0;
		while(!f11){
			CircleRight_R();
			f11=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_7);
			delay_nms(10);
		}
		while(f11){
			CircleRight_R();
			f11=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_7);
			delay_nms(10);
		}
		brake();
}
void turn_0_1(){
   f9=0;
		while(!f9){
			CircleLeft_R();
			f9=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_5);
			delay_nms(10);
		}
		while(f9){
			CircleLeft_R();
			f9=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_5);
			delay_nms(10);
		}
		brake();
}
//·µ»ØÊ±×ªÍä³ÌĞò
void turn_1(){
	 f2=0;
	while(!f2){
			CircleLeft_R();
			f2=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_1);
			delay_nms(10);
	}
		while(f2){
			CircleLeft_R();
			f2=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_1);
			delay_nms(10);}
		brake();
}
void turn_1_1(){
	 f2=0;
	while(!f2){
			CircleRight_R();
			f2=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2);
			delay_nms(10);
	}
		while(f2){
			CircleRight_R();
			f2=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2);
			delay_nms(10);}
		brake();
}
void turn_2(){
  f1=0;
	while(!f1){
			CircleLeft_R();
			f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_1);
			delay_nms(10);
		}
		while(f1){
			CircleLeft_R();
			f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_1);
			delay_nms(10);
		}
}
void turn_2_1(){
  f2=0;
	while(!f2){
			CircleRight_R();
			f2=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2);
			delay_nms(10);
		}
		while(f2){
			CircleRight_R();
			f2=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2);
			delay_nms(10);
		}
}
//µÚ¶ş´ÎÀ´Ê±È¥¸ß¸Ë×ªÍä³ÌĞò
void turn_22(void){
		u8 m;
	  u8 n;
		f1=0;
		while(!f1){
			CircleLeft_R();
			f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);
			delay_nms(10);
		}
		while(f1){
			CircleLeft_R();
			f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);
			delay_nms(10);
		}
			m=1;
	while(m){
		while(!f1){
			CircleLeft_R();
			f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_1);
			delay_nms(10);
		}
		while(f1){
			CircleLeft_R();
			f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_1);
			delay_nms(10);
		}
		m--;
	}
		brake();
}
void turn_22_1(void){
	u8 m;
	u8 n;
		f1=0;
		while(!f1){
			CircleLeft_R();
			f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);
			delay_nms(10);
		}
		while(f1){
			CircleLeft_R();
			f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);
			delay_nms(10);
		}
		m=1;
	while(m){
		while(!f1){
			CircleRight_R();
			f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2);
			delay_nms(10);
		}
		while(f1){
			CircleRight_R();
			f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2);
			delay_nms(10);
		}
		m--;
	}
		brake();
}
//È¥¸ß¸ËÖ±×ß³ÌĞò
void go_1(){
	u8 m=2;
	while(m){ 
	while(!f4){
			track1();
			f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
			delay_nms(10);
	 }
		while(f4){
			track1();
			f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
			delay_nms(10);
		}
		m--;
	}
  brake();
}
//¸ß¸Ë´¦µÄ×ªÍä
void turn_3(){
	 while(!f4){
			CarGoLeft_1();
			f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
			delay_nms(10);
	 }
	 while(f4){
			CarGoLeft_1();
			f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
			delay_nms(10);
	 }
		  brake();
}
void turn_3_1(){
	 while(!f6){
			CarGoLeft();
				f6=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);//5
			delay_nms(10);
	 }
	 while(f6){
			CarGoLeft();
				f6=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);//5
			delay_nms(10);
	 }
		  brake();
}
void turn_6(void){
  f4=0;
	while(!f4){
		CarGoRight();
	  f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
		delay_nms(2);
	}
	while(f4){
		CarGoRight();
	  f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
		delay_nms(2);
	}
	brake();
	while(!f4){
		goforwards();
		f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);
		delay_nms(2);
	}
	while(f4){
		goforwards();
		f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);
		delay_nms(2);
	}
	brake();
	while(!f4){
	f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
	CircleLeft_R();
	delay_nms(2);
	}
	while(f4){
	f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
	CircleLeft_R();
	delay_nms(2);
	}
	brake();
}
void turn_6_1(void){
f4=0;
	while(!f4){
		CarGoRight();
	  f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
		delay_nms(2);
	}
	while(f4){
		CarGoRight();
	  f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
		delay_nms(2);
	}
	brake();
	while(!f4){
		goforwards();
		f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);
		delay_nms(2);
	}
	while(f4){
		goforwards();
		f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);
		delay_nms(2);
	}
	brake();
	while(!f4){
	f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
	CircleLeft_R();
	delay_nms(2);
	}
	while(f4){
	f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
	CircleLeft_R();
	delay_nms(2);
	}
	brake();
}
void goforwards_distance(float n_dis){
	float dis,dis1,dis2;
	dis1=GetDistance_A();
	delay_nms(60);
	dis2=GetDistance_A();
	delay_nms(60);
	dis=(dis1+dis2)/2.0;
	if(dis>n_dis)
	  while(dis>n_dis){
		  track1();
		  dis1=GetDistance_A();
		  delay_nms(60);
		  dis2=GetDistance_A();
		  delay_nms(60);
		  dis=(dis1+dis2)/2.0;
	  }
	else if(dis<n_dis)
	  while(dis<n_dis){
		 setWheel(1,1,40);
			setWheel(2,1,40);
		  dis1=GetDistance_A();
		  delay_nms(60);
		  dis2=GetDistance_A();
		  delay_nms(60);
		  dis=(dis1+dis2)/2.0;
	  }
	brake();
}
void action_1(){
   
	 if(a==0x01||a==0x02){
		if(a==0x01)
			USART_SendData(USART3, 'F');
		else
			USART_SendData(USART3, 'G');
		while(duoji_success==0){
			delay_nms(10);
		}
		duoji_success=0;
		flag_count++;
   }
	else if(a==0x03){
		high_flag1=carpos;
	}
	else if(a==0x04){
		high_flag2=carpos;
	}
	else ; 
	 
	 
	 a=0x00;
}
void action_1_1(){
   
	  if(a==0x07||a==0x08){
	
		if(a==0x07)
			USART_SendData(USART3, 'F');
		else
			USART_SendData(USART3, 'G');
		while(duoji_success==0){
			delay_nms(10);
		}
		duoji_success=0;
		flag_count++;
   }
	else if(a==0x05){
		high_flag1=carpos;
	}
	else if(a==0x06){
		high_flag2=carpos;
	}
	else ; 
	 
	 
	 a=0x00;
}
int main(void)
{
	RCC_Configuration();
	GPIO_Configuration();
  DIS_A_INT();
	DIS_A_INT_1();
	GPIOG_Configuration();
	USART3_Configuration();
	TIM3_Init();
	TIM_PWM_Init();
  normal();//³£¹æËÙ¶È
	while(success==0){
		USART_SendData(USART3, 'a');//×÷ÎªÉÏµçÌáÊ¾
		delay_nms(1);
	}
	while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_9)==1){
		delay_nms(1);
	}
	//Ñ¡ÔñÈÎÎñ³¡µØ
	if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_0)==0)
	{
		mission = 1;
	}
	else
		{
			mission = 0;
		}

	//µÚÒ»½×¶ÎÑ­¼££¬´Ó³ö·¢ÇøÊ¼·¢£¬ÏòÇ°ĞĞ
		if(mission==1){
  goforwards_distance(80);
	carpos=1;
  while(a==(u8)0x00){
	  a=read2();
	}
	action_1();
	goforwards_distance(120);
	turn_0();
	carpos=2;
	while(carpos<=8){
  go_n_step(1);
	while(a==(u8)0x00){
		a=read1();
	}
	if(a==0x01||a==0x02){
		if(a==0x02)
			USART_SendData(USART3, 'B');
		if(carpos<8)
		   turn_2();
		else
			turn_22();
		goforwards_distance(80);
		while(duoji_success==0&&a==0x02){
			delay_nms(1);
		}
		duoji_success=0;
		if(a==0x01)
			USART_SendData(USART3, 'C');
		else
			USART_SendData(USART3, 'E');
		while(duoji_success==0){
			delay_nms(1);
		}
		duoji_success=0;
		flag_count++;
		goforwards_distance(120);
		turn_0();
   }
	else if(a==0x03){
		high_flag1=carpos;
	}
	else if(a==0x04){
		high_flag2=carpos;
	}
	else ;
	carpos++;
	a=0x00;
	}
	//ÓÃtemp1¼ÇÂ¼±È½Ï¿¿½üÆì¸ËµÄü
		//if(high_flag1>high_flag2)
		//{temp1=high_flag1;
		//	temp2=high_flag2;}
		//else{temp2=high_flag1;
		//	temp1=high_flag2;
		//flag1=1;}
  temp1=high_flag1;
	temp2=high_flag2;
	turn_6();
	t=500;
	while(t){
		track2();
		t--;
	}
	while(dis_1>180||dis_1<10){
			track2();
	  	dis_11=GetDistance_B();
	  	delay_nms(60);
	  	dis_12=GetDistance_B();
	  	delay_nms(60);
	 		dis_1=(dis_11+dis_12)/2.0;
	}
	dis_1=GetDistance_B();
	while(dis_1>180||dis_1<10){
			track2();
	  	delay_nms(60);
		  dis_11=GetDistance_B();
	  	delay_nms(60);
	  	dis_12=GetDistance_B();
	 		dis_1=(dis_11+dis_12)/2.0;
	}
	brake();
	USART_SendData(USART3, 'P');
	while(duoji_success==0){
		delay_nms(10);
	}
	duoji_success=0;
	delay_nms(500);
	go_back_1();
	turn_1();
	if(temp1<8){
		 goforwards_distance(120);
	   turn_0();
     back_n_step(8-temp1);
	   turn_2();
	}		
	goforwards_distance(80);
	USART_SendData(USART3, 'C');
	while(duoji_success==0){
			delay_nms(10);
	}
	duoji_success=0;
	goforwards_distance(120);
	turn_0();
	if(temp1>temp2)
	   back_n_step(temp1-temp2);
	else
		 go_n_step(temp2-temp1);
	turn_2();
	goforwards_distance(80);
	USART_SendData(USART3,'E');
	while(duoji_success==0){
			delay_nms(10);
	}
	duoji_success=0;
	delay_nms(500);
	goforwards_distance(120);
	turn_0();
	go_n_step(8-temp2);
	turn_1_1();
	go_1();
	turn_3();
	f1=1;
	while(f1){
		f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12);
		if(f1==0){
			delay_nus(20);
			f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12);
			if(f1==0){
				brake();
				break;
			}
		}
		track2();
	}
	while(duoji_success==0){
	USART_SendData(USART3, 'D');
	}
}
else if(mission==0){
	goforwards_distance(80);
	carpos=1;
  while(a==(u8)0x00){
	  a=read2();
	}
	action_1_1();
	goforwards_distance(120);
	turn_0_1();
	carpos=2;																																							
	while(carpos<=8){
  go_n_step_1(1);
	while(a==(u8)0x00){
		a=read1();
	}
	if(a==0x07||a==0x08){
		if(a==0x08)
			USART_SendData(USART3, 'B');
		if(carpos<8)
		   turn_2_1();
		else
			turn_22_1();
		goforwards_distance(80);
		while(duoji_success==0&&a==0x08){
			delay_nms(1);
		}
		duoji_success=0;
		if(a==0x07)
			USART_SendData(USART3, 'C');
		else
			USART_SendData(USART3, 'E');
		while(duoji_success==0){
			delay_nms(1);
		}
		duoji_success=0;
		flag_count++;
		goforwards_distance(120);
		turn_0_1();
   }
	else if(a==0x05){
		high_flag1=carpos;
	}
	else if(a==0x06){
		high_flag2=carpos;
	}
	else ;
	carpos++;
	a=0x00;
	}
	//ÓÃtemp1¼ÇÂ¼±È½Ï¿¿½üÆì¸ËµÄü
		temp1=high_flag1;
	  temp2=high_flag2;
	  turn_6_1();
		brake();
	t=500;
	while(t){
		track2();
		t--;
	}
	while(dis_1>180||dis_1<10){
			track2();
	  	dis_11=GetDistance_B();
	  	delay_nms(60);
	  	dis_12=GetDistance_B();
	  	delay_nms(60);
	 		dis_1=(dis_11+dis_12)/2.0;
	}
	dis_1=GetDistance_B();
	while(dis_1>180||dis_1<10){
			track2();
		delay_nms(60);
	  	dis_11=GetDistance_B();
	  	delay_nms(60);
	  	dis_12=GetDistance_B();
	 		dis_1=(dis_11+dis_12)/2.0;
	}
	brake();
	
	USART_SendData(USART3, 'P');
	while(duoji_success==0){
		delay_nms(10);
	}
	delay_nms(500);
	duoji_success=0;
	go_back_1();
	turn_1_1();
		if(temp1<8){
		 goforwards_distance(120);
	   turn_0_1();
     back_n_step(8-temp1);
	   turn_2_1();
	}		
	goforwards_distance(80);
	USART_SendData(USART3, 'C');
	while(duoji_success==0){
			delay_nms(10);
	}
	duoji_success=0;
	goforwards_distance(120);
	turn_0_1();
	if(temp1>temp2)
	   back_n_step(temp1-temp2);
	else
		 go_n_step(temp2-temp1);
	turn_2_1();
	goforwards_distance(80);
	USART_SendData(USART3,'E');
	while(duoji_success==0){
			delay_nms(10);
	}
	duoji_success=0;
	goforwards_distance(120);
	turn_0_1();
	go_n_step_1(8-temp2);
	turn_1();
	go_1();
	turn_3_1();
	f1=1;
	while(f1){
		f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12);
		if(f1==0){
			delay_nus(20);
			f1=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12);
			if(f1==0){
				brake();
				break;
			}
		}
		track2();
	}
	USART_SendData(USART3, 'D');
}
else
	;
}
void TIM3_IRQHandler(void){
  TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	i++;
	if(i==1){
		f3=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_3);//8
		f4=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10);//7
		f5=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11);//6
		f6=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4);//5
		f11=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_7);//µÚÒ»´Î×ªÍäµÄÅĞ¶Ï
		i=0;
	} 
	
	
   if(xi==1){
	   if(ruo==0){
	      CarGoRight();
	   if(f4==1){
			 brake();
		   ruo=1;
		 }
	  }
	  if(ruo==1){
	     goforwards();
	  if(f5==1){brake();
		ruo=2;
		}
	 }
	  if(ruo==2){
	     CircleLeft_R();
	     if((f3==0)&&(f4==0)&&(f5==0)&&(f6==0)){
				 brake();
		     ruo=3;
		     TIM_Cmd(TIM3,DISABLE);
	     }
	  }}
	  else if(xi==2)
			
		  {
				if(ruo==0){
	      CarGoRight_1();
	   if(f6==1){
			 brake();
		   ruo=1;
		 }
	  }
	  if(ruo==1){
	     goforwards();
	  if(f3==1){brake();
		ruo=2;
		}
	 }
	  if(ruo==2){
	     CircleRight_R();
	     if((f3==0)&&(f4==0)&&(f5==0)&&(f6==0)){
				 brake();
		     ruo=3;
		     TIM_Cmd(TIM3,DISABLE);
	     }
			}}
		else
			;
	}

		



/*À¶ÑÀÄ£¿é*/
void USART3_RCC_Configuration(void){
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
 //  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   //´ò¿ªGPIOA,AFIO,USART1ÍâÉèÊ±ÖÓ
  
}
void nvic(void){
	 NVIC_InitTypeDef NVIC_InitStructure;  //	 //	  ÃüÃûÒ»ÓÅÏÈ¼¶±äÁ¿

 	   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    //	   ½«ÓÅÏÈ¼¶·Ö×é·½Ê½ÅäÖÃÎªgroup1,ÓĞ2¸öÇÀÕ¼£¨´ò¶Ï£©ÓÅÏÈ¼¶£¬8¸öÏìÓ¦ÓÅÏÈ¼¶
     NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; //¸ÃÖĞ¶ÏÎªTIM2Òç³ö¸üĞÂÖĞ¶Ï
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//´ò¶ÏÓÅÏÈ¼¶Îª1£¬ÔÚ¸Ã×éÖĞÎª½ÏµÍµÄ£¬0ÓÅÏÈ¼¶×î¸ß
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; // ÏìÓ¦ÓÅÏÈ¼¶0£¬´ò¶ÏÓÅÏÈ¼¶Ò»ÑùÊ±£¬0×î¸ß
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	 	//	ÉèÖÃÊ¹ÄÜ
     NVIC_Init(&NVIC_InitStructure);					   	//	³õÊ¼»¯

	 	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    //	   ½«ÓÅÏÈ¼¶·Ö×é·½Ê½ÅäÖÃÎªgroup1,ÓĞ2¸öÇÀÕ¼£¨´ò¶Ï£©ÓÅÏÈ¼¶£¬8¸öÏìÓ¦ÓÅÏÈ¼¶
     NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //¸ÃÖĞ¶ÏÎªTIM2Òç³ö¸üĞÂÖĞ¶Ï
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//´ò¶ÏÓÅÏÈ¼¶Îª1£¬ÔÚ¸Ã×éÖĞÎª½ÏµÍµÄ£¬0ÓÅÏÈ¼¶×î¸ß
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; // ÏìÓ¦ÓÅÏÈ¼¶0£¬´ò¶ÏÓÅÏÈ¼¶Ò»ÑùÊ±£¬0×î¸ß
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	 	//	ÉèÖÃÊ¹ÄÜ
     NVIC_Init(&NVIC_InitStructure);					   	//	³õÊ¼»¯ 
	
	   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //ÒªÓÃÍ¬Ò»¸öGroup
     NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; //TIM3	Òç³ö¸üĞÂÖĞ¶Ï
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//	´ò¶ÏÓÅÏÈ¼¶Îª1£¬ÓëÉÏÒ»¸öÏàÍ¬£¬²»Ï£ÍûÖĞ¶ÏÏà»¥´ò¶Ï¶Ô·½
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 	//	ÏìÓ¦ÓÅÏÈ¼¶1£¬µÍÓÚÉÏÒ»¸ö£¬µ±Á½¸öÖĞ¶ÏÍ¬Ê±À´Ê±£¬ÉÏÒ»¸öÏÈÖ´ĞĞ
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
}
void USART3_Configuration(void){
	  USART_InitTypeDef USART_InitStructure; //´®¿ÚÉèÖÃ»Ö¸´Ä¬ÈÏ²ÎÊı
  
	  USART3_RCC_Configuration();
	  nvic();
	  
	  USART_InitStructure.USART_BaudRate = 38400; //²¨ÌØÂÊ38400
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //×Ö³¤8Î»
    USART_InitStructure.USART_StopBits = USART_StopBits_1; //1Î»Í£Ö¹×Ö½Ú
    USART_InitStructure.USART_Parity = USART_Parity_No; //ÎŞÆæÅ¼Ğ£Ñé
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;     //ÎŞÁ÷¿ØÖÆ
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      //´ò¿ªRx½ÓÊÕºÍTx·¢ËÍ¹¦ÄÜ
    USART_Init(USART3, &USART_InitStructure);  //³õÊ¼»¯
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  // Èô½ÓÊÕÊı¾İ¼Ä´æÆ÷Âú£¬Ôò²úÉúÖĞ¶Ï
    USART_Cmd(USART3, ENABLE);                     //Æô¶¯´®¿Ú                   
                                                   
       //-----ÈçÏÂÓï¾ä½â¾öµÚ1¸ö×Ö½ÚÎŞ·¨ÕıÈ··¢ËÍ³öÈ¥µÄÎÊÌâ-----// 
    USART_ClearFlag(USART3, USART_FLAG_TC);     // Çå·¢ËÍÍê³É±êÖ¾
}
void USART3_IRQHandler(void){
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET) //ÅĞ¶ÏÊÇ·ñÎª½ÓÊÕÖĞ¶Ï
	{
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);	//Çå³ı½ÓÊÜÖĞ¶Ï±êÖ¾Î»
		RxData=USART_ReceiveData(USART3);								//¶ÁÈ¡½ÓÊÜÊı¾İ{
			switch(RxData)
			{
				case (u8)0x53:success=1; break;
				case (u8)0x54:duoji_success=1;break;
				default:break;
			}
		
	}
	
	
	if(USART_GetITStatus(USART3,USART_IT_TXE)!=RESET)  //ÅĞ¶ÏÊÇ·ñÎª·¢ËÍÖĞ¶Ï
	{	
		USART_ClearITPendingBit(USART3,USART_IT_TXE);//Çå³ı·¢ËÍÖĞ¶Ï±êÖ¾Î»
		
	}
	if(USART_GetITStatus(USART3,USART_IT_TC)!=RESET)  //ÅĞ¶ÏÊÇ·ñÎª·¢ËÍÍê³ÉÖĞ¶Ï
	{
		USART_ClearITPendingBit(USART3,USART_IT_TC);	//Çå³ı·¢ËÍÍê³ÉÖĞ¶Ï±êÖ¾Î»
	}

 }	 
/*rfid¶Á¿¨Æ÷º¯Êı*/
//Ç°ÖÃrfid¶Á¿¨Æ÷
u8 read1()
{
	u16 times=0;
	u8 uid[8]={0};
	u8 block[4]={0};
	NVIC_Configuration(); 	 //ÉèÖÃNVICÖĞ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶
	uart1_init(19200);	 //´®¿Ú1,2³õÊ¼»¯Îª19200
 	t1=RFID_Init1();
	t1=RFID_Init1();
	
 	while(block[0]==0&&(times<10))
	{
		t2=GET_UID1(uid);//»ñÈ¡UID
		t2=GET_UID1(uid);//»ñÈ¡UID
	
		t3=RFID_READ1(uid,block);//¶ÁÈ¡rfidµÚÒ»¿éÊı¾İ
		times++;
	}	 
	t4=RFID_Disableantenna1();//¹Ø±ÕÌìÏß£¬¼õÉÙ·¢ÈÈ 
	return block[0];
}
//²àÖÃrfid¶Á¿¨Æ÷
u8 read2()
{
	u8 t=0;
	u16 times=0;
	u8 uid[8]={0};
	u8 block[4]={0};
	NVIC_Configuration(); 	 //ÉèÖÃNVICÖĞ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶
	uart2_init(19200);	 //´®¿Ú1,2³õÊ¼»¯Îª19200
	
	t=RFID_Init2();
	t=RFID_Init2();
	
	//delay_ms(300);
	
 	while(block[0]==0&&(times<10))
	{
		t=GET_UID2(uid);//»ñÈ¡UID
		t=GET_UID2(uid);//»ñÈ¡UID
	
		t=RFID_READ2(uid,block);//¶ÁÈ¡rfidµÚÒ»¿éÊı¾İ
		times++;
	}	 
	t=RFID_Disableantenna2();//¹Ø±ÕÌìÏß£¬¼õÉÙ·¢ÈÈ 
	return block[0];
}
/*while(ii<8)
		
		
		{go_one_step();
		a=read1();//¶ÁÈ¡rfid
		if(RxData_t[k]==0x01||RxData_t[k]==0x02){//Èç¹ûÊÇ¡°ºì¡±¡¢¡°×¨¡±
						USART_SendData(USART3, 'A');
					  adjust_sign=1;
			  }
			   else if(RxData_t[k]==0x04){                //Èç¹ûÊÇ¡°²¢¡±
				   USART_SendData(USART3,'A');
			  }
			  else if(RxData_t[k]==0x03){
				  USART_SendData(USART3,'B');     //Èç¹ûÊÇ¡±½ø¡°
			  }
				else 
					;
				ii++;}*/
		
				
		///////////////ÅĞ¶Ï²Ù×÷½áÊø
	/*	*/
 //µÚ¶ş½×¶ÎÑ­¼££¬×ªÍä²¢ÏòÇ°×ß
	
		//goforwards();	
	//setWheel(1,direction,40);
/*	setWheel(2,direction,40);
	while(sign!=1);
  if(sign==1){         //¶ÔµÚÒ»¸ùÖù×Ó½øĞĞ¼ì²â
			 USART_SendData(USART3, 'F');//ÒªÇó¶ÁÈ¡Ç°·½µÄrfid¶Á¿¨Æ÷
		   while(success!=1);          //µÈ´ıÊÕµ½·´À¡
		   delay_nms(20);
		   success=0;
		   if(mission==0){
			    
	  }
			 else{
				 if(RxData_t[k]==0x05||RxData_t[k]==0x06){//Èç¹ûÊÇ¡°Àí¡±¡¢¡°Êµ¡±
						USART_SendData(USART3, 'A');
					  adjust_sign=1;
			  }
			   else if(RxData_t[k]==0x07){                //Èç¹ûÊÇ¡°½»¡°
				   USART_SendData(USART3,'A');
			 }
			  else if(RxData_t[k]==0x08){
				  USART_SendData(USART3,'B');     //Èç¹ûÊÇ¡±ÈÚ¡±
			 }
		   }
			 while(success!=1);                 //µÈ´ıÊÕµ½³É¹¦·´À¡
			 success=0;
	     back_adjust();
			 while(dis<=150);
			 brake();
			 delay_nms(20);
			 if(mission==0)
			    CircleRight_R();
			 else
				  CircleLeft_B();
			 sign=2;                            //µÚ¶ş½×¶ÎµÄÑ­¼£
			 TIM_Cmd(TIM3,DISABLE);             //¹Ø±Õ¶¨Ê±Æ÷
	     car_pos=1;                         //¼ÇÂ¼ËùÔÚÎ»ÖÃÎª1
	}*/