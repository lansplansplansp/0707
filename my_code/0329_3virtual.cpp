#include<iostream>
using namespace std;
class Base {
public:
    Base() {};
    virtual ~Base() { cout << "Output from the destructor of class Base!" << endl; };
    virtual void DoSomething() { cout << "Do something in class Base!" << endl; };
};

class Derived : public Base {
public:
    Derived() {};
    ~Derived() { cout << "Output from the destructor of class Derived!" << endl; };
    void DoSomething() { cout << "Do something in class Derived!" << endl; };
};

int main() {
    Base *p = new Derived;
    p->DoSomething();
    delete p;
    return 0;
}