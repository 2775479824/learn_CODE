#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"Contact.h"

//#define N 100

////静态顺序表
//struct SeqList
//{
//	SLDataType a[N];
//	int size;
//};



typedef Info SLDataType;

//动态顺序表
typedef struct SeqList
{
	SLDataType* arr; //存储数据的底层结构
	int capacity;   //记录顺序表的空间大小
	int size;       //记录顺序表当前有效的数据个数
}SL;


//初始化和销毁
void SLInit(SL* ps);
void SLDestroy(SL* ps);
void SLPrint(SL* ps);//打印顺序表  因为不需要修改顺序表的数据，因此这里可以传值也可以传地址，选择传地址是为了保持接口一致性

//尾插
void SLPushBack(SL* ps, SLDataType x);
//头插
void SLPushFront(SL* ps, SLDataType x);

//头删
void SLPopFront(SL* ps);
//尾删
void SLPopBack(SL* ps);


//指定位置之前插入
void SLInsert(SL* ps, int pos, SLDataType x);
//指定位置删除
void SLErase(SL* ps, int pos);


//查找
int SLFind(SL* ps, SLDataType x);


