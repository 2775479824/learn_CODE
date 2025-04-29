#include "usart1.h"
/*
函数功能:USART1初始化
返回值：void
形参：void
函数说明：
        USART1_TX --   PA9  --  复用模式
				USART1_RX --   PA10 --  复用模式
		
*/
 
void Usart1_Init(void)
{
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
		GPIO_InitTypeDef GPIO_InitStruct={0};
		
	  GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF;//复用模式
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO_InitStruct);
		
		//3、配置IO复用功能关系
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);//将PA9复用到USART1
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);//将PA10复用到USART1

		//4、打开USART1时钟   USART1 --> APB2
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		
		//5、初始化USART1    XXX_Init
		USART_InitTypeDef USART_InitStruct = {0};
		USART_InitStruct.USART_BaudRate = 115200;//设置波特率（直接填入所需波特率的值）
		USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//发送器和接收器使能
		USART_InitStruct.USART_Parity =USART_Parity_No;//不使用奇偶校验
		USART_InitStruct.USART_StopBits = USART_StopBits_1;//停止位为1bit
		USART_InitStruct.USART_WordLength = USART_WordLength_8b;//数据为8bit
		USART_Init(USART1, &USART_InitStruct);
		
		//6、使能USART1 XXX_CMD
		USART_Cmd(USART1, ENABLE);
		
		NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(7-2,2,1)); 
		NVIC_EnableIRQ(USART1_IRQn);
		
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
		
	
		
}

/*
    设置终断服务函数
    名字固定，不需要声明和调用
*/

REC_BUF rec_buf;

void USART1_IRQHandler(void)
{
	u8 data;
	//1、接收中断
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE))
	{
		//清除标记位
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		
		//接收数据
		//数组接收str[len]
		//判断接收完成flag
		rec_buf.rec_str[rec_buf.len]=USART_ReceiveData(USART1);
		rec_buf.len++;
		
	}
	//2、空闲中断
	if(USART_GetITStatus(USART1, USART_IT_IDLE))
	{
		//清除标记位
		data = USART1 -> SR;
		data = USART1 -> DR;
		
		//处理数据
		rec_buf.rec_str[rec_buf.len]='\0'; //判断接收完成，完成后len=\0
		rec_buf.len =0;
		rec_buf.flag =1;
		printf("串口1接收到的数据为:%s\r\n",rec_buf.rec_str);
	}
}


/*
函数功能:USART1发送1字节数据至PC
返回值：void
形参：u8 data 发送1byte数据
函数说明：
*/

void usart1_send_byte(u8 data)
{
  //1、等待发送标志位为1（才可以发送数据）
	while(!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
	//2、发送数据
	USART_SendData(USART1,data);

}

//发送字符串函数———字节函数的基础上添加循环—判断字符结尾
void usart1_send_string(u8 *str)
{
	while(*str !='\0')
	{
		usart1_send_byte(*str);
		str++;
	}
}


/*
函数功能:PC通过USART1接收1字节数据
返回值：u8
形参：u8 data 接收1byte数据
函数说明：
*/
u8 usart1_receive_byte(void)
{
	u16 data;
	//接受标记位判断，等待上一次接收完成
	while(!USART_GetFlagStatus(USART1, USART_FLAG_RXNE));
	USART_ClearFlag(USART1,USART_FLAG_RXNE);
	data = USART_ReceiveData(USART1);
	return data;
}










/*printf重定向*/
//此函数不需要声明和调用，仅需要放在这个位置
int fputc(int c, FILE * stream)
{
	usart1_send_byte(c);
	return c;
}











