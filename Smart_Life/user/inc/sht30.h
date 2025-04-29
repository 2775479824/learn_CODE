#ifndef _SHT30_H
#define _SHT30_H


#include "stm32f4xx.h"

extern float te;
extern float hu;

void Sht30_Init(void);
void Sht30_ReadData(void);


#endif
