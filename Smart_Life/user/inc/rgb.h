#ifndef __RGB_H
#define __RGB_H

#include "stm32f4xx.h"
#include "delay.h"

#define RGB_DATA_H GPIO_SetBits(GPIOB, GPIO_Pin_15)
#define RGB_DATA_L GPIO_ResetBits(GPIOB, GPIO_Pin_15)

#define RGB_RED 	  0xff0000
#define RGB_GREEN 	0x00ff00
#define RGB_BLUE	  0x0000ff
#define RGB_SKY		  0x00ffff
#define RGB_MAGENTA 0xff00ff
#define RGB_YELLOW  0xffff00
#define RGB_ORANGE  0x7f6a00
#define RGB_BLACK   0x000000
#define RGB_WHITE   0xffffff
#define RGB_PURPLE  0x4169e1

void Rgb_Init(void);

void W2812_WriteColorData(unsigned int color);
void RGB_Reset(void);
void W2812_WriteByte(unsigned char Byte);

#endif
