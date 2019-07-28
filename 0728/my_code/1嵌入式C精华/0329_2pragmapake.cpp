#include<stdio.h>
#include<string.h>

using namespace std;

#define t1 stu_t1

#if 1
//#pragma pack(1)放这里下面两个都影响
typedef struct student
{
	char name[20];
	int num;
	short age;
	char sex;
	float score;
}stu_t1;
#endif

#if 1
#pragma pack(1)
typedef struct Student 
{
	char name[20];
	int num;
	short age;
	char sex;
	float score;
}stu_t2;
#endif
int main()
{
    printf("%d\n",sizeof(t1));
	printf("%d\n",sizeof(stu_t2));
	return 0;
}

