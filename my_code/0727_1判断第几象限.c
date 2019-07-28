#include <stdio.h>

//输入一个点的二维坐标，判断该点在第几象限
//坐标上的点不属于象限
int main()
{
	int x = 0;
	int y = 0;
	while(1)
	{
		printf("please input two number:\n");
		scanf("%d%d",&x,&y);
		x>0?(x=1):(x=-1);//不写括号会报错
		switch(x)
		{
			case 1:
				if(y>0)
				{
					printf("Is first quadrant\n");
				}
				else
				{
					printf("Is fourth quadrant\n");
				}
				break;
			case -1:
				if(y>0)
				{
					printf("Is second quadrant\n");
				}
				else
				{
					printf("Is third quadrant\n");
				}
				break;
			default:
				break;
		}	
	}
	
	return 0; 
}