#include<stdio.h>
#include<string.h>

int main()
{
    //4096 = 2^12
    char str[4096];//∑¿÷π‘ΩΩÁ
    char *p = "hello world";
    for(str=p;*str!=' ';*str++){
        p++;
        printf("%s\n",str);
    }
   return 0;
}
