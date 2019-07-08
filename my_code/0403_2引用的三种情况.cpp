#include <iostream>
//还没实现
using namespace std;

class Point 
{
public:
	Point()
	{
		x = 0;
		y = 0;
		++count;
		cout << "在构造函数" << endl; //一次
	}
	int print()
	{
		cout << x << ' ' << y << endl;
	}
	Point(const Point &obj);
	static int count;
private:
	int x;
	int y;
};

Point::Point(const Point &obj)
{
	this->x = obj.x;
	this->y = obj.y;
	++count;
}

Point movepoint1(Point obj)
{//传入一般对象
    return obj;//返回时有个临时对象
}
Point movepoint2(Point &obj)
{//传入对象引用
    return obj;//返回时有个临时对象
}
Point& movepoint3(Point &obj)
{//传入对象引用
    return obj;//返回对象的引用
}
int Point::count = 0;
int main()
{
	Point p1;
	cout << Point::count << endl;//1次构造
	Point p2 = movepoint1(p1);
	cout << Point::count << endl;//2次构造
	Point p3 = movepoint2(p1);
	cout << Point::count << endl;//1次构造
	Point p4 = movepoint3(p1);
	cout << Point::count << endl;//1次构造
	
	return 0;
}