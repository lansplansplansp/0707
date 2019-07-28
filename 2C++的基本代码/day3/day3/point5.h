#ifndef POINT5_H
#define POINT5_H
#include <iostream>
using namespace std;
class Point5
{
public:
    //默认的构造函数，初始化
    Point5();
    Point5(int x, int y);
    Point5(const Point5 &obj);
    ~Point5(); //析构，销毁
    static void showCount();
    void show() const;
    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;

    //运算符重载
    Point5 operator+(const Point5 &obj);
    Point5 operator-(const Point5 &obj);
    Point5 operator =(const Point5 &obj);
    Point5 operator +=(const Point5 &obj);
    Point5 operator++();//前置，先加后用
    Point5 operator++(int);//后置，先用后加
    //友元函数：类外函数、类的朋友
    friend void outershow(const Point5 &obj);//show的优化版；
    //  cout << obj
    friend ostream& operator <<(ostream &cout,
                          const Point5 &obj);//cout函数：以后都用它吧，因为：cout<<p1<<p2;
    // cin >> obj
    friend istream& operator >>(istream &cin,
                           Point5 &obj);

private:
    int x, y;
    //静态成员变量
    static int count;
};
// 类外函数
void Point5_test1();
void Point5_test2();
void Point5_test3();

#if 0
    Point5 p1;
    Point5 p2 = p1; //拷贝构造函数
    {const Point5 &obj = p1;
    this = &p2}

    p1+p2;
    {const Point5 &obj = p2;
    this = &p1}

    p2+p1;
    {const Point5 &obj = p1;
    this = &p2}

    int x=5;
    int y=6;
    int z = x+y;

#endif



#endif // POINT5_H
