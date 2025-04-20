#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>


struct ListNode
{
	int val;
	struct ListNode* next;
};


struct ListNode* FindKthToTail(struct ListNode* pListHead, int k)
{
	struct ListNode* slow, *fast;
	slow = fast = pListHead;
	while (--k)
	{
		//k大于链表长度
		if (fast == NULL)return NULL;
		fast = fast->next;
	}

	while (fast->next)
	{
		slow = slow->next;
		fast = fast->next;
	}

	return slow;
}
  


int main()
{

	return 0;
}