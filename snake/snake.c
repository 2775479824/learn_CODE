#include"snake.h"

//设置坐标
void SetPos(int x, int y) {
	//获得设备句柄
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//根据句柄设置光标的位置
	COORD pos = { x,y };
	SetConsoleCursorPosition(handle, pos);
}


//欢迎界面
void WelcomeToGame() {
	//欢迎信息
	SetPos(35, 10);
	printf("欢迎来到贪吃蛇小游戏\n");
	SetPos(36, 20);
	system("pause");
	system("cls");
	
	//操作说明
	SetPos(28, 10);
	printf("用↑、↓、←、→控制蛇的移动，F3为加速，F4为减速\n");
	SetPos(28, 15);
	printf("注：速度越快单个食物得分越高\n");
	SetPos(36, 20);
	system("pause");
	system("cls");
}

//绘制地图
void DrawMap()
{
	//上
	SetPos(0, 0);
	for (int i = 0; i <= 56; i += 2)
	{
		wprintf(L"%lc", WALL);
	}
	//下
	SetPos(0, 26);
	for (int i = 0; i <= 56; i += 2)
	{
		wprintf(L"%lc", WALL);
	}
	//左
	for (int i = 1; i <= 25; i++)
	{
		SetPos(0, i);
		wprintf(L"%lc", WALL);
	}
	//右
	for (int i = 1; i <= 25; i++)
	{
		SetPos(56, i);
		wprintf(L"%lc", WALL);
	}
}

void SnakeInit(pSnake ps) {
	//创建五个蛇身节点
	pSnakeNode cur = NULL;
	for (int i = 0; i < 5; i++)
	{
		cur = (pSnakeNode)malloc(sizeof(SnakeNode));
		if (cur == NULL)
		{
			perror("SnakeInit():malloc()");
			return;
		}
		cur->x = POS_X + 2 * i;
		cur->y = POS_Y;
		cur->next = NULL;
		//头插法
		if (ps->pSnake == NULL)
		{
			ps->pSnake = cur;
		}
		else {
			cur->next = ps->pSnake;
			ps->pSnake = cur;
		}
	}
	//打印蛇身
	cur = ps->pSnake;
	while (cur)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}
	//贪吃蛇的其他信息初始化
	ps->dir = RIGHT;
	ps->Foodweight = 10;
	ps->pFood = NULL;
	ps->score = 0;
	ps->SleepTime = 200;//200毫秒
	ps->status = OK;
	
}


void CreateFood(pSnake ps) {
	//食物是随机出现的，坐标是随机的，且坐标必须在墙内，坐标不能在蛇身上
	//x:2~54 -> 0~52+2 -> rand()%53   y:1~25 -> 0~24+1 -> rand()%25
	int x = 0, y = 0;
again:
	do
	{
		x = rand() % 53 + 2;
		y = rand() % 25 + 1;
	} while (x % 2 != 0);

	//坐标和蛇身的每个节点的坐标进行比较
	pSnakeNode cur = ps->pSnake;
	while (cur)
	{
		if (x == cur->x && y == cur->y)
		{
			goto again;
		}
		cur = cur->next;
	}
	//创建食物
	pSnakeNode pFood = (pSnakeNode)malloc(sizeof(SnakeNode));
	if (pFood == NULL)
	{
		perror("CreateFood()::malloc()");
		return;
	}
	pFood->x = x;
	pFood->y = y;

	ps->pFood = pFood;

	SetPos(x, y);
	wprintf(L"%lc", FOOD);
}

void GameStart(pSnake ps) {
	//设置控制台信息，包括窗口大小以及窗口的标题
	system("mode con cols=100 lines=30");
	system("title 贪吃蛇");
	
	//隐藏光标
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);//设置修改后的光标信息

	//打印欢迎信息
	WelcomeToGame();

	//绘制地图
	DrawMap();
	//初始化蛇身
	SnakeInit(ps);
	//创建食物
	CreateFood(ps);
}

void PrintHelpInfo()
{
	SetPos(62, 15);
	printf("1.不能穿墙，不能咬到自己");
	SetPos(62, 16);
	printf("2.用↑、↓、←、→控制蛇的移动");
	SetPos(62, 17);
	printf("3.F3为加速，F4为减速");
	SetPos(62, 19);
	printf("版权@bit109");
	SetPos(62, 21);
	printf("date:2023/1/17");
}


void pause()
{
	while (1)
	{
		Sleep(100);
		if (KEY_PRESS(VK_SPACE))
		{
			break;
		}
	}
}

int NextIsFood(pSnake ps, pSnakeNode pNext) {
	if (ps->pFood->x == pNext->x && ps->pFood->y == pNext->y)
		return 1;
	else
		return 0;
}

void EatFood(pSnake ps, pSnakeNode pNext) {
	pNext->next = ps->pSnake;
	ps->pSnake = pNext;
	//打印蛇身
	pSnakeNode cur = ps->pSnake;
	while (cur)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}
	ps->score += ps->Foodweight;
	//释放旧的食物
	free(ps->pFood);
	//新建新的食物
	CreateFood(ps);
}

void NotEatFood(pSnake ps, pSnakeNode pNext) {
	//新的节点指向头
	pNext->next = ps->pSnake;
	ps->pSnake = pNext;//更新头节点
	
	//寻找尾节点并重新打印蛇身
	pSnakeNode cur = ps->pSnake;
	while (cur->next->next != NULL)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}
	//将尾节点所在位置打印为空白
	SetPos(cur->next->x, cur->next->y);
	printf("  ");
	
	//释放尾节点
	free(cur->next);
	cur->next = NULL;

}

//检测是否撞墙
void KillByWall(pSnake ps) {
	if (ps->pSnake->x == 0 || ps->pSnake->x == 56 || ps->pSnake->y == 0 || ps->pSnake->y == 26)
	{
		ps->status = KILL_BY_WALL;
	}
}

//检测是否撞到自己
void KillBySelf(pSnake ps)
{
	//从第二个节点开始
	pSnakeNode cur = ps->pSnake->next;
	while (cur)
	{
		if (cur->x == ps->pSnake->x && cur->y == ps->pSnake->y)
		{
			ps->status = KILL_BY_SELF;
			return;
		}
		cur = cur->next;
	}
}

void SnakeMove(pSnake ps)
{
	pSnakeNode pNext = (pSnakeNode)malloc(sizeof(SnakeNode));
	if (pNext == NULL)
	{
		perror("SnakeMove()::malloc()");
		return;
	}
	pNext->next = NULL;

	switch (ps->dir)
	{
	case UP:
		pNext->x = ps->pSnake->x;
		pNext->y = ps->pSnake->y - 1;
		break;
	case DOWN:
		pNext->x = ps->pSnake->x;
		pNext->y = ps->pSnake->y + 1;
		break;
	case LEFT:
		pNext->x = ps->pSnake->x - 2;
		pNext->y = ps->pSnake->y;
		break;
	case RIGHT:
		pNext->x = ps->pSnake->x + 2;
		pNext->y = ps->pSnake->y;
		break;
	}
	//下一个坐标是否是食物
	if (NextIsFood(ps, pNext)) {
		//是食物就吃掉
		EatFood(ps,pNext);
	}
	else{
		//不是食物，正常走
		NotEatFood(ps,pNext);
	}
	//检测撞墙
	KillByWall(ps);
	//检测撞到自己
	KillBySelf(ps);
}

void GameRun(pSnake ps)
{
	//打印帮助信息
	PrintHelpInfo();

	do
	{
		//当前得分情况
		SetPos(62, 10);
		printf("总分:%5d\n", ps->score);
		SetPos(62, 11);
		printf("当前食物分值:%02d\n", ps->Foodweight);
		
		//检测按键   上，下，左，右，esc，空格，F3，F4
		//虚拟键值
		if (KEY_PRESS(VK_UP) && ps->dir != DOWN)
		{
			ps->dir = UP;
		}
		else if (KEY_PRESS(VK_DOWN) && ps->dir != UP)
		{
			ps->dir = DOWN;
		}		
		else if (KEY_PRESS(VK_LEFT) && ps->dir != RIGHT)
		{
			ps->dir = LEFT;
		}		
		else if (KEY_PRESS(VK_RIGHT) && ps->dir != LEFT)
		{
			ps->dir = RIGHT;
		}		
		else if (KEY_PRESS(VK_ESCAPE))
		{
			ps->status = ESC;
			break;
		}		
		else if (KEY_PRESS(VK_SPACE))
		{
			//游戏暂停
			pause();//暂停和停止暂停
		}
		else if (KEY_PRESS(VK_F3))
		{
			if (ps->SleepTime >= 80)
			{
				ps->SleepTime -= 30;
				ps->Foodweight += 2;
			}
		}
		else if (KEY_PRESS(VK_F4))
		{ 
			if (ps->Foodweight > 2)
			{
				ps->SleepTime += 30;
				ps->Foodweight -= 2;
			}
		}
	
		//睡眠一下
		Sleep(ps->SleepTime);

		//走一步
		SnakeMove(ps);
	} while (ps->status == OK);
}

//游戏结束后的资源释放
void GameEnd(pSnake ps)
{
	switch (ps->status)
	{
	case ESC:
		system("cls");
		SetPos(30, 12);
		printf("玩家退出游戏\n");
		break;
	case KILL_BY_WALL:
		system("cls");
		SetPos(30, 12);
		printf("很遗憾，撞墙了，游戏结束\n");
		break;
	case KILL_BY_SELF:
		system("cls");
		SetPos(30, 12);
		printf("很遗憾，咬到自己了，游戏结束\n");
		break;
	}

	//释放贪吃蛇的资源
	pSnakeNode cur = ps->pSnake;

	while (cur)
	{
		pSnakeNode del = cur;
		cur = cur->next;
		free(del);
	}
	ps->pSnake = NULL;
	free(ps->pFood);
	ps->pFood = NULL;
}