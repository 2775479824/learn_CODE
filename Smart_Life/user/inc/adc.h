#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx.h"
#include "stdio.h"

#define NTC_CH 10
#define IR_CH  11

void Adc_Init(void);
u32 Get_AdcValue(unsigned char ch);
u32 Get_AverageValue(unsigned char ch);

#endif
