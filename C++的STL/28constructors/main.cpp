//default preicate is less
#include <iostream>
#include <functional>
#include <set>
#include <map>
using namespace std;
int main ()
{
     int ary[] = { 5,3,7,5,2,3,7,5,5,4 };
     set<int> s1;
     set<int, greater<int> > s2;
     for ( int i=0; i<sizeof(ary)/sizeof(int); i++ )
     {
         s1.insert(ary[i]);
         s2.insert(ary[i]);
     }
     set<int>::iterator It = s1.begin();
     cout << "s1 : ";
     while ( It != s1.end() )
        cout << *(It++) << " ";
     cout << endl;
     It = s2.begin();
     cout << "s2 : ";
     while ( It != s2.end() )
        cout << *(It++) << " ";
     cout << endl;
     // second form of constructor
     set<int> s3(ary,ary+3);
     It = s3.begin();
     cout << "s3 : ";
     while ( It != s3.end() )
     cout << *(It++) << " ";
     cout << endl;
     // copy constructor (predicate of s1 is important)
     set<int, less<int> > s4(s1);
     It = s4.begin();
     cout << "s4 : ";
     while ( It != s4.end() )
        cout << *(It++) << " ";
     cout << endl;
     return 0;
//      int ary[] = {1,2,3,2,5,4,2,1,4,5};
//      multiset<int, less<int> > ms1;

//      multiset<int, greater<int> > ms2(ary,ary+10);
//      multiset<int>::iterator It;
//      cout << "ms2 : ";
//      for ( It = ms2.begin(); It != ms2.end(); It++ )
//      cout << *It << " ";
//      cout << endl;
//      // copy constructor
//      multiset<int, greater<int> > ms3(ms2);

//      cout << "ms3 : ";
//      for ( It = ms3.begin(); It != ms3.end(); It++ )
//      cout << *It << " ";
//      cout << endl;
//      It = ms2.begin();
//      while ( It != ms2.end() )
//      ms1.insert(*It++);
//      cout << "ms1 : ";
//      for ( It = ms1.begin(); It != ms1.end(); It++ )
//      cout << *It << " ";
//      cout << endl;
//      return 0;
//      typedef map <int, char, less<int> > M;
//      M m1;
//      m1.insert(M::value_type(2,'B'));
//      m1.insert(M::value_type(3,'C'));
//      m1.insert(M::value_type(1,'A'));
//      M::iterator It = m1.begin();
//      cout << endl << "m1:" << endl;
//      while ( It != m1.end() )
//      {
//          cout << (*It).first << " - "
//          << (*It).second
//          << endl;
//          It++;
//      }
//      // copy constructor
//      M m2(m1);
//      It = m2.begin();
//      cout << endl << "m2:" << endl;
//      while ( It != m2.end() )
//      {
//          cout << (*It).first << " - "
//          << (*It).second
//          << endl;
//          It++;
//      }
//      M m3(m2.begin(),m2.end());
//      It = m3.begin();
//      cout << endl << "m3:" << endl;
//      while ( It != m3.end() )
//      {
//          cout << (*It).first << " - "
//          << (*It).second
//          << endl;
//          It++;
//      }
//      return 0;
//     typedef multimap<int, char, less<int> > M;
//     M m1;
//     m1.insert(M::value_type(2,'B'));
//     m1.insert(M::value_type(3,'C'));
//     m1.insert(M::value_type(1,'A'));
//     m1.insert(M::value_type(1,'a'));
//     M::iterator It = m1.begin();
//     cout << endl << "m1:" << endl;
//     while ( It != m1.end() )
//     {
//         cout << (*It).first << " - "
//         << (*It).second
//         << endl;
//         It++;
//     }
//     // copy constructor
//     M m2(m1);
//     It = m2.begin();
//     cout << endl << "m2:" << endl;
//     while ( It != m2.end() )
//     {
//         cout << (*It).first << " - "
//         << (*It).second
//         << endl;
//         It++;
//     }
//     M m3(m2.begin(),m2.end());
//     It = m3.begin();
//     cout << endl << "m3:" << endl;
//     while ( It != m3.end() )
//     {
//         cout << (*It).first << " - "
//         << (*It).second
//         << endl;
//         It++;
//     }
//     return 0;
 }
