#include<stdio.h>

int main()
{
    int i,j,line;

    printf("please input a number:\n");
    scanf("%d",&line);
    for(i=1;i<=line;i++){
        for(j=0;j<line-i;j++)
            putchar(' ');
        for(j=0;j<i*2-1;j++)
            putchar('*');
        printf("\n");
    }
    return 0;
}
