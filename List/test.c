#include"List.h"


void test01()
{
	ListNode* plist = LTInit();
	LTPushBack(plist, 3);
	LTPushBack(plist, 4);
	LTPushFront(plist, 2);
	LTPushFront(plist, 5);
	LTPushFront(plist, 1);
	ListNode* findRet = LTFind(plist,5);
	LTErase(findRet);
	SLPrint(plist);
}


int main()
{
	test01();
	return 0;
}