#include"SList.h"


//打印链表
void SLTPrint(SLTNode* phead) {
	SLTNode* pcur = phead;
	while (pcur)
	{
		printf("%d->", pcur->data);
		pcur = pcur->next;
	}
	printf("NULL\n");
}

//创建新节点
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



//链表尾插
void SLTPushBack(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);
	SLTNode* newnode = SLTBuyNode(x);
	//链表为空
	if (*pphead == NULL)
	{
		*pphead = newnode;
		return;
	}
	//链表不为空，找尾节点
	SLTNode* ptail = *pphead;
	while (ptail->next)
	{
		ptail = ptail->next;
	}
	ptail->next = newnode;
}

//链表头插
void SLTPushFront(SLTNode** pphead, SLTDataType x) {
	assert(pphead);
	SLTNode* newnode = SLTBuyNode(x);
	//链表为空
	//链表不为空
	newnode->next = *pphead;
	*pphead = newnode;
}


//链表的头删和尾删
void SLTPopFront(SLTNode** pphead) {
	assert(pphead);
	assert(*pphead);

	//链表只有一个节点
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
	//链表不能为空
	assert(*pphead);
	
	//链表只有一个节点
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


//查找
SLTNode* SLTFind(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);
	//遍历链表
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

//在指定位置之前插入数据
void SLTInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x) {
	assert(pphead);
	assert(pos);
	assert(*pphead);
	SLTNode* newnode = SLTBuyNode(x);

	//pos刚好是头节点
	if (pos == *pphead)
	{
		//头插
		SLTPushFront(pphead, x);
		return;
	}


	//pos不是头节点的情况
	SLTNode* prev = *pphead;
	while (prev->next != pos)
	{
		prev = prev->next;
	}
	newnode->next = pos;
	prev->next = newnode;
}

//删除pos节点
void SLTErase(SLTNode** pphead, SLTNode* pos) {
	assert(pphead);
	assert(*pphead);
	assert(pos);

	//pos是头节点
	if (pos == *pphead)
	{
		//头删
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

//在指定位置之后插入数据
void SLTInsertAfter(SLTNode* pos, SLTDataType x)
{
	assert(pos);

	SLTNode* newnode = SLTBuyNode(x);
	newnode->next = pos->next;
	pos->next = newnode;
}

//删除pos之后的节点
void SLTEraseAfter(SLTNode* pos)
{
	assert(pos);
	assert(pos->next);
	SLTNode* del = pos->next;
	pos->next = pos->next->next;
	free(del);
	del = NULL;

}

//销毁链表
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
