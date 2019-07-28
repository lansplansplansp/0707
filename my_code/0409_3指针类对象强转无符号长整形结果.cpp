#include <iostream>
#include <stdio.h>

using namespace std;

class Point
{
public:
	Point();
	~Point();
private:
	int x;
};

Point::Point()
{}

int main()
{
	Point *p1 = new Point();
	Point *p2 = NULL;
	cout << (unsigned long)p2 << endl;
	printf("p1地址：%p\n",p1);
	printf("p1：%d\n",(unsigned long)p1);
	return 0;
}

//p2 = 0
//p1地址：0x150d010
//p1：22073360(十六进制数就是150d010)