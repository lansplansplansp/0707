#include<stdio.h>
//sprintf()后面的占位符是字符串里的
int main()
{
	char buff[1024];
    sprintf(buff,"bufflen:%d,after:%d",100,200);
    printf("%s\n",buff);
    return 0;
}
