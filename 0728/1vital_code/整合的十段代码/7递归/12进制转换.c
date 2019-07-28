#include<stdio.h>

void fun(int n)
{
	if(n==0)
		return;
	int res=n%10;
	n/=10;
	printf("%d",res);
	fun(n);
}
int main()
{
	fun(12345);
	return 0;
}
