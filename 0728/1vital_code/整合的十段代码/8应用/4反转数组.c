#include<stdio.h>
#include<time.h>
#define N 10

int main()
{
    srand(time(NULL));
    int a[N];
    int i,t;
    for(i=0;i<N;i++){
        a[i]=rand()%100;
            printf("%4d,",a[i]);
    }
    printf("\n");
    for(i=0;i<N/2;i++){
        t=a[i],a[i]=a[N-i-1],a[N-i-1]=t;
    }
    for(i=0;i<10;i++){
        printf("%4d,",a[i]);
    }
    printf("\n");
    return 0;
}
