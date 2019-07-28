#include <stdio.h>

//input a int 判断是否被3与7整除
int main()
{
	int n = 0;
	printf("please input int:\n");
	scanf("%d",&n);
	if(n%3==0 && n%7==0)
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}
	return 0;
}