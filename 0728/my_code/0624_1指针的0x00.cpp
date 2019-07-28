#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main()
{
	char *pstr = "\r";
	char *pLength1 = "1024";//直接1024是int型系统判断错误
	int i=0;
	cout << strlen(pstr) << endl;
	int contentlen=atoi(pLength1);
	cout << contentlen << endl;
	while(*pstr != 0x00)
	{
		cout << pstr[i] << endl;
		pstr++;
	}
	return 0;
}
//0x00==NULL=='\0'==0