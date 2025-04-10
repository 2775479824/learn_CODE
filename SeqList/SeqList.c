#include"SeqList.h"

//顺序表初始化
void SLInit(SL* sl)
{
	sl->arr = NULL;
	sl->size = sl->capacity = 0;
}

//顺序表销毁
void SLDestroy(SL* sl)
{
	if (sl->arr != NULL)
	{
		free(sl->arr);
		sl->arr = NULL;
		sl->capacity = sl->size = 0;
	}
	else
		return;
}

//容量检查及扩容
void SLCheckCapacity(SL* sl)
{
	if (sl->size == sl->capacity) {
		int newCapacity = sl->capacity == 0 ? 4 : 2 * sl->capacity;//如果容量为0那么直接给4，如果不为0则在原基础上翻倍
		SLDatatype* tmp = (SLDatatype*)realloc(sl->arr, newCapacity * sizeof(SLDatatype));
		
		if (tmp == NULL)//扩容失败
		{
			perror("realloc failed!\n");
			exit(1);
		}

		//扩容成功
		sl->arr = tmp;//将新扩容好的赋值给arr
		sl->capacity = newCapacity;//更新顺序表的容量
	}
}


//尾插
void SLPushback(SL* sl, SLDatatype x)
{
	//判断sl是否为空
	assert(sl);

	//先检查容量查看是否需要扩容
	SLCheckCapacity(sl);

	//空间足够，直接插入
	sl->arr[sl->size++] = x;
}

//头插
void SLPushFront(SL* sl, SLDatatype x)
{
	//判断sl是否为空
	assert(sl);

	//判断是否需要扩容
	SLCheckCapacity(sl);

	//将旧数据往后挪动
	for (int i = sl->size; i > 0; i--)
	{
		sl->arr[i] = sl->arr[i - 1];
	}
	sl->arr[0] = x;
	sl->size++;
}

//尾删   存在两种情况，第一种是直接删除最后一个数据并让size--，第二种是顺序表为空，没有数据可删，所以可以断言一下size是否为0
void SLPopBack(SL* sl)
{
	assert(sl);
	assert(sl->size);

	sl->size--;
}


//头删
void SLPopFront(SL* sl)
{
	assert(sl);
	assert(sl->size);

	//执行挪动操作
	for (int i = 0;i < sl->size-1; i++)
	{
		sl->arr[i] = sl->arr[i + 1];
	}
	sl->size--;
}

//指定位置之前插入数据
//删除指定位置数据

void SLInsert(SL* sl,int index, SLDatatype x) 
{
	assert(sl);
	assert(index >= 0 && index <= sl->size);

	for (int i = sl->size; i > index; i--)
	{
		sl->arr[i] = sl->arr[i - 1];
	}
	sl->arr[index] = x;
	sl->size++;
}
void SLErase(SL* sl, int index)
{
	//顺序表为空，不能删
	assert(sl);
	assert(index >= 0 && index < sl->size);
	//顺序表不为空，将index后面的数据往前挪动一位，size--
	for (int i = index;i < sl->size-1;i++)
	{
		sl->arr[i] = sl->arr[i + 1];
	}
	sl->size--;
}



//顺序表查找
int SLFind(SL* sl, SLDatatype x)
{
	for (int i = 0; i < sl->size; i++)
	{
		if (sl->arr[i] == x)
		{
			return i;
		}
	}
	return -1;
}

//test print
void Print(SL* sl)
{
	for (int i = 0; i < sl->size; i++)
	{
		printf("%d\t", sl->arr[i]);
	}
	printf("\n");
}
