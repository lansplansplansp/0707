// exchange two lists
#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>
#include <set>
#include <iterator>
#include <map>
#include <numeric>

using namespace std;
void print (list<int>& l)
{
     list<int>::iterator It = l.begin();
     while ( It != l.end() )
     {
        cout << *(It++) << " ";
     }
     cout << endl;
}
//===============================
void print (set<int, less<int> >& s)
{
     copy(s.begin(),s.end(),
     ostream_iterator<int>(cout," "));
     cout << endl;
}
//--------------------------------------------
typedef multimap<int, list<int> > M;
void print (M m)
{
     M::iterator It = m.begin();
     list<int>::iterator Li;//vector²»ÐÐ£¿
     while ( It != m.end() )
     {
         cout << "key : " << (*It).first
         << "; value : ";
         for ( Li = It->second.begin();
         Li != It->second.end(); Li++ )
         cout << *Li << " ";
         It++;
     }
     cout << endl;
}
int main ()
{
     list<int> li1(5), li2(5);
     iota(li1.begin(),li1.end(),1);
     iota(li2.begin(),li2.end(),5);
     cout << "li1 : ";
     print(li1);
     cout << "li2 : ";
     print(li2);
     li1.swap(li2);
     cout << endl <<"After swapping:" << endl;
     cout << "li1 : ";
     print(li1);
     cout << "li2 : ";
     print(li2);
     return 0;
//     int ary1[] = {1,2,3,2,3,4,8,2,5,6};
//     int ary2[] = {5,0,9,2,3,4,8,2,5,6};
//     set<int, less<int> > s1, s2;
//     s1.insert(ary1,ary1+10);
//     cout << "s1 : ";
//     print(s1);
//     cout << "s2 : ";
//     s2.insert(ary2,ary2+10);
//     print(s2);
//     if ( s1 != s2 )
//     s1.swap(s2);
//     cout << "s1 : ";
//     print(s1);
//     cout << "s2 : ";
//     print(s2);
//   return 0;
//     list<int> L1, L2;
//     L1.push_back(1);
//     L1.push_back(2);
//     L1.push_back(3);
//     copy(L1.begin(),L1.end(),back_inserter(L2));
//     M m1, m2;
//     m1.insert(M::value_type(1,L1));
//     m2.insert(M::value_type(2,L2));
//     cout << "multimap m1:" << endl;
//     print(m1);
//     cout << "multimap m2:" << endl;
//     print(m2);
//     if ( m1 == m2 )
//     cout << "multimaps m1 and m2 are equal"<< endl;
//     else
//     {
//         cout << endl << "After m1.swap(m2)"<< endl;
//         m1.swap(m2);
//         cout << "multimap m1:" << endl;
//         print(m1);
//         cout << "multimap m2:" << endl;
//         print(m2);
//     }
//     return 0;
}
