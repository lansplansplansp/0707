#include "point.h"
#include <iostream>
using namespace std;
//在定义对象的同时可以完成成员数据的初始化
// 自动调用
// 函数名与类名相同、没有返回值
Point::Point()
{//默认构造函数、无参数
    cout<<"default construtor"<<endl;
}

Point::Point(int x, int y)
{//重载构造函数
    this->x = x; //赋值方法
    this->y = y;
    cout<<"construtor wtih params"<<endl;
}

Point::Point(int x, int y, int flag):
    x(x),y(y),flag(flag)
{ //初始化列表

}

//方法作用在哪一个对象上
void Point::setX(int x)
{   //this指针，哪个对象调用该函数，
    //this指针就指向哪个对象
    this->x = x;
}
void Point::setY(int y)
{
    this->y = y;
}

int Point::getX()
{
    return this->x;
}

int Point::getY()
{
    return this->y;
}

void Point::setXY(int x, int y)
{
    this->x = x;
    this->y = y;
}
// p1.show()  p2.show()
void Point::show()
{//定义时不确定this指向谁
   //调用时才知道this指向谁
    cout<<"("<<this->getX()
       <<","<<this->getY()
      <<")"<<endl;
}
void  point_test1()
{
    //无参构造函数、全是默认参数的构造函数--不能同时出现
    Point p1, p2;
    p1.setXY(3,5);
    p2.setX(6);
    p2.setY(10);
    p1.show();
    p2.show();
    Point p3(10,10);//使用构造函数初始化
    p3.show();

    Point *p4 = new Point();//随机输出大数；
     p4->show();
    Point *p5 = new Point(3,3);
     p5->show();

    Point p6(6);
     p6.show();

#if 0
     //feng zhuang
    cout<<"("<<p1.getX()
       <<","<<p1.getY()
      <<")"<<endl;
#endif
}
