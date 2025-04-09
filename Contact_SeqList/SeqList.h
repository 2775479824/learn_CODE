#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"Contact.h"


//顺序表数据类型
typedef Info SLDataType;


//定义动态顺序表
typedef struct SeqList
{
	SLDataType* arr;
	int size;
	int capacity;
}SL;


//顺序表的初始化和销毁

void SLInit(SL* psl);
void SLDestroy(SL* psl);


//顺序表的容量检查以及扩容操作

void SLCheckCapacity(SL* psl);


//顺序表的头插、尾插

void SLPushFront(SL* psl, SLDataType x);
void SLPushBack(SL* psl, SLDataType x);

//顺序表的头删、尾删

void SLPopFront(SL* psl);
void SLPopBack(SL* psl);

//顺序表的查找

int SLFind(SL* psl, SLDataType x);

//指定位置之前插入
//指定位置删除

void SLInsert(SL* psl, int index, SLDataType x);
void SLErase(SL* psl, int index);

