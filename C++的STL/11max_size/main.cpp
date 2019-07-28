#include <iostream>
#include <deque>
#include <set>
#include <iterator>
    #include <map>
#include <functional>
using namespace std;
void print (set<int, less<int>> &s)
{
     copy(s.begin(),s.end(),
     ostream_iterator<int>(cout," "));
     cout << endl;
}

int main ()
{
     deque<int> d(10);
     cout << "Size of d = "<< d.size() << endl;
     cout << "Max_size of d = "<< d.max_size() << endl;
     return 0;
//     int ary[] = {1,2,3,2,3,4,8,2,5,6};
//     set<int, less<int> > s;
//     s.insert(ary,ary+10);
//     print(s);
//     cout << "size of set 's' = "
//     << s.size() << endl;
//     cout << "max_size of 's' = "
//     << s.max_size() << endl;
//     return 0;
//     typedef multimap<int, char, greater<int> > M;
//     typedef M::value_type v_t;
//     M m;
//     m.insert(v_t(2,'B'));
//     m.insert(v_t(3,'C'));
//     m.insert(v_t(1,'A'));
//     M::iterator It = m.begin();
//     cout << "m:" << endl;
//     while ( It != m.end() )
//     {
//         cout << (*It).first << " - "
//         << (*It).second
//         << endl;
//         It++;
//     }
//    cout << "size of multimap 'm' "<< m.size() << endl;
//    cout << "max_size of 'm' "<< m.max_size() << endl;
//    return 0;
}
