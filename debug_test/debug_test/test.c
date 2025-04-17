#define _CRT_SECURE_NO_WARNINGS 0
#include<stdio.h>


int main()
{
	int arr[3][3] = { 0 };
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			printf("&arr[%d][%d] = %p\n", i, j, &arr[i][j]);
		}
	}
	return 0;
}
