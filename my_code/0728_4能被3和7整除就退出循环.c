#include <stdio.h>

int main()
{
	int x = 0;
	int num = 0;
	printf("please input a number:\n");
	while(1)
	{
		scanf("%d",&x);
		if(x%3==0 && x%7==0)
		{
			break;
		}
		printf("Sum is:%d\n",num += x);
	}
	
	return 0;
}