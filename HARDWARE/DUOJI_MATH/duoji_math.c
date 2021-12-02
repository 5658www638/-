#include "led.h" 
#include "math.h" 
#include "delay.h"
#include "timer.h"
#include "sys.h"
#include "usart.h" 
#include "duoji_math.h"
#include "dcmi.h" 


//float photo_jiaotrue;//che_jiao������ǣ�photo_jiaotrue����ͷ����ڳ��ĺ����
//int x;������ͷ���ص�ͼ������
int y2;//������ͷ���ص�ʵ���������꣬�����ͬ�ھ��루mm��
double bujin_jiao;//���������ת�Ƕ�
int bujin_zhi=0;//�������һ�εĲ����������ֵ
extern int duoji11,duoji22,duoji33;//���������Ӧ��ֵ
double jiaodu1=0.0;//������һ�����
int bi1=350;//����צ�ӵı۳�MM
int bi2=350;//��һ�۳�
int bujin_sign=0;//������ʶ����ʧ��Ϊ1���ɹ���Ϊ0
int duoji2_sign=0;//���2��ʶ����ʧ��Ϊ1���ɹ���Ϊ0
int error_sign=0;//�ܱ�ʶ����ʧ��Ϊ1���ɹ���Ϊ0
int zhui_zong_sign=1;//׷�ٱ�ʶ����ֹͣΪ0��׷��Ϊ1
int mubiao2=0;//���2��Ŀ��ֵ

extern int duoji55,duoji66,duoji77;
extern int duoji1_kaizhua;
extern int duoji1_zhua;
extern int duoji2_zhi;

int bujin_last=0;
extern double x_tu,y,l;
void done(int photo_zhi,double y2 )
{
		 DCMI_Stop();
		 djapi_zhua(photo_zhi,y2); 
    DCMI_Start();
	x_tu=0;
	y=0;
	duoji77=duoji55;
	 	DCMI_Start(); 	
}


void step_move_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��GPIOFʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;				 //LED0-->PB.5 ????
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
 GPIO_Init(GPIOG, &GPIO_InitStructure);					 //?????????GPIOB.5
}
void step_move(int sds)///��������
{
	
	int bujin;
	DCMI_Stop();
	if(sds>=0)
{
		
    for(bujin=0;bujin<sds;bujin++)
     	{
				PGout(1)=0;//niʱ��
				PGout(0)=0;
				delay_us(1000);
				PGout(0)=1;
				delay_us(1000);			
       }
}

else
	{
		for(bujin=0;bujin<(-sds);bujin++)
     	{
				PGout(1)=1;
				PGout(0)=0;
				delay_us(1000);
				PGout(0)=1;
				delay_us(1000);			
       }	
			 	DCMI_Start(); 	
}
}

 void figure_up()
 {







 }
void bujin1(int photo_zhi,double y2)//���㲽���������ֵ�����Ʋ��� 
{
	
	
	int bujin_zhi0;//��������ڳ�ʼ�Ƕȸ�ת�ĽǶ�
	double photo_jiao;
	
	  jiaodu1=acos((y2*y2+bi2*bi2-bi1*bi1)/(2.0*bi2*y2))*40+21;  //���������ε�һ�����
		 printf("���������jiaodu1=%f   \r\n",jiaodu1);
	
//	   photo_jiao=2.729*(duoji55-53);
	   photo_jiao=0.9*(duoji55-164);	
	   bujin_jiao=90+photo_jiao+jiaodu1;
	   bujin_zhi0=bujin_jiao/0.225;////�����0�ȵ�����ֵ1600
	
	if(bujin_zhi0>=(0/0.225)&&bujin_zhi0<=(180/0.225))
		{
			bujin_zhi=bujin_zhi0-bujin_last;//����һ������ֵ���Ƚ�
			bujin_last=bujin_zhi0; //��¼�������ֵ��
	    //printf("bujin_zhi=%d   \r\n",bujin_zhi);	 
			printf("������ֵbujin_zhi0=%d   \r\n",bujin_zhi0); 
			bujin_sign=0;
		}
	else
		{
		   printf("������ֵ����!!  ����ϴε�ʵ��ת��ֵbujin_zhi=%d   \r\n",bujin_zhi);	 
			 printf("������ֵbujin_zhi0=%d   \r\n",bujin_zhi0);	
		 	bujin_sign=1;
			bujin_zhi=0;
		}	
	
}
int duoji22_tiaojie(int mub)//�ȿ������ת���2
	{
	if(duoji22<mub){
			for(;duoji22<mub;duoji22++){
				  if((mub-duoji22)>=30)duoji22+=(mub-duoji22)/15;
		else if((mub-duoji22)>=15)duoji22+=2;
		else if((mub-duoji22)>=2)duoji22+=1;		
			delay_ms(50);}
		}
	else if(duoji22>mub){
			for(;duoji22>mub;duoji22--){
				  if(-(mub-duoji22)>=30)duoji22-=-(mub-duoji22)/15;
		else if(-(mub-duoji22)>=15)duoji22-=2;
		else if(-(mub-duoji22)>=2)duoji22-=1;		
			delay_ms(50);}
				
		}
	//printf("duoji22=%d   \r\n",duoji22);
	//		printf("ok22");	
		return 1;
	}
void duoji33_tiaojie(int mub){
	if(duoji33<mub){
			for(;duoji33<mub;duoji33++){
				  if((mub-duoji33)>=30)duoji33+=(mub-duoji33)/15;
		else if((mub-duoji33)>=15)duoji33+=2;
		else if((mub-duoji33)>=2)duoji33+=1;		
			delay_ms(40);}
		}
	else if(duoji33>mub){
			for(;duoji33>mub;duoji33--){
				  if(-(mub-duoji33)>=30)duoji33-=-(mub-duoji33)/15;
		else if(-(mub-duoji33)>=15)duoji33-=2;
		else if(-(mub-duoji33)>=2)duoji33-=1;		
			delay_ms(40);}
				
		}
	//printf("duoji33=%d   \r\n",duoji33);
	//		printf("ok33");	
}
int duoji2_math(int y2)//������2��pwmֵ        y������ͷ���ص�ʵ���������꣬�����ͬ�ھ��루mm��
{   
	
	if(y2<=(bi1+bi2)&&y2>=100)//������������
		{
					float jiaodu2;//���2��ת�ĽǶ�
					jiaodu1=acos((y2*y2+bi2*bi2-bi1*bi1)/(2.0*bi2*y2))*40+19;  //���������ε�һ�����
					jiaodu2=2.0*jiaodu1;
		
			printf("���2��ת�ĽǶ�jiaodu2=%f   \r\n",jiaodu2);
								
					mubiao2=-jiaodu2+220;//���2�ĽǶȻ��㣬ÿ���������,115
			
					if(jiaodu2<=160&&mubiao2<=250&&mubiao2>=0)
						{						 
							printf("���2�ıȽ�ֵmubiao=%d   \r\n",mubiao2);
							//printf("���2�ɹ�!!\r\n");	 
							//printf("���2�ıȽ�ֵduoji22=%d   \r\n",duoji22);
							//printf("���������jiaodu1=%f   \r\n",jiaodu1);	
							duoji2_sign=0;
							return 1;
						}
						
						else
						 {
						 printf("���2ʧ��   �Ƕȳ�����!!\r\n");	
							duoji2_sign=1;	
							return 0;
						 }
						
    }
		
		 else
		{
		 printf("���2ʧ��   ����̫Զ!!\r\n");	
			duoji2_sign=1;	
			return 0;
		}
 
 
 
}

void djapi_zhua(int photo_zhi, double y2)
{	 
	
		bujin1(photo_zhi,y2);///////////////////////
	 duoji2_math(y2);
	error_sign=bujin_sign+duoji2_sign;
	if(error_sign==0)
		{
		
					delay_ms(500); 
			step_move(bujin_zhi);
					delay_ms(500);
		
				 delay_ms(500);
			 duoji11=duoji1_kaizhua;
					delay_ms(500);
			 while(!duoji22_tiaojie(mubiao2))
			 {
				  //printf("���ж��2!!\r\n");
			 }
				///////////////////////////
				 delay_ms(500);
			
		
				 delay_ms(500);
			 duoji11=duoji1_zhua;
				 delay_ms(500);
		
				 delay_ms(500);
			 duoji22_tiaojie(duoji2_zhi);
				delay_ms(500);
	  DCMI_Start();
			 
			 //printf("�˴�ץ��ɹ�!!\r\n");	
			  
   }	
		else
		{
			printf("�˴�ץ��ʧ��!!\r\n");	
			error_sign=0;
			bujin_sign=0;
			duoji2_sign=0;
			
		}

	
}
int x_fangqiu=0;
int y_fangqiu=2200;//�Գ�����Ϊԭ��

void bujin2(int x_che,int y_che)   
{
   float angle1;
	 double bujin_angle;
	 int bujin_zhi0,bujin_zhi; 
		
	 angle1=atan((float)((fabs(y_fangqiu-y_che))/(fabs(x_fangqiu-x_che))))*57.3;
	 printf("angle1=%f   \r\n",angle1);
	if(x_che<0)
   bujin_angle=-(90-angle1);
	if(x_che>0)
    bujin_angle=angle1;
  bujin_zhi0=bujin_angle/0.225;
	
	bujin_zhi=bujin_zhi0-bujin_last;
	bujin_last=bujin_zhi0; 	
  printf("bujin_zhi0=%d   \r\n",bujin_zhi0);	
  step_move(bujin_zhi);
	
}
void djapi_fang_qiu(int x_che,int y_che)//x_che����ʵ������  y_che
{
   bujin2(x_che,y_che);
      delay_ms(500 );
	 duoji11=duoji1_kaizhua;
	   delay_ms(500);
}	 





void duoji55_zhui_zong()////����ͷ׷�ٺ���
{
	
  static int zhi;
	if(zhui_zong_sign==1&&duoji55<=255&&duoji55>=0)
			{
						if(duoji55==66)
							{
								duoji66=190;  delay_ms(100);
//							 printf("duoji66:\r\n");
								zhi=1;
							}
								if(zhi==1&&duoji55<255)
								{
								  duoji55++; delay_ms(100);
								}
													
							
							if(duoji55==255)
							{
										duoji66=165;delay_ms(100);
								    zhi=0;
//							 printf("duoji66:\r\n");
							}
							
							if(zhi==0&&duoji55>66)
								{
								  duoji55--;delay_ms(100);
									
								}
								
//					printf("zhui_zong_sign:%d\r\n",zhui_zong_sign);		
//					printf("duoji55:%d\r\n",duoji55);
			
		 }

}







///diao  shi///////////////////////////////
void bujin8(double photo_jiao,double y2)//���㲽���������ֵ�����Ʋ��� 
{
	
	
	int bujin_zhi0;//��������ڳ�ʼ�Ƕȸ�ת�ĽǶ�
	  jiaodu1=acos((y2*y2+bi2*bi2-bi1*bi1)/(2.0*bi2*y2))*57.3;  //���������ε�һ�����
		 printf("jiaodu1=%f   \r\n",jiaodu1);
	   bujin_jiao=90+photo_jiao+jiaodu1;
	   bujin_zhi0=bujin_jiao/0.225;////�����0�ȵ�����ֵ1600
			bujin_zhi=bujin_zhi0-bujin_last;//����һ������ֵ���Ƚ�
			bujin_last=bujin_zhi0; //��¼�������ֵ��
	 printf("bujin_zhi=%d   \r\n",bujin_zhi);//	 printf("bujin_zhi0=%d   \r\n",bujin_zhi0);
	step_move(bujin_zhi);
}
void djapi_zhua8(double photo_jiao, double y2)
{	    
    duoji33_tiaojie(65); 
	  delay_ms(500);
    bujin8(photo_jiao,y2); 
	  delay_ms(500);
	duoji11=duoji1_kaizhua;
	    delay_ms(500);
   duoji2_math(y2);////////////////
	   delay_ms(500);
	   delay_ms(500);
	 duoji11=duoji1_zhua;
	   delay_ms(500);
	 duoji33_tiaojie(65);
	   delay_ms(500);
	 duoji22_tiaojie(duoji2_zhi);
	  delay_ms(500);
}		



