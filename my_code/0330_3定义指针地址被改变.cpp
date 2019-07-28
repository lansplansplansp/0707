#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

typedef struct STU
{
	short age;
	int score;
}stu_t;

stu_t *test()
{
	stu_t *t = (stu_t *)malloc(sizeof(stu_t));
	t->age = 18;
	t->score = 98;
	cout << t->age <<' '<< t->score << endl;

	printf("指针t地址     :%p\n",t);
	return t;
}

int main()
{
	stu_t *q = test();
	stu_t *p = NULL;
	cout << "my p 值 = " << p << endl;
	printf("my p 值 = %d\n",p);
	printf("my p 值 = %c\n",p);
	printf("指针q地址     :%p\n",q);
	cout << q->age <<' '<< q->score << endl;
	char *a = "192.168.1.104";
	char b[128];
	strcpy(b,a);
	cout << b << endl;
	return 0;
}