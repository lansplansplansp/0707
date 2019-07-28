#include <stdio.h>

//根据输入的三角形的三条边长判定是何种三角形（直角，等边，等腰）
//
int main()
{
	int Side_length[3] = {0};
	int max = 0;
	printf("please input three Side length:\n");
	scanf("%d%d%d",&a,&b,&c);
	max = a;
	max<b?max=b:max;
	max<c?max=c:max;
	printf("%d\n",max);
	
	switch(max)
	{
		case 1: break;
	}
	return 0;
}