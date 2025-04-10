#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//��̬˳���
//struct SeqList
//{
//	SLDatatype a[N];
//	int size;
//};

//��̬˳���
#define N 100
typedef int SLDatatype;
typedef struct SeqList
{
	SLDatatype* arr;//�洢���ݵĵײ�ṹ
	int capacity;//��¼˳���Ŀռ��С
	int size;//��Ч���ݸ���
}SL;

//��ʼ��������
void SLInit(SL* sl);
void SLDestroy(SL* sl);


void SLPushback(SL* sl,SLDatatype x);//β��

void SLPushFront(SL* sl, SLDatatype x);//ͷ��

void SLCheckCapacity(SL* sl);//���ݲ���

void SLPopBack(SL* sl);//βɾ

void SLPopFront(SL* sl);//ͷɾ

//ָ��λ��֮ǰ��������
//ɾ��ָ��λ������

void SLInsert(SL* sl,int index, SLDatatype x);
void SLErase(SL* sl, int index);


//˳������
int SLFind(SL* sl, SLDatatype x);


//test
void Print(SL* sl);