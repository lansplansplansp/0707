// sorts with user datatype
#include <iostream>
#include <iomanip>
#include <list>
#include <string>
using namespace std;
template <class T>
class Member
{
 public:
     Member(T f, T l) :
     first_n(f), last_n(l) {}
     void print();
 private:
     string last_n, first_n;
     // for sort() list member function
     friend bool operator < (Member& m1,
     Member& m2)
     { return m1.last_n < m2.last_n; }//会逐个字母比较
};
//---------------------------------------
template <class T>
void Member<T>::print()
{
     cout.setf(ios::left);
     cout << setw(15) << last_n.c_str()
     << first_n << endl;
}
typedef Member<string> M;
//========================================
int main ()
{
     list<M> li;
     li.push_back(M("Linda","Smith"));
     li.push_back(M("Arost","Robert"));
     li.push_back(M("Alex","Amstrong"));
     cout << "Before sorting by last name:\n"
     << "============================"
     << endl;
     list<M>::iterator It = li.begin();
     while ( It != li.end() )
     {
        (It++)->print();
     }
     cout << endl;
     li.sort();
     cout << "After sorting by last name:\n"
     << "============================"
     << endl;
     It = li.begin();
     while ( It != li.end() )
     {
         (It++)->print();
     }
     return 0;
 }
