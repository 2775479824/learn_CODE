#include"SeqList.h"

//通讯录菜单
void menu()
{
	printf("************** 通讯录 ***************\n");
	printf("*********** 1.添加联系人 ************\n");
	printf("*********** 2.删除联系人 ************\n");
	printf("*********** 3.查找联系人 ************\n");
	printf("*********** 4.修改联系人 ************\n");
	printf("*********** 5.查看通讯录 ************\n");
	printf("*********** 0. 退  出    ************\n");
	printf("*************************************\n");
}

int main()
{
	int op = -1;
	Contact con;
	ContactInit(&con);
	do {
		menu();
		printf("请选择你的操作：\n");
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
			//查找联系人
			ContactFind(&con);
			break;
		case 4:
			//修改联系人
			ContactModify(&con);
			break;
		case 5:
			//查看通讯录
			ContactShow(&con);
			break;
		case 0:
			//退出通讯录
			printf("通讯录退出中...\n");
			break;
		default:
			printf("输入有误，请重新输入！\n");
			break;
		}
	} while (op != 0);
	ContactDestroy(&con);
	return 0;
}