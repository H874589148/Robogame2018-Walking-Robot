#include "delay.h"
#include "usart.h"
#include "rfid.h"


//AABB0600000001010707
u8 RFID_init_data[10] = {0xAA,0xBB,0x06,0x00,0x00,0x00,0x08,0x01,0x31,0x38};//AABB0600000008013138
u8 Get_uid_data[9] = {0xAA,0xBB,0x05,0x00,0x00,0x00,0x01,0x10,0x11};//AABB05000000011011
u8 RFID_READ_data[20]={0xAA,0xBB,0x10,0x00,0x00,0x00,0x05,0x10,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00};
u8 Disable_antenna_data[10]={0xAA,0xBB,0x06,0x00,0x00,0x00,0x0C,0x01,0x00,0x0D};
u8 RFID_WRITE_data[23]={0xAA,0xBB,0x13,0x00,0x00,0x00,0x06,0x10,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
u8 RFID[9]={0xAA,0xBB,0x05,0x00,0x00,0x00,0x04,0x01,0x05};	
u8 LEDr[10]={0xAA,0xBB,0x06,0x00,0x00,0x00,0x07,0x01,0x02,0x07};	
	
u8 RFID_Init1(void)
{
	u8 len=0;
	u8 i=0;
	u8 data[10]={0};
	uart_send_mydata1(RFID_init_data,10);
	
	while(i<50)
		
		{
			if(USART_RX_STA&0x8000)
			{
				uart_receive_mydata1(data,&len);
				break;
			}
			i++;
			delay_nus(500);
		}
			
		
	USART_RX_STA=0;
	//uart_send_mydata(LEDr,10);	
		
	if(len==10&&data[8]==0)
	{
		return 1;
	}
	else 
	{
		return 0;		
	}
	
}

u8 RFID_Init2(void)
{
	u8 len=0;
	u8 i=0;
	u8 data[10]={0};
	uart_send_mydata2(RFID_init_data,10);
	
	while(i<50)
		
		{
			if(USART_RX_STA&0x8000)
			{
				uart_receive_mydata2(data,&len);
				break;
			}
			i++;
			delay_nms(10);
		}
			
		
	USART_RX_STA=0;
	//uart_send_mydata(LEDr,10);	
		
	if(len==10&&data[8]==0)
	{
		return 1;
	}
	else 
	{
		return 0;		
	}
	
}


u8 GET_RFID1(void)
{
	u8 i=0;
	u8 data[30];
	u8 len=0;
	uart_send_mydata1(RFID,9);
	while(i<50)
		{
			if(USART_RX_STA&0x8000)
			{
				uart_receive_mydata1(data,&len);
				break;
			}
			i++;
			delay_nms(10);
		}
	USART_RX_STA=0;	
	//for(i=9;i<15;i++)
		printf("%s",&data[9]);
  return 1;		
}

u8 GET_RFID2(void)
{
	u8 i=0;
	u8 data[30];
	u8 len=0;
	uart_send_mydata2(RFID,9);
	while(i<50)
		{
			if(USART_RX_STA&0x8000)
			{
				uart_receive_mydata2(data,&len);
				break;
			}
			i++;
			delay_nms(10);
		}
	USART_RX_STA=0;	
	//for(i=9;i<15;i++)
		printf("%s",&data[9]);
  return 1;		
}


u8 GET_UID1(u8 *uid)
{
	
	u8 len;
	u8 i;
	u8 data[19]={0};
	uart_send_mydata1(Get_uid_data,9);
	
	i=0;
	while(i<50)
		
		{
			if(USART_RX_STA&0x8000)
			{
				uart_receive_mydata1(data,&len);
				break;
			}
			i++;
			delay_nus(500);
		}
			
		
	USART_RX_STA=0;
	if(len==19)
	{
		for(i=0;i<8;i++)
		uid[i]=data[i+10];
	 
		return 1;
	}
	else
	{
		return 0;
	}
			
	
}
u8 GET_UID2(u8 *uid)
{
	
	u8 len;
	u8 i;
	u8 data[19]={0};
	uart_send_mydata2(Get_uid_data,9);
	
	i=0;
	while(i<50)
		
		{
			if(USART_RX_STA&0x8000)
			{
				uart_receive_mydata2(data,&len);
				break;
			}
			i++;
			delay_nms(10);
		}
			
		
	USART_RX_STA=0;
	if(len==19)
	{
		for(i=0;i<8;i++)
		uid[i]=data[i+10];
	 
		return 1;
	}
	else
	{
		return 0;
	}
			
	
}

u8 RFID_READ1(u8 *uid,u8 *block)
{
	u8 i=0;
	u8 len=0;
	u8 data[14]={2};
	for(i=0;i<8;i++)
		RFID_READ_data[i+9]=uid[i];
	RFID_READ_data[19]=0;
	for(i=4;i<19;i++)
		RFID_READ_data[19]=RFID_READ_data[i]^RFID_READ_data[19];
	uart_send_mydata1(RFID_READ_data,20);
	
	i=0;
	while(i<200)
		
		{
			if(USART_RX_STA&0x8000)
			{
				uart_receive_mydata1(data,&len);
				break;
			}
			i++;
			delay_nus(500);
		}
			
		
	USART_RX_STA=0;
		
	if(len==14)
	{
		for(i=0;i<4;i++)
			block[i]=data[i+9];
		return 1;
	}
	else 
		return 0;
	
}

u8 RFID_READ2(u8 *uid,u8 *block)
{
	u8 i=0;
	u8 len=0;
	u8 data[14]={2};
	for(i=0;i<8;i++)
		RFID_READ_data[i+9]=uid[i];
	RFID_READ_data[19]=0;
	for(i=4;i<19;i++)
		RFID_READ_data[19]=RFID_READ_data[i]^RFID_READ_data[19];
	uart_send_mydata2(RFID_READ_data,20);
	
	i=0;
	while(i<50)
		
		{
			if(USART_RX_STA&0x8000)
			{
				uart_receive_mydata2(data,&len);
				break;
			}
			i++;
			delay_nms(10);
		}
			
		
	USART_RX_STA=0;
		
	if(len==14)
	{
		for(i=0;i<4;i++)
			block[i]=data[i+9];
		return 1;
	}
	else 
		return 0;
	
}

u8  RFID_Disableantenna1(void)
{
	u8 len=0;
	u8 i=0;
	u8 data[10]={0};
	uart_send_mydata1(Disable_antenna_data,10);
	
	while(i<50)
	
	{
		if(USART_RX_STA&0x8000)
		{
			uart_receive_mydata1(data,&len);
			break;
		}
		i++;
		delay_nms(10);
	}
	
		USART_RX_STA=0;
	
	if(len==10&&data[8]==0)
	{
		
		return 1;
	}
	else 
	{
		return 0;		
	}
}

u8  RFID_Disableantenna2(void)
{
	u8 len=0;
	u8 i=0;
	u8 data[10]={0};
	uart_send_mydata2(Disable_antenna_data,10);
	
	while(i<50)
	
	{
		if(USART_RX_STA&0x8000)
		{
			uart_receive_mydata2(data,&len);
			break;
		}
		i++;
		delay_nms(10);
	}
	
		USART_RX_STA=0;
	
	if(len==10&&data[8]==0)
	{
		
		return 1;
	}
	else 
	{
		return 0;		
	}
}
u8 RFID_WRITE(u8 *uid,u8 *data)
{                 //Ïòblock0Ð´Êý¾Ý
	u8 i;
	for(i=0;i<8;i++)
	RFID_WRITE_data[i+9]=uid[i];
	for(i=0;i<4;i++)
	RFID_WRITE_data[i+18]=data[i];
	RFID_WRITE_data[22]=0;
	for(i=4;i<22;i++)
		RFID_WRITE_data[22]=RFID_WRITE_data[i]^RFID_WRITE_data[22];
	uart_send_mydata1(RFID_WRITE_data,23);
	delay_nms(100);
	return 1;
}
