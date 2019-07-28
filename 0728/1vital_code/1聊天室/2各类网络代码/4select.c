#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define ARRSIZE 1024

int tcp_server_init(int port)
{
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	printf("sfd = %d\n",sfd);

	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	int on = 1;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	int ret = bind(sfd,(struct sockaddr *)&serv,sizeof(serv));
	printf("ret = %d\n",ret);
	listen(sfd,5);
	return sfd;
}

int main()
{
	fd_set rset;
	int sfd = tcp_server_init(9876);
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
				cnt = recv(fdarr[i],buff,1024,0);
				if(cnt == 0)
				{
					close(fdarr[i]);
					FD_CLR(fdarr[i],&rset);
					fdarr[i] = 0;
					continue;
				}
				send(fdarr[i],buff,cnt,0);
			}
		}
	}
	close(sfd);
	return 0;
}

