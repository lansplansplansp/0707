#include <iostream>
#include <deque>
#include <algorithm>
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
int main ()
{
    deque<int> d;
    Print<int> print;
    for ( int i=0; i<5; i++ )
    d.push_back(i+1);
    while ( !d.empty() )
    {
        cout << "d.size()=" << d.size() << endl;
        for_each(d.begin(),d.end(),print);
        cout << endl;
        d.pop_front();
    }
    return 0;
}
