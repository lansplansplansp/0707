#include "mystring.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
mystring::mystring()
{
    this->icapacity = 16;//有个\0
    this->pstr = new char[this->icapacity];
    strcpy(this->pstr, "");
}

mystring::mystring(const char *str)
{
    this->icapacity = 16;
    if(str==NULL)
    {
        this->icapacity = 16;
        this->pstr = new char[this->icapacity];
        strcpy(this->pstr, "");
    }
    else if(strlen(str) < icapacity)
    {
        this->icapacity = 16;
         this->pstr = new char[this->icapacity];
        strcpy(this->pstr, str);
    }
    else if(strlen(str) > icapacity)
    {   //避免内存碎片  3 =>  4  5 =>8  2^n:给的内存有固定模式；
        this->icapacity = strlen(str)+1;
        this->pstr = new char[this->icapacity];
        strcpy(this->pstr, str);
    }
}
//旧的深拷贝与新的深拷贝比较:
#if 1
mystring::mystring(const mystring &str)
{
    this->icapacity = str.capacity();
    this->pstr = new char[this->icapacity];
    strcpy(this->pstr, str.pstr);
}

mystring &mystring::operator =(const mystring &str)
{
    delete []pstr;
    this->icapacity = str.capacity();
    this->pstr = new char[this->icapacity];
    strcpy(this->pstr, str.pstr);
    return *this;
}

#endif

mystring::~mystring()
{
    delete []pstr;
    cout << "descon"<<endl;
}

int mystring::capacity() const
{
    return this->icapacity - 1;
}

int mystring::lenght() const
{
    return strlen(this->pstr);
}

void mystring_test1()
{
    mystring s1;    //默认构造函数
    cout << s1.capacity() <<endl
         << s1.lenght() << endl;
    mystring s2("1234");    //带参数构造函数
    mystring s3 = s2; // 拷贝构造函数 定义并初始化
    s1 = s2;   // = 运算符重载=
}

