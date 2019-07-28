#include<stdio.h>
#include<string.h>

int main()
{
    char ch;
    printf("Input a character:");
    ch=getc(stdin);
    //ch=fgetc(stdin);
    putc(ch,stdout);
    //fputc(ch,stdout);
    return 0;
}
