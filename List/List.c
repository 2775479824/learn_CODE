#include"List.h"

//void LTInit(ListNode** pphead) {
//	*pphead = (ListNode*)malloc(sizeof(ListNode));
//	if (*pphead == NULL) {
//		perror("malloc failed!");
//		exit(1);
//	}
//	(*pphead)->data = -1;
//	(*pphead)->next = (*pphead)->prev = (*pphead);//当前哨兵位的前驱指针和后继指针都指向它本身。因为是循环链表
//}

//创建节点
ListNode* BuyNode(LTDataType x) {
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	if (newNode == NULL) {
		perror("malloc failed");
		exit(1);
	}
	newNode->data = x;
	newNode->next = newNode->prev = newNode;

	return newNode;
}


ListNode* LTInit() {
	ListNode* phead = BuyNode(-1);
	return phead;
}

//销毁  调用该函数后需外部手动置空哨兵位 plist = NULL
void LTDestroy(ListNode* phead) {

	//哨兵位不能为空
	assert(phead);
	ListNode* pcur = phead->next;

	while (pcur != phead)
	{
		ListNode* next = pcur->next;
		free(pcur);
		pcur = next;
	}

	free(phead);
	//phead = NULL; 这里置空对外部的plist无影响
}


//打印
void SLPrint(ListNode* phead) {
	assert(phead);
	ListNode* pcur = phead->next;
	while (pcur != phead) {
		printf("%d->", pcur->data);
		pcur = pcur->next;
	}
	printf("\n");
}


//头插
void LTPushFront(ListNode* phead, LTDataType x) {
	assert(phead);
	ListNode* newNode = BuyNode(x);
	newNode->next = phead->next;
	newNode->prev = phead;
	phead->next->prev = newNode;
	phead->next = newNode;
}

//尾插
void LTPushBack(ListNode* phead, LTDataType x) {
	ListNode* newNode = BuyNode(x);
	newNode->next = phead;
	newNode->prev = phead->prev;

	phead->prev->next = newNode;

	phead->prev = newNode;
}

//头删
void LTPopFront(ListNode* phead) {
	assert(phead);
	assert(phead->next != phead);

	ListNode* del = phead->next;

	del->next->prev = phead;
	phead->next = del->next;

	free(del);
	del = NULL;
}

//尾删
void LTPopBack(ListNode* phead) {
	assert(phead);
	//只有一个哨兵位，链表为空
	assert(phead->next != phead);

	ListNode* del = phead->prev;
	
	del->prev->next = phead;
	phead->prev = del->prev;

	free(del);
	del = NULL;
}


//查找
ListNode* LTFind(ListNode* phead, LTDataType x) {
	assert(phead);
	ListNode* pcur = phead->next;
	while (pcur != phead) {
		if (pcur->data == x) {
			return pcur;
		}
		pcur = pcur->next;
	}
	return NULL;
}



//在pos位置之后插入数据
void LTInsert(ListNode* pos, LTDataType x) {
	assert(pos);
	ListNode* newNode = BuyNode(x);
	newNode->next = pos->next;
	newNode->prev = pos;
	pos->next->prev = newNode;
	pos->next = newNode;
}
//删除pos位置的数据
void LTErase(ListNode* pos) {
	assert(pos);
	//pos->prev  pos  pos->next

	ListNode* pos_prev = pos->prev;
	ListNode* pos_next = pos->next;

	pos_prev->next = pos_next;
	pos_next->prev = pos_prev;
	free(pos);
	pos = NULL;
}