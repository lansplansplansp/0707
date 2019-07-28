#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

#include<stdio.h>
int main()
{
	int x;
	//read(0,&x,sizeof(x));
	//write(1,&x,sizeof(x));
	//read(STDIN_FILENO,&x,sizeof(x));
	//write(STDOUT_FILENO,&x,sizeof(x));
	int fd1;
	int fd2;
	fd1 = fileno(stdin);
	fd2 = fileno(stdout);
	read(fd1,1,sizeof(1));
	write(fd2,&x,sizeof(x));
	return 0;
}
