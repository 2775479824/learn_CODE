#include"SeqList.h"


int main()
{
	SL sl;
	SLInit(&sl);
	SLPushFront(&sl, 5);
	SLPushFront(&sl, 6);
	SLPushFront(&sl, 7);
	SLPushback(&sl, 4);
	SLPushback(&sl, 7);
	SLPushback(&sl, 3);
	SLPushback(&sl, 2);
	SLPushback(&sl, 1);
	
	Print(&sl);//76547321

	SLErase(&sl,4);
	Print(&sl);//7654321
	printf("%d\n",SLFind(&sl, 9));//return 3 
	return 0;
}