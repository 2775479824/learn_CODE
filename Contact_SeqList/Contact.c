//#include"Contact.h"
#include"SeqList.h"



//ͨѶ¼�ĳ�ʼ��������
//ʵ���Ͼ���˳���ĳ�ʼ��������

void ContactInit(Contact* pcon)
{
	SLInit(pcon);
}

void ContactDestroy(Contact* pcon)
{
	SLDestroy(pcon);
}

 
//���ӡ�ɾ�����޸ġ����ҡ��鿴ͨѶ¼����

void ContactAdd(Contact* pcon)
{
	//�ն˻�ȡ��ϵ������

	Info info;//������ϵ�˽ṹ�����
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

	//�������ݵ�ͨѶ¼�������浽˳���
	SLPushBack(pcon, info);
}


void ContactDel(Contact* pcon)
{
	//ɾ��֮ǰҪ�Ȳ��ң��ҵ���ɾ���Ҳ����Ǿ�û��ɾ
	printf("������Ҫɾ������ϵ��������\n");
	char name[NAME_MAX];
	scanf("%s", name);
	int findIndex = FindByName(pcon, name);
	if (findIndex < 0)
	{
		printf("����ϵ�˲����ڣ�\n");
		return;
	}
	//ִ��ɾ������
	SLErase(pcon, findIndex);
	printf("��ϵ��ɾ���ɹ���\n");
}


void ContactModify(Contact* pcon)
{
	//�޸�֮ǰҪ�Ȳ���
	//�ҵ��ˣ�ִ���޸Ĳ���
	//û���ҵ����޷�ִ���޸Ĳ���

	char name[NAME_MAX];
	printf("������Ҫ�޸ĵ���ϵ��������\n");
	scanf("%s", name);

	int findIndex = FindByName(pcon, name);
	if (findIndex < 0)
	{
		printf("Ҫ�޸ĵ���ϵ�˲����ڣ�\n");
		return;
	}
	//�ҵ��ˣ�ִ���޸Ĳ���
	printf("������������\n");
	scanf("%s", pcon->arr[findIndex].name);
	printf("���������䣺\n");
	scanf("%d", &pcon->arr[findIndex].age);
	printf("�������Ա�\n");
	scanf("%s", pcon->arr[findIndex].gender);
	printf("������绰��\n");
	scanf("%s", pcon->arr[findIndex].tel);
	printf("�������ַ��\n");
	scanf("%s", pcon->arr[findIndex].addr);
	
	printf("��ϵ���޸ĳɹ���\n");
}


int FindByName(Contact* pcon, char name[])
{
	for (int i = 0; i < pcon->size; i++)
	{
		if (strcmp(pcon->arr[i].name, name) == 0)
		{
			//�ҵ���
			return i;
		}
	}
	//�Ҳ���
	return -1;
}


void ContactFind(Contact* pcon)
{
	char name[NAME_MAX];
	printf("������Ҫ���ҵ��û�������\n");
	scanf("%s", name);

	int findIndex = FindByName(pcon, name);
	//�Ҳ���
	if (findIndex < 0)
	{
		printf("����ϵ�˲�����! \n");
		return;
	}
	//�ҵ��ˣ���ӡ��Ϣ
	printf("%s\t%s\t%s\t%s\t\t%s\n", "����", "�Ա�", "����", "�绰", "סַ");

	printf("%s\t%s\t%d\t%s\t\t%s\n", pcon->arr[findIndex].name, pcon->arr[findIndex].gender, pcon->arr[findIndex].age, pcon->arr[findIndex].tel, pcon->arr[findIndex].addr);
}


void ContactShow(Contact* pcon)
{
	printf("%s\t%s\t%s\t%s\t\t%s\n", "����", "�Ա�", "����", "�绰", "סַ");
	for (int i = 0; i < pcon->size; i++)
	{
		printf("%s\t%s\t%d\t%s\t\t%s\n", pcon->arr[i].name, pcon->arr[i].gender, pcon->arr[i].age, pcon->arr[i].tel, pcon->arr[i].addr);
	}
}
