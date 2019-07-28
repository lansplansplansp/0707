#include <iostream>
#include <deque>
#include <algorithm>
#include <set>
    //#include <map>
    //#include <map>
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
void print (set<int, less<int> >& s)
{
     set<int, less<int> >::iterator It;
     for ( It = s.begin(); It != s.end(); It++ )
     cout << *It << " ";
     cout << endl;
}
//==============================
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
//     deque<int> d(10);
//     Print<int> print;
//     fill(d.begin(),d.end(),5);
//     cout << "Deque d : ";
//     for_each(d.begin(),d.end(),print);
//     cout << endl;
//     cout << "Size of d = " << d.size()
//     << endl;
//     cout << "d.clear" << endl;
//     d.clear();
//     cout << "Deque d : ";
//     for_each(d.begin(),d.end(),print);
//     cout << endl;
//     cout << "Size of d = " << d.size()
//     << endl;
//     cout << "Deque d is ";
//     d.empty() ? cout << "" : cout << "not ";
//     cout << "empty" << endl;
//     return 0;
//     int ary[] = {1,2,3,2,3,4,8,2,5,6};
//     set<int, less<int> > s;
//     s.insert(ary,ary+10);
//     print(s);
//     s.clear();
//     cout << "Size of set s = " << s.size() << endl;
//     print(s);
//     return 0;
          int ary[] = {1,2,3,2,3,4,8,2,5,6};
          multiset<int, less<int> > s;
          s.insert(ary,ary+10);
          print(s);
          s.clear();
          cout << "Size of multiset s = " << s.size() << endl;
          print(s);
          return 0;
}
