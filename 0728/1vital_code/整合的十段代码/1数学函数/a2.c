#include<stdio.h>
#include<math.h>

int main()
{
    int n,a,i,j,sum1 = 0, sum2 = 0;

    printf("please input a,n\n");
    scanf("%d,%d",&n,&a);
    for(i = 0;i<n;i++){
        sum1 = 0;
        for(j = 0;j<i;j++){
            sum1+=a*pow(10,j);
        }
    }
    sum2 += sum1;
    printf("%d/n",sum2);
    return 0;
}
