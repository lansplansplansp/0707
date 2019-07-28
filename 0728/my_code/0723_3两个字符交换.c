#include <stdio.h>

int main()
{
	char ch1 = 'a';
	char ch2 = 'b';
	char cht;
	cht = ch1;
	ch1 = ch2;
	ch2 = cht;
	printf("%c,%c\n",ch1,ch2);
}