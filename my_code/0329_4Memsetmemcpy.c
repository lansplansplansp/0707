#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char d[100];
	char *s="Golden Global View";
	memset(d,0,sizeof(d));
	memcpy(d,s, strlen(s));
	printf("%s\n",d);
	printf("指针大小：%d\n",sizeof(s));
	return 0;
}