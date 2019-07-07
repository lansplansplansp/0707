#include<stdio.h>
#include<string.h>

int main()
{
    char str[10];
    char a[10];
    int i;
    printf("input:");
    scanf("%s",str);
    //for(i=0;str[i]!=0;i++)
    for(i=0;str[i]!='\0';i++)
    {
        a[i]=str[i]-32;
        printf("%c\t",a[i]);
    }
    return 0;
}
