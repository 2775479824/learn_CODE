#ifndef _SG90_H
#define _SG90_H


#include "stm32f4xx.h"

void SteeringPwm_Init(unsigned short arr,unsigned short psc);
void SetServoAngle(u8 angle);


#endif


