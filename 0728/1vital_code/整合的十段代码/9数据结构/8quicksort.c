#include<stdio.h>
#include<time.h>
#include "quick.h"

int main()
{
	int array[LEN];
	srand(time(NULL));
	array_init(array,LEN);
	array_disp(array,LEN);
	array_sort(array,0,LEN-1);
	array_disp(array,LEN);
	return 0;
}
void array_init(int arr[],int len)
{
	int i;
	for(i=0;i<len;i++)
		arr[i] = random()%100;
}
int small[LEN];
int big[LEN];
void array_sort(int arr[],int left,int right)
{
    if(right <= left)
            return;
    int i;
    int si=0,bi=0;
    int middle = arr[left];
    for(i=left+1;i<=right;i++)
    {
        if(arr[i] < middle)
            small[si++] = arr[i];
        else
            big[bi++] = arr[i];
    }
    int scnt = si;
    int bcnt = bi;
    for(si=0;si<scnt;si++)
    {
        arr[left+si] = small[si];
    }
    int mid = left+si;
    arr[mid] = middle;
    for(bi=0;bi<bcnt;bi++)
    {
        arr[mid+bi+1] = big[bi];
    }
    array_disp(arr,LEN);
    array_sort(arr,left,mid-1);
    array_sort(arr,mid+1,right);
}
void array_disp(int arr[],int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		printf("%d\t",arr[i]);
	}
	printf("\n");
}
