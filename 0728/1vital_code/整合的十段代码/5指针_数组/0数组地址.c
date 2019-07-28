#include<stdio.h>

int main()
{
    int a[2][3]={{0,2,3},{5,6,7}};
    //int a[2][3]={0,2,3,5,6,7};
    a[0][0]=10;
    int i,j;
    int n=0;
    for(i=0;i<2;i++){
        for(j=0;j<3;j++){
            a[i][j] = n++;
            printf("%d,",a[i][j]);
            printf("%p,",&a[i][j]);
        }
        printf("\n");
    }
    printf("sizeof(a)=%d\n",sizeof(a));
    return 0;
}
