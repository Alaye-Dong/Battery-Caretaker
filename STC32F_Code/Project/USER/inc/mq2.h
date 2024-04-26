#ifndef _MQ2_H_
#define _MQ2_H_

#include "headfile.h"

void MQ2_Init(void);
uint16 MQ2_ADC_Read(void);
float Smog_Get_Vol(void);
float Smog_GetPPM(void);

#endif