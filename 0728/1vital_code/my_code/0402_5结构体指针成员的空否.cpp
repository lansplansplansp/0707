#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct STU
{
	short age;
	int score;
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
	stu_t a;
	list_t b;
	a.next = b.PP;
	if(NULL != a.next)
	{
		cout << "a.next is OK !" << endl;
		cout << a.next << endl;
	}
	return 0;
}
//a.next is OK !