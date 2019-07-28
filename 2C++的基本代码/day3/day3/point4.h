#ifndef POINT4_H
#define POINT4_H
#include <iostream>
using namespace std;
//静态成员
class Point4
{
public:
    Point4();
    Point4(int x, int y):x(x),y(y){
        cout<<__FUNCTION__<<":"<<11<<endl;
    }//

    ~Point4();
    void showcount();//obj.showcount()
    //属于类 Point4::staticcount()
    static void staticcount();//showcount的优化：可以使一行复制，执行多个命令；
    void show();//一般对象调用；
    void show2() const;//const对象调用；以后就这样写；因为一般对象也可以调用他；
private:
    //私有成员变量，是属于对象的
    int x;
    int y;
    //静态数据成员，统计类创建了几个对象
    //属于类的，被所有的对象公有
    static int count;

};

void point4_test1();
void point4_test2();

#endif // POINT4_H
