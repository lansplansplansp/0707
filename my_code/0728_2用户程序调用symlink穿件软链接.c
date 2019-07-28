#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

//sym是符号Symbol，因为软链接也叫符号链接
//软链接放在共享目录下创建会出现Operation not supported:不支持操作，移动到非共享目录下就可以了
int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		fprintf(stderr,"usage:%s srcfile files\n",argv[0]);
		exit(1);	
	}
	//对源文件创建符号链接(软链接)
	if(symlink(argv[1],argv[2]) < 0)
	{
		perror("symlink error");
		exit(1);
	}
	
	char buffer[1024];
	ssize_t size;
	memset(buffer,0,sizeof(buffer));
	int fd = open(argv[2],O_RDONLY);
	if(fd < 0)
	{
		perror("open error");
		exit(1);
	}
	//读取软链接文件引用的源文件内容
	if((size = read(fd, buffer, sizeof(buffer))) < 0)
	{
		perror("read error");
	}
	else
	{
		write(STDOUT_FILENO, buffer,size);
	}
	
	//读取软链接文件本身内容
	memset(buffer, 0, sizeof(buffer));
	if((size = readlink(argv[2],buffer, sizeof(buffer))) < 0)
	{
		perror("readlink error");
	}
	else
	{
		write(STDOUT_FILENO, buffer, size);
	}
	printf("\n");
	close(fd);
	
	return 0;
}












