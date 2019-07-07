#include<stdio.h>
#include<time.h>

int main()
{
    srand(time(NULL));
    int a[10][10];
    int i,j,sum=0;
    for (i=0;i<10;i++){
        for(j=0;j<10;j++){
           a[i][j]=rand()%100;
        }
    }
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            printf("%4d,",a[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<10;i++){
       for(j=0;j<10;j++){
          if(i==j){
              sum+=a[i][j];
          }
       }
    }
    printf("%d\n",sum);
    return 0;
}
