#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <errno.h>

#define ARRSIZE 1024

extern int errno;

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
	int ret;
	int cnt;
	int nfds = 1;
	char buff[1024];
	struct sockaddr_in peer;
	socklen_t size;
	int sfd = tcp_server_init(9876);
	struct pollfd pfds[ARRSIZE];
	pfds[0].fd = sfd;
	pfds[0].events = POLLIN | POLLPRI;
	while(1)
	{
		ret = poll(pfds,nfds,-1);
		if(ret == 0)
			continue;
		if(ret < 0)
		{
			printf("errno:%d,msg:%s\n",errno,strerror(errno));
			break;
		}
		printf("ret = %d\n",ret);
		if((pfds[0].revents&POLLIN) == POLLIN)
		{
			size = sizeof(peer);
			int newfd = accept(sfd,(struct sockaddr *)&peer,&size);
			printf("ip:%s,port:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
			pfds[nfds].fd = newfd;
			pfds[nfds].events = POLLIN | POLLPRI;
			nfds++;
			ret--;
		}
		int i;
		for(i=1;i<nfds;i++)
		{
			if(ret == 0)
				break;
			if((pfds[i].revents&POLLIN) == POLLIN)
			{
				cnt = recv(pfds[i].fd,buff,1024,0);
				if(cnt == 0)
				{
					close(pfds[i].fd);
					pfds[i].fd = 0;
					continue;
				}
				send(pfds[i].fd,buff,cnt,0);
				ret--;
			}
		}
	}
	close(sfd);
	return 0;
}

