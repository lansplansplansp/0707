#ifndef ANIMALS_H
#define ANIMALS_H
#include <iostream>
using namespace std;
// 动物
class Animals
{
public:
    Animals();
    Animals(int w, int s);
    ~Animals();
    virtual void move()//多态（动态联编，编译前不知）
    {
        cout << "move" << endl;
    }
    void show() const;
private:
    int weight; //重量
    int size;   //体形大小
};

#endif // ANIMALS_H
