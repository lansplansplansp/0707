#include<stdio.h>
#include<time.h>

int main()
{
    srand(time(NULL));
    int a[4];
    int k,i,b,c,max=0,min=101;
    b=c=0;
    for(i=0;i<4;i++){
       a[i]=rand()%100;
       printf("%d,",a[i]);
    }
    printf("\n");
    for(i=0;i<4;i++){
       if(a[i]>max){
           max=a[i];
           b=i;
       }
    }
    k=a[0];a[0]=max;a[b]=k;
    for(i=0;i<4;i++){
       if(a[i]<min){
           min=a[i];
           c=i;
       }
    }
    k=a[3];a[3]=min;a[c]=k;
    for(i=0;i<4;i++){
       printf("%d,",a[i]);
    }
    printf("\n");
    return 0;
}
