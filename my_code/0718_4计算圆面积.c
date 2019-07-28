#include <stdio.h>
#include <math.h>

#define PI 3.14

int main()
{
	FILE *file1 = fopen("0718_3加减运算.c",wb);
	int x=0;
	printf("please input x:\n");
	scanf("%d",&x);
	printf("The Circle area is:%lf\n ",pow(x,2)*PI);
	printf("%d\n",eof);
	return 0;
}