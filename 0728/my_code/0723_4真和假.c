#include <stdio.h>

int main()
{
	if(NULL)
		printf("NULL is jia\n");//假
	if('\0')
		printf("'\0 is jia\n");//假
	if(0)
		printf("0 is jia\n");//假
	if('0')
		printf("'0' is jia\n");//真
	return 0;
}