#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    union check
    {
        int a;
        char b[2];
    }s;
    s.a=0x1234;
    printf("数据在内存中：\n");
    printf("地址：%8p\t%8p\t%8p\n",&s.b[0],&s.b[1],&s.a);
    printf("数据：%8x\t%8x\t%8x\n",s.b[0],s.b[1],s.a);
    if(s.b[0]==0x12)
        printf("1大端模式\n");
    else
        printf("2小端模式\n");
    return 0;
}
//小端前面数据小

