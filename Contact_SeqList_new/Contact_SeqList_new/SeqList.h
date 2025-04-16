#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"Contact.h"

//#define N 100

////��̬˳���
//struct SeqList
//{
//	SLDataType a[N];
//	int size;
//};



typedef Info SLDataType;

//��̬˳���
typedef struct SeqList
{
	SLDataType* arr; //�洢���ݵĵײ�ṹ
	int capacity;   //��¼˳���Ŀռ��С
	int size;       //��¼˳���ǰ��Ч�����ݸ���
}SL;


//��ʼ��������
void SLInit(SL* ps);
void SLDestroy(SL* ps);
void SLPrint(SL* ps);//��ӡ˳���  ��Ϊ����Ҫ�޸�˳�������ݣ����������Դ�ֵҲ���Դ���ַ��ѡ�񴫵�ַ��Ϊ�˱��ֽӿ�һ����

//β��
void SLPushBack(SL* ps, SLDataType x);
//ͷ��
void SLPushFront(SL* ps, SLDataType x);

//ͷɾ
void SLPopFront(SL* ps);
//βɾ
void SLPopBack(SL* ps);


//ָ��λ��֮ǰ����
void SLInsert(SL* ps, int pos, SLDataType x);
//ָ��λ��ɾ��
void SLErase(SL* ps, int pos);


//����
int SLFind(SL* ps, SLDataType x);


