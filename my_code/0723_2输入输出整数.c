#include <stdio.h>

int main()
{
	printf("please input two int:\n");
	int x=0;
	int y=0;
	scanf("%d,%d",&x,&y);
	printf("x+y = %d\n",x+y);
	x<<2;
	printf("%d\n",x);
	return 0;
}