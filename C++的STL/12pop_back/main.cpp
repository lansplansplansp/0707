#include <iostream>
#include <deque>//˫�˶��У���std::deque���˲����ɾ��������ʹ����Ԫ�ص�ָ�������ʧЧ���ڽӿ��Ϻ�std::vector���ơ�
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
