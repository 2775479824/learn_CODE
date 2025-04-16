#define _CRT_SECURE_NO_WARNINGS 1

#include"SeqList.h"

void menu()
{
	printf("*******************ͨѶ¼*********************\n");
	printf("*********1.�����ϵ��   2.ɾ����ϵ��**********\n");
	printf("*********3.�޸���ϵ��   4.������ϵ��**********\n");
	printf("*********5.�鿴��ϵ��   0.  �˳�    **********\n");
}

int main()
{
	int op = -1;

	Contact con;
	ContactInit(&con);

	do {
		menu();
		printf("��ѡ����Ĳ���:>");
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
			//�޸���ϵ��
			ContactModify(&con);
			break;
		case 4:
			//������ϵ��
			ContactFind(&con);
			break;
		case 5:
			//�鿴��ϵ��
			ContactShow(&con);
			break;
		case 0:
			//�˳�ͨѶ¼
			printf("�˳�ͨѶ¼��...\n");
			break;
		default:
			break;
		}
	} while (op!=0);

	ContactDestroy(&con);
	return 0;
}

//int main()
//{
//	Contact con;
//	ContactInit(&con);
//
//	ContactAdd(&con);
//	ContactDestroy(&con);
//
//	return 0;
//}