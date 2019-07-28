#ifndef POINT3_H
#define POINT3_H


class Point3
{
public:
    Point3();
    //Point3(Point3 &);
    ~Point3();  //析构函数，对象销毁自动调用
    void show();
    Point3(const Point3 &obj);
    void testThisPoint();
private:
    int *px;
    int *py;
};

void point3_test1();
void point3_test2();

#endif // POINT3_H
