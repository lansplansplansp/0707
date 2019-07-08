#include <iostream>

using namespace std;

class Point
{
public:
	Point();
};

Point::Point()
{
	
}

Point *P = new Point();

Point *test()
{
	return P;
}

int main()
{
	int *ch = NULL;
	if(!ch)
		cout << "ch is OK!" << endl;
	cout << !ch << endl;
	if(test())
		cout << "test is OK!" << endl;
	else
		cout << "test error!" << endl;
	cout << test() << endl;
	return 0;
}