#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>




//定义双向链表节点的结构

typedef int LTDataType;

typedef struct ListNode {
	LTDataType data;
	struct ListNode* prev;
	struct ListNode* next;
}ListNode;


//双向链表存在哨兵位，插入数据之前必须初始化一个哨兵位
//void LTInit(ListNode** pphead);
ListNode* LTInit();

//销毁
//void LTDestroy(ListNode** pphead);
void LTDestroy(ListNode* phead);//推荐使用一级指针，保持接口一致性

//打印
void SLPrint(ListNode* phead);


//头插
void LTPushFront(ListNode* phead, LTDataType x);
//尾插
void LTPushBack(ListNode* phead, LTDataType x);

//头删
void LTPopFront(ListNode* phead);
//尾删
void LTPopBack(ListNode* phead);

//查找
ListNode* LTFind(ListNode* phead, LTDataType x);


//在pos位置之后插入数据
void LTInsert(ListNode* pos, LTDataType x);
//删除pos位置的数据
void LTErase(ListNode* pos);