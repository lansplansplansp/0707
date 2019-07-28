#include<stdio.h>
#if 0
typedef enum weak
{
	SUN,//0
	MON,
	TUE,
	WEN,
	THI,
	FRI,
	SAT,//6
}weak_t;

#endif
#if 1
enum DIN//DIR
{
    EAST=100,
    WEST,
    SOUTH,
    NORTH,	 //103
};
int main()
{
    enum DIN din;
    printf("please input a direction\n");
    scanf("%s",din);
    switch(din)
    {
        case EAST:
        {
            printf("100\n");
            break;
        }
	case WEST:
        {
            printf("WEST\n");
            break;
        }
	case SOUTH:
        {
            printf("SOUTH\n");
            break;
        }
	case NORTH:
        {
            printf("NORTH\n");
            break;
        }
    }
}
#endif
#if 0
int main()
{
	printf("%d\t%d\n",SUN,SAT);
	//printf("%d\t%d\n",EAST,NORTH);
}
#endif
