#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

using namespace std;

//1、参数类型不同
int Add(int left, int right)
{
	cout << "int Add(int left, int  right)" << endl;
	return left + right;
}


double Add(double left, double right)
{
	cout << "double Add(double left, double right)" << endl;
	return left + right;
}

//2、参数个数不同

void f()
{
	cout << "f()" << endl;
}
void f(int a)
{
	cout << "f(int a)" << endl;
}

//3、参数类型顺序不同
void f(int a, char b)
{
	cout << "f(int a,char b)" << endl;
}

void f(char b, int a)
{
	cout << "f(char b, int a)" << endl;
}

//返回值不同不能作为重载条件，因为调用时无法区分
//void fxx() {}
//
//int fxx() { return 0; }

int main()
{
	
	return 0;
}