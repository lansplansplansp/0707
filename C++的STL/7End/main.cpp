#include <iostream>
#include <deque>
#include <iterator>
#include <numeric>
#include <set>
#include <string>
#include <iomanip>//·ÇÈ«²¿//setw(15)

using namespace std;
template <class T>
class Member
{
public:
     Member(T l, T f) : last(l), first(f) {}
     void print() const // const !!!
     {
          cout.setf(ios::left);
          cout << setw(15) << first.c_str()
          << last << endl;
     }
 private:
      T first, last;
      // const !!!
      friend bool operator < (const Member& m1, const Member& m2)
      {
        return (m1.last < m2.last) ? true : false;
      }
      friend bool operator == (const Member& m1, const Member& m2)
      {
        return (m1.last == m2.last) ? true : false;
      }
};
//===============================================
int main ()
{
//     deque<int> d(5);
//     iota(d.begin(),d.end(),1);
//     deque<int>::iterator It = d.begin();
//     while ( It != d.end() )
//        cout << *It++ << " ";
//     cout << endl;
//     // last element of the deque
//     It = d.end()-1;
//     cout << *It << endl;
//     return 0;
     typedef Member<string> M;
     typedef set<M, less<M> > S;
     M m("Frost","Robert");
     S s;
     s.insert(m);
     s.insert(M("Smith","John"));
     s.insert(M("Amstrong","Bill"));
     s.insert(M("Bain","Linda"));
     S::iterator It = s.begin();
     while ( It != s.end() )
     (It++)->print();
     return 0;
}
