#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int number = -12345;
    char string[32];
    itoa(number, string, 10);//没有该函数
    printf("integer = %d string = %s\n", number, string);
    return 0;
}