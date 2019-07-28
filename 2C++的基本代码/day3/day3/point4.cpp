 #include "point4.h"
#include <iostream>
using namespace std;
//初始化,在初始化时不受访问权限限制(私有公有限制)
int Point4::count = 0;

Point4::Point4()
{
    this->x = 0;
    this->y = 0;
    this->count++;
    cout<<__FUNCTION__<<":"<<12<<endl;
}
Point4::~Point4()
{
    this->count--;
    cout<<__FUNCTION__<<":"<<17<<endl;
}
void Point4::showcount()
{
    cout<<"count:"<<this->count<<endl;
    cout<<__FUNCTION__<<":"<<22<<endl;
}


void  Point4::staticcount()
{
    //可以访问类的静态成员
    cout<<"count:"<<count<<endl;
    //不能访问非静态成员
    //cout<<this->x<<this->y<<endl;
    cout<<__FUNCTION__<<":"<<32<<endl;
}

void point4_test1()
{
    Point4 p1;
    Point4::staticcount();
    //p1.staticcount();
    //p1.showcount();
    Point4 p2;
    Point4::staticcount();
    //p1.showcount();
    //p2.showcount();
    Point4 *p3 = new Point4();
    Point4::staticcount();
    //p3->showcount();
    delete p3;
    //p2.showcount();
    Point4::staticcount();
}



void Point4::show()
{
    //this->x++;
    //this->y++;
    cout<<"("<<this->x<<","
       <<this->y<<")"<<endl;
    cout<<__FUNCTION__<<":"<<61<<endl;
}

void Point4::show2() const
{//如果对函数声明const，
 //不能在函数内对任何数据作修改
    //this->x++;
    //this->y++;
    cout<<"("<<this->x<<","
       <<this->y<<")"<<endl;
    cout<<__FUNCTION__<<":"<<71<<endl;
}

void point4_test2()
{
    Point4 p1(1,1);
    Point4 p2(2,2);

    const Point4 p3(3,3);
    p3.show2();//const变量只能const函数输出；
    //p2 = p1; //运算符重载
    //p3 = p1;//常量不能赋值；
    Point4 &rp4 = p2;
    p2.show2();//一般变量也可以访问const函数；
    rp4 = p1;  //p2=p1
    p2.show();
    const Point4 &rp5 = p2;
   // rp5 = p1;   //rp5是常引用//有错误
    p2 = p1;      //p2仍然是变量

}

