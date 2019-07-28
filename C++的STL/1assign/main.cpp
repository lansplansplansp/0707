#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
int main ()
{
     int ary[]={1,2,3,4,5};
     vector<int> v;
     // assign to the "v" the contains of "ary"
     v.assign(ary,ary+5);
     copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));
     cout << endl;
     // replace v for 3 copies of 100
     v.assign(3,100);
     copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));
     cout << endl;
     return 0;
}
