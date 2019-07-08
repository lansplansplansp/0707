#include <stdio.h>
#include <iostream>
#include <string.h>//memcpy()

using namespace std;

int main()
{
	char a[64][64];
	char path[32] = {0};
	sprintf(path,"./compare/0");
	memcpy(a[0],path,strlen(path));
	cout << a[0] << endl;
	return 0;
}