#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
	char name[36] = "何俊_084_男.jpg";
	cout << strstr(name,"男") << endl;
	
	return 0;
}