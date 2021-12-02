#include "sys.h"
#include "usart.h"	
#include "led.h"
#include "inv_mpu.h"
#include "duoji_math.h"
#include "math.h"
#include "car.h"
extern int gg;
extern int ff;
extern int hh;
extern int kk;

extern int duoji,xieaibei;
extern int bujin;
extern int duoji11;
extern int duoji22;
extern int duoji33;
extern int duoji44;
extern int duoji55;
extern int duoji66;
extern int duoji88;
double jiaodu2;
double andlre=0;
double y22=400;
extern float angle;
extern double juli;
extern double x_tu,y;

int m10;

#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
 
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	

//��ʼ��IO ����1 
//bound:������
void uart_init(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif
	
}
extern float pitch,roll,yaw,photo_jiao;
int bujin;
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		

		 if(Res==1)
		{
			printf("x=%f  y=%f   \r\n",x_tu,y);
			printf("s=%f   \r\n",juli);
			printf("angle=%f   \r\n",angle);	
		}
		else if(Res==4)
		{
			duoji66=165;
			printf("duoji66=%d   \r\n",duoji66);	
		}
		else if(Res==0x10)
		{
		x_tu=0;
		y=0;
		xieaibei=1;
		}
		else if(Res==0x11)
		{

		}
		else if(Res==0x12)
		{
			duoji22-=5;
			printf("duoji22=%d\r\n",duoji22);
		}
		else if(Res==0x13)
		{
			duoji22+=5;
			printf("duoji22=%d\r\n",duoji22);
		}
		else if(Res==0x21)
		{

		}
		else if(Res==0x22)
		{
			andlre+=5;printf("andlre=%f\r\n",andlre);
		}
		else if(Res==0x23)
		{
			andlre-=5;printf("andlre=%f\r\n",andlre);
		}
		else if(Res==0x24)
		{
			duoji22-=1;
			printf("duoji22=%d\r\n",duoji22);
		}
		
		else if(Res==0x29)
		{
			duoji66+=5;
			printf("duoji66=%d   \r\n",duoji66);
		}
		else if(Res==0x30)
		{
			duoji66-=5;
			printf("duoji66=%d  \r\n",duoji66);
		}
		else if(Res==0x25)
		{
			duoji33+=5;
		  printf("duoji33=%d   \r\n",duoji33);
		}
		else if(Res==0x26)
		{
			duoji33-=5;
		//	printf("cos=%f   \r\n",cos(45));
			printf("duoji33=%d   \r\n",duoji33);
		}
		else if(Res==0x27)
		{
			duoji33-=1;
			printf("duoji33=%d",duoji33);
		}
		else if(Res==0x28)
		{
			duoji33++;
			printf("duoji33=%d",duoji33);
		}
		else if(Res==0x36)
		{
			duoji55+=10;
			printf("duoji=%d",duoji55);
		}
		else if(Res==0x37)
		{
			duoji55-=10;
			printf("duoji55=%d",duoji55);
		}
		else if(Res==0x38)
		{
			duoji55++;
			printf("duoji55=%d",duoji55);
		}
		else if(Res==0x39)
		{
			duoji55--;
				printf("duoji55=%d",duoji55);
		}
		else if(Res==0x40)
		{
			duoji22+=5;
		  printf("duoji22=%d   \r\n",duoji22);
		}
		else if(Res==0x41)
		{
			duoji22-=5;
			printf("duoji22=%d   \r\n",duoji22);
		}else if(Res==0x42)
		{
			duoji22++;
		  printf("duoji22=%d   \r\n",duoji22);
		}
		else if(Res==0x43)
		{
			duoji22--;
			printf("duoji22=%d   \r\n",duoji22);
		}
		else if(Res==0x43)
		{
			duoji11--;
			printf("duoji66=%d   \r\n",duoji66);
		}
		 if(Res==0x61)
		{
			front();
			gg=1;
			printf("go ahead\r\n");
		}
		 if(Res==0x62)
		{
			stop();
			gg=2;
				printf("stop\r\n");
		}
		 if(Res==0x63)
		{
			duoji88+=10;
			printf("duoji88:%d \r\n",duoji88);
		}
		else if(Res==0x64)
		{
			duoji88-=10;
			printf("duoji88:%d \r\n",duoji88);
		}
		else if(Res==0x65)
		{
			duoji88++;
			printf("duoji88:%d \r\n",duoji88);
		}
		else if(Res==0x67)
		{
	      	duoji88--;
			printf("duoji88:%d \r\n",duoji88);

		}
		else if(Res==0x68)
		{
		     front();
			 ff=0;
			 gg=1;
			 while(ff<100);
			
			 kk=0;
			 gg=6;
			 while(kk<100);

		}
		 if(Res==0x71)
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_2);//0
			GPIO_SetBits(GPIOA,GPIO_Pin_3);//1  ��ǰ  //���
		}
		 if(Res==0x72)
		{
			
			GPIO_SetBits(GPIOF,GPIO_Pin_2);//1    ��ǰ   //��ǰ
			GPIO_ResetBits(GPIOF,GPIO_Pin_3);//0
		}
		 if(Res==0x73)
		{
			GPIO_ResetBits(GPIOF,GPIO_Pin_4);//0  ���    //�Һ�
			GPIO_SetBits(GPIOF,GPIO_Pin_5);//1     
		}
		else if(Res==0x74)
		{
			GPIO_ResetBits(GPIOF,GPIO_Pin_6);//0   �Һ�		//��ǰ
			GPIO_SetBits(GPIOF,GPIO_Pin_7);//1     
		}
		else if(Res==0x66)
		{
			printf("ff:%d\r\n",ff);
			printf("gg:%d\r\n",gg);
			printf("hh:%d\r\n",hh);
			printf("kk:%d\r\n",kk);
			printf("\r\n");
		}
		if((USART_RX_STA&0x8000)==0)//����δ���
		{
			if(USART_RX_STA&0x4000)//���յ���0x0d
			{
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x8000;	//��������� 
			}
			else //��û�յ�0X0D
			{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
  } 
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
#endif	

 



