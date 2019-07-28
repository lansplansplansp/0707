#include<stdio.h>

void fun(int num)
{
	int res;
	if(num==0)	
		return;
	res = num % 10;
	num /= 10;
	fun(num);
	printf("%d\t",res);
}
int main()
{
	fun(123456);
	printf("\n");
	return 0;
}
