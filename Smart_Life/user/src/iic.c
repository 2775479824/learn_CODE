#include "iic.h"
#include "delay.h"

void IIC_Start(void)
{
	SCL_H;   //空闲
	SDA_H;   //空闲
	delay_us(5);
	SDA_L;   //拉低数据线，开始通信
	delay_us(5);
	SCL_L;   //时钟线拉低，开始通信
	
}

void IIC_Stop(void)
{
	SCL_H;  //拉高时钟线，准备终止通信
	SDA_L;  
	delay_us(5);
	SDA_H; //拉高数据线，终止通信
	delay_us(5);
}


void IIC_ACK_NACK(unsigned char ack)
{	
	SCL_L;	//SCL为低电平时才能改变SDA的状态
	delay_us(1);
	if(!ack)	SDA_L;	//产生应答信号
	else 		SDA_H;	//产生非应答信号
	delay_us(5);
	SCL_H;	//拉高SCL，从机读取应答信号
	delay_us(5);
	SCL_L;	//拉低SCL，准备接收下一个数据
}


/*********************************************************************************************************
* 函 数 名 : IIC_Wait_ACK
* 功能说明 : 作为发送方时，检测从机返回的应答信号
* 形    参 : 无
* 返 回 值 : 0：应答，1：非应答
* 备    注 : 
*********************************************************************************************************/ 
unsigned char IIC_Wait_ACK(void)
{
	unsigned char t = 0;
	SDA_H;	//释放数据线
	SCL_H;	//拉高SCL
	delay_us(5);
	while(SDA)			//SDA被拉低则认为从机给的应答信号
	{
		t++;
		if(t > 250)	//如果过了一段时间数据线还是为高，那么表示非应答信号
		{
			IIC_Stop();
			return 1;
		}
	}
	SCL_L;	//拉低SCL，准备下一个数据的接受
	delay_us(5);
	return 0;
}

/*********************************************************************************************************
* 函 数 名 : IIC_WriteByte
* 功能说明 : 发送一个字节的数据到IIC总线上
* 形    参 : data：需要发送的数据
* 返 回 值 : 无
* 备    注 : MSB（高位在前）
*********************************************************************************************************/ 
void IIC_WriteByte(unsigned char data)
{
	unsigned char count = 0;
	for(count=0;count<8;count++)
	{
		SCL_L;	//SCL为低电平时才能改变SDA的状态
		if(data&0x80)	SDA_H;
		else			SDA_L;
		data <<= 1;
		delay_us(5);
		SCL_H;	//数据已准备好，通知从机读取
		delay_us(5);
	}
	SCL_L;
	delay_us(5);
}


/*********************************************************************************************************
* 函 数 名 : IIC_ReadByte
* 功能说明 : 读取IIC总线上的一个字节
* 形    参 : ack：0应答，1非应答
* 返 回 值 : 读取到的数据
* 备    注 : MSB（高位在前）
*********************************************************************************************************/ 
unsigned char IIC_ReadByte(unsigned char ack)
{
	unsigned char count = 0, data = 0;
	SDA_H;		//释放数据线
	for(count=0;count<8;count++)
	{
		SCL_L;	//通知从机准备数据
		delay_us(5);
		SCL_H;	//从机已经准备好数据了
		data <<= 1;		//准备一个空位
		data |= !!SDA;	//二值化，确保结果只有1和0
		delay_us(5);
	}
	SCL_L;
	delay_us(5);
	IIC_ACK_NACK(ack);
	return data;
}

