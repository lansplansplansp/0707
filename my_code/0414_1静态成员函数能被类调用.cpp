#include <iostream>
#include <stdio.h>

using namespace std;

class	Point
{
public:
	Point();
	Point(int x,int y);
	Point operator+(const Point &obj);
	Point operator-(const Point &obj);
	Point operator=(const Point &obj);
	Point operator++();
	Point operator++(int);
	friend ostream& operator << (ostream &cout, const Point &obj);
	friend istream& operator >> (istream &cin, Point &obj);
	
	static void staticcount();
private:
	int x;
	int y;
	static int count;
};

Point::Point():x(0),y(0)
{
	count++;
}

Point::Point(int x,int y)
{
	this->x = x;
	this->y = y;
	count++;
}

Point Point::operator+(const Point &obj)
{
	int xx = this->x+obj.x;
	int yy = this->y+obj.y;
	Point p(xx,yy);
	return p;
}

Point Point::operator-(const Point &obj)
{
	int xx = this->x-obj.x;
	int yy = this->y-obj.y;
	Point p(xx,yy);
	return p;
}

Point Point::operator=(const Point &obj)
{
	this->x = obj.x;
	this->y = obj.y;
	return *this;
}

ostream& operator << (ostream &cout,const Point &obj)
{
	cout << "(" << obj.x << "," << obj.y << ')';
	return cout;
}

istream& operator >> (istream &cin, Point &obj)
{
	cin >> obj.x >> obj.y;
	return cin;
}

void  Point::staticcount()
{
    cout<<"count:"<<count<<endl;
    cout<<__FUNCTION__<<":"<<32<<endl;
}

int Point::count = 0;

int main()
{
	int a = 28;
	float b = 28.0;
	if(a == b)
		printf("a b is equal!\n");
	else
		printf("a b is not equal!\n");
	float c = 12.3456;
	cout << c << endl;
	cout << (int)(c*1000) << endl;

	cout << ((int)(c*1000))/1000.0 << endl;
	Point p1(2,3);
	Point p2(1,3);
	Point p3 = p2;
	Point p4;
	Point::staticcount();
	p4.staticcount();//静态成员函数能被类对象访问
	p4 = p1;
	cout << p4 << endl;
	cout << p3 << endl;
	cout << p1+p2 << endl;
	Point p5;
	cin >> p5;
	cout << p5 << endl;
	return 0;
}