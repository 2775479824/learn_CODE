#ifndef _BEEP_H         //防止此文件被重复定义
#define _BEEP_H         //定义文件

#include "stm32f4xx.h"  //M4芯片的支持文件，在每个.h文件中都要包含

#define BEEP_ON (GPIO_SetBits(GPIOC, GPIO_Pin_12))
#define BEEP_OFF (GPIO_ResetBits(GPIOC, GPIO_Pin_12))
//异或^: 1^0 =1 1^1 =0
#define BEEP_TAG (GPIOC->ODR ^=(1 << 12) )




/*****************函数声明*********************/
void Beep_Init(void);

#endif


