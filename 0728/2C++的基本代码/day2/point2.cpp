#include "point2.h"
#include <iostream>
#include <math.h>
using namespace std;

//有个一个默认的构造函数//系统给自动罗列出来的，不要删，删了会怎样？
// Point()  --可以把它重写覆盖
//还有一个默认的拷贝构造函数
Point2::Point2(const Point2 &obj)
{
    this->x = obj.x;
    this->y = obj.y;
    cout << "copy  construtor"<<endl;
}
void point2_test1()
{
    Point2 p1(5,5);
    Point2 p2 = p1; //定义对象的同时进行初始化
        // p2.x = p1.x
        // p2.y = p2.y
    Point2 p3(p2); //调用拷贝构造函数
    Point2 p4;  //先定义对象（默认构造函数）
    p4 = p2;    //对象赋值--运算符重载
    p1.show();
    p2.show();
}

void Point2::show()
{//定义时不确定this指向谁
   //调用时才知道this指向谁
    cout<<"("<<this->x
       <<","<<this->y
      <<")"<<endl;
}
//对象作为参数--通过拷贝构造函数完成值拷贝
double distance(Point2 p1, Point2 p2)
{
     int x1=p1.getX();
     int y1=p1.getY();
     int y2=p2.getY();
     int x2=p2.getX();
     return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    //(p1.x-p2.x)*(p1.x-p2.x) +

}
//对象作为参数--通过拷贝构造函数完成值拷贝
double distance2(Point2 &p1, Point2 &p2)
{
    return 0.0;
}

void point2_test2()
{
    Point2 p1(5,5);
    Point2 p2(6,6);
    // distance Point2 p1 =  test2::p1
    cout << distance(p1,p2) <<endl;
}


Point2 movepoint1(Point2 obj)
{//传入一般对象
    obj.setX(obj.getX()+1);
    obj.setY(obj.getY()+1);
    return obj; //返回时有个临时对象
}
Point2 movepoint2(Point2 &obj)
{//传入对象引用
    obj.setX(obj.getX()+1);
    obj.setY(obj.getY()+1);
    return obj; //返回时有个临时对象
}
Point2& movepoint3(Point2 &obj)
{//传入对象引用
    obj.setX(obj.getX()+1);
    obj.setY(obj.getY()+1);
    return obj; //返回对象的引用
}

void point2_test3()
{
    Point2 p1;
    movepoint1(p1);//2次拷贝
    Point2 p2 = movepoint1(p1);//2次
    movepoint2(p1).show();//1次
    movepoint2(p1);//1次
    movepoint3(p1);//0次
}




