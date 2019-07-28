// add an element to the front of the list
#include <iostream>
#include <list>
#include <iomanip>
#include <string>
using namespace std;
template <class T>
class Name
{
 public:
     Name(T f, T l) : first(f), last(l) {}
     void print()
     {
         cout.setf(ios::left);
         cout << setw(15) << first.c_str()
         << last << endl;
     }
 private:
     T first, last;
};
//==========================================
int main ()
{
     typedef Name<string> N;
     typedef list<N> D;
     D l;
     D::iterator It;
     N n1(string("Albert"),string("Johnson"));
     N n2("Lana","Vinokur");
     l.push_front(n1);
     l.push_front(n2);
     // unnamed object
     l.push_front(N("Linda","Bain"));
     It = l.begin();
     while ( It != l.end() )
        (It++)->print();//只有该printf()能找到定义
     cout << endl;
     return 0;
}
