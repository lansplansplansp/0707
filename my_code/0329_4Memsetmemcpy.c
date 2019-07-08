#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

typedef struct STU
{
	short age;
	int score;
}stu_t;

int main()
{
#if 0
	stu_t sa;
	stu_t sb = {18,100};
	memset(&sa,0,sizeof(sa));
	memcpy(&sa,&sb,sizeof(sb));
	cout << sa.age << ' ' << sa.score << endl;
#endif
#if 1
	char d[100];
//警告：已弃用从字符串常量转换为“char*”（解决：0403_1重载解决已弃用字符串常量转为char型指针问题.cpp）
//将*s改为s[]就没有warning了。
	char s[]="Golden Global View";
	memset(d,0,sizeof(d));
	memcpy(d,s, strlen(s));
	printf("%s\n",d);
	printf("指针大小：%d\n",sizeof(s));
	//8,所以是64位操作系统（改为s[]就不是8，是19）
	
#endif
	return 0;
}