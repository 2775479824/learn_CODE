#ifndef _USART3_H         //防止此文件被重复定义
#define _USART3_H         //定义文件

#include "stm32f4xx.h"  //M4芯片的支持文件，在每个.h文件中都要包含
#include "stdio.h"


/*****************函数声明*********************/
typedef struct
	{
		u8 u3_str[20];
		u8 u3_len;
		u8 u3_flag;
	}U3_REC_BUF;
	extern U3_REC_BUF u3_rec_buf;




void Usart3_Init(void);
void usart3_send_byte(u8 data);
void usart3_send_string(u8 *str);

#endif