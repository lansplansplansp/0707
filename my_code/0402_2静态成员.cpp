#include <iostream>

using namespace std;

class Point
{
public:
	Point();
//private:静态成员必须时共有成员
	static int cnt;
};

Point::Point()
{
	cnt++;
}

int Point::cnt = 0;

int main()
{
	Point p1;
	Point p2;
	cout << Point::cnt << endl;
	return 0;
}