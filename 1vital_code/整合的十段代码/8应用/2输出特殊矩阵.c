#include<stdio.h>

int main()
{
    int a[10][10]={100};
    int i,j;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            if(j==0)
                a[i][0]=1;
            else if(i==j)
                a[i][j]=1;
            else  printf(" ");
        }
    }
    printf("\n\n");
    for(i=2;i<10;i++){
        for(j=1;j<i;j++){
            a[i][j]=a[i-1][j]+a[i-1][j-1];
        }
    }
    for(i=0;i<10;i++){
        for(j=0;j<=i;j++){
            printf("%4d,",a[i][j]);
        }
        printf("\n\n");
    }
    return 0;
}
