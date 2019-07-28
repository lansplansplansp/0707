//finds a given element
#include <iostream>
#include <set>
#include <iomanip>
#include <string>
#include <map>
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
//        (It++)->print();
//     It = s.find(m);
//     if ( It == s.end() )
//     cout << "element not found" << endl;
//     else
//     {
//         cout << "element is found : ";
//         (*It).print();
//     }
//     return 0;
//     typedef map<int,char> M;
//     char ch = 'A';
//     M m;
//     for ( int i=0; i<5; i++ )
//     m[i] = ch++;

//     M::iterator It = m.begin();
//     cout << "map m:" << endl;
//     while ( It != m.end() )
//     {
//         cout << (*It).first << " - "
//         << (*It).second << endl;
//         It++;
//     }
//     It = m.find(4);
//     if ( It != m.end() )
//     cout << "element key '4' has value "
//     << (*It).second << endl;
//     else
//     cout << "element key '4' not found"
//     << endl;
//     return 0;
     typedef multimap<int,char> M;
     typedef M::value_type v_t;
     char ch = 'A';
     M m;
     for ( int i=0; i<5; i++ )
     m.insert(v_t(i,ch++));
     m.insert(v_t(4,'F'));
     M::iterator It = m.begin();
     cout << "multimap m:" << endl;
     while ( It != m.end() )
     {
         cout << (*It).first << " - "
         << (*It).second << endl;
         It++;
     }
     It = m.find(4);
     if ( It != m.end() )
     cout << "element key '4' has value "
          << (*It).second << endl;
     else
     cout << "element key '4' not found"
     << endl;
     M::iterator upp = m.upper_bound(4);
     cout << "all elements with key '4'" << endl;
     while ( It != upp )
     {
         cout << (*It).first << " - "
         << (*It).second << endl;
         It++;
     }
     return 0;
}
