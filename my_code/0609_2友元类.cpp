#include <iostream>
 
using namespace std;
class B;
class A;
void Show( A& , B& );
 
class B
{
private:
	int tt;
	friend class A;
	friend void Show( A& , B& );
	 
public:
	B( int temp = 100):tt ( temp ){}
	/*报错
	void Show( A &a )
	{
	  cout << a.value << endl;
	  cout << tt << endl; 
	}
	*/
	//B不是A的友元类
};
 
class A
{
private:
	int value;
	//friend class B;加了这个也报错
	friend void Show( A& , B& );
	 
public:
	A(int temp = 200 ):value ( temp ){}
	 
	void Show( B &b )
	{
	  cout << value << endl;
	  cout << b.tt << endl; 
	}
};
 
void Show( A& a, B& b )
{
	cout << a.value << endl;
	cout << b .tt << endl;
}
 
int main()
{
	cout << "hello world" << endl;
	A a;
	B b;
	a.Show( b );//200 	100
	Show( a, b );//200	100
    return 0;
}
//如果A是B的友元类，B不一定是A的友元类
