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
    char headBuff[1024*1024] ={0};
	char Jsonbuff[1024*1024*3] = {0};
	char *pstr = NULL,*pString = NULL;
    int cnt = 0;
	int i, contentlen=0;
	char pLength1[12];
    cnt = recv(sockfd, headBuff, 1024*1024,0);//接收HTTP请求头
	
	pstr = strstr(headBuff,"Content-Length:");
	
	for(i=0;i < 12;i++)
	{
		if(pstr[strlen("Content-Length:")+i]=='\r')
			break;
		pLength1[i]=pstr[strlen("Content-Length:")+i];				
	}
	contentlen=atoi(pLength1);//获得body长度
	printf("contentlen = %d\n",contentlen);
	
	printf("cnt = %d \n",cnt);
	printf("headBuff = %s \n",headBuff);
	
	pString = strstr(headBuff, "\r\n\r\n");
	if (pString)
	{
		pString += strlen("\r\n\r\n");
		cnt -= (pString - headBuff);
	}
	
	printf("after cnt = %d \n",cnt);//=0

	memcpy(Jsonbuff, pString, cnt);
	printf("before Jsonbuff:%s \n",Jsonbuff);//空

	if(pstr != NULL)
	{
		int lens=0;
		while(cnt < contentlen)
		{
			//lens = recv(sockfd, Jsonbuff+cnt, contentlen-cnt,0);//OK
			lens = read(sockfd, Jsonbuff+cnt, contentlen-cnt);//OK
			cnt += lens;
		}
	}
	printf("Jsonbuff = %s \n",Jsonbuff);
}
int main()
{
    int fd = tcp_serv_init(9876);//sfd

    int newfd;
    while(1)
    {
        printf("waitng for client .......\n");
        newfd = accept(fd, NULL, NULL);
        printf("client connect successful\n");
        serve(newfd);
        close(newfd);
    }
    close(fd);
    return 0;
}

