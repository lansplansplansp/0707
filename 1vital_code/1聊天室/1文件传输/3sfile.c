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
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("sfd = %d\n", sfd);
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port   =  htons(6789);
    serv.sin_addr.s_addr  = htonl(INADDR_ANY);
    int on = 1;
    setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    int ret ;
    ret = bind(sfd,(struct sockaddr *)&serv,sizeof(serv));
    printf("bind ret = %d\n", ret);
    listen(sfd, 5);
    int newfd;
    newfd = accept(sfd, NULL, NULL);
    printf("newfd = %d\n", newfd);
    int total;
    int filenamelen;
    char filename[32];
    read(newfd,&total,4);
    printf("total:%d\n",total);
    read(newfd,&filenamelen,4);
    printf("filenamelen:%d\n",filenamelen);
    read(newfd,filename,filenamelen);
    printf("filename:%s\n",filename);
    int filefd = open(filename,O_WRONLY|O_CREAT);
    char buff[32];
    int cnt;
    int acc = 0;

    while(1)
    {
        cnt = read(newfd, buff, 32);
        printf("%s",buff);
        if(cnt==0)break;
        acc += cnt;
        write(filefd, buff, cnt);
    }
    printf("\n");
    if(acc==total)
    printf("successful\n");
    close(filefd);
    close(newfd);
    close(sfd);
    return 0;
}
