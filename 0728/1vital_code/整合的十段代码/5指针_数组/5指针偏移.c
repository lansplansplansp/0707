#include<stdio.h>

int main()
{
#if 1
	char a[]={2,4,6,8,10};
	char *p=a;
#endif
#if 0
	(*p)++;
	printf("%4d,%4d\n",*(a+0),p[0]);
	printf("%4d,%4d\n",a[0],*(p+0));
#endif
#if 0
	*p++;
	printf("%4d,%4d\n",a[0],*p);
#endif
#if 0
	*(p++);
	printf("%4d,%4d\n",a[0],*p);
#endif
#if 0
	int x = 100,*y;
   	y = &x;
	printf("%d\n",y);
	printf("%d\t%d\n",sizeof(x),sizeof(int));
	printf("%d\t%d\n",sizeof(y),sizeof(int *));
#endif
#if 0
	int x = 0x1234;
	int *y = (int *)0x1234;
	printf("%p\t%p\n",&x,&y);
	printf("%d\t%d\n",&x,&y);
	printf("%p\t%p\n",x,y);
	printf("%d\t%d\n",x,y);
	printf("0x%x\t0x%x\n",x,y);
#endif
#if 0
	*(++p);
	printf("%4d,%4d\n",a[0],*p);
#endif
#if 1
	(*p)++;
	printf("%4d,%4d\n",a[0],*p);
#endif
	return 0;
}
