#include"SeqList.h"

//顺序表的初始化和销毁

void SLInit(SL* psl)
{
	psl->arr = NULL;
	psl->capacity = psl->size = 0;
}

void SLDestroy(SL* psl)
{
	if (psl->arr != NULL)
	{
		free(psl->arr);
	}
	psl->arr = NULL;
	psl->capacity = psl->size = 0;
}


//顺序表的容量检查以及扩容操作

void SLCheckCapacity(SL* psl)
{
	if (psl->capacity == psl->size)
	{
		int newCapacity = psl->capacity == 0 ? 4 : 2 * psl->capacity;
		SLDataType* tmp = (SLDataType*)realloc(psl->arr, newCapacity * sizeof(SLDataType));
		if (tmp == NULL)
		{
			perror("扩容失败！\n");
			exit(1);
		}
		psl->arr = tmp;
		psl->capacity = newCapacity;
	}
}


//顺序表的头插、尾插

void SLPushFront(SL* psl, SLDataType x)
{
	assert(psl);
	SLCheckCapacity(psl);
	for (int i = psl->size; i > 0; i--)
	{
		psl->arr[i] = psl->arr[i - 1];
	}
	psl->arr[0] = x;
	psl->size++;
}
void SLPushBack(SL* psl, SLDataType x)
{
	assert(psl);
	SLCheckCapacity(psl);
	psl->arr[psl->size++] = x;
}

//顺序表的头删、尾删

void SLPopFront(SL* psl)
{
	assert(psl);
	assert(psl->size);
	for (int i = 0; i < psl->size - 1; i++)
	{
		psl->arr[i] = psl->arr[i + 1];
	}
	psl->size--;
}
void SLPopBack(SL* psl)
{
	assert(psl);
	assert(psl->size);
	psl->size--;
}

//顺序表的查找

//int SLFind(SL* psl, SLDataType x)
//{
//	assert(psl);
//	for (int i = 0; i < psl->size; i++)
//	{
//		if (psl->arr[i] == x)
//		{
//			return i;
//		}
//	}
//	return -1;
//}

//指定位置之前插入
//指定位置删除

void SLInsert(SL* psl, int index, SLDataType x)
{
	assert(psl);
	assert(index >= 0 && index <= psl->size);
	for (int i =psl->size;i>index;i-- )
	{
		psl->arr[i] = psl->arr[i - 1];
	}
	psl->arr[index] = x;
	psl->size++;
}
void SLErase(SL* psl, int index)
{
	assert(psl);
	assert(index >= 0 && index < psl->size);
	for (int i = index; i < psl->size - 1; i++)
	{
		psl->arr[i] = psl->arr[i + 1];
	}
	psl->size--;

}
