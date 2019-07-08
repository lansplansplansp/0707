#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef struct stu
{
	int socre;
	int age;
	char sname[36];
}stu_t;

int main()
{
	int x = 1;
	cout << !x << endl;
	cout << x << endl;
	/*
	stu_t *ss = NULL;
	stu_t STU = {99,18,"huihui"};
	char Buff[sizeof(stu_t)+1]= {0};
	ss = (stu_t *)Buff;
	cout << ss->sname <<endl;
	strcpy(ss->sname,"tylan");
	cout << ss->sname <<endl;
	ss -> age = 20;
	cout << ss->age <<endl;
	cout << sizeof(ss->sname) <<endl;
	memset(ss->sname,0,strlen(ss->sname));
	memcpy(ss->sname,"cheng",strlen("cheng"));
	cout << ss->sname <<endl;
	cout << sizeof(ss) << ' ' << sizeof(STU) << endl;
	*/
	return 0;
}
//结构体指针需要先给地址