#include "point3.h"
#include <iostream>
using namespace std;
Point3::Point3()
{
    px = new int(0);
    py = new int(0); //初始化为0
    cout<<__FUNCTION__<<":"<<8<<endl;
}
#if 1
//浅拷贝
Point3::Point3(const Point3 &obj)
{
    this->px = obj.px;
    this->py = obj.py;
    cout<<"copy con"<<endl;
}
#endif
#if 0
//深拷贝
Point3::Point3(const Point3 &obj)
{
    this->px = new int;
    this->py = new int;
    *(this->px) = *(obj.px);
    *(this->py) = *(obj.py);
    cout<<__FUNCTION__<<":"<<26<<endl;
}
#endif
#if 1
Point3::~Point3()
{
    //释放资源
    delete px;
    delete py;
    cout<<__FUNCTION__<<":"<<34<<endl;
}
#endif
void Point3::show()
{
    {//定义时不确定this指向谁
       //调用时才知道this指向谁
        cout<<"("<< *(this->px)
           <<","<<  *(this->py)
          <<")"<<endl;
        cout<<__FUNCTION__<<":"<<43<<endl;
    }
}
void point3_test1()
{//为什么只析构一次
    Point3 p1;
    p1.show();
    //delete p1;
    //调用默认的拷贝构造函数--浅拷贝
    Point3 p2 = p1;//浅拷贝会崩掉
    //delete p2;
    p2.show();

}
void Point3::testThisPoint()
{
    cout << this << endl;
}
void point3_test2()
{
    Point3 p1,p2;
    cout <<"p1:"<<&p1<<endl;
    cout <<"p2:"<<&p2<<endl;
    p1.testThisPoint();
    p2.testThisPoint();//相同说明内部有this指针
}
