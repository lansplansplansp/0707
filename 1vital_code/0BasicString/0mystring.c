#include<stdio.h>
#include "mystring.h"
#include <assert.h>

int main()
{
    printf("please input a string str1:\n");
    char str1[1024];
    scanf("%s",str1);
    printf("str1 munber count result:\n%d\n",mystrlen(str1));
    printf("please input a string str2:\n");
    char str2[1024];
    scanf("%s",str2);
    printf("The compare result:\n");
    if(mystrcmp(str1,str2) == -1)
    {
        printf("str1 < str2\n");
    }
    else if(mystrcmp(str1,str2) == 1)
    {
        printf("str1 > str2\n");
    }
    else if(mystrcmp(str1,str2) == 0)
    {
        printf("str1 = str2\n");
    }
    mystrcat(str1,str2);
    printf("The linking result:\n%s\n",str1);

    printf("please input a string str1:\n");
    scanf("%s",str1);
    printf("please input a string str2:\n");
    getchar();
    gets(str2);
    mystrcpy(str1,str2);
    printf("mystrcpy result is:\n%s\n",str1);

    printf("please input a string str1:\n");
    gets(str1);
    printf("please input a string str2:\n");
    gets(str2);
    strcpy(str1,str2);
    printf("strcpy result is:\n");
    puts(str1);
    return 0;
}

int mystrlen(char str[])
{
    int i = 0;
    while(str[i++]!='\0');
    return --i;
}

int mystrcmp(char str1[],char str2[])
{
    int i = 0;
    while(1)
    {
        if(str1[i] > str2[i])
            return 1;
        else if(str1[i] < str2[i])
            return -1;
        else if(str1[i] == str2[i])
        {
            if(str1[i] == '\0')
                return 0;
            i++;
        }
    }
}

void mystrcat(char str1[],char str2[])
{
    int i=0,j=0;
    while(str1[i++]!='\0');
    i--;
    while(str2[j]!='\0')
    {
        str1[i++]=str2[j++];
    }
    str1[i]='\0';
}

void mystrcpy(char str1[],char str2[])
{
    int i=0;
    for(i=0;str2[i]!='\0';i++)
    {
        str1[i]=str2[i];
    }
    str1[i] = '\0';
}

char* strcpy( char *strDest, const char *strSrc )
{
     //assert宏的原型定义在<assert.h>中,其作用是如果它的条件返回错误,则终止程序执行
     assert( strDest != NULL && strSrc != NULL );
     char *address = strDest;
     while((*strDest++ = *strSrc++) != '\0' );
     return address;
}
