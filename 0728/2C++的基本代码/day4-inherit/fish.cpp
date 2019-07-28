#include "fish.h"

Fish::Fish()
{ //默认调用父类的构造函数
     this->gill = 0;
     cout << "Fish constructor"<<endl;
}

Fish::Fish(int w, int s):Animals(w, s)
{//显示调用父类的构造函数完成父类成员初始化
    //this->weight = w;
    //this->size = s;
    this->gill = 0;
    cout << "Fish constructor2"<<endl;
}

Fish::Fish(int w, int s, int g)
    :Animals(w,s),gill(g)  //参数列表
{//派生类扩展了新的属性
    // Animals()
    // this->gill = g;
    cout << "Fish constructor3"<<endl;
}
#if 1
void  Fish::move()
{//派生类同名覆盖基类的成员函数
    cout << "swimming" << endl;
}
#endif
void  Fish::swim()
{//派生类的扩展行为
    cout << "swimming" << endl;
}


Fish::~Fish()
{
    cout << "Fish destructor"<<endl;
}

void fish_test1()
{
    //Animals a1;
    //a1.show();
    Fish  f1; // 定义f1 调用Fish构造函数
    //f1.show(); //同名覆盖之前， "move"
    //f1.move();
    // 派生类和基类的构造函数、析构函数执行顺序
    Fish  f2(5,10);
}
void fish_test2()
{
    Fish f3(5,5,1);
    f3.move();  //同名覆盖之后 "swimming"
    f3.swim();
    f3.Animals::move(); //类名限定符
    f3.Fish::move();
}








