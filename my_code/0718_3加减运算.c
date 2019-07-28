#include <stdio.h>

int main()
{
	int a = 5;
	int b = 3;
	printf("%d+%d = %d\n",a,b,a+b);
	printf("%d-%d = %d\n",a,b,a-b);
	printf("%d*%d = %d\n",a,b,a*b);
	//printf("%d/%d = %f\n",a,b,(float)a/b);//不建议用
	
	printf("%d%%%d = %d\n",a,b,a+b);

	return 0;
}