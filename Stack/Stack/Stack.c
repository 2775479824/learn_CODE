#include "Stack.h"

//初始化
void STInit(ST* ps) {
	assert(ps);
	ps->val = NULL;
	ps->capacity = 0;
	ps->top = 0;//top为0代表top指向栈顶元素的下一个
}

//销毁
void STDestroy(ST* ps) {
	free(ps->val);
	ps->val = NULL;
	ps->top = ps->capacity = 0;
}

//栈顶插入数据
void STPush(ST* ps, STDataType x) {
	assert(ps);

	if (ps->top == ps->capacity)
	{
		//扩容
		int newCapacity = (ps->capacity == 0) ? 4 : ps->capacity * 2;
		STDataType* tmp = (STDataType*)realloc(ps->val, newCapacity * sizeof(STDataType));
		if (tmp == NULL)
		{
			perror("realloc fail!");
			return;
		}
		ps->val = tmp;
		ps->capacity = newCapacity;
	}
	ps->val[ps->top] = x;
	ps->top++;

}

//栈顶删除数据
void STPop(ST* ps) {
	assert(ps);
	assert(!STEmpty(ps));
	ps->top--;
}

//获取栈顶数据
STDataType STTop(ST* ps)
{
	assert(ps);
	assert(!STEmpty(ps));

	return ps->val[ps->top--];
}

int STSize(ST* ps)
{
	assert(ps);
	return ps->top;
}

bool STEmpty(ST* ps)
{
	assert(ps);
	
	return ps->top == 0;
}