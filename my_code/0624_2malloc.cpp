#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main()
{
	char *pJsonBuff = NULL;
	int contentlen = 10;
	pJsonBuff = (char *)malloc(contentlen + 128);
	cout << sizeof(pJsonBuff) << endl;
	printf("pJsonBuff:%p\n",pJsonBuff);
	return 0;
}
//malloc之后就有地址了