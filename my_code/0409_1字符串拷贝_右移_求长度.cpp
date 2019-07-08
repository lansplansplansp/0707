#include <iostream>
#include <string.h>
#include <assert.h>
#define MAX 20

using namespace std;
#if 1
//2
void my_strcpy3(char *Dstr,char *Cstr)
{
	while((*Dstr++ = *Cstr++) != '\0');
}
//4
void my_strcpy2(char *Dstr,const char *Cstr)
{
	while((*Dstr++ = *Cstr++) != '\0');
}
//7
void my_strcpy1(char *Dstr,const char *Cstr)
{
	assert(Dstr != NULL && Cstr != NULL);
	while((*Dstr++ = *Cstr++) != '\0');
}
//10
char *my_strcpy(char *Dstr,const char *Cstr)
{
	assert(Dstr != NULL && Cstr != NULL);
	char *astr = Dstr;
	while((*Dstr++ = *Cstr++) != '\0');
	return astr;
}
#endif
void my_move1(char *pstr,int steps)
{
	int n = sizeof(pstr)-steps;
	char temp[MAX];
	strcpy(temp,pstr+n);
	strcpy(temp+steps,pstr);
	*(temp+sizeof(pstr)) = '\0';
	strcpy(pstr,temp);
}
//换做mencpy就有问题
void my_move2(char *pstr,int steps)
{
	int n = sizeof(pstr)-steps;
	char tmp[MAX];
	memmove(tmp,pstr+n,steps);
	memmove(pstr+steps,pstr,n);
	memmove(pstr,tmp,steps);
}

int main()
{
	char str[] = "12345678";//不能传超过指针字节数量
	char str1[] = " ";//是""就不报错但结果不正常
	my_strcpy3(str1,str);
	cout << str1 << endl;
	cout << str << endl;
	my_move2(str,3);
	cout << str << endl;
	my_move1(str,2);
	cout << str << endl;
	return 0;
}