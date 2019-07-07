#include<stdio.h>
#include<string.h>
#include<time.h>
#include "find.h"

#define LEN 11

int main()
{
    int array[LEN];
    int index;
    srand(time(0));
    array_init(array,LEN);
    array_disp(array,LEN);
    array_sort(array,0,LEN-1);
    array_disp(array,LEN);
    index = array_find(array,0,LEN-1,10);
    if(index==-1)
        printf("not found 10!\n");
    else
        printf("'10'`s index:%d\n",index);
    index = array_find2(array,0,LEN-1,20);
    if(index==-1)
        printf("not found 20!\n");
    else
        printf("'20'`s index:%d\n",index);
    return 0;
}
void array_init(int arr[],int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        arr[i] = random()%100;
    }
}

int temp[LEN];
void array_sort(int arr[],int left,int right)
{
    if (right<=left)
            return;

    int mid = (left+right)/2;
    array_disp(arr,LEN);
    array_sort(arr,left,mid);
    array_sort(arr,mid+1,right);
    int j = mid+1;
    int k = left;
    int i=left;
    while(i<=mid&&j<=right)
    {
            if(arr[i]<arr[j])
                    temp[k++] = arr[i++];
            else
                    temp[k++] = arr[j++];

    }
    while(i<=mid)
    {
            temp[k++] = arr[i++];
    }
    while(j<=right)
    {
            temp[k++] = arr[j++];
    }
    memcpy(&arr[left],&temp[left],sizeof(int)*(right-left+1));
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
int array_find(int arr[],int left,int right,int value)
{
	int index = -1;
	if(right <= left)
		return index;
	int mid = (left+right)/2;
	if(arr[mid] == value)
	{
		index = mid;
	}	
	else if(arr[mid] < value)
	{
		index = array_find(arr,mid+1,right,value);
	}
	else
		index = array_find(arr,left,mid-1,value);
	return index;
}
int array_find2(int arr[],int left,int right,int value)
{
	int index = -1;
	int mid;
	while(left <= right)
	{
		mid = (left+right)/2;
		if(arr[mid] == value)
		{
			index = mid;
			break;
		}
		else if(arr[mid] <value)
		{
			left = mid+1;
		}
		else
		{
			right = mid-1;
		}
	}	
	return index;
}
