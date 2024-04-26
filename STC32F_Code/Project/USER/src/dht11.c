#include "headfile.h"

#define uint unsigned int
#define uchar unsigned char

#define DATA_PIN P40
//#define DATA P3^4//这样宏定义在编译的时候会报错，具体的看我写的一篇文章，在问题解决分类里面，有详细的解释
int RLL,RHH,CLL,CHH; //用于储存温湿度的数据定义
char DAMPH[8],TEMPH[8],DAMPL[8],TEMPL[8];//用于储存温湿度的字符型数组定义
char dot[1]=".";//小数点

// void delay_us(uchar n)  //定义延时为us级的延时函数                       
// {
//   while(n--); 
// }

// void delay_ms(uint z)//定义延时为ms级的延时函数
// {
//   uint x,y;
//   for(x=z;x>0;x--)
//   for(y=614;y>0;y--);
// }

void Delay1000ms()//定义延时为1s的延时函数		
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
	DATA_PIN=0;//将总线拉低
	delay_ms(20);//延时20ms，确保延时大于18ms，这样DHT11可以检测到起始信号，然后就可以开始发出响应信号
	DATA_PIN=1;//将总线拉高
	delay_us(30);
	DATA_PIN=1;
}

int readdht11_byte() //定义一个以字节为单位的函数，分别读取dht11发送的40bits的数据
{   
  int i,dht;  
  for(i=8;i>0;i--)//下面的这个循环实现读取八个bit的数据
  {      
    dht=dht<<1;//每次读取前，将数据的高位移位向左移位
    while(!DATA_PIN);//等待DHT11的50us低电平数据分隔信号过去
	delay_us(35);//数据低电平分隔信号过去后，等待35us，然后再判断，具体为什么要等待，待下文分晓
    if(DATA_PIN==1) //如果延时35us后，信号还是高电平的话，那么就执行if里面的程序
  	{
      dht=dht|0x01;//dht的最低位置1，其他的位不改变
      delay_us(55);//再延时55us，等待高电平信号过去
    }   
    else;//如果延时35us后，是低电平的话，那么就什么都不执行，在下一次if循化，dht数据移位的时候，会自动把最低位置为0，然后向左移位             
  } 
  return(dht);//将这个dht返回   
}

void read_dht11() //定义一个读取DHT11返回的40bits的数据的函数
{
  DHT11_Start();//先让DHT11开始工作
  if(!DATA_PIN)//如果DHT11发出低电平信号响应的话，就执行下面的这段程序
  {   
    while(!DATA_PIN);//等待低电平响应信号过去
    while(DATA_PIN);//再等待DHT11低电平响应信号之后的一段80us的高电平确认信号过去
    RHH=readdht11_byte();//读取湿度的整数位
    RLL=readdht11_byte();//读取湿度的小数位
    CHH=readdht11_byte();//读取温度的整数位
    CLL=readdht11_byte();//读取温度的小数位
   }  
}

void Trans()//将读取的温湿度转换成字符型
{
	sprintf(TEMPH,"%d",CHH);//将温度整数位转换成字符
	sprintf(TEMPL,"%d",CLL/1000);//将温度的小数位转换成字符
	sprintf(DAMPH,"%d",RHH);
	sprintf(DAMPL,"%d",RLL/10000);
	strcat(TEMPH,dot);//将小数点和温度的整数位合成一串字符
	strcat(TEMPH,TEMPL);//将合成后的温度整数位+小数点与温度的小数位合成一串字符
	strcat(DAMPH,dot);
	strcat(DAMPH,DAMPL);
}

// void main()
// {	
//     OLED_Init();//初始化OLED
//     OLED_CLS(); //OLED清屏		
// 	OLED_P8x16Str(0,2,"TEMP:");//在OLED上面显示TEMP:字符串
// 	OLED_P8x16Str(64,2,"DAMP:");         
// 	OLED_P8x16Str(100,6,"RAA");
// 	Uart_Init();//串口程序初始化
// 	while(1)//循环执行下面的这段代码
// 	{
// 		read_dht11();//读取DHT11的数值
// 		Delay1000ms();//延时1s,因为DHT11的刷新频率在1s 左右
// 		Trans();//将读取的数据转换成一串字符
// 		Send_String("TEMP NOW: ");//在串口上显示这段内容
// 		Send_String(TEMPH);//将温度值发送到串口上
// 		Send_String("\r\n");//另取一行
// 		Send_String("DAMP NOW: ");
// 		Send_String(DAMPH);
// 		Send_String("\r\n");
// 		OLED_P8x16Str(0,4,TEMPH);//在OLED上显示出当前温度值
// 		OLED_P8x16Str(64,4,DAMPH);	
// 	}
// }
