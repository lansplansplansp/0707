#include "animals.h"

Animals::Animals()
{
    weight = 5;
    size = 10;
    cout << "Animals constructor"<<endl;
}
Animals::Animals(int w, int s)
{
    weight = w;
    size = s;
    cout << "Animals constructor2"<<endl;
}
Animals::~Animals()
{
    cout << "Animals destructor"<<endl;
}



void Animals::show() const
{
    cout << "weight:"<<weight<<endl
         << "size:"<<size<<endl;
}
