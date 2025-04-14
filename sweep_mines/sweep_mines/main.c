#include"game.h"

void menu()
{
	printf("*************************\n");
	printf("******  1. play   *******\n");
	printf("******  0. exit   *******\n");
	printf("*************************\n");
}

void game()
{
	char mine[ROWS][COLS];//存放布置好的雷
	char show[ROWS][COLS];//存放排查出的雷的信息
	//初始化棋盘  mine数组全是0，show数组全是*
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');

	//打印棋盘
	DisplayBoard(show, ROW, COL);
	//布置雷
	SetMines(mine, ROW, COL);

	//排查雷
	FindMines(mine, show, ROW, COL);

}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));

	do
	{
		menu();
		printf("请选择:>");
		scanf_s("%d",&input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误，请重新选择!\n");
			break;
		}
	} while (input);


	return 0;
}