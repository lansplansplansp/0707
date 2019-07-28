#include<stdio.h>
#include<string.h>

int main()
{
    printf("please input a char:\n");
    char ch = getchar();
    putchar(ch);
    FILE *fp = fopen("hello.c","r");
    if(NULL == fp)
    {
        printf("hello.c not exist\n");
        return 1;
    }
    char c;
    while(1){
        c = fgetc(fp);
        if(feof(fp))
            break;
        fputc(c,stdout);
    }
    fclose(fp);
    return 0;
}
