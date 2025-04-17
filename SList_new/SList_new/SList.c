#include"SList.h"


//��ӡ����
void SLTPrint(SLTNode* phead) {
	SLTNode* pcur = phead;
	while (pcur)
	{
		printf("%d->", pcur->data);
		pcur = pcur->next;
	}
	printf("NULL\n");
}

//�����½ڵ�
SLTNode* SLTBuyNode(SLTDataType x)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	if (newnode == NULL)
	{
		perror("malloc fail!");
		exit(1);
	}
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}



//����β��
void SLTPushBack(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);
	SLTNode* newnode = SLTBuyNode(x);
	//����Ϊ��
	if (*pphead == NULL)
	{
		*pphead = newnode;
		return;
	}
	//����Ϊ�գ���β�ڵ�
	SLTNode* ptail = *pphead;
	while (ptail->next)
	{
		ptail = ptail->next;
	}
	ptail->next = newnode;
}

//����ͷ��
void SLTPushFront(SLTNode** pphead, SLTDataType x) {
	assert(pphead);
	SLTNode* newnode = SLTBuyNode(x);
	//����Ϊ��
	//����Ϊ��
	newnode->next = *pphead;
	*pphead = newnode;
}


//�����ͷɾ��βɾ
void SLTPopFront(SLTNode** pphead) {
	assert(pphead);
	assert(*pphead);

	//����ֻ��һ���ڵ�
	if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
		return;
	}

	SLTNode* newhead = (*pphead)->next;
	free(*pphead);
	*pphead = newhead;
	
}
void SLTPopBack(SLTNode** pphead) {
	assert(pphead);
	//������Ϊ��
	assert(*pphead);
	
	//����ֻ��һ���ڵ�
	if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
		return;
	}
	SLTNode* ptail = *pphead;
	SLTNode* prev = NULL;
	while (ptail->next)
	{
		prev = ptail;
		ptail = ptail->next;
	}
	prev->next = NULL;
	free(ptail);
	ptail = NULL;
}


//����
SLTNode* SLTFind(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);
	//��������
	SLTNode* pcur = *pphead;
	while (pcur)
	{
		if (pcur->data == x)
		{
			return pcur;
		}
		pcur = pcur->next;
	}
	return NULL;
}

//��ָ��λ��֮ǰ��������
void SLTInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x) {
	assert(pphead);
	assert(pos);
	assert(*pphead);
	SLTNode* newnode = SLTBuyNode(x);

	//pos�պ���ͷ�ڵ�
	if (pos == *pphead)
	{
		//ͷ��
		SLTPushFront(pphead, x);
		return;
	}


	//pos����ͷ�ڵ�����
	SLTNode* prev = *pphead;
	while (prev->next != pos)
	{
		prev = prev->next;
	}
	newnode->next = pos;
	prev->next = newnode;
}

//ɾ��pos�ڵ�
void SLTErase(SLTNode** pphead, SLTNode* pos) {
	assert(pphead);
	assert(*pphead);
	assert(pos);

	//pos��ͷ�ڵ�
	if (pos == *pphead)
	{
		//ͷɾ
		SLTPopFront(pphead);
		return;
	}

	SLTNode* prev = *pphead;
	while (prev->next != pos)
	{
		prev = prev->next;
	}
	prev->next = pos->next;
	free(pos);
	pos = NULL;
}

//��ָ��λ��֮���������
void SLTInsertAfter(SLTNode* pos, SLTDataType x)
{
	assert(pos);

	SLTNode* newnode = SLTBuyNode(x);
	newnode->next = pos->next;
	pos->next = newnode;
}

//ɾ��pos֮��Ľڵ�
void SLTEraseAfter(SLTNode* pos)
{
	assert(pos);
	assert(pos->next);
	SLTNode* del = pos->next;
	pos->next = pos->next->next;
	free(del);
	del = NULL;

}

//��������
void SLTDestroy(SLTNode** pphead) {
	assert(pphead);
	assert(*pphead);
	SLTNode* pcur = *pphead;
	while (pcur)
	{
		SLTNode* next = pcur->next;
		free(pcur);
		pcur = next;
	}
	*pphead = NULL;
}
