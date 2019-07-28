#include <iostream>
#include <deque>
#include <string>
#include <iterator>
using namespace std;
template <class T>
class Name
{
 public:
 Name(T t) : name(t) {}
     void print()
     {
        cout << name << " ";
     }
 private:
     T name;
};
//=============================
int main ()
{
     typedef Name<string> N;
     typedef deque<N> D;
     D d;
     D::iterator It;
     N n1("Robert");
     N n2("Alex");
     d.push_back(n1);
     d.push_back(n2);
     // unnamed object of the type Name
     d.push_back(N("Linda"));
     It = d.begin();
     while ( It != d.end() )
        (It++)->print();
     cout << endl;
     return 0;
}
