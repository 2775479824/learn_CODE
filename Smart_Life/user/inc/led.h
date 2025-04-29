#ifndef _LED_H         //防止此文件被重复定义
#define _LED_H         //定义文件

#include "stm32f4xx.h"  //M4芯片的支持文件，在每个.h文件中都要包含

/*************************宏定义***********************/
//宏定义名字保证全部大写，用来与变量做区分
//宏定义后不能加分号



#define LED1_ON   (GPIO_ResetBits(GPIOC,GPIO_Pin_4))
#define LED1_OFF  (GPIO_SetBits(GPIOC,GPIO_Pin_4))

#define LED2_ON   (GPIO_ResetBits(GPIOC,GPIO_Pin_5))
#define LED2_OFF  (GPIO_SetBits(GPIOC,GPIO_Pin_5))

#define LED3_ON   (GPIO_ResetBits(GPIOB,GPIO_Pin_0))
#define LED3_OFF  (GPIO_SetBits(GPIOB,GPIO_Pin_0))


#define LED1_TAG (GPIOC->ODR ^= (1 << 4))
#define LED2_TAG (GPIOC->ODR ^= (1 << 5))
#define LED3_TAG (GPIOB->ODR ^= (1 << 0))


/*****************函数声明*********************/
void Led_Init(void);

#endif


