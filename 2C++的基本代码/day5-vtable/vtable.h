#ifndef VTABLE1_H
#define VTABLE1_H

#include <iostream>
using namespace std;

class Base{
public:
    virtual void f()
    {
        cout << "Base::f" <<endl;
    }
    virtual void g()
    {
        cout << "Base::g" <<endl;
    }
    virtual void h()
    {
        cout << "Base::h" <<endl;
    }
};

class Derive : public Base{
public:
    virtual void f1()
    {
        cout << "Base::f1" <<endl;
    }
    virtual void g1()
    {
        cout << "Base::g1" <<endl;
    }
    virtual void h1()
    {
        cout << "Base::h1" <<endl;
    }
};
typedef void (*Func)(void);

void test_Base_vTable();
void test_Derive_vTable();
void test_Derive1_vTable();

#endif // VTABLE_H
