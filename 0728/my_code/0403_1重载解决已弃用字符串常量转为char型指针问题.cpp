#include <iostream>

using namespace std;

void func(char *a)
{
	cout << a << endl;
}

void func(const char *a)
{
	cout << a << endl;
}

int main()
{
	char a[] = "hello 123";
	func(a);
	const char b[] = "hello 123";
	func(b);
	
	return 0;
}