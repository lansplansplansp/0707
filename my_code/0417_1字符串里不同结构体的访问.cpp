#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 2
//跟JSON不一样，sprintf()将其他类型转成了char类型，性质完全变了，而JSON是在双方知道传送规则前提下将不同类型转换成字符串传送，接收后再转换成原来的类型
using namespace std;

typedef struct stu
{
	int score;
	int age;
}stu_t;

typedef struct list
{
	char a;
	char b;
}list_t;

typedef struct node
{
	int a;
	int b;
}node_t;
int main()
{
	int i;
	stu_t x = {100,20};
	list_t y = {'h','r'};
	node_t z = {3,1};
	char buffer[128];
	sprintf(buffer,"%d%d%c%c%d%d", x.score,x.age,y.a,y.b,z.a,z.b);
	printf("%s\n",buffer);//10020hr31
	printf("%p\n",buffer);
	stu_t *px = (stu_t *)buffer;
	printf("%p\n",px);
	list_t *py = (list_t *)(buffer+sizeof(stu_t));
	printf("%p\n",py);
	for(i=0;i<sizeof(buffer);i++)
	{
		printf("%c ",buffer[i]);
		if(i%64==0&&i!=0)
			cout << endl;
		if(i == 127)
			cout << endl;
	}
	//printf("%c %c\n",px->score,px->age);
	//printf("%c %c\n",py->a,py->b);
}