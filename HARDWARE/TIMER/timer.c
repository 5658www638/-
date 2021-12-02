#include "timer.h"
#include "led.h"
#include "usart.h"
#include "lcd.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved			224			117			  
////////////////////////////////////////////////////////////////////////////////// 	 

int duoji11=212;
int duoji22=250;
int duoji33=145;
int duoji88=97;

//int duoji11=145;
int duoji1_kaizhua=145;
int duoji1_zhua=217;

//	int duoji22=166;
//	int duoji88=176;
//	int duoji11=145;
//	int duoji33=183;

//int duoji22=166;
int  duoji2_zhi=166;

//int duoji33=180;//pin40 37//100
int duoji3_shuipin=198;//125,199�ǹ���Ļ�е��
int duoji3_qi=184;
int duoji3_zuigao=140;
int duoji44=130;
int duoji55=68;//����ͷˮƽת�����
int duoji66=232;//210
int duoji77;//�����ݴ�duoji55��ֵ
//int duoji88=176;
int duo8;
#define zuoqian PAout(13)
#define zuohou PFout(13)
#define youqian PFout(14)
#define youhou PFout(10)
int pwm_zq,pwm_zh,pwm_yq,pwm_yh;

int red1[6]={0,25,   70,185,   0,240};//��ɫ
int red2[6]={220,240, 70,173,  0,240};//��ɫ

int blue2[6]={125,240,     80,240,      30,160};//��ɫ
//int blue2[6]={113,240,     80,240,      15,103};//��ɫ
		
extern double Angleduo2;
double joint;


int jishu,jishu4;


 int ff;
 int gg;
int hh;
 int kk;
///71 53
extern u8 ov_frame;
extern volatile u16 jpeg_data_len;
extern double r,y,l;

//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		jishu++;
		if(jishu==2000)//20ms��10usһ��������Ӧ���1���ź�ֵ
		{
		jishu=0;
		if(gg==1){ff++;}
		else	if(gg==3)
		{ff--;}
		else	if(gg==5)
		{hh++;}
		else	if(gg==4)
		{hh--;}
		else	if(gg==6)
		{kk++;}
		}	

		if(jishu<duoji11)
		{duoji1=1;}
		else if(jishu>duoji11)
		{duoji1=0;}
		
		if(jishu<duoji22)
		{duoji2=1;}
		else if(jishu>duoji22)
		{duoji2=0;}
		
		if(jishu<duoji33)
		{duoji3=1;}
		else if(jishu>duoji33)
		{duoji3=0;}

	
		
		if(jishu<duoji55)
		{duoji5=1;}
		else if(jishu>duoji55)
		{duoji5=0;}
		if(jishu<duoji66)
		{duoji6=1;}
		else if(jishu>duoji66)
		{duoji6=0;}
		if(duoji88>=247)
			duo8=247;
		else if(duoji88<=117)
			duo8=117;
		else duo8=duoji88;
		if(jishu<duo8)
		{duoji8=1;}
		else if(jishu>duo8)
		{duoji8=0;}
		
		if(jishu<pwm_zq)
			zuoqian=1;
		else if(jishu>pwm_zq)
			zuoqian=0;
		if(jishu<pwm_zh)
			zuohou=1;
		else if(jishu>pwm_zh)
			zuohou=0;
		if(jishu<pwm_yq)
			youqian=1;
		else if(jishu>pwm_yq)
			youqian=0;
		if(jishu<pwm_yh)
			youhou=1;
		else if(jishu>pwm_yh)
			youhou=0;
		
		if(duoji55>202)
		{
			joint=(180-1.6*(duoji22-166));
			Angleduo2=(duoji88-192)*1.5;
		}		
		else if(duoji55<126)
		{
			joint=(180-1.6*(duoji22-166));
			Angleduo2=(duoji88-152)*1.5;
		}
		else if((duoji55>=126)&&(duoji55<=155))
		{
			joint=(180-1.6*(duoji22-166));
			Angleduo2=(duoji88-168)*1.5;
		}
		else if((duoji55<=202)&&(duoji55>155))
		{
			joint=(180-1.6*(duoji22-166));
			Angleduo2=(duoji88-172)*1.5;
		}
		
		
	}
	TIM_ClearITPendingBit(TIM3 ,TIM_IT_Update);  //����жϱ�־λ
}


