#include <iostream>

using namespace std;

class Complex
{
public:
	Complex():real(0),imag(0){};
	Complex(double r,double i):real(r),imag(i){};
	Complex(double r):real(r),imag(0){};
	
	void Print()
	{
		cout << "real = " << real << "imag = " << imag << endl;
	}
	Complex operator+(Complex c)
	{
		return Complex(this->real + c.real,this->imag +c.imag);
	}
private:
	double real;
	double imag;
};

int main()
{
	Complex c;
	c = 1.2;
	c.Print();//real = 1.2imag = 0
	Complex c1(2.9,4.1);
	Complex c2 = c1 + 3.1;
	c2.Print();//real = 6imag = 4.1
	return 0;
}