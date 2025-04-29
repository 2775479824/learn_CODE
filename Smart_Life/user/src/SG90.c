#include "sg90.h"


/*********************************************************************************************************
* 函 数 名 : SteeringPwm_Init
* 功能说明 : 初始化TIM2：CH2，输出PWM驱动舵机
* 形    参 : arr：重装载，psc：预分频
* 返 回 值 : 无
* 备    注 : Fpwm（HZ） = Fclk / （（arr+1）*（psc+1））
			 Duty_ratio（%） = CRR1 / ARR
			 84M / 840 = 0.1M 故记一个数的时间为10us  定时周期：（1999 + 1） * 10us = 20ms
*********************************************************************************************************/ 
void SteeringPwm_Init(unsigned short arr,unsigned short psc)
{
	GPIO_InitTypeDef 		    GPIO_InitStruct			    = {0};
	TIM_OCInitTypeDef 		  TIM_OCInitStruct		    = {0};
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct	= {0};
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);							//使能PA外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,  ENABLE);							//开启TIM2外设时钟
					
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);	  				//PA1复用TIM2功能
					
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_1;													//初始化引脚
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;												//复用模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;												//推挽输出
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;										//无上下拉
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;										//50MHZ
	GPIO_Init(GPIOA, &GPIO_InitStruct);																//根据GPIO_InitStruct初始化
		
	//配置定时器
	TIM_TimeBaseInitStruct.TIM_Period 		   = arr-1;									//重装载
	TIM_TimeBaseInitStruct.TIM_Prescaler 	   = psc-1;									//预分频
	TIM_TimeBaseInitStruct.TIM_CounterMode 	 = TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;			    //不分频
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	
	//配置PWM
	TIM_OCInitStruct.TIM_OCMode 	   = TIM_OCMode_PWM1;			    			//PWM模式1，TIMx_CNT<TIMx_CCR1时为有效电平
	TIM_OCInitStruct.TIM_OCPolarity  = TIM_OCPolarity_High;		  			//输出极性为低
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;				//比较输出使能
	TIM_OCInitStruct.TIM_Pulse		   = 0;															//设置比较寄存器的初值
	TIM_OC2Init(TIM2, &TIM_OCInitStruct);			
				
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);									//使能CCR2的预装载
	TIM_Cmd(TIM2, ENABLE);																						//使能TIM2外设
}


/*********************************************************************************************************
* 函 数 名 : SetServoAngle
* 功能说明 : 设置舵机的角度，0~180
* 形    参 : angle：角度值
* 返 回 值 : 无
* 备    注 : 只需要调用一次，舵机即可保持角度；0.5ms--0°  2.5ms--180°


当脉冲宽度为1.5ms时，舵机处于0度位置；当脉冲宽度为2.5ms时，舵机处于180度位置。
因此，每增加0.1ms的脉冲宽度，舵机的角度增加18度（180度/10ms）
*********************************************************************************************************/ 

 
 //舵机控制
//angle：0：0度，1:45度，2:90度，3:135度，4:180度
void SetServoAngle(u8 angle)
{
	switch(angle)
	{
		case 0:
			TIM_SetCompare2(TIM2,500);//0.5ms    
			break;
		case 1:
			TIM_SetCompare2(TIM2,1000);//1.0ms
			break;
	   case 2:
			TIM_SetCompare2(TIM2,1500);//1.5ms
			break;
	   case 3:
			TIM_SetCompare2(TIM2,2000);//2.0ms
			break;
	   case 4:
			TIM_SetCompare2(TIM2,2500);//2.5ms
			break;
	}
}
