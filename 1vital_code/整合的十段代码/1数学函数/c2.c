#include<stdio.h>
#include<math.h>

int main()
{
    double pi=0.0,k=1.0,t=1.0;
    while(1){
        pi += k/t;
        if(fabs(k/t)<1e-6)
            break;
        k -= k;
        t += 2;
    }
    printf("%f\n",4*pi);
    return 0;
}
