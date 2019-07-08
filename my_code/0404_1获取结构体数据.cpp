#include <iostream>
#include <string>

using namespace std;

typedef struct STU
{
	char sex;
	int score;
	string name;
}stu_t;

int main()
{
	int a;
	stu_t *s;
	stu_t b = {'F',100,"lan"};
	s = &b;
	a = s->score;
	cout << (int *)(s->score) << endl;
	while(1)
	{
		sleep(6);
	}
	cout << a << endl;
	return 0;
}