#include <iostream>
#include <stdio.h>

using namespace std;

typedef enum weak
{
	SUN,//0
	MON = 2,
	TUE,
	WEN,
	THI,
	FRI,
	SAT,//6
}weak_t;

enum DIN//DIR
{
    EAST=100,
    WEST,
    SOUTH,
    NORTH	 //103
};

int main()
{
	printf("%d\n",TUE);//3
	cout << SUN << endl;//0
	cout << MON << endl;//2
	cout << EAST << endl;//100
	cout << NORTH << endl;//103
	return 0;
}
//最后一个成员有没有逗号结尾都行