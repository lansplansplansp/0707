#include<stdio.h>
#include<math.h>

int main()
{
    int n,i,j;
    printf("input:");
    scanf("%d",&n);
    for(i=0;i<=4*n-4;i++){
        if(i%2 != 0)
            continue;
        for(j=0;j<=4*n-4;j++){
            if(j%2 != 0)
                printf(" ");
            else if(j==abs(2*n-2-i))
                printf("*");
            else if(j==4*n-4-abs(2*n-2-i))
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}

