#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 2

using namespace std;

typedef struct stu
{
	char *name;
	int age;
}stu_t;

void init_info(stu_t ss[],int num)
{
	int i;
	char name[32];
	for(i=0;i<num;i++)
	{
		scanf("%s %d",name,&ss[i].age);
		ss[i].name = (char *)malloc(sizeof(name+1));
		strcpy(ss[i].name,name);
	}
}

int main()
{
	int i;
	stu_t stu1[NUM];
	memset(stu1,0,sizeof(stu_t)*NUM);
	init_info(stu1,NUM);
	
	char *pListInfo = new char[sizeof(stu_t) * NUM+1];
	memset(pListInfo,0,sizeof(stu_t) * NUM+1);
	memcpy(pListInfo,stu1,sizeof(stu_t) * NUM);
	
	cout << (unsigned long)stu1 << endl;
	cout << (unsigned long)pListInfo << endl;
	printf("pListInfo:%d\n",pListInfo);//cout输出乱码
	//pListInfo:162037800
	for(i=0;i<NUM;i++)
	{
		stu_t *stu2 = (stu_t *)(pListInfo+sizeof(stu_t)*i);		
		cout << i << ':' << stu2->name << ' ' << stu2->age << endl;
		
		//stu_t stu2 = stu1[i];
		//cout << i << ':' << stu2.name << ' ' << stu2.age << endl;
	}
	free(pListInfo);
	for(i=0;i<NUM;i++)
	{
		free(stu1[i].name);
	}
	return 0;
}