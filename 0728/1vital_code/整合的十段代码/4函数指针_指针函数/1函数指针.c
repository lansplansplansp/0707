#include<stdio.h>
typedef int (*operator)(int,int);

int int_add(int a,int b)
{
    return(a+b);
}
int int_sub(int a,int b)
{
    return(a-b);
}
typedef int (*operator)(int,int);
int main()
{
    operator yunsuan = int_add;
    printf("%d\n",yunsuan(4,5));
    yunsuan = int_sub;
    printf("%d\n",yunsuan(4,5));
    return 0;
}
