#include<stdio.h>
#include <string.h>

int i=0;

void fun(char str[],int start,int LEN)
{
    if(start == LEN)
        return;
    fun(str,start+1,LEN);
    printf("%c\t",str[start]);
}
int main()
{
    fun("ABCDEFG",0,strlen("ABCDEFG"));
    printf("\n");
    return 0;
}
