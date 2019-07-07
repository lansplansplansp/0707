#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct STU
{
	short age;
	int score;
}stu_t;

void test(stu_t **p)
{
	printf("二级指针前内容:%p\n",*p);
	stu_t *t = (stu_t *)malloc(sizeof(stu_t));
	t->age = 18;
	t->score = 98;
	cout << t->age <<' '<< t->score << endl;
	*p = t;
	printf("二级指针地址  :%p\n",p);
	printf("二级指针后内容:%p\n",*p);
	printf("指针t地址     :%p\n",t);
}

void test2(stu_t *p)
{
	printf("一级指针前内容:%p\n",*p);
	stu_t *t = (stu_t *)malloc(sizeof(stu_t));
	t->age = 18;
	t->score = 98;
	cout << t->age <<' '<< t->score << endl;
	p = t;
	printf("一级指针后内容:%p\n",*p);
	printf("指针t地址     :%p\n",t);
}

int main()
{
	stu_t *q = NULL;
#if 0
	printf("指针q前地址   :%p\n",q);
	test2(q);
	printf("不传二级指针   :%p\n",q);
	cout << q->age <<' '<< q->score << endl;

	cout << "不传二级指针形参！！！！！！！！！！：\n";
#endif	

	printf("指针q前地址   :%p\n",q);
	test(&q);
	printf("指针q后地址   :%p\n",q);
	cout << q->age <<' '<< q->score << endl;
	
	return 0;
}