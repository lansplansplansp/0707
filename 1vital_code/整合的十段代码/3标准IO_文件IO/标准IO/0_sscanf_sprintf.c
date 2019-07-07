#include<stdio.h>

int main()
{
    printf("%d\n", BUFSIZ);
    char str[] = "11 22 33 44 ";
    char a[4][20];
    char buff[1024];
    sscanf(str,"%s%s%s%s",a[0],a[1],a[2],a[3]);
    int i;
    for(i=0;i<4;i++)
        printf("%s\t",a[i]);
    printf("\n");
    sprintf(buff,"%d,%d",100,200);
    printf("%s\n",buff);
    return 0;
}
