#define _CRT_SECURE_NO_WARNINGS 1

#include"SeqList.h"

//初始化和销毁
void SLInit(SL* ps)
{
	ps->arr = NULL;
	ps->size = ps->capacity = 0;
}

void SLDestroy(SL* ps) {

}

void SLCheckCapacity(SL* ps)
{
	if (ps->size == ps->capacity)
	{
		int newCapacity = ps->capacity == 0 ? 4 : 2 * ps->capacity;
		SLDataType* tmp = (SLDataType*)realloc(ps->arr, newCapacity * sizeof(SLDataType));
		if (tmp == NULL) {
			perror("realloc error!");
			exit(1);
		}
		//扩容成功
		ps->arr = tmp;
		ps->capacity = newCapacity;
	}
}

//打印顺序表
void SLPrint(SL* ps)
{
	for (int i = 0;i < ps->size;i++)
	{
		printf("%d ", ps->arr[i]);
	}
	printf("\n");
}

//尾插
void SLPushBack(SL* ps, SLDataType x)
{
	//断言，粗暴解决方式，也可以用if判断直接return
	assert(ps != NULL);
	//空间不够，扩容
	SLCheckCapacity(ps);
	//空间足够，直接插入
	ps->arr[ps->size++] = x;
}
//头插
void SLPushFront(SL* ps, SLDataType x)
{
	assert(ps);

	//判断是否扩容
	SLCheckCapacity(ps);

	//旧数据往后挪动一位
	for (int i = ps->size;i > 0;i--)
	{
		ps->arr[i] = ps->arr[i - 1];
	}
	ps->arr[0] = x;
	ps->size++;
}


//头删
void SLPopFront(SL* ps)
{
	assert(ps);
	assert(ps->size);

	for (int i = 0;i < ps->size - 1 ;i++)
	{
		ps->arr[i] = ps->arr[i + 1];   
	}
	ps->size--;
}
//尾删
void SLPopBack(SL* ps)
{
	//无数据
	assert(ps);
	assert(ps->size);
	//有数据
	ps->size--;
}


//指定位置之前插入
void SLInsert(SL* ps, int pos, SLDataType x)
{
	assert(ps);
	assert(pos >= 0 && pos <= ps->size);
	SLCheckCapacity(ps);

	//pos及之后的数据往后挪动一位，pos空出来
	for (int i = ps->size;i > pos;i--)
	{
		ps->arr[i] = ps->arr[i - 1];
	}
	ps->arr[pos] = x;
	ps->size++;
}
//指定位置删除
void SLErase(SL* ps, int pos)
{
	assert(ps);
	assert(ps->size);
	assert(pos >= 0 && pos <= ps->size);
	for (int i = pos;i<ps->size-1;i++)
	{
		ps->arr[i] = ps->arr[i + 1];
	}
	ps->size--;
}
