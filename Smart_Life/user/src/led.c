#include "led.h"

/*
函数功能：LED管脚初始化
返回值：void
形参：void
函数说明：
        LED1  --   PC4  --  通用推挽输出
				LED2  --   PC5  --  通用推挽输出
				LED3  --   PB0  --  通用推挽输出
*/
 
void Led_Init(void)
{
	
	//1、打开GPIOC时钟  --  rcc：有关时钟配置
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	
	
	//2、初始化GPIO
	//有关某个器件的初始化函数     XXX_Init()
	GPIO_InitTypeDef GPIO_InitStruct={0};//定义结构体变量
	//结构体别名        结构体变量
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//输出模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//推挽模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;//无上下拉
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//查找成员，可以配置的值     跳转到结构体：鼠标右键结构体别名
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_SetBits(GPIOC,GPIO_Pin_4);//PC4输出高电平
	GPIO_SetBits(GPIOC,GPIO_Pin_5);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
		
	  GPIO_InitStruct.GPIO_Mode =GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_OType =GPIO_OType_PP;
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	
	  GPIO_Init(GPIOB,&GPIO_InitStruct);
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
	
}






