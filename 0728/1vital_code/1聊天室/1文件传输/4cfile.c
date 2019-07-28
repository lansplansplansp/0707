#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("cfd = %d\n", cfd);
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port   =  htons(6789);
    serv.sin_addr.s_addr  = inet_addr("127.0.0.1");
    connect(cfd, (struct sockaddr *)&serv, sizeof(serv));
    int filefd = open("3sfile.c",O_RDONLY);
    printf("filefd:%d\n",filefd);
    char msghead[11];
    FILE *fp = fopen("3sfile.c","r");
    fseek(fp,0,SEEK_END);
    int len = ftell(fp);
    rewind(fp);
    fclose(fp);
    printf("len:%d\n",len);
    write(cfd,&len,sizeof(len));
    len = strlen("server.bak")+1;
    printf("filenamelen:%d\n",len);
    write(cfd,&len,sizeof(len));
    memcpy(msghead,"server.bak",11);
    printf("msg:%s\n",msghead);
    write(cfd,msghead,sizeof(msghead));
    printf("msghead successful\n");

    char buff[32];
    int cnt;
    while(1)
    {
        cnt = read(filefd,buff,32);
        printf("%s",buff);
        if(cnt==0)break;
        write(cfd,buff,cnt);
    }
    printf("\n");
    close(filefd);
    close(cfd);
    return 0;
}

