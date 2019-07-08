#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int fun(char *pstr)
{
	if(pstr == NULL)
		cout << "pstr is NULL" << endl;
	else
		cout << "true" << endl;
	return 0;
}

int fun2(int *pstr)
{
	cout << "int fun2" << endl;
	cout << pstr[0] << endl;
	return 0;
}

int main()
{
	int nMediaBufLen = 2048;
	char *pMediaBuff = (char*)malloc(nMediaBufLen);
	if(!pMediaBuff)
	{
		cout << "pMediaBuff is NULL" << endl;
	}
	else 
		cout << "pMediaBuff is not NULL" << endl;
	int *pfd = NULL;
	if(!pfd)
		cout << "pfd is 0"<< endl;
	int fd = 3;
	fun2(&fd);
	typedef int	fd_mask;	
	fd_mask y = 8;
	cout << "y = " << y << endl;
	unsigned char zy;
	zy = 0;
	if(!zy)
		cout << "is ok " << endl;
	else
		cout << "not ok " << endl;
	int x = 0;
	char ss[10] = {0};
	fun(ss);
	cout << sizeof(ss) << endl;
	cout << strlen(ss) << endl;
	while(1)
	{	
		if(x != -1)
		{
			cout << x << endl;
			x++;
			sleep(1);
			continue;
		}
		cout << "!!" << endl;//永远不会走到这
	}
	return 0;
}