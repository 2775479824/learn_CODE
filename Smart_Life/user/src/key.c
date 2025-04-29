#include "key.h"
#include "delay.h"
/*
函数功能:按键管脚初始化
返回值：void
形参：void
函数说明：
        KEY1  --   PA0 --  输入模式
				KEY2  --   PC13 -- 输入模式
				KEY3  --   PB1--  输入模式
		
*/
 
void Key_Init(void)
{
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
		GPIO_InitTypeDef GPIO_InitStruct={0};
		
	  GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IN;
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	  GPIO_Init(GPIOA,&GPIO_InitStruct);
		
		
		 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
		
	  GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IN;
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	  GPIO_Init(GPIOC,&GPIO_InitStruct);

		
		
		 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
		
	  GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IN;
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	  GPIO_Init(GPIOB,&GPIO_InitStruct);
		
}


/*
函数功能:按键扫描
返回值：u8     0:没有按键按下   1：按下KEY1  2：按下KEY2  3：按下KEY3
形参：void
函数说明：
        KEY1  --   PA0 --  输入模式
				KEY2  --   PC13 -- 输入模式
				KEY3  --   PB1--  输入模式
		
*/

u8 key_scan(void)
{
	static u8 flag = 0; //记录按键状态 0:代表按键没有按下
	//1、判断按键有没有按下
	if((KEY1== 1 || KEY2== 0 || KEY3== 0 ) && flag == 0)
	{
		delay_ms(30);//按键消抖
		flag = 1;
		//2、判断按下的是哪一个按键
		if(KEY1 == 1)//代表按下按键1
			return 1;
		if(KEY2 == 0)
			return 2;
		if(KEY3 == 0)
			return 3;
	}
	//3、判断按键是否松开
	else if(KEY1 == 0 && KEY2 == 1 && KEY3 == 1 && flag ==1)
	{
		flag = 0;
	}

	return 0;


}








