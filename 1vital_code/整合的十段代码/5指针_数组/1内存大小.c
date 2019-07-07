#include<stdio.h>
#include<string.h>

int main()
{
    char chr[]={'a','b','c','d','e','f'};
    char *p = chr;

    printf("size:%d,%d\n",sizeof(p),sizeof(*p));
    short *s = (short *)chr;
    printf("addr:%p,%p\n",s,p);
    printf("size:%d,%d\n",sizeof(s),sizeof(*s));
    printf("*s = 0x%x\n\%p\n",*s,s);
    return 0;
}
