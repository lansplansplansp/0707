#include<stdio.h>
//标准i/o有缓冲区(数据不能被保护，例如关机后就没了)，文件i/o没有缓冲区；
int main()
{
#if 0
	char x = '#';
	int i;
	for(i=0;i<1024;i++)
	{
		printf("%c",x);
	}
	while(1)
	;
#endif
#if 0
	char x = '#';
	int i;
	for(i=0;i<1025;i++)
	{
		printf("%c",x);
	}
	while(1)
	;
#endif
#if 0
	char x = '#';
	int i;
	for(i=0;i<1024;i++)
	{
		printf("%c",x);
		fflush(stdout);
	}
	while(1)
	;
#endif
#if 1 
	char x = '#';
	int i;
	for(i=0;i<1024;i++)
	{
		printf("%c",x);
		printf("\n");
	}
	while(1)
	;
#endif
#if 0
	printf("%d\n", BUFSIZ);
	char x = '#';
	int i;
	for(i=0;i<1024;i++)//1'1025;
	{
		printf("%c",x);
		//2'printf("\n");
		fflush(stdout);//这三种方法都会使这个程序缓冲区溢出；
	}
	while(1)
	;
#endif
	return 0;
}
