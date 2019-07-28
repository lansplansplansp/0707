#include <stdio.h>

int main()
{
	int cnt = 123456;
	int *p = &(cnt+1);//错
	printf("%d\n",*p);
	return 0;
}