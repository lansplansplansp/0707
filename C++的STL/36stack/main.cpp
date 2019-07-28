// The C++ Stack is a container adapter that gives the
// programmer the functionality of a stack -- specifically,
// a FILO (first-in, last-out) data structure.
// push, pop, size, top, empty
//all stack functions
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <deque>
#include <iterator>
#include <numeric>
using namespace std;
int main ()
{
    vector<int> v1(5), v2(5), v3(5);
    iota(v1.begin(), v1.end(), 0);
    iota(v2.begin(), v2.end(), 5);
    iota(v3.begin(), v3.end(), 10);
    stack<vector<int> > s;
    s.push(v1);
    s.push(v2);
    s.push(v3);
    cout << "size of stack 's' = "
    << s.size() << endl;
    if ( v3 != v2 )
    s.pop();
    cout << "size of stack 's' = "
    << s.size() << endl;
    vector<int> top = s.top();
    cout << "Contents of v2 : ";
    copy(top.begin(),top.end(),
    ostream_iterator<int>(cout," "));
    cout << endl;
    while ( !s.empty() )
        s.pop();
    cout << "Stack 's' is " << (s.empty() ? ""
    : "not ") << "empty" << endl;
    return 0;
}
