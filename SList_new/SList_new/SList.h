#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//����ڵ�ṹ

typedef int SLTDataType;
typedef struct SListNode
{
	SLTDataType data;
	struct SListNode* next;
}SLTNode;

//��ӡ����
void SLTPrint(SLTNode* phead);

//�����ͷ���β��
void SLTPushFront(SLTNode** pphead, SLTDataType x);
void SLTPushBack(SLTNode** pphead, SLTDataType x);



//�����ͷɾ��βɾ
void SLTPopFront(SLTNode** pphead);
void SLTPopBack(SLTNode** pphead);


//����
SLTNode* SLTFind(SLTNode** pphead, SLTDataType x);

//��ָ��λ��֮ǰ��������
void SLTInsert(SLTNode** pphead,SLTNode* pos, SLTDataType x);

//ɾ��pos�ڵ�
void SLTErase(SLTNode** pphead, SLTNode* pos);

//��ָ��λ��֮���������
void SLTInsertAfter(SLTNode* pos, SLTDataType x);

//ɾ��pos֮��Ľڵ�
void SLTEraseAfter(SLTNode* pos);

//��������
void SLTDestroy(SLTNode** pphead);
