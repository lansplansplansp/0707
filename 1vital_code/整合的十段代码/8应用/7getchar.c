#include<stdio.h>

int main()
{
    char c;
    printf("please input a number:\n");
    c=getchar();
    switch(c){
        case 'a':printf("got a\n");
        case 'b':printf("got b\n");
             break;
        default:printf("haha\n");
    }
}
