#include "kunpeng.h"

Kunpeng::Kunpeng()
{
    this->status = 1;
    cout << "kunpeng constructor"<<endl;
}
//同名覆盖
void Kunpeng::move()
{
    if(status) // kun
        cout << "swimming" << endl;
    else
        cout << "flying" << endl;
}

void Kunpeng_test1()
{
    // Fish:weight,size,gill
    // Bird:weight,size,wing
    Kunpeng k1;//24
    cout << sizeof(k1)<<endl;

    //k1.move();
    //Fish:move
    //Fish::Animals::move
    //Bird:move
    //Bird::Animals::move

    //类名限定符
    k1.Fish::move();
    k1.Bird::move();
    // 菱形继承：通过类名限定符，解决不了最基类的二义性
    //k1.Animals::move();
    //解决二义性
    k1.move();//法1：同名覆盖；法2：虚继承、虚基类

}

void Kunpeng_test2()
{
    // Animal::weight,size
    // Fish::gill
    // Bird::wing
    // Kunpeng:status
    // 隐含三个指针
    Kunpeng k2;  //32
    cout << sizeof(k2)<<endl;

    k2.move(); //Keng::move
    k2.Fish::move(); //Fish::move
    k2.Bird::move();
    k2.Animals::move(); //只能虚继承实现
}
void Kunpeng_test3()
{//父类指针可以指向派生类，子类指针不可以指向父类，因为父类基本，只有基本指针可以指向更多
    //应用虚函数才能实现指向不同move
    Animals *p;
    Animals a;
    Fish f;
    Bird b;
    Kunpeng k;
    p = &a;
    a.move();
    p = &f;
    f.move();
    p = &b;
    b.move();
    p = &k;
    k.move();
    cout<<"first!"<<endl;

}












