#include <stdio.h>
/**********************
从键盘输入一个百分制分数，将其转化为等级分输出？
90以上，等级为A
80-90,等级为B，
70-80,等级为C，
60-70，等级为D，
60分以下，等级为E
**********************/
int main()
{
	int score = 0;
	while(1)
	{
		printf("please input a score:\n");
		scanf("%d",&score);
		if(score<0 || score >100)
		{
			continue;
		}
		if(score>=90)
		{
			printf("Is Grade A\n");
		}
		else if(score>=80)
		{
			printf("Is Grade B\n");
		}	
		else if(score>=70)
		{
			printf("Is Grade C\n");
		}	
		else if(score>=60)
		{
			printf("Is Grade D\n");
		}	
		else
		{
			printf("Is Grade E\n");
		}
	}
	return 0;
}