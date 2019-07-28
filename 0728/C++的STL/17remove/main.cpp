// removes elements from the list
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
using namespace std;
template <class T, class D>
class Salary
{
    public:
    Salary(T t) : id(t) {}
    Salary(T t,D d) : id(t), sal(d) {}
    void print ()
    { cout << id << " " << sal << endl; }
    private:
    T id;
    D sal;
    friend bool operator ==(const Salary& s1,const Salary& s2)
    { return s1.id == s2.id; }
};
//==========================================
int main ()
{
     typedef Salary<string,double> S;
     typedef list<S> L;
     L l;
     l.push_back(S("012345",70000.0));
     l.push_back(S("012346",60000.0));
     l.push_back(S("012347",72000.0));
     L::iterator It = l.begin();
     while ( It != l.end() )
        (It++)->print();
     cout << endl;
     S s("012345");
     l.remove(s);
     It = l.begin();
     while ( It != l.end() )
        (It++)->print();
     cout << endl;
     return 0;
}
