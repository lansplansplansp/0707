// the number the elements in the list
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <iomanip>
#include <string>
using namespace std;
void print (set<int, less<int> >& s)
{
     set<int, less<int> >::iterator It;
     for ( It = s.begin(); It != s.end(); It++ )
     cout << *It << " ";
     cout << endl;
}
//--------------------------------------------
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
//     int ary[] = {1,2,3,2,3,4,8,2,5,6};
//     set<int, less<int> > s;
//     s.insert(ary,ary+10);
//     print(s);
//     cout << "Size of set s = " << s.size() << endl;
//     s.clear();
//     cout << "Size of set s = " << s.size() << endl;
//     return 0;
//     typedef ID<string> Id;
//     typedef multimap<int, Id> M;
//     typedef M::value_type v_t;
//     M m;
//     m.insert(v_t(1,Id("000123","Shevchenko")));
//     m.insert(v_t(2,Id("000124","Pushkin")));
//     m.insert(v_t(3,Id("000125","Shakespeare")));
//     // same key
//     m.insert(v_t(3,Id("000126","Smith")));
//     cout << "size of multimap 'm' = "
//     << m.size() << endl;
//     M::iterator It = m.begin();
//     while ( It != m.end() )
//     {
//         cout.setf(ios::left);
//         cout << setw(3) << (*It).first;//输出1   2   3   4
//         It->second.print();//输出printf()函数的内容
//         It++;
//     }
//     return 0;
}
