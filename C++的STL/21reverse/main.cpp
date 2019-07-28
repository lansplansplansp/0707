// reverse the list
#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>
#include <iterator>
using namespace std;
int main ()
{
     list<int> l(10);
     iota(l.begin(),l.end(),1);
     copy(l.begin(),l.end(),ostream_iterator<int>(cout," "));
     cout << endl;
     l.reverse();
     copy(l.begin(),l.end(),ostream_iterator<int>(cout," "));
     cout << endl;
     return 0;
}
