#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>




//����˫������ڵ�Ľṹ

typedef int LTDataType;

typedef struct ListNode {
	LTDataType data;
	struct ListNode* prev;
	struct ListNode* next;
}ListNode;


//˫����������ڱ�λ����������֮ǰ�����ʼ��һ���ڱ�λ
//void LTInit(ListNode** pphead);
ListNode* LTInit();

//����
//void LTDestroy(ListNode** pphead);
void LTDestroy(ListNode* phead);//�Ƽ�ʹ��һ��ָ�룬���ֽӿ�һ����

//��ӡ
void SLPrint(ListNode* phead);


//ͷ��
void LTPushFront(ListNode* phead, LTDataType x);
//β��
void LTPushBack(ListNode* phead, LTDataType x);

//ͷɾ
void LTPopFront(ListNode* phead);
//βɾ
void LTPopBack(ListNode* phead);

//����
ListNode* LTFind(ListNode* phead, LTDataType x);


//��posλ��֮���������
void LTInsert(ListNode* pos, LTDataType x);
//ɾ��posλ�õ�����
void LTErase(ListNode* pos);