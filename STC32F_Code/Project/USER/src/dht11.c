#include "headfile.h"

#define uint unsigned int
#define uchar unsigned char

#define DATA_PIN P36
//#define DATA P3^4//�����궨���ڱ����ʱ��ᱨ��������Ŀ���д��һƪ���£����������������棬����ϸ�Ľ���
int RLL,RHH,CLL,CHH; //���ڴ�����ʪ�ȵ����ݶ���
char DAMPH[8],TEMPH[8],DAMPL[8],TEMPL[8];//���ڴ�����ʪ�ȵ��ַ������鶨��
char dot[1]=".";//С����

// void delay_us(uchar n)  //������ʱΪus������ʱ����                       
// {
//   while(n--); 
// }

// void delay_ms(uint z)//������ʱΪms������ʱ����
// {
//   uint x,y;
//   for(x=z;x>0;x--)
//   for(y=614;y>0;y--);
// }

void Delay1000ms()//������ʱΪ1s����ʱ����		
{
	unsigned char i, j, k;
	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void DHT11_Start()
{
	DATA_PIN=0;//����������
	delay_ms(20);//��ʱ20ms��ȷ����ʱ����18ms������DHT11���Լ�⵽��ʼ�źţ�Ȼ��Ϳ��Կ�ʼ������Ӧ�ź�
	DATA_PIN=1;//����������
	delay_us(30);
	DATA_PIN=1;
}

int readdht11_byte() //����һ�����ֽ�Ϊ��λ�ĺ������ֱ��ȡdht11���͵�40bits������
{   
  int i,dht;  
  for(i=8;i>0;i--)//��������ѭ��ʵ�ֶ�ȡ�˸�bit������
  {      
    dht=dht<<1;//ÿ�ζ�ȡǰ�������ݵĸ�λ��λ������λ
    while(!DATA_PIN);//�ȴ�DHT11��50us�͵�ƽ���ݷָ��źŹ�ȥ
	delay_us(35);//���ݵ͵�ƽ�ָ��źŹ�ȥ�󣬵ȴ�35us��Ȼ�����жϣ�����ΪʲôҪ�ȴ��������ķ���
    if(DATA_PIN==1) //�����ʱ35us���źŻ��Ǹߵ�ƽ�Ļ�����ô��ִ��if����ĳ���
  	{
      dht=dht|0x01;//dht�����λ��1��������λ���ı�
      delay_us(55);//����ʱ55us���ȴ��ߵ�ƽ�źŹ�ȥ
    }   
    else;//�����ʱ35us���ǵ͵�ƽ�Ļ�����ô��ʲô����ִ�У�����һ��ifѭ����dht������λ��ʱ�򣬻��Զ������λ��Ϊ0��Ȼ��������λ             
  } 
  return(dht);//�����dht����   
}

void read_dht11() //����һ����ȡDHT11���ص�40bits�����ݵĺ���
{
  DHT11_Start();//����DHT11��ʼ����
  if(!DATA_PIN)//���DHT11�����͵�ƽ�ź���Ӧ�Ļ�����ִ���������γ���
  {   
    while(!DATA_PIN);//�ȴ��͵�ƽ��Ӧ�źŹ�ȥ
    while(DATA_PIN);//�ٵȴ�DHT11�͵�ƽ��Ӧ�ź�֮���һ��80us�ĸߵ�ƽȷ���źŹ�ȥ
    RHH=readdht11_byte();//��ȡʪ�ȵ�����λ
    RLL=readdht11_byte();//��ȡʪ�ȵ�С��λ
    CHH=readdht11_byte();//��ȡ�¶ȵ�����λ
    CLL=readdht11_byte();//��ȡ�¶ȵ�С��λ
   }  
}

void Trans()//����ȡ����ʪ��ת�����ַ���
{
	sprintf(TEMPH,"%d",CHH);//���¶�����λת�����ַ�
	sprintf(TEMPL,"%d",CLL/1000);//���¶ȵ�С��λת�����ַ�
	sprintf(DAMPH,"%d",RHH);
	sprintf(DAMPL,"%d",RLL/10000);
	strcat(TEMPH,dot);//��С������¶ȵ�����λ�ϳ�һ���ַ�
	strcat(TEMPH,TEMPL);//���ϳɺ���¶�����λ+С�������¶ȵ�С��λ�ϳ�һ���ַ�
	strcat(DAMPH,dot);
	strcat(DAMPH,DAMPL);
}

// void main()
// {	
//     OLED_Init();//��ʼ��OLED
//     OLED_CLS(); //OLED����		
// 	OLED_P8x16Str(0,2,"TEMP:");//��OLED������ʾTEMP:�ַ���
// 	OLED_P8x16Str(64,2,"DAMP:");         
// 	OLED_P8x16Str(100,6,"RAA");
// 	Uart_Init();//���ڳ����ʼ��
// 	while(1)//ѭ��ִ���������δ���
// 	{
// 		read_dht11();//��ȡDHT11����ֵ
// 		Delay1000ms();//��ʱ1s,��ΪDHT11��ˢ��Ƶ����1s ����
// 		Trans();//����ȡ������ת����һ���ַ�
// 		Send_String("TEMP NOW: ");//�ڴ�������ʾ�������
// 		Send_String(TEMPH);//���¶�ֵ���͵�������
// 		Send_String("\r\n");//��ȡһ��
// 		Send_String("DAMP NOW: ");
// 		Send_String(DAMPH);
// 		Send_String("\r\n");
// 		OLED_P8x16Str(0,4,TEMPH);//��OLED����ʾ����ǰ�¶�ֵ
// 		OLED_P8x16Str(64,4,DAMPH);	
// 	}
// }