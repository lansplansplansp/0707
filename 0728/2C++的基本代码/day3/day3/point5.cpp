#include "point5.h"
#include <iostream>
using namespace std;

int Point5::count = 0;

Point5::Point5():x(0),y(0)//对象不是两个参数走的函数
{
    this->count++;
    cout<<__FUNCTION__<<":"<<10<<endl;
}
Point5::~Point5()
{
    this->count--;
    cout<<__FUNCTION__<<":"<<15<<endl;
}
Point5::Point5(int x, int y)//对象是两个参数走的函数
{
    this->x = x;
    this->y = y;
    this->count++;
    cout<<__FUNCTION__<<":"<<22<<endl;
}
Point5::Point5(const Point5 &obj)
{//深浅拷贝
    this->x = obj.x;
    this->y = obj.y;
    this->count++; //深拷贝//不单只有的属性才要深拷贝；
    cout<<__FUNCTION__<<":"<<29<<endl;
}
//静态成员函数，没有this指针
void Point5::showCount()
{
    cout<<"current objects:"
       <<count<<endl;
    //静态成员函数不能访问非静态成员
    //cout<<x<<endl;  error
}
void Point5::show() const
{
    cout<<"("<<this->x<<","
       <<this->y<<")"<<endl;
    //非静态成员函数可以访问静态成员
    //cout<<count<<endl;  ok
}

void Point5_test1()
{
    //观察对象个数
    Point5::showCount();
    Point5 p1(4,4);
    Point5 p2 = p1; //Point5 p2(p1);//深拷贝命令；
    Point5::showCount();
    p1.show();
    p2.show();
    //cout<<p1<<endl  运算符重载
    //   <<p2<<endl;
    #if 0
    Point5 p3;
    p3 = p1+p2;  // + 有没有含义
            //符号相同、含义不同
    int x=5;
    int y=6;
    int z = x+y;
    #endif
}


Point5 Point5::operator +(const Point5 &obj)
{
    cout<<__FUNCTION__<<":"<<71<<endl;
    int xx = this->x + obj.x;
    int yy = this->y + obj.y;
    Point5 newPoint(xx, yy);
    return newPoint;//法1
    //return Point5(xx, yy);//法2
}
Point5 Point5::operator-(const Point5 &obj)
{
    cout<<__FUNCTION__<<":"<<79<<endl;
    int xx = this->x - obj.x;
    int yy = this->y - obj.y;
    Point5 newPoint(xx, yy);
    return newPoint;
}
Point5 Point5::operator =(const Point5 &obj)
{
    cout<<__FUNCTION__<<":"<<88<<endl;
    this->x = obj.x ;
    this->y = obj.y ;
    return *this;
}
Point5 Point5::operator +=(const Point5 &obj)
{
    cout<<__FUNCTION__<<":"<<95<<endl;
    this->x = this->x + obj.x;
    this->y = this->y + obj.y;//法1
    //*this = *this + obj;//法2
    return *this;
}
Point5 Point5::operator++()//前置，先加后用
{
    cout<<__FUNCTION__<<":"<<103<<endl;
    this->x++;
    this->y++;
    return *this; //调用拷贝构造函数
}
Point5 Point5::operator++(int)//后置，先用后加
{
    cout<<__FUNCTION__<<":"<<110<<endl;
    Point5 temp = *this;
    this->x++;
    this->y++;
    return temp;
}


void Point5_test2()
{
#if 1
    Point5 p1(5,5);
    Point5 p2;
    p2 = p1;//写标准的，用返回值，可以用if语句判断
    p2.show();
    p1.show();
#endif
#if 0
    Point5 p1(1,1);
    Point5 p2(2,2);
    Point5 p3 = p1+p2;
    p3.show();
#endif
}

//类外函数-友元--打破了类的封装性
void outershow(const Point5 &obj)
{
    cout<<"("<<obj.x<<","
       <<obj.y<<")"<<endl;
}



//  cout << obj --类的友元，可以访问类的私有成员
ostream& operator <<(ostream &cout,const Point5 &obj)
{
    cout<<"("<<obj.x<<","<<obj.y<<")"<<endl;
    return cout;
}
// cin >> obj
istream& operator >>(istream &cin,Point5 &obj)
{
    cin>>obj.x>>obj.y;
    return cin;
}

void Point5_test3()
{
    Point5 p1(5,5);
    Point5 p2(10,10);
    p1.show();  //用类内函数输出坐标点
    outershow(p1); //使用友元函数来输出
    cout<<p1;      //使用运算符重载来输出
    //cout<<p2;
    //cout<<p1<  ==> cout<<p2;
    cout<<p1<<p2;//返回引用的效果

    Point5 p3;
    cin>>p3;
    cout<<p3;
}












