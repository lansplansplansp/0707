#include <iostream>
#include <math.h>

#include "CRefObject.h"

using namespace std;
//֧�����ü����Ķ���Ҫ��CRefObject�̳�
class CTest: public CRefObject
{
public:
	CTest(int n)
		:m_n(n)
	{
		cout << "CTest(" << m_n << ") \n";
		cout << "GetRefCount in CTest()" << CRefObject::GetRefCount()<< endl;
	}
	~CTest()
	{
		cout << "~CTest(" << m_n << ") \n";
		cout << "GetRefCount in ~CTest()" << CRefObject::GetRefCount()<< endl;
	}
	
	void Print()
	{
		cout << "m_n:" << m_n << "\n";
		cout << CRefObject::GetRefCount()<< endl;
	}
	int m_n;
};
int main(int argc, char* argv[])
{
	{
		CRefPtr<CTest> p1(new CTest(1));
		CRefPtr<CTest> p2(new CTest(2));
		p1->Print();
		p1 = p2;
		p1->Print();
	}
	return 0;
}
