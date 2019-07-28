#include<stdio.h>

int main()
{
    int i,j;
    int r=0,w=0;
    int max;
    int a[4][5];
    for (i=0;i<4;i++){
        for(j=0;j<5;j++){
           a[i][j]=rand()%100;
           printf("%d,",a[i][j]);
        }
        printf("\n");
    }
    max=a[0][0];
    for(i=0;i<4;i++){
       for(j=0;j<5;j++){
          if(max<a[i][j]){
              max=a[i][j];
              r=i;w=j;
          }
            //  printf("%d,%d,%d\n",max[r][w],r,w);
       }
    }
    printf("max[%d][%d] = %d\n",r,w,max);
    return 0;
}
