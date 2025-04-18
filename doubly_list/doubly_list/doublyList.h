#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int LTDataType;

//双向链表结构
typedef struct ListNode {
	LTDataType data;
	struct ListNode* next;
	struct ListNode* prev;
}ListNode;

//因为双向链表是带哨兵位的，因此插入数据前要初始化一个哨兵节点
//void LTInit(ListNode** pphead);
ListNode* LTInit();
void LTDestroy(ListNode** pphead);

//不需要改哨兵位，不需要传二级指针

//头插尾插
void LTPushBack(ListNode* phead, LTDataType x);
void LTPushFront(ListNode* phead, LTDataType x);
//头删尾删
void LTPopBack(ListNode* phead);
void LTPopFront(ListNode* phead);

//查找
ListNode* LTFind(ListNode* phead,LTDataType x);

//双向链表打印
void LTPrint(ListNode* phead);

//在pos位置之后插入数据
void LTInsert(ListNode* pos, LTDataType x);

//删除pos位置的数据
void LTErase(ListNode* pos);