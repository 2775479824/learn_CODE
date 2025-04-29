#include "beep.h"
/*
函数功能：蜂鸣器管脚初始化
返回值：void
形参：void
函数说明：
        BEEP  --   PC12  --  通用推挽输出
		
*/
 
void Beep_Init(void)
{
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
		GPIO_InitTypeDef GPIO_InitStruct={0};
		
	  GPIO_InitStruct.GPIO_Mode =GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_OType =GPIO_OType_PP;
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	
	  GPIO_Init(GPIOC,&GPIO_InitStruct);
		GPIO_ResetBits(GPIOC, GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_12);

}






