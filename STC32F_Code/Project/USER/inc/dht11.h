#ifndef __DHT11_H
#define __DHT11_H

#include  "headfile.h"

extern int RLL,RHH,CLL,CHH; //用于储存温湿度的数据定义
extern char DAMPH[8],TEMPH[8],DAMPL[8],TEMPL[8];//用于储存温湿度的字符型数组定义
extern char dot[1];//小数点

void Delay1000ms(void);
void DHT11_Start(void);
int readdht11_byte(void);
void read_dht11(void);
void Trans(void);
float Temperature_Fusion(void);
uint8 Threshold_Warning(float detected_value, float threshold_value);
void Print_Get_Data(void);

#endif