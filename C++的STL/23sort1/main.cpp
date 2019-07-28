// sorts the list
#include <iostream>
#include <list>
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
//-----------------------------
int main ()
{
     int ary[] = {3,2,5,7,3,6,7,2,4,5};
     list<int> li(ary,ary+10);
     Print<int> print;
     cout << "Before sorting\nli : ";
     for_each(li.begin(),li.end(),print);
     cout << endl << endl;
     li.sort(greater<int>());
     cout << "After li.sort(greater())\nli : ";
     for_each(li.begin(),li.end(),print);
     cout << endl << endl;
     li.sort(less<int>());
     cout << "After li.sort(less())\nli : ";
     for_each(li.begin(),li.end(),print);
     cout << endl;
     return 0;
}
