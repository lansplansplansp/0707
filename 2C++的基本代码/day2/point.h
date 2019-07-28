#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point();    //构造函数:作用：初始化；
    Point(int x, int y=4);//x不能=常数了，因为在一个类中定义了全部是默认参数的构造函数后，不能再定义重载构造函数。
    Point(int x, int y, int flag);
#if 1
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
#endif
#if 1
    void setXY(int x, int y);
#endif
    void show();
private:
    int x;
    int y;
    int flag;
};


void  point_test1();

#endif // POINT_H
