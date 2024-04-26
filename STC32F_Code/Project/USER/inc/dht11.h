#ifndef __DHT11_H
#define __DHT11_H

#include  "headfile.h"

extern int RLL,RHH,CLL,CHH; //���ڴ�����ʪ�ȵ����ݶ���
extern char DAMPH[8],TEMPH[8],DAMPL[8],TEMPL[8];//���ڴ�����ʪ�ȵ��ַ������鶨��
extern char dot[1];//С����

void Delay1000ms(void);
void DHT11_Start(void);
int readdht11_byte(void);
void read_dht11(void);
void Trans(void);


#endif