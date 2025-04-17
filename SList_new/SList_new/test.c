#include"SList.h"


void SListTest01()
{
	SLTNode* plist = NULL;
	SLTPushBack(&plist, 3);
	SLTPushBack(&plist, 4);
	SLTPushBack(&plist, 5);
	SLTPushFront(&plist, 2);
	SLTPushFront(&plist, 1);
	SLTPrint(plist);
	SLTEraseAfter(SLTFind(&plist, 1));
	SLTPrint(plist);

}

int main()
{
	SListTest01();
	return 0;
}