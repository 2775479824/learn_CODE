#ifndef _DELAY_H         //防止此文件被重复定义
#define _DELAY_H         //定义文件

#include "stm32f4xx.h"  //M4芯片的支持文件，在每个.h文件中都要包含


void delay_us(u32 nus);
void delay_ms(u32 nms);

#endif
