#include"SeqList.h"

//ͨѶ¼�˵�
void menu()
{
	printf("************** ͨѶ¼ ***************\n");
	printf("*********** 1.�����ϵ�� ************\n");
	printf("*********** 2.ɾ����ϵ�� ************\n");
	printf("*********** 3.������ϵ�� ************\n");
	printf("*********** 4.�޸���ϵ�� ************\n");
	printf("*********** 5.�鿴ͨѶ¼ ************\n");
	printf("*********** 0. ��  ��    ************\n");
	printf("*************************************\n");
}

int main()
{
	int op = -1;
	Contact con;
	ContactInit(&con);
	do {
		menu();
		printf("��ѡ����Ĳ�����\n");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			//�����ϵ��
			ContactAdd(&con);
			break;
		case 2:
			//ɾ����ϵ��
			ContactDel(&con);
			break;
		case 3:
			//������ϵ��
			ContactFind(&con);
			break;
		case 4:
			//�޸���ϵ��
			ContactModify(&con);
			break;
		case 5:
			//�鿴ͨѶ¼
			ContactShow(&con);
			break;
		case 0:
			//�˳�ͨѶ¼
			printf("ͨѶ¼�˳���...\n");
			break;
		default:
			printf("�����������������룡\n");
			break;
		}
	} while (op != 0);
	ContactDestroy(&con);
	return 0;
}