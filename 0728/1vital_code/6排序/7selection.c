#include<stdio.h>
#include<time.h>
#include "select.h"

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
void array_sort(int array[],int len)
{
    int i,j;
    int max,maxindex;
    for(i=0;i<len;i++)
    {
        array_disp(array,LEN);
        max = array[0];
        maxindex = 0;
        for(j=1;j<len-i;j++)
        {
            if(array[j] > max)
            {
                max = array[j];
                maxindex = j;
            }
        }
        array[maxindex] = array[j-1];
        array[j-1] = max;
    }
}
void array_disp(int array[],int len)
{
    int i;
    for(i=0;i<len;i++)
        printf("%d\t",array[i]);
    printf("\n");
}
