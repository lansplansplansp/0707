// returns a reverse iterator to the beginning of the list
#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <set>
#include <iomanip>
#include <string>
#include <map>
#include <deque>
using namespace std;
template <class T>
class Member
{
 public:
     Member(T l, T f) : last(l), first(f) {}
     void print() const // const !!!
     {
         cout.setf(ios::left);
         cout << setw(15) << first.c_str() << last << endl;
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
template<class T>
class ID
{
public:
    ID(T t, T n) : id(t), name(n) {}
    void print ()
    {
        cout.setf(ios::left);
        cout << setw(15) << name.c_str()
        << id << endl;
        cout.unsetf(ios::left);
    }
private:
    T id, name;
};
//======================================
int main ()
{
//     list<int> l(10);
//     iota(l.begin(),l.end(),1);//指定初始值自增函数
//     copy(l.begin(),l.end(),ostream_iterator<int>(cout," "));//拷贝自增数组到容器ostream_iterator
//     cout << endl;
//     list<int>::reverse_iterator It = l.rbegin();
//     while ( It != l.rend() )
//        cout << *(It++) << " ";
//     cout << endl;
//     return 0;
//     typedef Member<string> M;
//     typedef set<M, less<M> > S;
//     M m("Frost","Robert");
//     S s;
//     s.insert(m);
//     s.insert(M("Smith","John"));
//     s.insert(M("Amstrong","Bill"));
//     s.insert(M("Bain","Linda"));
//     S::iterator It = s.begin();
//     while ( It != s.end() )
//     (It++)->print();
//     cout << endl;
//     S::reverse_iterator rI = s.rbegin();
//     while ( rI != s.rend() )
//      (rI++)->print();
//     return 0;
//     typedef ID<string> Id;
//     typedef map<int, Id> M;
//     typedef M::value_type v_t;
//     M m;
//     m.insert(v_t(1,Id("000123","Shevchenko")));
//     m.insert(v_t(2,Id("000124","Pushkin")));
//     m.insert(v_t(3,Id("000125","Shakespeare")));
//     // same key
//     m.insert(v_t(3,Id("000126","Smith")));
//     M::reverse_iterator It = m.rbegin();
//     while ( It != m.rend() )
//     {
//         cout.setf(ios::left);
//         cout << setw(3) << (*It).first;
//         It->second.print();
//         It++;
//     }
//    return 0;
    typedef ID<string> Id;
    typedef multimap<int, Id> M;
    typedef M::value_type v_t;
    M m;
    m.insert(v_t(1,Id("000123","Shevchenko")));
    m.insert(v_t(2,Id("000124","Pushkin")));
    m.insert(v_t(3,Id("000125","Shakespeare")));
    // same key
    m.insert(v_t(3,Id("000126","Smith")));
    M::reverse_iterator It = m.rbegin();
    while ( It != m.rend() )
    {
        cout.setf(ios::left);
        cout << setw(3) << (*It).first;
        It->second.print();
        It++;
    }
    return 0;
}
