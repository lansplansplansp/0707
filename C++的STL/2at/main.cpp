#include <iostream>
#include <vector>
using namespace std;
int main ()
{
     vector<int> v(3,0);
     v[0] = 100;
     v.at(1) = 200;
     for ( int i=0; i<3; i++ )
        cout << v.at(i) << " ";
     return 0;
}
