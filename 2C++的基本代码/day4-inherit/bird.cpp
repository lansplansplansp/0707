#include "bird.h"

Bird::Bird()
{
    this->wing = 0;
    cout << "Bird constructor1"<<endl;
}
Bird::Bird(int w, int s)
    :Animals(w, s)
{
    this->wing = 0;
    cout << "Bird constructor2"<<endl;
}
Bird::Bird(int w, int s, int wing)
    :Animals(w,s), wing(wing)
{
    cout << "Bird constructor3"<<endl;
}
Bird::~Bird()
{
    cout << "Bird destructor"<<endl;
}

void Bird::move()
{
    cout << "flying"<<endl;
}
void Bird::fly()
{
    cout << "flying"<<endl;
}


