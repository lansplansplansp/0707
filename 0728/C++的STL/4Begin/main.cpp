#include <iostream>
#include <deque>
#include <iterator>
#include <numeric>
#include <set>
            #include <map>
            #include <functional>
#include <string>
using namespace std;
int main ()
{
//     deque<int> d(5);
//     iota(d.begin(),d.end(),1);
//     deque<int>::iterator It = d.begin();
//     while ( It != d.end() )
//        cout << *It++ << " ";
//     cout << endl;
//     // third element of the deque
//     It = d.begin()+2;
//     cout << *It << endl;
//     return 0;
//     int ary[] = {1,2,3,2,4,5,7,2,6,8};//不重复输出元素
//     set<int> s(ary,ary+10);
//     copy(s.begin(),s.end(),ostream_iterator<int>(cout," "));
//     return 0;
//         int ary[] = {1,2,3,2,4,5,7,2,6,8};
//         multiset<int> s(ary,ary+10);
//         copy(s.begin(),s.end(),ostream_iterator<int>(cout," "));
//         return 0;
//     typedef map<int, char, greater<int> > M;//数字可从大到小排序
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
//     return 0;
     typedef multimap<string,int> M;//字母可以从小到大排序
     typedef M::value_type v_t;
     M m;
     m.insert(v_t("first",100));
     m.insert(v_t("second",200));
     m.insert(v_t("third",300));
     m.insert(v_t("second",400));
     m.insert(v_t("third",500));
     M::iterator It = m.begin();
     cout << "m:" << endl;
     while ( It != m.end() )
     {
         cout << (*It).first << " - "
         << (*It).second
         << endl;
         It++;
     }
     return 0;
}
