#include<iostream>
#include<stdio.h>
#include<stdlib.h>
//C++一般用cstdlib  来用system("pause")； 不过C++兼容C
#define OUT
#define IN
#define INOUT

//IN     表示输入参数，指针指向的值不会修改；
//OUT    表示输出参数，指针指向的值会修改，且不会读；
//INOUT  表示输入输出参数，指针指向的值会修改，且会读取

void function1(OUT int* p)
{
	*p = 10;
	return;
}

void function2(IN int* p)
{
	printf("%d\n", *p);
	return;
}

void function3(INOUT int* p)
{
	*p = 190;
	printf("%d\n", *p);
	return;
}

int main(void)
{
	int a = 0;

	function1(&a);
	function2(&a);
	function3(&a);

	return 0;
} 