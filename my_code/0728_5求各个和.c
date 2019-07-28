#include <stdio.h>

//给出一个数，求各个位之和
int main()
{
	int x = 0;
	int sum = 0;
	int n = 0;
	while(1)
	{
		printf("please inpput a number:\n");
		scanf("%d",&x);
		while(x)
		{
			n = x%10;
			sum += n;
			x/=10;
		}
		printf("The sum is:%d\n",sum);	
		sum  = 0;
	}
	
	return 0;
}