#include"List.h"

//void LTInit(ListNode** pphead) {
//	*pphead = (ListNode*)malloc(sizeof(ListNode));
//	if (*pphead == NULL) {
//		perror("malloc failed!");
//		exit(1);
//	}
//	(*pphead)->data = -1;
//	(*pphead)->next = (*pphead)->prev = (*pphead);//��ǰ�ڱ�λ��ǰ��ָ��ͺ��ָ�붼ָ����������Ϊ��ѭ������
//}

//�����ڵ�
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

//����  ���øú��������ⲿ�ֶ��ÿ��ڱ�λ plist = NULL
void LTDestroy(ListNode* phead) {

	//�ڱ�λ����Ϊ��
	assert(phead);
	ListNode* pcur = phead->next;

	while (pcur != phead)
	{
		ListNode* next = pcur->next;
		free(pcur);
		pcur = next;
	}

	free(phead);
	//phead = NULL; �����ÿն��ⲿ��plist��Ӱ��
}


//��ӡ
void SLPrint(ListNode* phead) {
	assert(phead);
	ListNode* pcur = phead->next;
	while (pcur != phead) {
		printf("%d->", pcur->data);
		pcur = pcur->next;
	}
	printf("\n");
}


//ͷ��
void LTPushFront(ListNode* phead, LTDataType x) {
	assert(phead);
	ListNode* newNode = BuyNode(x);
	newNode->next = phead->next;
	newNode->prev = phead;
	phead->next->prev = newNode;
	phead->next = newNode;
}

//β��
void LTPushBack(ListNode* phead, LTDataType x) {
	ListNode* newNode = BuyNode(x);
	newNode->next = phead;
	newNode->prev = phead->prev;

	phead->prev->next = newNode;

	phead->prev = newNode;
}

//ͷɾ
void LTPopFront(ListNode* phead) {
	assert(phead);
	assert(phead->next != phead);

	ListNode* del = phead->next;

	del->next->prev = phead;
	phead->next = del->next;

	free(del);
	del = NULL;
}

//βɾ
void LTPopBack(ListNode* phead) {
	assert(phead);
	//ֻ��һ���ڱ�λ������Ϊ��
	assert(phead->next != phead);

	ListNode* del = phead->prev;
	
	del->prev->next = phead;
	phead->prev = del->prev;

	free(del);
	del = NULL;
}


//����
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



//��posλ��֮���������
void LTInsert(ListNode* pos, LTDataType x) {
	assert(pos);
	ListNode* newNode = BuyNode(x);
	newNode->next = pos->next;
	newNode->prev = pos;
	pos->next->prev = newNode;
	pos->next = newNode;
}
//ɾ��posλ�õ�����
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