#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct STU
{
	short age;
	int score;
}stu_t;

int main()
{
	stu_t b;
	cout << b.age << ' ' << b.score << endl;
	stu_t a = {0};
	cout << a.age << ' ' << a.score << endl;
	return 0;
}
//a,b结果都是0 0