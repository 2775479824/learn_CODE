#include "usart3.h"
/*
函数功能:USART1初始化
返回值：void
形参：void
函数说明：
        USART3_TX --   PB11  --  复用模式
				USART3_RX --   PB10 --  复用模式
		
*/
 
void Usart3_Init(void)
{
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
		GPIO_InitTypeDef GPIO_InitStruct={0};
		
	  GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF;//复用模式
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10;
	  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB,&GPIO_InitStruct);
		
		//3、配置IO复用功能关系
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);//将PA9复用到USART1
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);//将PA10复用到USART1

		//4、打开USART1时钟   USART1 --> APB2
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		
		//5、初始化USART1    XXX_Init
		USART_InitTypeDef USART_InitStruct = {0};
		USART_InitStruct.USART_BaudRate = 115200;//设置波特率（直接填入所需波特率的值）
		USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//发送器和接收器使能
		USART_InitStruct.USART_Parity =USART_Parity_No;//不使用奇偶校验
		USART_InitStruct.USART_StopBits = USART_StopBits_1;//停止位为1bit
		USART_InitStruct.USART_WordLength = USART_WordLength_8b;//数据为8bit
		USART_Init(USART3, &USART_InitStruct);
		
		//6、使能USART1 XXX_CMD
		USART_Cmd(USART3, ENABLE);
		
		NVIC_InitTypeDef NVIC_InitStruct; // 确保变量名一致
    NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;      // 串口3中断源
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;        //使能
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;     // 子优先级
    NVIC_Init(&NVIC_InitStruct); // 调用初始化函数
		
		
		
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
}

/*
    设置终断服务函数
    名字固定，不需要声明和调用
*/

U3_REC_BUF u3_rec_buf;

void USART3_IRQHandler(void)
{
	u8 data;
	//1、接收中断
	if(USART_GetFlagStatus(USART3, USART_IT_RXNE)==SET)
	{
		//清除标记位
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		
		//接收数据
		//数组接收str[len]
		//判断接收完成flag
		u3_rec_buf.u3_str[u3_rec_buf.u3_len]=USART_ReceiveData(USART3);
		u3_rec_buf.u3_len++;
		
	}
	//2、空闲中断
	if(USART_GetITStatus(USART3, USART_IT_IDLE)==SET)
	{
		//清除标记位
		data = USART3 -> SR;
		data = USART3 -> DR;
		
		//处理数据
		u3_rec_buf.u3_str[u3_rec_buf.u3_len]='\0'; //判断接收完成，完成后len=\0
		u3_rec_buf.u3_len =0;
		u3_rec_buf.u3_flag =1;
		//printf("串口1接收到的数据为:%s\r\n",rec_buf.rec_str);
		for(u8 i = 0; i < 4; i++)
		{
			printf("串口3接收到的数据为:%d:0x%02x",i,u3_rec_buf.u3_str[i]);
		}
		printf("\r\n");
	}
}


/*
函数功能:USART3发送1字节数据至PC
返回值：void
形参：u8 data 发送1byte数据
函数说明：
*/

void usart3_send_byte(u8 data)
{
  //1、等待发送标志位为1（才可以发送数据）
	while(!USART_GetFlagStatus(USART3, USART_FLAG_TXE));
	//2、发送数据
	USART_SendData(USART3,data);

}

//发送字符串函数———字节函数的基础上添加循环—判断字符结尾
void usart3_send_string(u8 *str)
{
	while(*str !='\0')
	{
		usart3_send_byte(*str);
		str++;
	}
}




