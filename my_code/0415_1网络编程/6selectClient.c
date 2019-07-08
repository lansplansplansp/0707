#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define ARRSIZE 1024

int tcp_client_init(int port)
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
	serv.sin_port = htons(port);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	int on = 1;
	setsockopt(cfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    int ret = connect(cfd,(struct sockaddr *)&serv,sizeof(serv));
	if(ret == -1)
	{
		perror("connect error\n");
        return 1;
	}
	else
		printf("connect success! ret = %d\n",ret);
	return cfd;
}

int main()
{
	fd_set wset;
	fd_set rset;
	int cfd = tcp_client_init(9876);
	int fdarr[ARRSIZE] = {0};
	int fdi = 0;
	fdarr[fdi++] = cfd;
	int maxfd = cfd;
	int cnt;
	char buff[1024];
	struct sockaddr_in peer;
	socklen_t size;
	
	struct timeval to = {0};
	to.tv_sec = 3;//3秒
	to.tv_usec= 0;//0微秒	
	
	int error = 1;
	int	error_len = sizeof(int);
	
	
	while(1)
	{
		FD_ZERO(&wset);
		int i;			
		FD_SET(cfd,&wset);
		select(maxfd+1,&rset,&wset,NULL,&to);
		if(FD_ISSET(cfd,&wset))
		{
			if (getsockopt(cfd, SOL_SOCKET, SO_ERROR, (char *)&error, (socklen_t *)&error_len) < 0)//成功返回0
			{
				error = 1;
				printf("connect failed,cfd = %d,error = %d\n",cfd,error);
				sleep(2);
			}
			else
			{
				printf("socket success,cfd = %d,error = %d\n",cfd,error);            
				FD_SET(cfd,&rset);
				sleep(2);
			}
		}
		if(FD_ISSET(cfd,&rset))
		{
			printf("rset have something\n");            
			memset(buff,0,1024);
			fgets(buff,1024,stdin);
			write(cfd,buff,strlen(buff));
			printf("after write\n");//当接收不到信息，阻塞等待（服务端出问题）
			cnt = recv(cfd,buff,1024,0);				
			printf("after recv\n");

			if(cnt == 0)
			{
				close(cfd);
				FD_CLR(cfd,&wset);
				cfd = 0;
				continue;
			}
			printf("buff :%s",buff);
		}
	}
	close(cfd);
	printf("cfd :%d",cfd);//不打印直接关掉
	return 0;
}

