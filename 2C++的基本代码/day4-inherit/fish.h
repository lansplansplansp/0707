#ifndef FISH_H
#define FISH_H
#include "animals.h"
//单继承
class Fish : virtual public Animals
{
public:
    Fish();
    Fish(int w, int s);
    Fish(int w, int s, int g);
    ~Fish();
    void move(); //同名覆盖override
    void swim();
    // move();
    // int weight
    // int size
private:
    int gill;//鱼鳃
};

void fish_test1();
void fish_test2();

#endif // FISH_H
