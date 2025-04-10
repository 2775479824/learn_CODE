#include"SeqList.h"

//˳����ʼ��
void SLInit(SL* sl)
{
	sl->arr = NULL;
	sl->size = sl->capacity = 0;
}

//˳�������
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

//������鼰����
void SLCheckCapacity(SL* sl)
{
	if (sl->size == sl->capacity) {
		int newCapacity = sl->capacity == 0 ? 4 : 2 * sl->capacity;//�������Ϊ0��ôֱ�Ӹ�4�������Ϊ0����ԭ�����Ϸ���
		SLDatatype* tmp = (SLDatatype*)realloc(sl->arr, newCapacity * sizeof(SLDatatype));
		
		if (tmp == NULL)//����ʧ��
		{
			perror("realloc failed!\n");
			exit(1);
		}

		//���ݳɹ�
		sl->arr = tmp;//�������ݺõĸ�ֵ��arr
		sl->capacity = newCapacity;//����˳��������
	}
}


//β��
void SLPushback(SL* sl, SLDatatype x)
{
	//�ж�sl�Ƿ�Ϊ��
	assert(sl);

	//�ȼ�������鿴�Ƿ���Ҫ����
	SLCheckCapacity(sl);

	//�ռ��㹻��ֱ�Ӳ���
	sl->arr[sl->size++] = x;
}

//ͷ��
void SLPushFront(SL* sl, SLDatatype x)
{
	//�ж�sl�Ƿ�Ϊ��
	assert(sl);

	//�ж��Ƿ���Ҫ����
	SLCheckCapacity(sl);

	//������������Ų��
	for (int i = sl->size; i > 0; i--)
	{
		sl->arr[i] = sl->arr[i - 1];
	}
	sl->arr[0] = x;
	sl->size++;
}

//βɾ   ���������������һ����ֱ��ɾ�����һ�����ݲ���size--���ڶ�����˳���Ϊ�գ�û�����ݿ�ɾ�����Կ��Զ���һ��size�Ƿ�Ϊ0
void SLPopBack(SL* sl)
{
	assert(sl);
	assert(sl->size);

	sl->size--;
}


//ͷɾ
void SLPopFront(SL* sl)
{
	assert(sl);
	assert(sl->size);

	//ִ��Ų������
	for (int i = 0;i < sl->size-1; i++)
	{
		sl->arr[i] = sl->arr[i + 1];
	}
	sl->size--;
}

//ָ��λ��֮ǰ��������
//ɾ��ָ��λ������

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
	//˳���Ϊ�գ�����ɾ
	assert(sl);
	assert(index >= 0 && index < sl->size);
	//˳���Ϊ�գ���index�����������ǰŲ��һλ��size--
	for (int i = index;i < sl->size-1;i++)
	{
		sl->arr[i] = sl->arr[i + 1];
	}
	sl->size--;
}



//˳������
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
