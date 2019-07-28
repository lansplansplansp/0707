#include <iostream>
#include <deque>
#include <iterator>
#include <algorithm>
#include <set>
    #include <map>
#include <string>
using namespace std;
void print (set<int, less<int> >& s)
{
     set<int, less<int> >::iterator It;
     for ( It = s.begin(); It != s.end(); It++ )
     cout << *It << " ";
     cout << endl;
}
typedef map<string, int, less<string> > M;
void print (M& m)
{
    M::iterator It = m.begin();
    cout << "map :" << endl;
    while ( It != m.end() )
    {
        cout << (*It).first << " - "
        << (*It).second
        << endl;
        It++;
    }
}
//-----------------------------------
//typedef multimap<string, int, less<string> > M;
//void print (M& m)
//{
//     M::iterator It = m.begin();
//     cout << "multimap :" << endl;
//     while ( It != m.end() )
//     {
//         cout << (*It).first << " - ";
//         cout << (*It).second << endl;
//         It++;
//     }
//}
//
int main ()
{
//     deque<int> d(10);
//     deque<int>::iterator It;
//     for ( int i=0; i<10; i++ )
//         d[i] = i+1;
//     copy(d.begin(),d.end(),ostream_iterator<int>(cout," "));
//     cout << endl;
//     It = d.begin()+2;
//     // remove third element
//     d.erase(It);
//     copy(d.begin(),d.end(),ostream_iterator<int>(cout," "));
//     cout << endl;
//     It = d.begin();
//     // remove 2 elements from beginning fo d
//     d.erase(It,It+2);
//     copy(d.begin(),d.end(),ostream_iterator<int>(cout," "));
//     cout << endl;
//     return 0;
    int ary[] = {1,2,3,2,3,4,8,2,5,6};
     set<int, less<int> > s;
     s.insert(ary,ary+10);
     print(s);
     // erase '2'
     s.erase(6);
     print(s);
     set<int, less<int> >::iterator It;
     It = s.find(5);
     // erase '5'
     s.erase(It);
     print(s);
     It = s.find(4);
     // erase from It to the end of set
     s.erase(It,s.end());
     print(s);
     return 0;
//     typedef M::value_type v_t;
//     M m;
//     m.insert(v_t("AAA",1));
//     m.insert(v_t("BBB",2));
//     m.insert(v_t("CCC",3));
//     m["DDD"] = 4;
//     m["EEE"] = 5;
//     print(m);
//     // remove element with key 'BBB'
//     m.erase("BBB");
//     print(m);
//     M::iterator It;
//     It = m.find("DDD");
//     // remove element pointed by It
//     m.erase(It);
//     print(m);
//     It = m.find("CCC");
//     // remove the range of elements
//     m.erase(m.begin(),++It);
//     print(m);
//     return 0;
//    typedef M::value_type v_t;
//    M m;
//    m.insert(v_t("AAA",1));
//    m.insert(v_t("BBB",2));
//    m.insert(v_t("CCC",3));
//    m.insert(v_t("EEE",4));
//    m.insert(v_t("CCC",5));
//    m.insert(v_t("DDD",6));
//    print(m);
//    // remove element with key 'BBB'
//    m.erase("BBB");
//    print(m);
//    M::iterator It;
//    It = m.find("DDD");
//    // remove element pointed by It
//    m.erase(It);
//    print(m);
//    It = m.find("CCC");
//    // remove the range of elements
//    m.erase(m.begin(),It);
//    print(m);
    return 0;
}
