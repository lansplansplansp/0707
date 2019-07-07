#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

#include<stdio.h>
int main()
{
    int fd1 = open("1fscanf_scanf.c",O_RDONLY);
    int fd2 = open("1.c.bac",O_WRONLY | O_CREAT);
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
    close(fd1);
    close(fd2);
    return 0;
}
