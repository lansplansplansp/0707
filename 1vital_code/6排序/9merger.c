#include<stdio.h>
#include<string.h>
#include<time.h>
#include "merger.h"

int main()
{
    int array[LEN];
    srand(time(0));
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
#if 0
    for(k=left;k<=right;k++)
    {
        arr[k] = temp[k];
    }
#endif
#if 1
    memcpy(&arr[left],&temp[left],sizeof(int)*(right-left+1));
#endif
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
