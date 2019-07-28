#include <stdio.h>

//从键盘输入三个浮点数，用三目运算符求出三个数中的最大者，输出
int main()
{
	float x = 0;
	float y = 0;
	float z = 0;
	float max = 0;
	while(1)
	{
		printf("please input three number:\n");
		scanf("%f%f%f",&x,&y,&z);
		(x>y?(max=x):(max=y))>z?(max = max):(max=z);
		printf("The max number is:%f\n",max);
	}

	return 0;
}