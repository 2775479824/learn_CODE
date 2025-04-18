#include"doublyList.h"


void test01()
{
	ListNode* list = LTInit();
	LTPushBack(list,1);
	LTPushBack(list,2);
	LTPushBack(list,3);
	LTPrint(list);
	LTInsert(LTFind(list, 2), 0);
	LTPrint(list);
}



int main()
{
	test01();
	return 0;
}