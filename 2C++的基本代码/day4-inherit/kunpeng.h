#ifndef KUNPENG_H
#define KUNPENG_H
#include "fish.h"
#include "bird.h"
// 虚继承
class Kunpeng : virtual public Fish,
        virtual public Bird
{
public:
    Kunpeng();
    Kunpeng(int w, int s, int gill ,
            int wing, int status);
    void move();
private:
    int status;
};

void Kunpeng_test1();
void Kunpeng_test2(); //虚类继承测试例子
void Kunpeng_test3(); //虚函数继承测试例子
#endif // KUNPENG_H
