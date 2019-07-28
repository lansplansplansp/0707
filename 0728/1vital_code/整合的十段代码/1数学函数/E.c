#include<stdio.h>
#include<math.h>
#define PI 3.141592653
#define MUL (x,y) x*y

int main()
{
//  MUL(1,2);
    //MUL(1+2,3+4);?
    printf("%lf\n",sqrt(10));
    printf("%lf\n",sin(20));
    printf("%s,%s,%d\n",__FILE__,__FUNCTION__,__LINE__);
    double s1 = PI * 2;
    double s2 = PI * 3;
    return 0;
}
