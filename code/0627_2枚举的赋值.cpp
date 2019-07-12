#include <stdio.h>
#include <iostream>

using namespace std;

typedef enum _NUM
{
	one = 0x1,//分号报错
	two = 0x2,
	three = 0x3,
	four = 0x4,
	five = 0x6,
	eleven = 0xb,
}num_t;

int main()
{
	cout << one << endl;
	cout << two << endl;
	cout << eleven << endl;
	printf("%x\n",eleven);//b
	printf("0x%x\n",eleven);//0xb
	
	return 0;
}