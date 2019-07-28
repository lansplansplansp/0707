//returns the function that compares keys
#include <iostream>
#include <set>
    //#include <map>
using namespace std ;
template <class T>
void truefalse(T& t)
{
    cout << (t?"True":"False") << endl;
}
int main ()
{
    set<int> s;//这个要干啥呢
    cout << "s.key_comp()(1,2) returned ";
    truefalse(s.key_comp()(1,2)); // True
    cout << "s.key_comp()(2,1) returned ";
    truefalse(s.key_comp()(2,1)); // False
    cout << "s.key_comp()(1,1) returned ";
    truefalse(s.key_comp()(1,1)); // False
    return 0;
}
