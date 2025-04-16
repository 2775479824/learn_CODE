#define _CRT_SECURE_NO_WARNINGS 1
#include"Contact.h"
#include"SeqList.h"


//通讯录的初始化和销毁
void ContactInit(Contact* pcon)
{
	SLInit(pcon);
}
void ContactDestroy(Contact* pcon)
{
	SLDestroy(pcon);
}

//增加、删除、修改、查找、查看通讯录
void ContactAdd(Contact* pcon) {
	Info info;

	//获取终端输入数据
	printf("请输入联系人姓名：\n");
	scanf("%s", info.name);
	printf("请输入联系人年龄：\n");
	scanf("%d", &info.age);
	printf("请输入联系人性别：\n");
	scanf("%s", info.gender);
	printf("请输入联系人电话：\n");
	scanf("%s", info.tel);
	printf("请输入联系人住址：\n");
	scanf("%s", info.addr);
	

	//保持数据到通讯录
	SLPushBack(pcon, info);
	
}

int FindByName(Contact* pcon, char name[])
{
	for (int i = 0;i < pcon->size;i++)
	{
		if (strcmp(pcon->arr[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;
}

void ContactDel(Contact* pcon) {
	//删除之前查找
	//找到了，删
	//找不到，不删
	printf("请输入要删除的联系人姓名：\n");
	char name[NAME_MAX];
	scanf("%s", name);
	int findIndex = FindByName(pcon, name);
	if (findIndex < 0) {
		printf("该联系人不存在!\n");
		return;
	}
	//执行删除操作
	SLErase(pcon, findIndex);
	printf("删除成功!\n");

}
void ContactModify(Contact* pcon) {
	//找到了就修改
	//找不到不改
	char name[NAME_MAX];
	printf("请输入要修改的联系人姓名：>");
	scanf("%s", name);
	int findIndex = FindByName(pcon, name);
	if (findIndex < 0)
	{
		printf("该联系人不存在!\n");
		return;
	}
	printf("请输入姓名：\n");
	scanf("%s", pcon->arr[findIndex].name);
	printf("请输入年龄：\n");
	scanf("%d", &pcon->arr[findIndex].age);
	printf("请输入性别：\n");
	scanf("%s", pcon->arr[findIndex].gender);
	printf("请输入电话：\n");
	scanf("%s", pcon->arr[findIndex].tel);
	printf("请输入住址：\n");
	scanf("%s", pcon->arr[findIndex].addr);

	printf("联系人修改成功!\n");
}
void ContactFind(Contact* pcon) {
	char name[NAME_MAX];
	printf("请输入要查找的联系人姓名：>");
	scanf("%s", name);
	int findIndex = FindByName(pcon, name);
	if (findIndex < 0) {
		printf("该联系人不存在!\n");
		return;
	}
	printf("%s %s %s %s %s\n", "姓名", "性别", "年龄", "电话", "住址");
	printf("%s %s %d %s %s\n", pcon->arr[findIndex].name, pcon->arr[findIndex].gender, pcon->arr[findIndex].age, pcon->arr[findIndex].tel, pcon->arr[findIndex].addr);
}
void ContactShow(Contact* pcon) {

	printf("%s %s %s %s %s\n", "姓名", "性别", "年龄", "电话", "住址");
	for (int i = 0;i < pcon->size;i++)
	{
		printf("%s %s %d %s %s\n", pcon->arr[i].name, pcon->arr[i].gender, pcon->arr[i].age, pcon->arr[i].tel, pcon->arr[i].addr);
	}
}