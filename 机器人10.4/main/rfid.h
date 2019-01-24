#ifndef __RFID_H
#define __RFID_H	 
#include "sys.h"



u8 RFID_READ1(u8 *uid,u8 *block);//读取rfid第一块数据
u8 RFID_Init1(void);//初始化读卡器，使能天线
u8 RFID_Disableantenna1(void);//关闭天线，减少发热
u8 GET_UID1(u8 *uid);//获取UID
u8 RFID_WRITE(u8 *uid,u8 *data);
u8 GET_RFID1(void);	 			

u8 RFID_READ2(u8 *uid,u8 *block);//读取rfid第一块数据
u8 RFID_Init2(void);//初始化读卡器，使能天线
u8 RFID_Disableantenna2(void);//关闭天线，减少发热
u8 GET_UID2(u8 *uid);//获取UID
u8 GET_RFID2(void);	 			
#endif
