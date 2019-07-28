#ifndef BIRD_H
#define BIRD_H
#include <iostream>
using namespace std;
#include "animals.h"
//单继承
class Bird : virtual public Animals
{
public:
    Bird();
    Bird(int w, int s);
    Bird(int w, int s, int wing);
    ~Bird();
    void move();
    void fly();
private:
    int wing;
};

#endif // BIRD_H
