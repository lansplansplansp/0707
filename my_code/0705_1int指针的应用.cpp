#include <stdio.h>
#include <iostream>
#include <stdlib.h>

int main()
{
	int *msg = new int;
	*msg = 1;
	printf("*msg = %d\n",*msg);
	
	char *pstr = 0;
	if(pstr == NULL)
	{
		printf("pstr == NULL\n");
	}
	else
	{
		printf("pstr != NULL\n");
	}
	
	return 0;
}