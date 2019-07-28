#include <stdio.h>

//从键盘输入一个字符，若为小写字母，则转化为大写字母;若为大写字母，则转化为小写字母;否则转化为ASCII码表中的下一个字符。
int main()
{
	char ch = '\0';
	
	printf("please input a char:\n");
	scanf("%c",&ch);
	char ch1 = getchar();
	
	if(ch>='a' && ch<='z')
	{
		ch = ch - ('a'-'A');
	}
	else if(ch>='A' && ch<='Z')
	{
		ch = ch + ('a'-'A');
	}
	else 
	{
		ch = ch +1;
	}
	printf("ch:%c\n",ch);
	
	return 0;
}