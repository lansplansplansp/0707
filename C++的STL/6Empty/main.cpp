#include <iostream>
#include <deque>
#include <set>//multisetÒ²ÒªËü
#include <map>
using namespace std;
void print (set<int, less<int> >& s)
{
     set<int, less<int> >::iterator It;
     for ( It = s.begin(); It != s.end(); It++ )
     cout << *It << " ";
     cout << endl;
}
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
     deque<int> d;
     cout << "Deque is ";
     d.empty() ? cout << "" : cout << "not ";
     cout << "empty" << endl;
     d.push_back(100);
     cout << "Deque is ";
     d.empty() ? cout << "" : cout << "not ";
     cout << "empty" << endl;
     cout << d.size() << endl;
     deque<int>::iterator It = d.begin();
     while(It != d.end())
         cout << *It++;
      cout << endl;
     return 0;
//     int ary[] = {1,2,3,2,3,4,8,2,5,6};
//     set<int, less<int> > s;
//     s.insert(ary,ary+10);
//     print(s);
//     cout << "set is " << ((s.empty()) ? "" : "not ")
//     << "empty" << endl;
//     s.clear();
//     cout << "set is " << ((s.empty()) ? "" : "not ")
//     << "empty" << endl;
//     return 0;
//        int ary[] = {1,2,3,2,3,4,8,2,5,6};
//        multiset<int, less<int> > s;
//        s.insert(ary,ary+10);
//        print(s);
//        cout << "multiset is " << ((s.empty()) ? "" : "not ")
//        << "empty" << endl;
//        s.clear();
//        cout << "multiset is " << ((s.empty()) ? "" : "not ")
//        << "empty" << endl;
//        return 0;
//     typedef map<int,int> M;
//     M m;
//     m[1] = 100;
//     m[3] = 200;
//     m[5] = 300;
//     cout << "values of map 'm': ";
//     M::iterator It = m.begin();
//     while ( It != m.end() )
//     {
//         cout << (*It).second << " ";
//         It++;
//     }
//     cout << endl;
//     cout << "size of map = " << m.size()
//     << endl;
//     cout << "map 'm' is " << (m.empty() ?
//     "" : "not ") << "empty" << endl << endl;
//     m.erase(m.begin(),m.end());
//     cout << "After m.erase(m.begin(),m.end())"
//     << endl;
//     cout << "size of map = " << m.size()
//     << endl;
//     cout << "map 'm' is " << (m.empty() ?
//     "" : "not ") << "empty" << endl;
//     return 0;
//      typedef multimap<int,int> M;
//      typedef M::value_type v_t;
//      M m;
//      m.insert(v_t(1,100));
//      m.insert(v_t(1,200));
//      m.insert(v_t(2,300));
//      m.insert(v_t(3,400));
//      cout << "values of multimap 'm': ";
//      M::iterator It = m.begin();
//      while ( It != m.end() )
//      {
//      cout << (*It).second << " ";
//      It++;
//      }
//      cout << endl;
//      cout << "size of multimap = " << m.size()
//      << endl;
//      cout << "multimap 'm' is " << (m.empty() ?
//      "" : "not ") << "empty" << endl << endl;
//      m.erase(m.begin(),m.end());
//      cout << "After m.erase(m.begin(),m.end())"
//      << endl;
//      cout << "size of multimap = " << m.size()
//      << endl;
//      cout << "multimap 'm' is " << (m.empty() ?
//      "" : "not ") << "empty" << endl;
//      return 0;
}
