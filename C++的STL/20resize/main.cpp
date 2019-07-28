// change the size of the list
#include <iostream>
#include <list>
#include <vector>

using namespace std;
int main ()
{
    vector<int> l(10);
    list<int> L(10);
    cout << "Size of list l = "<< l.size() << endl;
    l.resize(100);
    cout << "After l.resize(100)" << endl;
    cout << "Size of list L = " << L.size() << endl;
    L.resize(5);
    cout << "After L.resize(5)" << endl;
    cout << "Size of list L = " << L.size();
    return 0;
}
