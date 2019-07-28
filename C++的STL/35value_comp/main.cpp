//returns the function that compares values
#include <iostream>
#include <set>
//#include <map>
using namespace std ;
template <class T>
void truefalse(T & t)
{
    cout << (t?"True":"False") << endl;
}
int main ()
{
     set<int> s;
     cout << "s.value_comp()(1,2) returned ";
     truefalse(s.value_comp()(1,2)); // True
     cout << "s.value_comp()(2,1) returned ";
     truefalse(s.value_comp()(2,1)); // False
     cout << "s.value_comp()(1,1) returned ";
     truefalse(s.value_comp()(1,1)); // False
     return 0;
}
