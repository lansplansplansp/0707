#include <iostream>
#include <deque>
#include <iterator>
#include <algorithm>
#include <set>
    #include <map>
    #include <string>
using namespace std;
template <class T>
class Print
{
 public:
    void operator () (T& t)
    {
        cout << t << " ";
    }
};
//=============================

void print (set<int, less<int> >& s)
{
     set<int, less<int> >::iterator It;
     for ( It = s.begin(); It != s.end(); It++ )
        cout << *It << " ";
     cout << endl;
}
//--------------------------------------------

void print (multiset<int, less<int> >& s)
{
     multiset<int, less<int> >::iterator It;
     for ( It = s.begin(); It != s.end(); It++ )
     cout << *It << " ";
     cout << endl;
}
//--------------------------------------------

int main ()
{
     int ary[5];
     fill(ary,ary+5,1);
     deque<int> d;
     deque<int>::iterator It;
     Print<int> print;
     copy(ary,ary+5,
     back_inserter(d));
     cout << "deque d : ";
     for_each(d.begin(),d.end(),print);
     cout << endl;
     It = d.begin();
     // insert value "5" at the position "It"
     cout << "d.insert(It,5) : ";
     d.insert(It,5);
     for_each(d.begin(),d.end(),print);
     cout << endl;
     // insert range ary+2 - ary+5 at the position "It"
     It = d.begin()+5;
     cout << "d.insert(It,ary+2,ary+5) : ";
     d.insert(It,ary+2,ary+5);
     for_each(d.begin(),d.end(),print);
     cout << endl;
     // insert 2 value of "20" at the position "It"
     It = d.end()-2;
     cout << "d.insert(It,2,20) : ";
     d.insert(It,2,20);
     for_each(d.begin(),d.end(),print);
     cout << endl;
     return 0;
//      int ary[] = {1,2,3,2,3,4,8,2,5,6};
//      set<int, less<int> > s;
//      s.insert(10);
//      print(s);
//      s.insert(ary,ary+5);
//      print(s);
//      set<int, less<int> >::iterator It = s.begin();
//      s.insert(It,20);
//      print(s);
//      return 0;
//       int ary[] = {1,2,3,2,3,4,8,2,5,6};
//       multiset<int, less<int> > s;
//       s.insert(10);
//       print(s);
//       s.insert(ary,ary+5);
//       print(s);
//       multiset<int, less<int> >::iterator It = s.begin();
//       s.insert(It,20);
//       print(s);
//       return 0;
//       typedef map<int, char, less<char> > M;//和set一样，可以不重复输出元素
//       typedef M::value_type v_t;
//       M m1, m2;
//       char ch = 'A';
//       for ( int i=0; i<3; i++ )
//       {
//           m1[i+1] = ch+i;
//           m2[i+4] = ch+i+3;
//       }
//       cout << "m1 :" << endl;
//       M::iterator It = m1.begin();
//       while ( It != m1.end() )
//       {
//           cout << (*It).first << " - "
//           << (*It).second << endl;
//           It++;
//       }
//       cout << "m2 :" << endl;
//       It = m2.begin();
//       while ( It != m2.end() )
//       {
//           cout << (*It).first << " - "
//           << (*It).second << endl;
//           It++;
//       }
//       // insert new element
//       m1.insert(v_t(5,'E'));
//       It = m2.find(6);
//       // insert element pointed by It
//       m1.insert(*It);
//       cout << "m1 :" << endl;
//       It = m1.begin();
//       while ( It != m1.end() )
//       {
//           cout << (*It).first << " - "
//           << (*It).second << endl;
//           It++;
//       }
//       // insert the range of elements
//       m1.insert(m2.begin(),m2.end());
//       cout << "m1 :" << endl;
//       It = m1.begin();
//       while ( It != m1.end() )
//       {
//           cout << (*It).first << " - "
//           << (*It).second << endl;
//           It++;
//       }
//       return 0;
//       typedef multimap<int, char, less<char> > M;
//       typedef M::value_type v_t;
//       M m1, m2;
//       char ch = 'A';
//       for ( int i=0; i<3; i++ )
//       {
//           m1.insert(v_t(i+1,ch+i));
//           m2.insert(v_t(i+4,ch+i+3));
//       }
//       cout << "m1 :" << endl;
//       M::iterator It = m1.begin();
//       while ( It != m1.end() )
//       {
//           cout << (*It).first << " - "
//           << (*It).second << endl;
//           It++;
//       }
//       cout << "m2 :" << endl;
//       It = m2.begin();
//       while ( It != m2.end() )
//       {
//           cout << (*It).first << " - "
//           << (*It).second << endl;
//           It++;
//       }
//       // insert new element
//       m1.insert(v_t(5,'E'));

//       It = m2.find(6);
//       // insert element pointed by It
//       m1.insert(*It);
//       cout << "m1 :" << endl;
//       It = m1.begin();
//       while ( It != m1.end() )
//       {
//           cout << (*It).first << " - "
//           << (*It).second << endl;
//           It++;
//       }
//       // insert the range of elements
//       m1.insert(m2.begin(),m2.end());
//       cout << "m1 :" << endl;
//       It = m1.begin();
//       while ( It != m1.end() )
//       {
//           cout << (*It).first << " - "
//           << (*It).second << endl;
//           It++;
//       }
//       return 0;
 }
