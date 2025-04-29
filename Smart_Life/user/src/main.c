#include "main.h"
#include "led.h"
#include "beep.h"
#include "relay.h"
#include "delay.h"
#include "key.h"
#include "usart1.h"
#include "rgb.h"
#include "lcd.h"
#include "font.h"
#include "11.h"
#include "iic.h"
#include "sht30.h"
#include "usart3.h"
#include "sg90.h"  // 添加舵机头文件
#include "adc.h"  // 添加ADC头文件
#include <stdio.h>

// 定义界面状态
#define PAGE_NONE 0
#define PAGE_WELCOME 1
#define PAGE_INFO 2
#define PAGE_RGB 3
#define PAGE_SENSOR 4

// 定义舵机角度状态
#define ANGLE_45 45
#define ANGLE_90 90
#define ANGLE_135 135

// 全局变量
u8 current_page = PAGE_NONE;
u8 servo_angle = ANGLE_45;
extern float te;  // 温度
extern float hu;  // 湿度
u32 light_value = 0;  // 光照值
u32 flame_value = 0;  // 火焰值

// 函数声明
void show_welcome_page(void);
void show_info_page(void);
void show_rgb_page(void);
void show_sensor_page(void);
void update_rgb_color(u8 angle);
void check_sensors(void);
u8 key_scan(void);  // 添加按键扫描函数声明

int main(void)
{
	u8 key;
	float data1[10];
	float data2[10];
	u8 data;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Led_Init();
	Key_Init();
	Beep_Init();
	BEEP_OFF;  // 初始化时关闭蜂鸣器
	Relay_Init();
	Usart1_Init();
	Rgb_Init();
	st7789vm_init();
	Sht30_Init();
	SysTick_Config(168000);
	Usart3_Init();
	SteeringPwm_Init(4000, 84);  // 初始化舵机PWM
	SetServoAngle(0);  // 初始化舵机角度为0度
	Adc_Init();  // 初始化ADC

	LCD_LED_H;  
	delay_ms(100); 

	LCD_clear(WHITE); 
	delay_ms(50); 

	while(1)
	{
		key = key_scan();
		
		// 按键1控制界面切换
		if(key == 1)
		{
			current_page++;
			if(current_page > PAGE_SENSOR)
				current_page = PAGE_WELCOME;
				
			LCD_clear(WHITE);
			delay_ms(50);
			
			switch(current_page)
			{
				case PAGE_WELCOME:
					show_welcome_page();
					break;
				case PAGE_INFO:
					show_info_page();
					break;
				case PAGE_RGB:
					show_rgb_page();
					break;
				case PAGE_SENSOR:
					show_sensor_page();
					break;
			}
		}
		
		// 按键2控制舵机角度
		if(key == 2 && current_page == PAGE_RGB)
		{
			servo_angle += 45;
			if(servo_angle > ANGLE_135)
				servo_angle = ANGLE_45;
				
			// 根据角度设置舵机位置
			switch(servo_angle)
			{
				case ANGLE_45:
					SetServoAngle(1);  // 45度
					break;
				case ANGLE_90:
					SetServoAngle(2);  // 90度
					break;
				case ANGLE_135:
					SetServoAngle(3);  // 135度
					break;
			}
			
			update_rgb_color(servo_angle);
			show_rgb_page();
		}
		
		// 在传感器页面检查传感器状态
		if(current_page == PAGE_SENSOR)
		{
			check_sensors();
		}
		
		delay_ms(100);
	}
}

// 显示欢迎页面
void show_welcome_page(void)
{
	LCD_clear(WHITE);  // 清屏
	LCD_dis_hz(20, 80, RED, (u8*)"欢", 16, 0, WHITE);
	LCD_dis_hz(40, 80, RED, (u8*)"迎", 16, 0, WHITE);
	LCD_dis_pic(120, 0, (u8*)gImage_vitality);
}

// 显示信息页面
void show_info_page(void)
{
	LCD_clear(WHITE);  // 清屏
	// 第一行：小组号
	LCD_dis_hz(10, 20, BLACK, (u8*)"小", 16, 0, WHITE);
	LCD_dis_hz(26, 20, BLACK, (u8*)"组", 16, 0, WHITE);
	LCD_dis_hz(42, 20, BLACK, (u8*)"号", 16, 0, WHITE);
	LCD_dis(58, 20, BLACK, (u8*)":", 16, 0, WHITE);
	LCD_dis(68, 20, BLACK, (u8*)"1", 16, 0, WHITE);
	LCD_dis(78, 20, BLACK, (u8*)"7", 16, 0, WHITE);
	
	// 第二行：班级
	LCD_dis_hz(10, 40, BLACK, (u8*)"班", 16, 0, WHITE);
	LCD_dis_hz(26, 40, BLACK, (u8*)"级", 16, 0, WHITE);
	LCD_dis(42, 40, BLACK, (u8*)":", 16, 0, WHITE);
	LCD_dis(58, 40, BLACK, (u8*)"2", 16, 0, WHITE);
	LCD_dis(68, 40, BLACK, (u8*)"2", 16, 0, WHITE);
	LCD_dis(78, 40, BLACK, (u8*)"-", 16, 0, WHITE);
	LCD_dis(88, 40, BLACK, (u8*)"2", 16, 0, WHITE);
	
	// 第三行：专业
	LCD_dis_hz(10, 60, BLACK, (u8*)"专", 16, 0, WHITE);
	LCD_dis_hz(26, 60, BLACK, (u8*)"业", 16, 0, WHITE);
	LCD_dis(42, 60, BLACK, (u8*)":", 16, 0, WHITE);
	
	// 第四行：专业名称
	LCD_dis_hz(10, 80, BLACK, (u8*)"智", 16, 0, WHITE);
	LCD_dis_hz(26, 80, BLACK, (u8*)"能", 16, 0, WHITE);
	LCD_dis_hz(42, 80, BLACK, (u8*)"科", 16, 0, WHITE);
	LCD_dis_hz(58, 80, BLACK, (u8*)"学", 16, 0, WHITE);
	LCD_dis_hz(74, 80, BLACK, (u8*)"与", 16, 0, WHITE);
	LCD_dis_hz(90, 80, BLACK, (u8*)"技", 16, 0, WHITE);
	LCD_dis_hz(106, 80, BLACK, (u8*)"术", 16, 0, WHITE);
	
	LCD_dis_pic(120, 0, (u8*)gImage_vitality);
}

// 显示RGB页面
void show_rgb_page(void)
{
	LCD_clear(WHITE);  // 清屏
	LCD_dis(20, 20, BLACK, (u8*)"R", 16, 0, WHITE);
	LCD_dis(36, 20, BLACK, (u8*)"G", 16, 0, WHITE);
	LCD_dis(52, 20, BLACK, (u8*)"B", 16, 0, WHITE);
	LCD_dis(68, 20, BLACK, (u8*)":", 16, 0, WHITE);
	
	switch(servo_angle)
	{
		case ANGLE_45:
			LCD_dis_hz(84, 20, RED, (u8*)"红", 16, 0, WHITE);
			break;
		case ANGLE_90:
			LCD_dis_hz(84, 20, GREEN, (u8*)"绿", 16, 0, WHITE);
			break;
		case ANGLE_135:
			LCD_dis_hz(84, 20, BLUE, (u8*)"蓝", 16, 0, WHITE);
			break;
	}
	
	LCD_dis_hz(20, 40, BLACK, (u8*)"舵", 16, 0, WHITE);
	LCD_dis_hz(36, 40, BLACK, (u8*)"机", 16, 0, WHITE);
	LCD_dis_hz(52, 40, BLACK, (u8*)"角", 16, 0, WHITE);
	LCD_dis_hz(68, 40, BLACK, (u8*)"度", 16, 0, WHITE);
	LCD_dis(84, 40, BLACK, (u8*)":", 16, 0, WHITE);
	
	char angle_str[4];
	sprintf(angle_str, "%d", servo_angle);
	LCD_dis(100, 40, BLACK, (u8*)angle_str, 16, 0, WHITE);
}

// 显示传感器页面
void show_sensor_page(void)
{
	LCD_clear(WHITE);  // 清屏
	LCD_dis_hz(20, 20, BLACK, (u8*)"光", 16, 0, WHITE);
	LCD_dis_hz(36, 20, BLACK, (u8*)"照", 16, 0, WHITE);
	LCD_dis(52, 20, BLACK, (u8*)":", 16, 0, WHITE);
	
	LCD_dis_hz(20, 40, BLACK, (u8*)"火", 16, 0, WHITE);
	LCD_dis_hz(36, 40, BLACK, (u8*)"焰", 16, 0, WHITE);
	LCD_dis(52, 40, BLACK, (u8*)":", 16, 0, WHITE);
}

// 更新RGB颜色
void update_rgb_color(u8 angle)
{
	switch(angle)
	{
		case ANGLE_45:
			W2812_WriteColorData(RGB_RED);
			break;
		case ANGLE_90:
			W2812_WriteColorData(RGB_GREEN);
			break;
		case ANGLE_135:
			W2812_WriteColorData(RGB_BLUE);
			break;
	}
}

// 检查传感器状态
void check_sensors(void)
{

	
	// 显示光照状态
	if(light_value < 20)  // 光照较弱
	{
		LCD_dis_hz(68, 20, BLACK, (u8*)"暗", 16, 1, WHITE);
		W2812_WriteColorData(RGB_WHITE);  // 打开白光

	}
	else
	{
		LCD_dis_hz(68, 20, BLACK, (u8*)"亮", 16, 1, WHITE);
		W2812_WriteColorData(RGB_BLACK);  // 关闭灯光

	}
	
	// 显示火焰状态
	if(flame_value > 70)  // 火焰强度超过70%
	{
		LCD_dis_hz(68, 40, RED, (u8*)"警", 16, 0, WHITE);
		LCD_dis_hz(84, 40, RED, (u8*)"告", 16, 0, WHITE);
		BEEP_ON;  // 打开蜂鸣器
		W2812_WriteColorData(RGB_RED);  // RGB显示红色
	}
	else
	{
		LCD_dis_hz(68, 40, BLACK, (u8*)"正", 16, 0, WHITE);
		LCD_dis_hz(84, 40, BLACK, (u8*)"常", 16, 0, WHITE);
		BEEP_OFF;  // 关闭蜂鸣器
	}
}

u16 time_cnt[5] = {0};
void SysTick_Handler(void)
{
	if(SysTick ->CTRL & (1 << 16))
	{
		time_cnt[0]++;
		
		if(time_cnt[0] == 1000)   //1s
		{
			time_cnt[0] = 0;
			
			u8 data1[20] = {0};
			u8 data2[20] = {0};
			// 读取光照传感器数据
			light_value = Get_AverageValue(NTC_CH);
			light_value = 100 - (light_value * 100) / 4096;  // 计算光照强度百分比
			
			// 读取火焰传感器数据
			flame_value = Get_AverageValue(IR_CH);
			flame_value = 100 - (flame_value * 100) / 4096;  // 计算火焰强度百分比
			
			if(current_page == PAGE_SENSOR){
						// 显示光照和火焰值
			sprintf((char *)data1,"light:%d%%",light_value);
			sprintf((char *)data2,"flame:%d%%",flame_value);
			LCD_dis(0,160,RED,(u8*)data1,32,1,YELLOW);
			LCD_dis(0,200,RED,(u8*)data2,32,1,YELLOW);
			}

		}
	}
}