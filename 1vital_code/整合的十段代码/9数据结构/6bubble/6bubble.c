#include<stdio.h>
#include<time.h>
#include "bubble.h"

int main()
{
	srand(time(0));
	int arr[LEN];
	array_init(arr,LEN);
	array_disp(arr,LEN);
	array_sort(arr,LEN);
	array_disp(arr,LEN);
	return 0;
}
void array_init(int array[],int len)
{
	int i;
	for(i=0;i<len;i++)
		array[i] = random()%100;
}
void swap(int *a,int *b)
{
	int c;
	c = *a;
	*a = *b;
	*b = c;
}
void array_sort(int array[],int len)
{
	int i,j;
	for(i=0;i<len;i++)
	{
		for(j=i+1;j<len;j++)
		{
			if(array[i] > array[j])
			{
				swap(&array[i],&array[j]);
			}
		}
	}
}
void array_disp(int array[],int len)
{
	int i;
	for(i=0;i<len;i++)
		printf("%d\t",array[i]);
	printf("\n");
}
