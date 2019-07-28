#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main ()
{
     string str[]={"Alex","John","Robert"};
     // empty vector object
     vector<int> v1;

     // creates vector with 10 empty elements
     vector<int> v2(10);
     v2[0]=100;
     cout << v2[0] << ' ' << v2[1] << endl;
     v2.at(0)=200;
     cout << v2[0] << endl;
     // creates vector with 10 elements,
     // and assign value 0 for each
     vector<int> v3(10,1);
     cout << v3[0] << ' ' << v3[1] << endl;
     // creates vector and assigns
     // values from string array
     vector<string> v4(str+0,str+3);
     for ( int i=0; i<3; i++ )
     cout << v4[i] << " ";
     cout << endl;
     vector<string>::iterator sIt = v4.begin();
     while (sIt!=v4.end())
     cout << *sIt++ << " ";
     cout << endl;
     // copy constructor
     vector<string> v5(v4);
     for ( int i=0; i<3; i++ )
     cout << v5[i] << " ";
     cout << endl;
     cout << v5.back() << endl;
     return 0;
}
