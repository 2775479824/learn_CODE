#include "rgb.h"
#include "delay.h"


/*************************************
* 函 数 名 : Rgb_Init
* 功能说明 : RGB灯珠端口初始化
* 形    参 : 无
* 返 回 值 : 无
* 备    注 : PB15
***************************************/ 
void Rgb_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//使能PB外设时钟
	
	GPIO_InitStruct.GPIO_Pin 	  = GPIO_Pin_15;			//初始化引脚
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_OUT;		//输出模式
	GPIO_InitStruct.GPIO_OType 	= GPIO_OType_PP;		//推挽输出
	GPIO_InitStruct.GPIO_PuPd 	= GPIO_PuPd_UP;			//无上下拉
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_2MHz;	//2MHZ
	GPIO_Init(GPIOB, &GPIO_InitStruct);					    //根据GPIO_InitStruct初始化
	
	RGB_DATA_H;
		
	
	RGB_Reset();										//复位
	W2812_WriteColorData(RGB_BLACK);					//RGB1默认熄灭
	W2812_WriteColorData(RGB_BLACK);					//RGB2默认熄灭
	W2812_WriteColorData(RGB_BLACK);					//RGB3默认熄灭
	W2812_WriteColorData(RGB_BLACK);					//RGB4默认熄灭
	delay_ms(10);
}


/**********************************
* 函 数 名 : W2812_WriteColorData
* 功能说明 : 写入颜色值
* 形    参 : color：需要显示的颜色
* 返 回 值 : 无
* 备    注 : 通过RGB配比，可以显示出不同的颜色。
						 IO模拟时序不是很准确，而且效率极低，项目中不建议使用此方法
************************************/ 
void W2812_WriteColorData(unsigned int color)
{
	
	
}
/***********************************
* 函 数 名 : W2812_WriteByte
* 功能说明 : 向RGB灯珠写入一个字节的数据
* 形    参 : Byte：要写入的数值
* 返 回 值 : 无
* 备    注 : 	Data transefer time:
				T0H 		0 code ,high voltage time 		0.4us ±150ns
				T1H 		1 code ,high voltage time 		0.8us ±150ns
				T0L 		0 code , low voltage time 		0.85us ±150ns
				T1L 		1 code ,low voltage time 		0.45us ±150ns
				RES 		low voltage time 				Above 50us
************************************/ 
void W2812_WriteByte(unsigned char Byte)
{
	
}
/*******************************
* 函 数 名 : RGB_Reset
* 功能说明 : 
* 形    参 : 
* 返 回 值 : 
* 备    注 : 
********************************/ 
void RGB_Reset(void)
{
	
}
