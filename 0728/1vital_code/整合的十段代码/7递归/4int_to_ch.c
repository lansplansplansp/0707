#include<stdio.h>

int fun(int num)
{
    if(num == 0)
        return;
    char res = num%10 + '0';
    num/=10;
    fun(num);
    printf("%c  ",res);
}
int main()
{
    printf("please input a num:\n");
    int n;
    scanf("%d",&n);
    printf("it's character is:\n");
    fun(n);
    printf("\n");
    return 0;
}
