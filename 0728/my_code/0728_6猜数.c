#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x = 0;
	int y = 0;
	x = rand()%10;
	printf("(%d)\n",x);
	while(1)
	{
		printf("please input you number:\n");
		scanf("%d",&y);
		if(y != x)
		{
			printf("again...\n");
			continue;
		}
		else 
		{
			printf("Good job\n");
			break;
		}
	}
	
	return 0;
}