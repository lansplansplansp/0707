#include <stdio.h>

//输入年份和月份，判断该年是否是闰年，并根据给出的月份判断是什么季节，该月有多少天
int main()
{
	char Leap_year[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
	char Nonleap_year[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	int year;
	int month;
	int flag = 0;
	printf("please input year and month:\n");
	scanf("%d%d",&year,&month);
	if(year%4 == 0 && year%100 != 0 || year%400 == 0)
	{
		printf("Is Leap year,");
		flag = 1;
	}
	else
	{
		printf("Is Nonleap year,");
	}
	if(month>=1 &&month<=3)
	{
		printf("spring,");
	}
	if(month>=4 &&month<=6)
	{
		printf("summer,");
	}	
	if(month>=7 &&month<=9)
	{
		printf("autumn,");
	}
	if(month>=10 &&month<=12)
	{
		printf("winter,");
	}	
	if(flag)
	{
		printf("this month has %d days\n",Leap_year[month]);
	}
	else
	{
		printf("this month has %d days\n",Nonleap_year[month]);
	}
	
	return 0;
}