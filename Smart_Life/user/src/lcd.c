#include "lcd.h"
#include "font.h"

/********************
PB4--CS--推挽输出
PB3--SCL--推挽输出
PD2--D/C--推挽输出
PB5--MOSI--推挽输出
PA15--BL--推挽输出
********************/
void LCD_IO_init(void)
{
	//GPIO初始化
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//1.开时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//1.开时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//1.开时钟
	
	//推挽输出
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_3 |GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	LCD_LED_L;
}

/*
**********************************************************************
函数功能：spi数据交换的函数(主机发送一个字节数据给从机，并且读取从机发送过来的一个字节数据)
函数形参：主机要发送给从机的数据
函数返回值：主机读到从机数据
备注：数据位8bit  先高后低的顺序
**********************************************************************
*/
void LCD_spi_byte(u8 data)
{
	u8 i,buf = 0;
	SPI2_SCL_H;
	for(i = 0; i < 8; i++)    //循环发送8位数据
	{
		SPI2_SCL_L;
		if(data & 0x80)  //判断最高位是否为1
		{
			LCD_MOSI_H;
		}
		else
		{
			LCD_MOSI_L;
		}
		SPI2_SCL_H;							//产生上升沿，帮助从机
			data = data << 1;
		//buf |= 1; //由于没有MISO也就是不需要管接受回来的数据所以这里的值不重要
	}
}

/*
****************************************************************************************
* 函数名: st7789vm_write_command
* 函数作用: st7789vm oled的写入命令
* 参数: command    写入的命令数据
* 返回值: 无
*/
void st7789vm_write_command(uint8_t command)
{
	LCD_CS_L;										//拉低片选
	LCD_COMMAND;                //表示发送的是命令
	LCD_spi_byte(command); 		  //具体发送的8位命令
	LCD_CS_H;                   //拉高片选
}

/*
****************************************************************************************
* 函数名: st7789vm_write_command_parameter
* 函数作用: st7789vm oled的写入命令参数
* 参数: parameter    写入的命令参数数据
* 返回值: 无
*/
void st7789vm_write_command_parameter(uint8_t parameter)
{
	LCD_CS_L;													//拉低片选
	LCD_DATA;					                //表示发送的是数据
	LCD_spi_byte(parameter);      		//具体发送的8位命令参数
	LCD_CS_H;                         //拉高片选
}


/*
****************************************************************************************
* 函数名: st7789vm_write_data
* 函数作用: st7789vm LCD的写入数据函数
* 参数: write_data    写入的数据
* 返回值: 无
* 函数描述：坐标值，颜色值
****************************************************************************************
*/
void st7789vm_write_data(uint16_t write_data)//0x80
{
	LCD_CS_L;													//拉低片选
	LCD_DATA;                         //表示发送的是数据
	LCD_spi_byte(write_data >> 8);//先发送高8位
	LCD_spi_byte(write_data);     //再发送低八位
	LCD_CS_H;													//拉高片选
}

/*
****************************************************************************************
* 函数名: st7789vm_set_position
* 函数作用: st7789vm oled的坐标设置
* 参数:  sx    起始X轴坐标
*        sy    起始Y轴坐标
*        ex    停止X轴坐标
*        ey    停止Y轴坐标
* 返回值: 无
****************************************************************************************
*/
//void st7789vm_set_position(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey)
//{
//	st7789vm_write_command(0X2A); //设置X轴坐标命令
//	st7789vm_write_data(sx); //设置显示X轴起始坐标
//	st7789vm_write_data(ex); //设置显示X轴停止坐标
//	
//	st7789vm_write_command(0X2B); //设置Y轴坐标命令
//	st7789vm_write_data(sy); //设置显示Y轴起始坐标
//	st7789vm_write_data(ey); //设置显示Y轴停止坐标
//	
//	st7789vm_write_command(0X2C); //写入显示数据命令
//}



/*
****************************************************************************************
* 函数名: st7789vm_clear_display
* 函数作用:    ST7789VM 清屏
* 参数:  sx    起始X轴坐标
*        sy    起始Y轴坐标
*        ex    停止X轴坐标
*        ey    停止Y轴坐标
*        clear_color    清屏的颜色
* 返回值: 无
****************************************************************************************
*/
void LCD_clear(uint16_t color)
{
	/*确定区域*/
	//确定x方向
	st7789vm_write_command(0x2A);     //横坐标命令
	//起始横坐标
	 st7789vm_write_data(0);   //x=0
	//结束横坐标
	 st7789vm_write_data(LCD_W - 1);  //x=240  0-239
	
	//确定Y方向
	st7789vm_write_command(0x2B);     //纵坐标命令
	//起始纵坐标
	st7789vm_write_data(0);   //y=0
	//结束纵坐标
	st7789vm_write_data(LCD_H - 1);  //y=240
	
	
	/*确定颜色*/
	st7789vm_write_command(0x2C);     //颜色命令    RGB二进制位数寄存器
	for(u32 i = 0; i < LCD_W * LCD_H; i++)
	{
		st7789vm_write_data(color);
	}
}

/*
****************************************************************************************
* 函数名: st7789vm_init
* 函数作用: ST7789VM 初始化
* 参数: 无
* 返回值: 无
****************************************************************************************
*/
void st7789vm_init(void)
{
	LCD_IO_init();
	delay_ms(100);
	
	
	
	
	/* start initial sequence */ 
	st7789vm_write_command(0x36);
	st7789vm_write_command_parameter(0x00);

	st7789vm_write_command(0x3A); 
	st7789vm_write_command_parameter(0x05);

	st7789vm_write_command(0xB2);
	st7789vm_write_command_parameter(0x0C);
	st7789vm_write_command_parameter(0x0C);
	st7789vm_write_command_parameter(0x00);
	st7789vm_write_command_parameter(0x33);
	st7789vm_write_command_parameter(0x33); 

	st7789vm_write_command(0xB7); 
	st7789vm_write_command_parameter(0x35);  

	st7789vm_write_command(0xBB);
	st7789vm_write_command_parameter(0x19);

	st7789vm_write_command(0xC0);
	st7789vm_write_command_parameter(0x2C);

	st7789vm_write_command(0xC2);
	st7789vm_write_command_parameter(0x01);

	st7789vm_write_command(0xC3);
	st7789vm_write_command_parameter(0x12);   

	st7789vm_write_command(0xC4);
	st7789vm_write_command_parameter(0x20);  

	st7789vm_write_command(0xC6); 
	st7789vm_write_command_parameter(0x0F);    

	st7789vm_write_command(0xD0); 
	st7789vm_write_command_parameter(0xA4);
	st7789vm_write_command_parameter(0xA1);

	st7789vm_write_command(0xE0);
	st7789vm_write_command_parameter(0xD0);
	st7789vm_write_command_parameter(0x04);
	st7789vm_write_command_parameter(0x0D);
	st7789vm_write_command_parameter(0x11);
	st7789vm_write_command_parameter(0x13);
	st7789vm_write_command_parameter(0x2B);
	st7789vm_write_command_parameter(0x3F);
	st7789vm_write_command_parameter(0x54);
	st7789vm_write_command_parameter(0x4C);
	st7789vm_write_command_parameter(0x18);
	st7789vm_write_command_parameter(0x0D);
	st7789vm_write_command_parameter(0x0B);
	st7789vm_write_command_parameter(0x1F);
	st7789vm_write_command_parameter(0x23);

	st7789vm_write_command(0xE1);
	st7789vm_write_command_parameter(0xD0);
	st7789vm_write_command_parameter(0x04);
	st7789vm_write_command_parameter(0x0C);
	st7789vm_write_command_parameter(0x11);
	st7789vm_write_command_parameter(0x13);
	st7789vm_write_command_parameter(0x2C);
	st7789vm_write_command_parameter(0x3F);
	st7789vm_write_command_parameter(0x44);
	st7789vm_write_command_parameter(0x51);
	st7789vm_write_command_parameter(0x2F);
	st7789vm_write_command_parameter(0x1F);
	st7789vm_write_command_parameter(0x1F);
	st7789vm_write_command_parameter(0x20);
	st7789vm_write_command_parameter(0x23);

	st7789vm_write_command(0x21); 
	st7789vm_write_command(0x11); 
	st7789vm_write_command(0x29); 
	
	/* 清空屏幕显示 */
	LCD_clear(WHITE);

	/* 开启背光 */
	LCD_LED_H;
}


/*
   清除特定区域为某种颜色
1、先确定坐标点
2、最终坐标点确定
3、在确定的区域写入颜色
*/
void LCD_xy_clear(u16 x, u16 y, u16 w,u16 h, u16 color)
{
	/*确定区域*/
	//确定x方向
	st7789vm_write_command(0x2A);     //横坐标命令
	//起始横坐标
	 st7789vm_write_data(x);   //x=0
	//结束横坐标
	 st7789vm_write_data(w);  //x=240  0-239
	
	//确定Y方向
	st7789vm_write_command(0x2B);     //纵坐标命令
	//起始纵坐标
	st7789vm_write_data(y);   //y=0
	//结束纵坐标
	st7789vm_write_data(h);  //y=240
	
	
	/*确定颜色*/
	st7789vm_write_command(0x2C);     //颜色命令    RGB二进制位数寄存器
	for(u32 i = 0; i < w*h; i++)
	{
		st7789vm_write_data(color);
	}
}


/*
打一个打点函数
*/
void LCD_Point(u16 x, u16 y, u16 color)
{
	/*确定区域*/
	//确定x方向
	st7789vm_write_command(0x2A);     //横坐标命令
	//起始横坐标
	 st7789vm_write_data(x);   //x=0
	//结束横坐标
	 st7789vm_write_data(x);  //x=240  0-239
	
	//确定Y方向
	st7789vm_write_command(0x2B);     //纵坐标命令
	//起始纵坐标
	st7789vm_write_data(y);   //y=0
	//结束纵坐标
	st7789vm_write_data(y);  //y=240
	
	
	/*确定颜色*/
	st7789vm_write_command(0x2C);     //颜色命令    RGB二进制位数寄存器
	st7789vm_write_data(color);
	
}

/*
显示16大小字符
根据取模实例，按照行数和列数进行循环读取，先确定整体区域，再往区域写入数据
*/
void LCD_dis_ch16(u16 x, u16 y, u16 color, u8 ch)
{
	u8 n;
	u16 temp;
	n = ch - ' '; //获取偏移值，用于遍历查找数组结构
	for(u8 i = 0; i < 16; i++)
	{
		//先将遍历得到的数据结构存储
		temp = ASC16[n * 16 + i];
		//将存储的数据显示在待定的区域
		for(u8 j = 0; j<8; j++)
		{
			//数据高位在前
			if(temp & (0x80 >> j))
			{
				//使用打点函数打满整个区域
				LCD_Point( x+j, y+i, color);
			}
		}
	}
}

/******************************************************************************
*函数名    ：LCD_dis_ch32
*函数功能  ：LCD屏幕显示32*32的字符
*函数参数  ：u16 x,u16 y,u16 color,u8 ch
*函数返回值：无
*函数描述  ：x:起始横坐标 y：起始纵坐标
********************************************************************************/
void LCD_dis_ch32(u16 x, u16 y, u16 color, u8 ch)
{
	u8 n;
	u8 i, j;
	u16 temp;
	
	/*计算要显示的字符与空格字符的偏移量*/
	n = ch - ' ';
	
	/*显示*/
	for(i = 0; i < 32; i++)   //遍历所占用的行数   代表的是y方向坐标
	{
		temp = ASC32[n*64 + 2 * i] << 8 | ASC32[n*64 + 2*i + 1];
		for(j = 0; j < 16; j++)  //遍历每行的像素点个数  代表的是x方向坐标
		{
			//判断对应像素点位是否是要显示的字符的轮廓点
			if(temp & (1 << (15-j)))               
			{                                    
				//要将字符的轮廓点打点
				LCD_Point(x+j, y+i, color);
			}
		}
	}
}


/******************************************************************************
*函数名    ：LCD_dis_ch
*函数功能  ：LCD屏幕显示可设定大小的字符
*函数参数  ：u16 x,u16 y,u16 color,u8 ch,u8 size ,u8 mode,u16 b_color 
*函数返回值：无
*函数描述  ：
						size 字号大小   16  32
						mode 传入1  就带背景颜色
						mode 传入0  就不带背景颜色
********************************************************************************/
void LCD_dis_ch(u16 x, u16 y, u16 color, u8 ch, u8 size, u8 mode, u16 b_color)
{
	u8 n;
	u8 i,j;
	u16 temp;
	
	/*计算要显示的字符与空格字符的偏移量*/
	n = ch - ' ';
	
	//显示
	/*显示*/
	for(i=0; i<size; i++)   //遍历所占用的行数
	{ 
		//拿到每一行像素点的数据（一行就一个字节数据）
		if(size == 16)
		{
			temp = ASC16[n*16 + i];
		}			
		else if(size == 32)
		{
			temp = ASC32[n*64 + 2*i] <<8 |  ASC32[n*64 + 2*i+1];
		}			
		
		for(j = 0; j < size / 2; j++)  //遍历每行的像素点个数
		{
			//判断对应像素点是否位要显示的字符的轮廓点
			if(temp & (1 << (size / 2 - 1 - j)))
			{
				//要将字符的轮廓点打点
				LCD_Point(x+j, y+i, color);
			}
			//字的背景色
			else
			{
				if(mode == 1)
				{
					LCD_Point(x+j, y+i, b_color);
				}
			}
			
		}
	}		
}

/******************************************************************************
*函数名    ：LCD_dis_hz
*函数功能  ：LCD屏幕显示可选大小的汉字
*函数参数  ：u16 x,u16 y,u16 color，u8 *hz，u8 size ,u8 mode,u16 b_color 
*函数返回值：无
*函数描述  ：
						size 字号大小   16  32
						mode 传入1  就带背景颜色
						mode 传入0  就不带背景颜色
********************************************************************************/
void LCD_dis_hz(u16 x, u16 y, u16 color, u8 *hz, u8 size, u8 mode, u16 b_color)
{
	u8 i, j;
	u8 n = 0;
	u32 temp;
	
	
	/*计算要显示的汉字与字库数组中的汉字的偏移*/
	while(table[2*n] != '\0')                          
	{
		if(*hz == table[2*n]  &&  *(hz+1) == table[2*n+1])
		{
			break;
		}
		n++;    //下一个汉字
	}
	//如果没找到汉字就跳过显示
	if(table[2*n] == '\0')
	{
		return ;
	}
	
	//n值就是要显示的汉字与第一个汉字的偏移量
	
	/*显示*/
	for(i = 0; i < size; i++)    //遍历汉字所占的行数
	{
		//取出每行的字模数据
		if(size == 16)   //16, 32
		{
			temp = hz16[n*32 + 2 * i] << 8 | hz16[n*32 + 2 * i + 1];
		}			
		else if(size == 32)  
		{
			temp = hz32[n*128 + 4*i] << 24 | hz32[n * 128 + 4 * i + 1] << 16 | hz32[n*128 + 4 * i + 2] << 8  | hz32[n*128 + 4 * i +3 ];
		}
		
		for(j = 0; j < size; j++)  //遍历每行所占的像素点数
		{
			//判断对应像素点是否位要显示的字符的轮廓点
			if(temp & (1 << (size - 1 - j)))
			{
				LCD_Point(x + j, y + i, color);
			}
			//背景色
			else
			{
				if(mode == 1)
				{
					LCD_Point(x + j, y + i, b_color);
				}
			}
		}
	}
}

/******************************************************************************
*函数名    ：LCD_dis
*函数功能  ：LCD屏幕显示可选大小的汉字和字符混合
*函数参数  ：u16 x,u16 y,u16 color，u8 *str，u8 size ,u8 mode,u16 b_color 
*函数返回值：无
*函数描述  ：
						size 字号大小   16  32
						mode 传入1  就带背景颜色
						mode 传入0  就不带背景颜色
********************************************************************************/
void LCD_dis(u16 x, u16 y, u16 color, u8 *str, u8 size, u8 mode, u16 b_color)  
{
	
	while(*str != '\0')  //"asdf\0"
	{
		/*判断是字符*/
		if(*str >= 32 && *str <= 127)  //只要在ASCLL值范围的都是字符，否则为汉字
		{
			LCD_dis_ch(x, y, color, *str, size, mode, b_color);
			//数组中
			str++;  
			//屏幕
			x += size / 2;  
			if(x >= LCD_W - 1 - size)
			{
				y += size;
				x = 0;
			}		
		}
		
		/*判断是汉字*/
		else
		{
			LCD_dis_hz(x, y, color, str, size, mode, b_color);
			//数组中
			str += 2;
			//屏幕
			x += size;
			if(x >= LCD_W - 1 - size)
			{
				y += size;
				x = 0;
			}			
		}	
	}
}



/*
  图片显示函数
  结构体存储图像数据
*/
void LCD_dis_pic(u16 x, u16 y, const u8 *pic)
{
	//指针指向结构体获取数据
	//声明一个指针
	//创建结构体
	HEADCOLOR *head;  //创建结构体指针
	u16 *p;                 //创建指向颜色的指针   
	head = (HEADCOLOR *)pic;  //通过结构体获取图像的所有信息
	p = (u16 *)(pic + sizeof(HEADCOLOR)); //得到图像所有的像素点
	
	//现在已经有了要写入的数据，只需要确定写入的位置
	//设置3个地址
	//1.2A-列地址
	st7789vm_write_command(0x2A);
	st7789vm_write_data(x);             
	st7789vm_write_data(x + head->w - 1);   //图像或者字符信息，坐标是从0开始
	//2.2B-行地址
	st7789vm_write_command(0x2B);
	st7789vm_write_data(y);             
	st7789vm_write_data(y + head->h - 1);
	//3.2C-写入数据
	st7789vm_write_command(0x2C);
	for(u32 i = 0; i < head->w * head ->h; i++)
	{
		st7789vm_write_data(*p);
		p++;
	}
}






