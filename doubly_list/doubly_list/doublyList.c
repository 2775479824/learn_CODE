#include"doublyList.h"

//void LTInit(ListNode** pphead) {
//	*pphead = (ListNode*)malloc(sizeof(ListNode));
//	if (*pphead == NULL)
//	{
//		perror("malloc fail!\n");
//		exit(1);
//	}
//	(*pphead)->data = -1;
//	(*pphead)->next = (*pphead)->prev = (*pphead);
//}

ListNode* LTInit()
{
	ListNode* phead = (ListNode*)malloc(sizeof(ListNode));
	if (phead == NULL)
	{
		perror("malloc fail!\n");
		exit(1);
	}
	phead->data = -1;
	phead->next = phead->prev = phead;

	return phead;
}

ListNode* BuyNode(LTDataType x)
{
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	newnode->data = x;
	newnode->next = newnode->prev = newnode;
	return newnode;
}


void LTPushBack(ListNode* phead, LTDataType x)
{
	assert(phead);
	ListNode* newnode = BuyNode(x);
	newnode->prev = phead->prev;
	newnode->next = phead;
	phead->prev->next = newnode;
	phead->prev = newnode;
}
void LTPushFront(ListNode* phead, LTDataType x) {
	assert(phead);
	ListNode* newnode = BuyNode(x);
	//phead  newnode  phead->next
	newnode->next = phead->next;
	newnode->prev = phead;
	phead->next->prev = newnode;
	phead->next = newnode;
}

//头删尾删
void LTPopBack(ListNode* phead) {
	assert(phead);
	assert(phead->next != phead);
	ListNode* del = phead->prev;
	del->prev->next = phead;
	phead->prev = del->prev;
	free(del);
	del = NULL;
	
}
void LTPopFront(ListNode* phead) {
	assert(phead);
	assert(phead->next != phead);
	ListNode* del = phead->next;
	del->next->prev = phead;
	phead->next = del->next;
	free(del);
	del = NULL;
}

//查找
ListNode* LTFind(ListNode* phead,LTDataType x)
{
	assert(phead);
	ListNode* pcur = phead->next;
	while (pcur != phead)
	{
		if (pcur->data == x)
		{
			return pcur;
		}
		pcur = pcur->next;
	}
	return NULL;
}

//在pos位置之后插入数据
void LTInsert(ListNode* pos, LTDataType x) {
	assert(pos);
	ListNode* newnode = BuyNode(x);

	//pos   newnode  pos->next
	newnode->next = pos->next;
	newnode->prev = pos;
	pos->next->prev = newnode;
	pos->next = newnode;
}
//删除pos位置的数据
void LTErase(ListNode* pos) {
	assert(pos);
	//pos->prev  pos  pos->next
	pos->next->prev = pos->prev;
	pos->prev->next = pos->next;
	free(pos);
	pos = NULL;
}

//也可以用一级指针，但需要外部手动置空哨兵位，推荐用一级指针的原因是保持接口一致性
void LTDestroy(ListNode** pphead) {
	assert(pphead);
	assert(*pphead);
	ListNode* pcur = (*pphead)->next;
	while (pcur != *pphead)
	{
		ListNode* next = pcur->next;
		free(pcur);
		pcur = next;
	}
	//链表中只有哨兵位
	free(*pphead);
	*pphead = NULL;
}


void LTPrint(ListNode* phead) {
	assert(phead);
	ListNode* pcur = phead->next;
	while (pcur != phead)
	{
		printf("%d->", pcur->data);
		pcur = pcur->next;
	}
	printf("\n");
}