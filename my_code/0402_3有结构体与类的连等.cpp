#include <iostream>

using namespace std;

typedef struct STU
{
	int age;
	int num;
}stu_t;

class Point
{
public:
	Point();
	int test();
private:
	int x;
};

Point::Point():x(0)
{
	
}
int Point::test()
{
	//return this->x = 11;
	return x = 10;
}
int main()
{
	stu_t z;
	Point p;
	z.num = z.age = p.test();
	cout << z.num <<endl;
	cout << z.age <<endl;
	cout << p.test() <<endl;
	
	return 0;
}