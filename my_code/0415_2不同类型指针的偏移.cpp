#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 2

using namespace std;

typedef struct stu
{
	int score;
	int age;
	int a;
}stu_t;

int main()
{
	stu_t ss = {100,19};
	stu_t *pss = &ss;
	char ch = 'j';
	char *pch = &ch;
	bool a;
	int b = 1;
	a = b;
	cout << sizeof(*pss) << endl;
	cout << a << ' ' << sizeof(a) << endl;
	cout << pss << endl;
	pss++;
	cout << pss << endl;
	printf("%p\n",pch);
	pch++;	
	printf("%p\n",pch);
	cout << sizeof(float) << endl;
	return 0;
}
//该结构体指针偏移8位，字符指针偏移1位