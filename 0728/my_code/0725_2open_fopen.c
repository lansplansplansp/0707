#include <stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include <stdlib.h>
#include <string.h>

//open是UNIX系统（包括LINUX、Mac等）的系统调用函数,是文件IO
//fopen是C语言库函数,是标准IO
int main()
{
#if 0
	int fd1 = open("0626_2spritf.cpp",O_RDONLY);
	//O_CREATE参数时，open第三个参数需要加创建文件的权限
    int fd2 = open("1.c.bac",O_WRONLY | O_CREAT,00200);//写和没有就建立//有返回-1打开文件失败情况
    printf("fd1=%d,fd2=%d\n",fd1,fd2);

    char buff[12];
    int cnt;
    while(1)
    {
        cnt = read(fd1,buff,12);
        if(cnt == 0)
            break;
        write(fd2,buff,cnt);
    }
#endif
#if 1
	FILE *fp = NULL;

    fp = fopen("encode.pcm","r");
    if(NULL == fp)
    {
        printf("file not exist\n");
        return 1;
    }
	fseek(fp,0L,SEEK_END);
	printf("%d:ftell(fp):%d\n",__LINE__,ftell(fp));
#endif
#if 0
	cnt = ftell(fp);
	fseek(fp,0L,SEEK_SET);
	char *buffer;
	if(cnt > 0)
	{
		printf("cnt:%d\n",cnt);
		buffer = (char *)malloc(cnt+1);
	}
	fread(buffer,1,cnt,fp);
	write(1,buffer,cnt);

    char line[1024];
	char *pline;
	while(1){
        pline = fgets(line,1023,fp);
        if(pline == NULL)
            break;
		fputs(line,stdout);
    }
#endif
	//fwrite(fp,1,ftell(fp),stdout);//linux中STDOUT_FILENO表示标准输出文件
								  //C语言中  stdout
	
//    close(fd1);
//    close(fd2);
	
	return 0;
}