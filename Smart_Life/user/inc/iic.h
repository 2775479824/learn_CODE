#ifndef _IIC_H
#define _IIC_H


#include "stm32f4xx.h"


#define SDA_H (GPIO_SetBits(GPIOB,GPIO_Pin_7))
#define SDA_L (GPIO_ResetBits(GPIOB,GPIO_Pin_7))
#define SCL_H (GPIO_SetBits(GPIOB,GPIO_Pin_6))
#define SCL_L (GPIO_ResetBits(GPIOB,GPIO_Pin_6))
#define SDA   (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))

//#define IIC_SDA PBout(7)
//#define IIC_SCL PBout(6)
//#define IIC_SDAIN     PBin(7)      // ‰»ÎSDA 

void IIC_WriteByte(unsigned char data);
unsigned char IIC_ReadByte(unsigned char ack);
unsigned char IIC_Wait_ACK(void);
void IIC_ACK_NACK(unsigned char ack);
void IIC_Stop(void);
void IIC_Start(void);

#endif
