#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>

typedef int STDataType;

typedef struct Stack
{
	STDataType* val;
	int top;
	int capacity;
}ST;



//初始化和销毁
void STInit(ST* ps);
void STDestroy(ST* ps);

//栈顶插入删除数据
void STPush(ST* ps,STDataType x);
void STPop(ST* ps);

//获取栈顶数据
STDataType STTop(ST* ps);

int STSize(ST* ps);

bool STEmpty(ST* ps);