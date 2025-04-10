#pragma once

#include<locale.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>

#define WALL L'■'
#define BODY L'●'
#define FOOD L'★'

//蛇默认的起始坐标
#define POS_X 24
#define POS_Y 5

//按键检测
#define KEY_PRESS(VK) ((GetAsyncKeyState(VK) & 0x1) ? 1 : 0)

//用枚举类型维护游戏当前的状态
enum GAME_STATUS
{
	OK=1,//游戏正常运行
	ESC,//自行退出游戏
	KILL_BY_WALL,//撞墙结束游戏
	KILL_BY_SELF//咬到自己结束游戏
};

//蛇行走的方向
enum DIRECTION
{
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};


//蛇身的节点定义
typedef struct SnakeNode
{
	int x;
	int y;
	struct SnakeNode* next;
}SnakeNode, * pSnakeNode;
//相当于typedef struct SnakeNode* pSnakeNode;


//贪吃蛇
typedef struct Snake
{
	pSnakeNode pSnake;//维护整条蛇的指针
	pSnakeNode pFood;//指向食物的指针
	int score;//当前游戏得分
	int Foodweight;//一个食物的分数
	int SleepTime;//蛇休眠时间，休眠时间越短，蛇的速度越快，反之蛇的速度越慢
	enum GAME_STATUS status;//游戏当前状态
	enum DIRECTION dir;//蛇当前的移动方向
}Snake, * pSnake;


//——————————————————函数声明——————————————————————————//
//游戏开始前的准备
void GameStart(pSnake ps);
//设置坐标
void SetPos(int x, int y);
//欢迎界面
void WelcomeToGame();
//绘制地图
void DrawMap();
//初始化蛇身
void SnakeInit(pSnake ps);
//创建食物
void CreateFood(pSnake ps);

//游戏运行的整个逻辑
void GameRun(pSnake ps);

//打印帮助信息
void PrintHelpInfo();

//蛇的移动
void SnakeMove(pSnake ps);

//判断蛇头的下一步是否为食物
int NextIsFood(pSnake ps,pSnakeNode pNext);

//下一个节点是食物
void EatFood(pSnake ps, pSnakeNode pNext);

//下一个节点不是食物
void NotEatFood(pSnake ps, pSnakeNode pNext);

//检测是否撞墙
void KillByWall(pSnake ps);

//检测是否撞到自己
void KillBySelf(pSnake ps);


//游戏结束后的资源释放
void GameEnd(pSnake ps);