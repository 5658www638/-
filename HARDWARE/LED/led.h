#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED�˿ڶ���

#define LED0 PBout(5)// PB5
#define LED1 PAout(5)//	//����
#define duoji1 PBout(10)// PB5
#define duoji2 PBout(11)// PB5
#define duoji3 PBout(12)// PB5
#define duoji6 PBout(13)// PB5
#define duoji5 PBout(14)// PB5
#define duoji8 PGout(0)// PG0
void LED_Init(void);//��ʼ��		 				    
#endif

