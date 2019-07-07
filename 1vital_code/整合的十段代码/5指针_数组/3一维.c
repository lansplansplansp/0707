#include<stdio.h>

int main()
{
    int a[5]={0,1,2,3,4};
    int *pa1=a;
    printf("%d,%d,%d\n",&a,a,pa1);
    printf("%d,%d,%d\n",*a,a[0],*pa1);
    printf("%d,%d,%d\n",*pa1+0,pa1[0],*(pa1+0));

    int *pa2=a+2;

    if(pa1==pa2)
        printf("pa1 and pa2 point to same");
    else
        printf("%d\n",pa2-pa1);
    return 0;
}
