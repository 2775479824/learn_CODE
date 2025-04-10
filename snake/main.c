#include"snake.h"


//测试函数
void test() {
	int op = 0;
	do
	{
		//创建贪吃蛇
		Snake snake = { 0 };
		GameStart(&snake);//游戏开始前的准备
		GameRun(&snake);//游戏开始
		GameEnd(&snake);//游戏结束后
		SetPos(30, 15);
		printf("是否继续游戏？(Y/N):");
		op = getchar();
		getchar();//清理\n
	} while (op=='Y'||op=='y');
}


int main()
{
	//修改适配本地中文环境
	setlocale(LC_ALL, "");
	test();//测试函数
	return 0;
}