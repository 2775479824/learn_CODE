#ifndef _KEY_H         //防止此文件被重复定义
#define _KEY_H         //定义文件

#include "stm32f4xx.h"  //M4芯片的支持文件，在每个.h文件中都要包含

#define KEY1 (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
#define KEY2 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))
#define KEY3 (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1))



/*****************函数声明*********************/
void Key_Init(void);

#endif

