#pragma once


//#include<stdio.h>//暂时添加


// #include"SeqList.h"  头文件嵌套问题，解决方法：前置声明

#define NAME_MAX 100
#define GENDER_MAX 20
#define TEL_MAX 12
#define ADDR_MAX 100


//通讯录数据类型
typedef struct PersonInfo
{
	char name[NAME_MAX];
	int age;
	char gender[GENDER_MAX];
	char tel[TEL_MAX];
	char addr[ADDR_MAX];
}Info;

//使用顺序表的前置声明
struct SeqList;

//改名
typedef struct SeqList Contact;


//通讯录操作接口

//通讯录的初始化与销毁
void ContactInit(Contact* pcon);
void ContactDestroy(Contact* pcon);

//增加、删除、修改、查找、查看通讯录方法
void ContactAdd(Contact* pcon);
void ContactDel(Contact* pcon);
void ContactModify(Contact* pcon);
void ContactFind(Contact* pcon);
void ContactShow(Contact* pcon);