#define _CRT_SECURE_NO_WARNINGS 1

#include"SeqList.h"

void slTest01()
{
	SL sl;
	SLInit(&sl);

	//����β��
	//SLPushBack(&sl, 1);
	//SLPushBack(&sl, 2);
	//SLPushBack(&sl, 3);
	//SLPushBack(&sl, 4);
	//SLPushBack(&sl, 5);
	//SLPushBack(&sl, 6);

	//SLPrint(&sl);
	////����βɾ
	//SLPopBack(&sl);
	//SLPopBack(&sl);
	//SLPopBack(&sl);
	//SLPrint(&sl);

	////����ͷɾ
	//SLPopFront(&sl);
	//SLPopFront(&sl);
	//SLPopFront(&sl);
	//SLPrint(&sl);


	//����ͷ��
	//SLPushFront(&sl, 6);
	//SLPushFront(&sl, 5);
	//SLPushFront(&sl, 4);
	//SLPushFront(&sl, 3);
	//SLPushFront(&sl, 2);
	//SLPrint(&sl);
	//SLPushFront(&sl, 1);
	//SLPrint(&sl);

}


int main()
{
	slTest01();
	return 0;
}