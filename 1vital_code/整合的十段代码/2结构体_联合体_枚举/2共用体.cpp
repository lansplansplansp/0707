#include <bits/stdc++.h>

#include <time.h>


using namespace std;

int main()
{
    union check
    {
        int a;
        char b[2];
    }s;
    s.a=0x1234;
    printf("�������ڴ��У�\n");
    printf("������%8s\t%8s\t%8s\n","s.b[0]","s.b[1]","s.a");
    printf("��ַ��%8p\t%8p\t%8p\n",&s.b[0],&s.b[1],&s.a);
    printf("���ݣ�%8x\t%8x\t%8x\n",s.b[0],s.b[1],s.a);
    if(s.b[0]==0x12)
        printf("1���ģʽ\n");
    else
        printf("2С��ģʽ\n");
    return 0;
}

