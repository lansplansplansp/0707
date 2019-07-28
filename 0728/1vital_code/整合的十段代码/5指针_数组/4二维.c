#include<stdio.h>

int main()
{
    int a[3][4] = {0};
    int (*p)[4] = a;
    printf("%d\t%d\t%d\n",a[1][0],*(*(a+1)+0),*(a[1]+0));
    printf("%p\t%p\t%p\n",&a[1][0],*(a+1)+0,a[1]+0);
    printf("%d\t%d\t%d\n",p[1][0],*(*(p+1)+0),*(p[1]+0));
    printf("%p\t%p\t%p\n",&p[1][0],*(p+1)+0,p[1]+0);
    return 0;
}
