#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define ARRSIZE 1024

int server_init_port(int port)
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
	int cnt;
	char buff[1024];
	int sfd = server_init_port(9876);
	int epfd = epoll_create(ARRSIZE);
	struct epoll_event ev;
	ev.data.fd = sfd;
	ev.events = EPOLLIN | EPOLLPRI;
	epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&ev);
	struct epoll_event revs[ARRSIZE];
	int evcnt;
	struct sockaddr_in peer;
	socklen_t size;
	while(1)
	{
		evcnt = epoll_wait(epfd,revs,ARRSIZE,-1);
		int i;
		for(i=0;i<evcnt;i++)
		{
			if(revs[i].data.fd == sfd)
			{
				size = sizeof(peer);
				int newfd = accept(sfd,(struct sockaddr *)&peer,&size);
				printf("newfd:%d,ip:%s,port:%d\n",newfd,inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
				ev.data.fd = newfd;
				ev.events = EPOLLIN | EPOLLPRI;
				epoll_ctl(epfd,EPOLL_CTL_ADD,newfd,&ev);
			}
			else
			{
				cnt = recv(revs[i].data.fd,buff,1024,0);
				if(cnt == 0)
				{
					ev.data.fd = revs[i].data.fd;
					epoll_ctl(epfd,EPOLL_CTL_DEL,revs[i].data.fd,&ev);
					close(revs[i].data.fd);
				}
				send(revs[i].data.fd,buff,cnt,0);
			}
		}
	}
	close(sfd);
	return 0;
}
