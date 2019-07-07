#include<stdio.h>
void f(int num)
{
    if(num==1)
        return;
    int res;
    if(num%2)
    {
       res = (num*3)+1;
       num = num*3+1;
    }
    else
    {
       res = num /2;
       num=num/2;
    }
    printf("%4d",res);
    f(num);
}
int main()
{
    printf("please input a number:\n");
    int n;
    scanf("%d",&n);
    f(n);
    printf("\n");
    return 0;
}
