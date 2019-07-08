#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

bool OpenView(void *)
{
	return 0;
}

typedef struct STU
{
	short age;
	int score;
	char name[20];
	void *next;
}stu_t;

typedef struct List
{
	int x;
	int y;
	void *PP;
}list_t;

int main()
{
	stu_t *ss = (stu_t *)malloc(sizeof(stu_t));
	//ss->name[20] = "lansp";类型不匹配
	strcpy(ss->name,"lansp");
	cout << strlen(ss->name) << endl;
	return 0;
}
