#include"snake.h"


//���Ժ���
void test() {
	int op = 0;
	do
	{
		//����̰����
		Snake snake = { 0 };
		GameStart(&snake);//��Ϸ��ʼǰ��׼��
		GameRun(&snake);//��Ϸ��ʼ
		GameEnd(&snake);//��Ϸ������
		SetPos(30, 15);
		printf("�Ƿ������Ϸ��(Y/N):");
		op = getchar();
		getchar();//����\n
	} while (op=='Y'||op=='y');
}


int main()
{
	//�޸����䱾�����Ļ���
	setlocale(LC_ALL, "");
	test();//���Ժ���
	return 0;
}