#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//链表节点结构

typedef int SLTDataType;
typedef struct SListNode
{
	SLTDataType data;
	struct SListNode* next;
}SLTNode;

//打印链表
void SLTPrint(SLTNode* phead);

//链表的头插和尾插
void SLTPushFront(SLTNode** pphead, SLTDataType x);
void SLTPushBack(SLTNode** pphead, SLTDataType x);



//链表的头删和尾删
void SLTPopFront(SLTNode** pphead);
void SLTPopBack(SLTNode** pphead);


//查找
SLTNode* SLTFind(SLTNode** pphead, SLTDataType x);

//在指定位置之前插入数据
void SLTInsert(SLTNode** pphead,SLTNode* pos, SLTDataType x);

//删除pos节点
void SLTErase(SLTNode** pphead, SLTNode* pos);

//在指定位置之后插入数据
void SLTInsertAfter(SLTNode* pos, SLTDataType x);

//删除pos之后的节点
void SLTEraseAfter(SLTNode* pos);

//销毁链表
void SLTDestroy(SLTNode** pphead);
