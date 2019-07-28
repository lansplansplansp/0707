#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

using namespace std;

int main()
{
	char *pJsonBuff = NULL;
	int contentlen = 10;
	pJsonBuff = (char *)malloc(contentlen + 128);
	cout << sizeof(pJsonBuff) << endl;//4
	printf("pJsonBuff:%p\n",pJsonBuff);
	if(pJsonBuff[0] == '\0')
	{
		printf("pJsonBuff[0] == 0\n");
		//cout << "pJsonBuff[0] == "\0"" << endl;
	}
	if(pJsonBuff[sizeof(pJsonBuff)] == '\0')
	{
		//cout << "pJsonBuff[sizeof(pJsonBuff)] == "\0"" << endl;
		printf("pJsonBuff[sizeof(pJsonBuff)] == 0\n");
	}
	return 0;
}
//malloc之后就有地址了,malloc开辟的空间里面填满了'\0'