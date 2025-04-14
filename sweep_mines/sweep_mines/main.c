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
	char mine[ROWS][COLS];//��Ų��úõ���
	char show[ROWS][COLS];//����Ų�����׵���Ϣ
	//��ʼ������  mine����ȫ��0��show����ȫ��*
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');

	//��ӡ����
	DisplayBoard(show, ROW, COL);
	//������
	SetMines(mine, ROW, COL);

	//�Ų���
	FindMines(mine, show, ROW, COL);

}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));

	do
	{
		menu();
		printf("��ѡ��:>");
		scanf_s("%d",&input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("ѡ�����������ѡ��!\n");
			break;
		}
	} while (input);


	return 0;
}