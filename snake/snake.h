#pragma once

#include<locale.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>

#define WALL L'��'
#define BODY L'��'
#define FOOD L'��'

//��Ĭ�ϵ���ʼ����
#define POS_X 24
#define POS_Y 5

//�������
#define KEY_PRESS(VK) ((GetAsyncKeyState(VK) & 0x1) ? 1 : 0)

//��ö������ά����Ϸ��ǰ��״̬
enum GAME_STATUS
{
	OK=1,//��Ϸ��������
	ESC,//�����˳���Ϸ
	KILL_BY_WALL,//ײǽ������Ϸ
	KILL_BY_SELF//ҧ���Լ�������Ϸ
};

//�����ߵķ���
enum DIRECTION
{
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};


//����Ľڵ㶨��
typedef struct SnakeNode
{
	int x;
	int y;
	struct SnakeNode* next;
}SnakeNode, * pSnakeNode;
//�൱��typedef struct SnakeNode* pSnakeNode;


//̰����
typedef struct Snake
{
	pSnakeNode pSnake;//ά�������ߵ�ָ��
	pSnakeNode pFood;//ָ��ʳ���ָ��
	int score;//��ǰ��Ϸ�÷�
	int Foodweight;//һ��ʳ��ķ���
	int SleepTime;//������ʱ�䣬����ʱ��Խ�̣��ߵ��ٶ�Խ�죬��֮�ߵ��ٶ�Խ��
	enum GAME_STATUS status;//��Ϸ��ǰ״̬
	enum DIRECTION dir;//�ߵ�ǰ���ƶ�����
}Snake, * pSnake;


//������������������������������������������������������������������������������������������������//
//��Ϸ��ʼǰ��׼��
void GameStart(pSnake ps);
//��������
void SetPos(int x, int y);
//��ӭ����
void WelcomeToGame();
//���Ƶ�ͼ
void DrawMap();
//��ʼ������
void SnakeInit(pSnake ps);
//����ʳ��
void CreateFood(pSnake ps);

//��Ϸ���е������߼�
void GameRun(pSnake ps);

//��ӡ������Ϣ
void PrintHelpInfo();

//�ߵ��ƶ�
void SnakeMove(pSnake ps);

//�ж���ͷ����һ���Ƿ�Ϊʳ��
int NextIsFood(pSnake ps,pSnakeNode pNext);

//��һ���ڵ���ʳ��
void EatFood(pSnake ps, pSnakeNode pNext);

//��һ���ڵ㲻��ʳ��
void NotEatFood(pSnake ps, pSnakeNode pNext);

//����Ƿ�ײǽ
void KillByWall(pSnake ps);

//����Ƿ�ײ���Լ�
void KillBySelf(pSnake ps);


//��Ϸ���������Դ�ͷ�
void GameEnd(pSnake ps);