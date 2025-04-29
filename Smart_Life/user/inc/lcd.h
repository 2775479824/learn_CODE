#ifndef __LCD_H_
#define __LCD_H_

#include "stm32f4xx.h"
#include "delay.h"


//设置结构体存储图像数据
typedef struct _HEADCOLOR
{
	unsigned char scan;           //扫描方式
	unsigned char gray;           //灰度
	unsigned short w;              //宽
	unsigned short h;              //高
	unsigned char is565;          //rgb位数
	unsigned char rgb;            //颜色顺序
}HEADCOLOR;


#define SPI2_SCL_H 	(GPIO_SetBits(GPIOB, GPIO_Pin_3))
#define SPI2_SCL_L 	(GPIO_ResetBits(GPIOB, GPIO_Pin_3))
#define LCD_MOSI_H 	(GPIO_SetBits(GPIOB, GPIO_Pin_5))
#define LCD_MOSI_L 	(GPIO_ResetBits(GPIOB, GPIO_Pin_5))
#define LCD_CS_H		(GPIO_SetBits(GPIOB,GPIO_Pin_4))
#define LCD_CS_L		(GPIO_ResetBits(GPIOB,GPIO_Pin_4))
#define LCD_DATA		(GPIO_SetBits(GPIOD,GPIO_Pin_2))
#define LCD_COMMAND	(GPIO_ResetBits(GPIOD,GPIO_Pin_2))
#define LCD_LED_H	  (GPIO_SetBits(GPIOA,GPIO_Pin_15))
#define LCD_LED_L	  (GPIO_ResetBits(GPIOA,GPIO_Pin_15))


#define LCD_W  240
#define LCD_H  240


/* 颜色定义开始 */
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			 			 0XFFE0
#define GBLUE			 			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 		 0XBC40 //棕色
#define BRRED 			 		 0XFC07 //棕红色
#define GRAY  			 		 0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)
/* 颜色定义结束 */

void st7789vm_init(void);//初始化
void LCD_xy_clear(u16 x, u16 y, u16 w,u16 h, u16 color);//确定某个区域为某种颜色
void LCD_clear(uint16_t color);
void LCD_Point(u16 x, u16 y, u16 color);   //打点函数
void LCD_dis_ch16(u16 x, u16 y, u16 color, u8 ch);   //
void LCD_dis_ch16(u16 x, u16 y, u16 color, u8 ch);
void LCD_dis_ch32(u16 x, u16 y, u16 color, u8 ch);
void LCD_dis_ch(u16 x, u16 y, u16 color, u8 ch, u8 size, u8 mode, u16 b_color);
void LCD_dis_hz(u16 x, u16 y, u16 color, u8 *hz, u8 size, u8 mode, u16 b_color);
void LCD_dis(u16 x, u16 y, u16 color, u8 *str, u8 size, u8 mode, u16 b_color);
void LCD_dis_pic(u16 x, u16 y, const u8 *pic);

#endif
