#include <iostream>
#include <deque>//双端队列；在std::deque两端插入和删除并不会使其它元素的指针或引用失效。在接口上和std::vector相似。
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
    //=============================
int main ()
{
    deque<int> d;
    Print<int> print;
    for ( int i=0; i<5; i++ )
    d.push_back(i+1);
    while (!d.empty())
    {
        cout << "d.size()=" << d.size() << endl;
        for_each(d.begin(),d.end(),print);
        cout << endl;
        d.pop_back();
    }
    return 0;
}
