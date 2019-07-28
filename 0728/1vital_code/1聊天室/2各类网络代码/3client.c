#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int cfd = socket(AF_INET,SOCK_STREAM,0);
    if(cfd < 0)
    {
        perror("socket create cfd error\n");
        return 1;
    }
    printf("cfd = %d\n",cfd);
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(9876);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(cfd,(struct sockaddr *)&serv,sizeof(serv));

    char buff[1024];
    int pid = fork();
    if (pid < 0)
    {
        printf ("error!\n");
        exit(-1);
    }
    if (pid == 0)
    {
        while (1)
        {
            printf("in child's write:\n");
            memset(buff,0,1024);
            fgets(buff,1024,stdin);
            write(cfd,buff,strlen(buff));
        }
    }
    else
    {
        while (1)
        {
            printf("in parent's read:\n");
            memset(buff,0,1024);
            if(read(cfd,buff,1024) <= 0)
                break;
            fputs(buff,stdout);
        }
    }
    close(cfd);
    return 0;
}

