#include<stdio.h>
#include<string.h>
#define t2 stu_t1
#if 1
#pragma pack(1)
typedef struct student
{
	char name[20];
	int num;
	short age;
	char sex;
	float score;
}stu_t1;
#endif
#if 0
typedef struct student 
{
	char name[20];
	int num;
	short age;
	char sex;
	float score;
}stu_t1;
#endif
int main()
{
    printf("%d\n",sizeof(t2));
}

