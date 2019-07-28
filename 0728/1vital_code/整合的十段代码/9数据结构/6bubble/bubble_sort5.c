#include<stdio.h>
#define SIZE 10
int main()
{
	int a[SIZE]={12,43,9,67,98,101,89,3,35};
	int i,j,t;
	printf("is bubble sort:\n");
	for(i=0;i<10-1;i++)
	{
		for(j=0;j<10-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				t=a[j+1];
				a[j+1]=a[j];
				a[j]=t;
			}
		}	
	}
	printf("The result is:\n");
	for(i=0;i<10;i++)
	{
		printf("%d ",a[i]);	
	}
	printf("\n");
	return 0;
}
