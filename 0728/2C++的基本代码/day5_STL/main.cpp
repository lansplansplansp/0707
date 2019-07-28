#include <iostream>
#include<string>
#include<vector>//动态数组
//#include<list>
//#include<queue>
//#include<algorithm>//算法
//#include<map>//哈希；
using namespace std;

#if 0
template <typename T> //==template <class T>
void myswap(T &x,T &y)
{//减少代码量，但效率低
    T t;
    t = x;
    x = y;
    y = t;
    //调试
    cout << "myswap123" << endl;
}

template <typename T1,typename T2>
void print(T1 &x ,T2 &y)
{}

class point
{
private:
    int x;
    int y;
};

#endif
#if 1
//模板
template <typename T3> //==template <class T3>
class point
{
public:
    point(T3 x,T3 y)
    {
        this->x = x;
        this->y = y;
    }
    void show() const;
private:
    T3 x;
    T3 y;
};
template <typename T3>
void point<T3>::show() const
{
    cout<<"("<<this->x<<","<<this->y<<")"<<endl;
}
#endif
int main(int argc, char *argv[])
{
#if 0
    int a = 10,b = 20;
    myswap(a,b);
    cout << a <<endl << b <<endl;

    string sa = "abc",sb = "123";
    myswap(sa,sb);
    cout << sa <<endl << sb <<endl;

    point p1,p2;
    myswap(p1,p2);
#endif
#if 1
    vector<int> vct;//动态数组；容器
    vct.push_back(1);
    vct.push_back(2);
    vct.push_back(3);
    vct.push_back(4);//算法
    cout<<vct.size()<<endl;//4
    int i;
    for(i=0;i<vct.size();i++)
        cout << vct[i] <<endl;
    vct.pop_back();//删除最后一个数:4
    for(i=0;i<vct.size();i++)
        cout << vct[i] <<endl;

    //迭代器--指针
    vector<int>::iterator iter = vct.begin();//迭代器
    while (1) {
        if(iter != vct.end())
        {
            cout<<*iter<<endl;
            iter++;
        }
        else
            break;
    }

    point<int> pts[4] = {//Point<int>对象数组
        point<int>(1,1),
        point<int>(2,2),
        point<int>(3,3),
        point<int>(4,4)
    };
    //把四个数组放到向量里面去+4是最后一个元素的后面
    vector<point<int>> pvct;
    pvct.assign(pts,pts+4);//法1：函数
    //vector<point<int>> pvct(pts+0,pts+4);//向量：法2：重载
    vector<point<int>>::iterator p;//迭代
    for(p=pvct.begin();p!=pvct.end();p++)
        (*p).show();
#endif
#if  0
    point<int> pa(1,2);
    pa.show();
    point<double> pd(1.5,2.5);
    pd.show();
#endif
    return 0;
}
