#include"snake.h"

//��������
void SetPos(int x, int y) {
	//����豸���
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//���ݾ�����ù���λ��
	COORD pos = { x,y };
	SetConsoleCursorPosition(handle, pos);
}


//��ӭ����
void WelcomeToGame() {
	//��ӭ��Ϣ
	SetPos(35, 10);
	printf("��ӭ����̰����С��Ϸ\n");
	SetPos(36, 20);
	system("pause");
	system("cls");
	
	//����˵��
	SetPos(28, 10);
	printf("�á������������������ߵ��ƶ���F3Ϊ���٣�F4Ϊ����\n");
	SetPos(28, 15);
	printf("ע���ٶ�Խ�쵥��ʳ��÷�Խ��\n");
	SetPos(36, 20);
	system("pause");
	system("cls");
}

//���Ƶ�ͼ
void DrawMap()
{
	//��
	SetPos(0, 0);
	for (int i = 0; i <= 56; i += 2)
	{
		wprintf(L"%lc", WALL);
	}
	//��
	SetPos(0, 26);
	for (int i = 0; i <= 56; i += 2)
	{
		wprintf(L"%lc", WALL);
	}
	//��
	for (int i = 1; i <= 25; i++)
	{
		SetPos(0, i);
		wprintf(L"%lc", WALL);
	}
	//��
	for (int i = 1; i <= 25; i++)
	{
		SetPos(56, i);
		wprintf(L"%lc", WALL);
	}
}

void SnakeInit(pSnake ps) {
	//�����������ڵ�
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
		//ͷ�巨
		if (ps->pSnake == NULL)
		{
			ps->pSnake = cur;
		}
		else {
			cur->next = ps->pSnake;
			ps->pSnake = cur;
		}
	}
	//��ӡ����
	cur = ps->pSnake;
	while (cur)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}
	//̰���ߵ�������Ϣ��ʼ��
	ps->dir = RIGHT;
	ps->Foodweight = 10;
	ps->pFood = NULL;
	ps->score = 0;
	ps->SleepTime = 200;//200����
	ps->status = OK;
	
}


void CreateFood(pSnake ps) {
	//ʳ����������ֵģ�����������ģ������������ǽ�ڣ����겻����������
	//x:2~54 -> 0~52+2 -> rand()%53   y:1~25 -> 0~24+1 -> rand()%25
	int x = 0, y = 0;
again:
	do
	{
		x = rand() % 53 + 2;
		y = rand() % 25 + 1;
	} while (x % 2 != 0);

	//����������ÿ���ڵ��������бȽ�
	pSnakeNode cur = ps->pSnake;
	while (cur)
	{
		if (x == cur->x && y == cur->y)
		{
			goto again;
		}
		cur = cur->next;
	}
	//����ʳ��
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
	//���ÿ���̨��Ϣ���������ڴ�С�Լ����ڵı���
	system("mode con cols=100 lines=30");
	system("title ̰����");
	
	//���ع��
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);//�����޸ĺ�Ĺ����Ϣ

	//��ӡ��ӭ��Ϣ
	WelcomeToGame();

	//���Ƶ�ͼ
	DrawMap();
	//��ʼ������
	SnakeInit(ps);
	//����ʳ��
	CreateFood(ps);
}

void PrintHelpInfo()
{
	SetPos(62, 15);
	printf("1.���ܴ�ǽ������ҧ���Լ�");
	SetPos(62, 16);
	printf("2.�á������������������ߵ��ƶ�");
	SetPos(62, 17);
	printf("3.F3Ϊ���٣�F4Ϊ����");
	SetPos(62, 19);
	printf("��Ȩ@bit109");
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
	//��ӡ����
	pSnakeNode cur = ps->pSnake;
	while (cur)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}
	ps->score += ps->Foodweight;
	//�ͷžɵ�ʳ��
	free(ps->pFood);
	//�½��µ�ʳ��
	CreateFood(ps);
}

void NotEatFood(pSnake ps, pSnakeNode pNext) {
	//�µĽڵ�ָ��ͷ
	pNext->next = ps->pSnake;
	ps->pSnake = pNext;//����ͷ�ڵ�
	
	//Ѱ��β�ڵ㲢���´�ӡ����
	pSnakeNode cur = ps->pSnake;
	while (cur->next->next != NULL)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}
	//��β�ڵ�����λ�ô�ӡΪ�հ�
	SetPos(cur->next->x, cur->next->y);
	printf("  ");
	
	//�ͷ�β�ڵ�
	free(cur->next);
	cur->next = NULL;

}

//����Ƿ�ײǽ
void KillByWall(pSnake ps) {
	if (ps->pSnake->x == 0 || ps->pSnake->x == 56 || ps->pSnake->y == 0 || ps->pSnake->y == 26)
	{
		ps->status = KILL_BY_WALL;
	}
}

//����Ƿ�ײ���Լ�
void KillBySelf(pSnake ps)
{
	//�ӵڶ����ڵ㿪ʼ
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
	//��һ�������Ƿ���ʳ��
	if (NextIsFood(ps, pNext)) {
		//��ʳ��ͳԵ�
		EatFood(ps,pNext);
	}
	else{
		//����ʳ�������
		NotEatFood(ps,pNext);
	}
	//���ײǽ
	KillByWall(ps);
	//���ײ���Լ�
	KillBySelf(ps);
}

void GameRun(pSnake ps)
{
	//��ӡ������Ϣ
	PrintHelpInfo();

	do
	{
		//��ǰ�÷����
		SetPos(62, 10);
		printf("�ܷ�:%5d\n", ps->score);
		SetPos(62, 11);
		printf("��ǰʳ���ֵ:%02d\n", ps->Foodweight);
		
		//��ⰴ��   �ϣ��£����ң�esc���ո�F3��F4
		//�����ֵ
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
			//��Ϸ��ͣ
			pause();//��ͣ��ֹͣ��ͣ
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
	
		//˯��һ��
		Sleep(ps->SleepTime);

		//��һ��
		SnakeMove(ps);
	} while (ps->status == OK);
}

//��Ϸ���������Դ�ͷ�
void GameEnd(pSnake ps)
{
	switch (ps->status)
	{
	case ESC:
		system("cls");
		SetPos(30, 12);
		printf("����˳���Ϸ\n");
		break;
	case KILL_BY_WALL:
		system("cls");
		SetPos(30, 12);
		printf("���ź���ײǽ�ˣ���Ϸ����\n");
		break;
	case KILL_BY_SELF:
		system("cls");
		SetPos(30, 12);
		printf("���ź���ҧ���Լ��ˣ���Ϸ����\n");
		break;
	}

	//�ͷ�̰���ߵ���Դ
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