#define _CRT_SECURE_NO_WARNINGS 1

#include"SeqList.h"

void menu()
{
	printf("*******************通讯录*********************\n");
	printf("*********1.添加联系人   2.删除联系人**********\n");
	printf("*********3.修改联系人   4.查找联系人**********\n");
	printf("*********5.查看联系人   0.  退出    **********\n");
}

int main()
{
	int op = -1;

	Contact con;
	ContactInit(&con);

	do {
		menu();
		printf("请选择你的操作:>");
		scanf("%d", &op);

		switch (op)
		{
		case 1:
			//添加联系人
			ContactAdd(&con);
			break;
		case 2:
			//删除联系人
			ContactDel(&con);
			break;
		case 3:
			//修改联系人
			ContactModify(&con);
			break;
		case 4:
			//查找联系人
			ContactFind(&con);
			break;
		case 5:
			//查看联系人
			ContactShow(&con);
			break;
		case 0:
			//退出通讯录
			printf("退出通讯录中...\n");
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