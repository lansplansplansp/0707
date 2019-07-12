#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main()
{
	char ch = '\0';
	if(&ch == NULL)
	{
		cout << "ch is NULL" << endl;
	}
	else
	{
		cout << "ch is not NULL" << endl;
	}
	return 0;
}
//非指针的类型定义了就不可能有空的情况