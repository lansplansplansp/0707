#ifndef POINT2_H
#define POINT2_H
#include <iostream>
using namespace std;
class Point2
{
public:
    Point2()
    {
        cout<<"con1"<<endl;
    }
    Point2(int x, int y):x(x),y(y)//参数列表；
    {
        cout<<"con2"<<endl;
    }
    void show();
    //拷贝构造函数
    Point2(const Point2 &obj);
    int getX(){ return x;}
    int getY(){ return y;}
    void setX(int x){this->x=x;}
    void setY(int y){this->y=y;}

private:
    int x;
    int y;
};

void point2_test1();
//求两点之间的距离
double distance(Point2 p1, Point2 p2);
double distance2(Point2 p1, Point2 p2);
void point2_test2();
void point2_test3();

#endif // POINT2_H
