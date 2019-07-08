#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

//服务端接收图片
//客户端发送图片

int tcp_serv_init(int serv_port)
{
    int port = serv_port;
    int servfd;
    servfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in  servaddr;
    servaddr.sin_family= AF_INET;
    servaddr.sin_addr.s_addr = 	htonl(INADDR_ANY);
    servaddr.sin_port =  htons(port);
	
	int on = 1;
	int s = setsockopt(servfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	if(s<0)
	{
		perror("setsockopt");
		exit(6);
	}
    
	int ret;
	printf("ip:%s,port:%d\n",inet_ntoa(servaddr.sin_addr),ntohs(servaddr.sin_port));
    ret = bind(servfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if(ret < 0 )
    {
        printf("bind error\n");
        exit(1);
    }
    listen(servfd, 5);
    return servfd;
}

void serve(int sockfd)
{
	printf("enter the reve sockfd:%d\n",sockfd);
    char headBuff[1024*1024] ={0};
    read(sockfd, headBuff, 1024*1024);//接收HTTP请求头
	printf("read after\n");
	printf("headBuff:%s \n",headBuff);
	return;
}
int main()
{
    int fd = tcp_serv_init(9876);//sfd

    int newfd;
    while(1)
    {
        printf("waitng for client, fd:%d.......\n",fd);
        newfd = accept(fd, NULL, NULL);
        printf("client connect successful, newfd = %d\n",newfd);
        serve(newfd);
        close(newfd);
    }
    close(fd);
    return 0;
}

