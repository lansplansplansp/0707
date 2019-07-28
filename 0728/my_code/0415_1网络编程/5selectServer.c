#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ARRSIZE 1024

int tcp_server_init(int port)
{
	int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd < 0)
    {
        perror("socket create sfd error\n");
        return 1;
    }
    printf("sfd = %d\n",sfd);
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(9876);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int on = 1;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	
	int ret = bind(sfd,(struct sockaddr *)&serv,sizeof(serv));
	if(ret == -1)
	{
		perror("bind error\n");
        return 1;
	}
	else
		printf("connect success! ret = %d\n",ret);
	listen(sfd,5);
	return sfd;
}

int main()
{
	int sfd = tcp_server_init(9876);
 	fd_set rset;
	int fdarr[ARRSIZE] = {0};
	int fdi = 0;
	fdarr[fdi++] = sfd;
	int maxfd = sfd;
	int cnt;
	char buff[1024];
	struct sockaddr_in peer;
	socklen_t size;
	while(1)
	{
		FD_ZERO(&rset);
		int i;
		for(i = 0;i<fdi;i++)
			FD_SET(fdarr[i],&rset);
		select(maxfd+1,&rset,NULL,NULL,NULL);
		if(FD_ISSET(sfd,&rset))
		{
			size = sizeof(peer);
			int newfd = accept(sfd,(struct sockaddr *)&peer,&size);
			printf("ip:%s,port:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
			fdarr[fdi++] = newfd;
			if(maxfd<newfd)
				maxfd = newfd;
		}
		for(i = 1;i<fdi;i++)
		{
			if(fdarr[i]!=0&&FD_ISSET(fdarr[i],&rset))
			{			
				printf("enter i = %d\n",i);
				memset(buff,0,1024);
				cnt = recv(fdarr[i],buff,1024,0);
				printf("buff :%s",buff);
				if(cnt == 0)
				{
					close(fdarr[i]);
					FD_CLR(fdarr[i],&rset);
					fdarr[i] = 0;
					continue;
				}			
				printf("start send\n");

				send(fdarr[i],buff,cnt,0);
							
				printf("after send\n");

			}
		}
	}
	close(sfd);	
	printf("sfd :%d",sfd);//不打印直接退出
	return 0;
}

