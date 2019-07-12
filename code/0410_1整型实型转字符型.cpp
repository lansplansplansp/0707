#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;

//C++任意类型转化成字符串
void my_CPlus()
{
	string s1 = "1";
	ostringstream os;
	os << s1 << 1 << "---" << 0.235;
	s1 = os.str();
	cout << s1 << endl;
}

void my_itoa(int a,char *pstr)
{
	char ch;
	int n,i=0;
	if(a == 0)
	{
		pstr[i] = '0';
		return;
	}
	while(a)
	{
		n = a%10;
		a /= 10;
		ch = '0'+n;
		pstr[i] = ch;
		i++;
	}
	pstr[i++] = '\0';
}

void my_ftoa(float a,char *pstr)
{
	int c,m,n = 10,i=0,t=0;
	char ch;
	float b = a;
	while(b != (int)b)
	{
		t++;
		n *= 10;
		b = a*n;
	}
	c = b;
	cout << c << endl;
	while(c)
	{
		m = c%10;
		c /= 10;
		ch = '0'+m;
		if(t == i)
		{
			pstr[i] = ch;
			pstr[++i] = '.';
		}
		else
		{	
			pstr[i] = ch;
		}
		i++;
	}
	pstr[i++] = '\0';
}

int main()
{
	char str[10] ;
	char str1[10] ;
	int j=0,i,da = 12345;
	float fa = 123.45;
	
	my_itoa(da,str);
	cout << str << endl;
	cout << "strlen(str):" << strlen(str) << endl;
	for(i=strlen(str)-1;i>=0;i--)
	{
		str1[j] = str[i];
		printf("str1[%d]:%c\n",j,str1[j]);
		j++;
	}
	j = 0;
	cout << "str1:" << str1 << endl;
	my_CPlus();
	my_ftoa(fa,str);
	cout << str << endl;
	for(i=strlen(str)-1;i>=0;i--)
	{
		str1[j] = str[i];
		printf("str1[%d]:%c\n",j,str1[j]);
		j++;
	}
	cout << "str1:" << str1 << endl;
	
	return 0;
}