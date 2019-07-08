#include <iostream>

using namespace std;
//行不通
Point *pp = NULL;

class	Point
{
public:
	Point();
	Point(int x,int y);
	static Point* createNew();
	Point operator+(const Point &obj);
	Point operator-(const Point &obj);
	Point operator=(const Point &obj);
	Point operator++();
	Point operator++(int);
	friend ostream& operator << (ostream &cout, const Point &obj);
	friend istream& operator >> (istream &cin, Point &obj);
private:
	int x;
	int y;
};
Point* Point::createNew()
{
	return new Point();
}
Point::Point():x(0),y(0){}

Point::Point(int x,int y)
{
	this->x = x;
	this->y = y;
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

void fun()
{
	
}

int main()
{	
	pp = (Point *)Point::createNew();
	Point p1(2,3);
	Point p2(1,3);
	Point p3 = p2;
	Point p4;
	p4 = p1;
	pp = p1;
	cout << "pp: " << pp << endl;
	cout << p4 << endl;
	cout << p3 << endl;
	cout << p1+p2 << endl;
	Point p5;
	cin >> p5;
	cout << p5 << endl;
	return 0;
}