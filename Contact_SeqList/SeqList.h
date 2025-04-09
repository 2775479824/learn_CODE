#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"Contact.h"


//˳�����������
typedef Info SLDataType;


//���嶯̬˳���
typedef struct SeqList
{
	SLDataType* arr;
	int size;
	int capacity;
}SL;


//˳���ĳ�ʼ��������

void SLInit(SL* psl);
void SLDestroy(SL* psl);


//˳������������Լ����ݲ���

void SLCheckCapacity(SL* psl);


//˳����ͷ�塢β��

void SLPushFront(SL* psl, SLDataType x);
void SLPushBack(SL* psl, SLDataType x);

//˳����ͷɾ��βɾ

void SLPopFront(SL* psl);
void SLPopBack(SL* psl);

//˳���Ĳ���

int SLFind(SL* psl, SLDataType x);

//ָ��λ��֮ǰ����
//ָ��λ��ɾ��

void SLInsert(SL* psl, int index, SLDataType x);
void SLErase(SL* psl, int index);

