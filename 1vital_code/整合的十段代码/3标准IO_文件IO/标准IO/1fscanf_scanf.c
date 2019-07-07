#include<stdio.h>

int main()
{
    int x;
    int y;
    scanf("%d",&x);
    fscanf(stdin,"%d",&y);
    printf("%d\n",x);
    fprintf(stdout,"%d\n",y);
    return 0;
}
