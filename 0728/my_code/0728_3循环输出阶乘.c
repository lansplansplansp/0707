#include <stdio.h>

//输入一个整数  输出他的阶乘  用循环实现
int main()
{
	int x = 0;
	int sum = 1;
	while(1)
	{
		printf("please input a number:\n");
		scanf("%d",&x);
		if(x < 0)
			continue;

		while(x)
		{
			sum *= x--;
		}
		printf("The factorial is:%d\n",sum);//输入x = 0也符合x的阶乘 = 1
		sum = 1;
	}
	
	return 0;
}