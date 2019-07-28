#include <iostream>
#include "animals.h"
#include "fish.h"
#include "kunpeng.h"
using namespace std;
//空类
class A
{
};
// 基类  父类
class  Base
{
public:
    int x;
protected:
    int y;
private:
    int z;
};
// 派生类  子类   --继承
class Derive1 : public Base
{
    /*
public:
    int x;
protected:
    int y;
private:
    int z;
    */
    void show();
};

class Derive2 : protected  Base
{
    void show();
};
class Derive3 : private  Base
{
    void show();
};
#if 1
void Derive1::show()
{
    //公有成员：类外可见、类内可见、派生类可见
    this->x = 10; // 可以
    //保护成员：类外不可见、类内可见、派生类可见
    this->y = 10; // 可以
    //私有成员：类外不可见、类内可见，派生类不可见
    //this->z = 10;  //不可以
}
#endif


int main(int argc, char *argv[])
{
#if 0
    //fish_test1();
    //fish_test2();
    //Kunpeng_test1();
    //Kunpeng_test2();
    Kunpeng_test3();
#endif

#if 0
    //类外
    Base b;
    b.x = 10; //可以
    //b.y = 10;  //不可以
    //b.z = 10;  //不可以
    Derive1 d1; //公有继承
    d1.x = 20; //公有 可以
    //d1.y = 20; //保护 不可以
    //d1.z = 20; //私有 不可以
    Derive2 d2; //保护继承
    //d2.x = 20; //保护 不可以
    //d2.y = 20; //保护 不可以
    //d2.z = 20; //私有  不可以
    Derive3 d3; //私有 继承
    //d2.x = 20; //私有 不可以
    //d2.y = 20; //私有 不可以
    //d2.z = 20; //私有  不可以
#endif

#if 1
    A a;
    Base  b;
    Derive1 d;
//    E e;
    cout << sizeof(a)<< endl
         << sizeof(b) << endl
         << sizeof(d) << endl;
//         << sizeof(e) << endl;
#endif
    return 0;
}


#if 0
class E : private Base
{
    /*
private:
    int x;
private:
    int y;
private:  //父类私有
    int z;
    */
public:
    int a;
protected:
    int b;
private:
    int c;  //自己私有

#if 0
    void show()
    {

    }
 #endif
};
class F : protected Base
{
    /*
protected:
    int x;
protected:
    int y;
private:  //父类私有
    int z;
    */
public:
    int a;
protected:
    int b;
private:
    int c;  //自己私有
    void show()
    {

    }
};

int test()
{

}

#endif
