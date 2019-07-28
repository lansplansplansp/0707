//派生类继承虚基类很多时候不用重写的，重写的情况：
#include <iostream>

using namespace std;

class Point 
{
public:
	Point()
	{
		x = 5;
		y = 10;
	}
	virtual int print()
	//int print()
	{
		cout << x << ' ' << y << endl;
	}
	virtual void show() = 0;
private:
	int x;
	int y;
};

class derive : virtual public Point
{
public:
	derive()
	{
		x = 10;
		y = 20;
	}
	/*
	int print()//不重写也行
	{
		cout << x << ' ' << y << endl;
	}*/
	void show()//纯虚函数必须重写
	{
		cout << x << ' ' << y << endl;
	}
private:
	int x;
	int y;
};

int main()
{
	Point *p;
	derive a;
	p = &a;
	p->print();
	p->show();
	return 0;
}