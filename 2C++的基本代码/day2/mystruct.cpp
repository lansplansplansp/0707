#include "mystruct.h"
#include <iostream>
using namespace std;
//类内函数--类名限定符
#if 1
void STU::setSno(int no)
{   //类内函数是可以访问类的私有成员
    sno = no;
}
void test2_class()
{
    STU s3;
    //s3.sno = 1003// error
    s3.setSno(1003);
    cout << s3.getSno() << endl;

    STU s4; //栈对象
    // s4.sno
    s4.setSno(1004);
     cout << s4.getSno() << endl;
    //setSno(1003);  //
    //成员函数作用在哪一个对象上 s3还是s4
    //对象名.函数名
    //对象名.成员名
    // 定义Point类。坐标点(x,y),通过公有函数访问
    //创建对象，存储在堆
    STU *s5 = new STU();//堆对象
    s5->setSno(1005);
     cout << s5->getSno() << endl;
    delete s5;
}
#endif
#if 1
void test_struct_class()
{   //类外函数，不能访问类的私有成员、保护成员
    stu_t   s1;
    STU     s2;
    cout << sizeof(s1)<<endl<< sizeof(s2)<<endl;
    //访问成员
    //s1.sno = 1001;
    //s2.sno = 102;
    // int STU::sno is private
    // 类名限定符
    //s2.sno = 1002;  //类外不能
    //s2.age = 1003;  //继承可以，类外不可
    s2.sex = 'F'; //公有：类内、类外都可
    cout << s2.sex <<endl;
}
#endif
