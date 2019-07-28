//returns the number of elements
#include <iostream>
#include <set>
    #include <map>
    #include <list>
    #include <numeric>
#include <string>
#include <fstream>
using namespace std;
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
     int ary[] = {1,2,3,2,3,4,8,2,5,6};
     set<int, less<int> > s;
     s.insert(ary,ary+10);
     print(s);
     cout << "count of '2' (0 or 1) is ";
     int n = s.count(2);
     cout << n << endl;
     return 0;
//     int ary[] = {1,2,3,2,3,4,8,2,5,6};
//     multiset<int, less<int> > s;
//     s.insert(ary,ary+10);
//     print(s);
//     cout << "count of '2' is ";
//     int n = s.count(2);
//     cout << n << endl;
//     return 0;
//     list<int> L1(3), L2(3);
//     iota(L1.begin(),L1.end(),1);
//     iota(L2.begin(),L2.end(),4);

//     typedef map<int, list<int> > M;
//     M m;
//     m.insert(M::value_type(1,L1));
//     m.insert(M::value_type(2,L2));
//     M::iterator It;
//     list<int>::iterator Li;
//     for ( It = m.begin(); It != m.end(); It++ )
//     {
//         cout << "map " << (*It).first << ": ";
//         for ( Li = It->second.begin();
//         Li != It->second.end(); Li++ )
//         cout << *Li << " ";
//         cout << endl;
//     }
//     int n = m.count(2);
//     cout << "count of element with key '2' (0 or 1) is "
//     << n << endl;
//     return 0;
//     typedef multimap<char,string> M1;
//     typedef M1::value_type v_t1;
//     M1 m1;
//     typedef multimap<string,char,less<string> > M2;
//     typedef M2::value_type v_t2;
//     M2 m2;
//     string word;
//     int counter = 0;
//     ifstream In("/usr/share/dict/words");
//     if ( In.good() )
//     {
//         while(1)
//         {
//             getline(In,word);
//             char ch = word.at(0);
//             // file is sorted
//             if ( ch != 'A' && ch != 'a' )
//                break;
//             else
//             {
//                 // for conting of words
//                 m1.insert(v_t1(ch,word));
//                 // for upper-lower bound
//                 m2.insert(v_t2(word,ch));
//             }
//             counter++;
//         }
//         In.close();
//     }
//     cout << "System Dictionary consists " << counter
//     << " words,\nwith first letter 'a' or 'A'"
//     << endl;
//     cout << m1.count('A') << " words start with 'A'"
//     << endl;
//     cout << m1.count('a') << " words start with 'a'"
//     << endl;
//     M2::iterator low = m2.lower_bound("Aba");
//     M2::iterator upp = m2.upper_bound("Abe");
//     cout << "Range of the words from 'Aba' to 'Abe':"
//     << endl;
//     while ( low != upp )
//     {
//         cout << (*low).first << endl;
//         low++;
//     }
//     return 0;
}
