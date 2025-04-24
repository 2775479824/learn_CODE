#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>

using namespace std;

class Dog
{
public:
	string name;
	double jb_longth;
	double jb_width;
	void jb_bigger(double* jb_longth, double* jb_width) {
		*jb_longth *= 1.5;
		*jb_width *= 1.2;
	}
	void wangwangwang(Dog dog)
	{
		cout << dog.name << ":Íô!Íô!Íô!" << endl;
	}

};


int main()
{
	Dog dog;
	dog.name = "ÕÅ¿¥ºÀ";
	dog.jb_longth = 3;
	dog.jb_width = 1.5;
	dog.jb_bigger(&dog.jb_longth, &dog.jb_width);
	cout << dog.jb_longth * dog.jb_width << endl;
	dog.wangwangwang(dog);
	return 0;
}

