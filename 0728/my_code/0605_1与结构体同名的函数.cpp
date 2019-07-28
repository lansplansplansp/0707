#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

typedef struct STU
{
	short stuage;
	int stuscore;
	int stunamelen;	
	char* stuname;
	//实参类型为常量字符串，参数要const char *类型，char *背后的含义是：给我个字符串，我要修改它。
	STU(int age,int score,int namelen,const char *name)
	{
		stuage = age;
		stuscore = score;
		stunamelen = namelen;
		stuname = new char[namelen+1];
		memcpy(stuname,name,stunamelen);
	}
	~STU()
	{
		stuage = 0;
		stuscore = 0;
		stunamelen = 0;
		if(stuname)
		{
			delete stuname;
		}
		stuname = NULL;//释放之后一定要赋值为空，避免野指针
	}
}stu_t;

int main()
{
	char c,c1;
	unsigned char ch;
	c = 128;
	c1 = 127;
	ch = 200;
	printf("c:%d,c1:%d,ch:%d\n",c,c1,ch);//c = -128,c1 = 127;ch = 200//所以该编译器的char型有有符号类型
	stu_t *aa = NULL;
	aa = new stu_t(20,100,strlen("lansp"),"lansp");
	cout << aa->stuage << ' ' << aa->stuscore << ' ' << aa->stuname << endl;
	return 0;
}
//与结构体同名的函数起到构造函数作用，但不能像类一样可以类外定义,前提：用g++编译,还可以做析构函数
umetvwu4e0xh:admin:admin.123:1542594185 
fdd4108d62d96ef100bdb4fb179eeee3
