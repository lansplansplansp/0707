#include<stdio.h>

int f(int n)
{
    int ret;
    if(n==1 || n==0)
        return;
    ret  = n * f(n-1);
    return ret;//多了返回值
}
int main()
{
    int n;
    printf("please input int:\n");
    scanf("%d",&n);
    printf("%d\n",f(n));
    return 0;
}
