#ifndef __RFID_H
#define __RFID_H	 
#include "sys.h"



u8 RFID_READ1(u8 *uid,u8 *block);//��ȡrfid��һ������
u8 RFID_Init1(void);//��ʼ����������ʹ������
u8 RFID_Disableantenna1(void);//�ر����ߣ����ٷ���
u8 GET_UID1(u8 *uid);//��ȡUID
u8 RFID_WRITE(u8 *uid,u8 *data);
u8 GET_RFID1(void);	 			

u8 RFID_READ2(u8 *uid,u8 *block);//��ȡrfid��һ������
u8 RFID_Init2(void);//��ʼ����������ʹ������
u8 RFID_Disableantenna2(void);//�ر����ߣ����ٷ���
u8 GET_UID2(u8 *uid);//��ȡUID
u8 GET_RFID2(void);	 			
#endif
