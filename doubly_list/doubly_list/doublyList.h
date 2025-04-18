#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int LTDataType;

//˫������ṹ
typedef struct ListNode {
	LTDataType data;
	struct ListNode* next;
	struct ListNode* prev;
}ListNode;

//��Ϊ˫�������Ǵ��ڱ�λ�ģ���˲�������ǰҪ��ʼ��һ���ڱ��ڵ�
//void LTInit(ListNode** pphead);
ListNode* LTInit();
void LTDestroy(ListNode** pphead);

//����Ҫ���ڱ�λ������Ҫ������ָ��

//ͷ��β��
void LTPushBack(ListNode* phead, LTDataType x);
void LTPushFront(ListNode* phead, LTDataType x);
//ͷɾβɾ
void LTPopBack(ListNode* phead);
void LTPopFront(ListNode* phead);

//����
ListNode* LTFind(ListNode* phead,LTDataType x);

//˫�������ӡ
void LTPrint(ListNode* phead);

//��posλ��֮���������
void LTInsert(ListNode* pos, LTDataType x);

//ɾ��posλ�õ�����
void LTErase(ListNode* pos);