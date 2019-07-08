#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct STU
{
	short age;
	int score;
}stu_t;


int main()
{
	stu_t *p;
	stu_t ss = {21,100};
	p = &ss;
	p->age;
	cout << p->age << ' ' << p->score << endl;
	
	return 0;
}
//指针符号正规写法：p->age