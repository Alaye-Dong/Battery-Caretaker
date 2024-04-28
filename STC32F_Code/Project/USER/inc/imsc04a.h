#ifndef __IMSC04A_H
#define __IMSC04A_H

#include "headfile.h"

void IMSC04A_Init(void);
uint16 IMSC04A_ADC_Read(void);
uint16 ADC_Press_Average_Data(void);
float Press_Get_Vol(void);

#endif