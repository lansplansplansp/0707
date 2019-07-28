#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//执行参数第三个以后可以创建多个硬链接文件
//unlink函数调用配套使用(还没写)
int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr,"usage:%s srcfile files\n",argv[0]);
		exit(1);
	}
	int i;
	for(i = 2; i < argc;i++)
	{
		if(link(argv[1],argv[i]) < 0)
		{
			perror("link error");
			continue;//创建不成功的下一个还要创建的
		}
	}
	printf("create success\n");
	
	return 0;
}