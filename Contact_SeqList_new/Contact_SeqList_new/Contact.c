#define _CRT_SECURE_NO_WARNINGS 1
#include"Contact.h"
#include"SeqList.h"


//ͨѶ¼�ĳ�ʼ��������
void ContactInit(Contact* pcon)
{
	SLInit(pcon);
}
void ContactDestroy(Contact* pcon)
{
	SLDestroy(pcon);
}

//���ӡ�ɾ�����޸ġ����ҡ��鿴ͨѶ¼
void ContactAdd(Contact* pcon) {
	Info info;

	//��ȡ�ն���������
	printf("��������ϵ��������\n");
	scanf("%s", info.name);
	printf("��������ϵ�����䣺\n");
	scanf("%d", &info.age);
	printf("��������ϵ���Ա�\n");
	scanf("%s", info.gender);
	printf("��������ϵ�˵绰��\n");
	scanf("%s", info.tel);
	printf("��������ϵ��סַ��\n");
	scanf("%s", info.addr);
	

	//�������ݵ�ͨѶ¼
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
	//ɾ��֮ǰ����
	//�ҵ��ˣ�ɾ
	//�Ҳ�������ɾ
	printf("������Ҫɾ������ϵ��������\n");
	char name[NAME_MAX];
	scanf("%s", name);
	int findIndex = FindByName(pcon, name);
	if (findIndex < 0) {
		printf("����ϵ�˲�����!\n");
		return;
	}
	//ִ��ɾ������
	SLErase(pcon, findIndex);
	printf("ɾ���ɹ�!\n");

}
void ContactModify(Contact* pcon) {
	//�ҵ��˾��޸�
	//�Ҳ�������
	char name[NAME_MAX];
	printf("������Ҫ�޸ĵ���ϵ��������>");
	scanf("%s", name);
	int findIndex = FindByName(pcon, name);
	if (findIndex < 0)
	{
		printf("����ϵ�˲�����!\n");
		return;
	}
	printf("������������\n");
	scanf("%s", pcon->arr[findIndex].name);
	printf("���������䣺\n");
	scanf("%d", &pcon->arr[findIndex].age);
	printf("�������Ա�\n");
	scanf("%s", pcon->arr[findIndex].gender);
	printf("������绰��\n");
	scanf("%s", pcon->arr[findIndex].tel);
	printf("������סַ��\n");
	scanf("%s", pcon->arr[findIndex].addr);

	printf("��ϵ���޸ĳɹ�!\n");
}
void ContactFind(Contact* pcon) {
	char name[NAME_MAX];
	printf("������Ҫ���ҵ���ϵ��������>");
	scanf("%s", name);
	int findIndex = FindByName(pcon, name);
	if (findIndex < 0) {
		printf("����ϵ�˲�����!\n");
		return;
	}
	printf("%s %s %s %s %s\n", "����", "�Ա�", "����", "�绰", "סַ");
	printf("%s %s %d %s %s\n", pcon->arr[findIndex].name, pcon->arr[findIndex].gender, pcon->arr[findIndex].age, pcon->arr[findIndex].tel, pcon->arr[findIndex].addr);
}
void ContactShow(Contact* pcon) {

	printf("%s %s %s %s %s\n", "����", "�Ա�", "����", "�绰", "סַ");
	for (int i = 0;i < pcon->size;i++)
	{
		printf("%s %s %d %s %s\n", pcon->arr[i].name, pcon->arr[i].gender, pcon->arr[i].age, pcon->arr[i].tel, pcon->arr[i].addr);
	}
}