#ifndef _USART1_H         //防止此文件被重复定义
#define _USART1_H         //定义文件

#include "stm32f4xx.h"  //M4芯片的支持文件，在每个.h文件中都要包含
#include "stdio.h"


/*****************函数声明*********************/
typedef struct
	{
		u8 rec_str[512];
		u8 len;
		u8 flag;

	}REC_BUF;
extern REC_BUF rec_buf;




void Usart1_Init(void);
void usart1_send_byte(u8 data);
void usart1_send_string(u8 *str);
u8 usart1_receive_byte(void);

#endif
