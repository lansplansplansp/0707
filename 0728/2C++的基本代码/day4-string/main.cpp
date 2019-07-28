#include <iostream>
#include <string>
#include "mystring.h"
using namespace std;

int main()
{
    //mystring_test1();

#if 1
    string s1="abc";
    string s11("ABC");
    string s2;
    string s3(5, 'a');

    cout << s1+s11 << endl;//abcABC
    cout << s1 << endl
         << s11 << endl
         << s2 << endl
         << s3 << endl;

    cout << s1[0] << endl;

    const char *s4 = s3.c_str();  // "aaaaa"
    cout << s4 << endl;
    cout << s1.capacity()<<endl//15
          <<  s3.size()<<endl//5
           <<s3.length()<<endl//5
           << s2.empty()<<endl;//1

    cout << s2.size() << s2.capacity() << s2.length() << endl;

    cout << s1.substr(1,2)<<endl;
    //bool operator == (const string &s1,const string &s2)const;//友元比较
#endif
    return 0;
}
