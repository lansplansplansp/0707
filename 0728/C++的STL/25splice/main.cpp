// merge two lists
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
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
//====================================
int main ()
{
     list<int> li1, li2, li3, li4;
     Print<int> print;
     for ( int i=0; i<5; i++ )
     {
         li1.push_back(i);
         li2.push_back(i+5);
         li3.push_back(i+10);
         li4.push_back(i+15);
     }
     cout << "li1 : ";
     for_each(li1.begin(),li1.end(),print);
     cout << endl;
     cout << "li2 : ";
     for_each(li2.begin(),li2.end(),print);
     cout << endl;
     cout << "li3 : ";
     for_each(li3.begin(),li3.end(),print);
     cout << endl;
     cout << "li4 : ";
     for_each(li4.begin(),li4.end(),print);
     cout << endl << endl;
     li1.splice(li1.end(),li2);
     cout << "1li1 : ";
     for_each(li1.begin(),li1.end(),print);
     cout << endl << endl;
     li1.splice(li1.end(),li3,li3.begin(),li3.end());
     cout << "2li1 : ";
     for_each(li1.begin(),li1.end(),print);
     cout << endl << endl;
     list<int>::iterator It;
     It = find(li4.begin(),li4.end(),18);
     li1.splice(li1.begin(),li4,It);
     cout << "li1 : ";
     for_each(li1.begin(),li1.end(),print);
     cout << endl;
     cout << "li4 : ";
     for_each(li4.begin(),li4.end(),print);
     cout << endl;
     return 0;
 }
