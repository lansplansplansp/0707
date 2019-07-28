#include <stdio.h>

//给出一个数，求各个位奇数之和
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
			x/=10;
			if(n%2!=0)
			{
				sum += n;
			}
			else
			{
				continue;
			}
		}
		printf("The sum is:%d\n",sum);	
		sum  = 0;
	}
	
	return 0;
}