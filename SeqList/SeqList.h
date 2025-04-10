#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//静态顺序表
//struct SeqList
//{
//	SLDatatype a[N];
//	int size;
//};

//动态顺序表
#define N 100
typedef int SLDatatype;
typedef struct SeqList
{
	SLDatatype* arr;//存储数据的底层结构
	int capacity;//记录顺序表的空间大小
	int size;//有效数据个数
}SL;

//初始化和销毁
void SLInit(SL* sl);
void SLDestroy(SL* sl);


void SLPushback(SL* sl,SLDatatype x);//尾插

void SLPushFront(SL* sl, SLDatatype x);//头插

void SLCheckCapacity(SL* sl);//扩容操作

void SLPopBack(SL* sl);//尾删

void SLPopFront(SL* sl);//头删

//指定位置之前插入数据
//删除指定位置数据

void SLInsert(SL* sl,int index, SLDatatype x);
void SLErase(SL* sl, int index);


//顺序表查找
int SLFind(SL* sl, SLDatatype x);


//test
void Print(SL* sl);