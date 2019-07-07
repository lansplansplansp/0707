#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	char *p;
	p = new char[10];
	if(p == NULL)
	{
		printf("p is NULL!\n");
	}
	else 
		printf("p is not NULL!\n");
	printf("0:%c\t '0':%c\n",0,'0');
	printf("0:%d\t '0':%d\tNULL:%d\t'\\0':%d\n",0,'0',NULL,'\0');
	return 0;
}