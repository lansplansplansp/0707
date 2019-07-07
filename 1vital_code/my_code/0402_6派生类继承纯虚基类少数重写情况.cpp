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
	int print(int a)
	{
		cout << a << endl;
		cout << "ded" << endl;
	}
	virtual void show()
	{
		cout << x << ' ' << y << endl;
	}
	virtual void func()=0;
private:
	int x;
	int y;
};

class derive : public Point
{
public:
	derive()
	{
		x = 10;
		y = 20;
	}
	int print(int a)
	{
		cout << a << endl;
		cout << "sun" << endl;
	}/*
	void show()
	{
		cout << x << ' ' << y << endl;
	}*/
	void func()
	{
		cout<<"B(func)"<<endl;
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
	//p->print(3.14);
	a.print(1);
	a.show();
	p->show();
	p->func();
	return 0;
}