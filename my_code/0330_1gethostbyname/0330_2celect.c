#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <netdb.h>

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
	struct hostent *hptr;
	
	
	
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
//将NULL以形参传入，即不传入时间结构，就是将select置于阻塞状态，一定等到监视文件描述符集合中某个文件描述符发生变化为止
		select(maxfd+1,&rset,NULL,NULL,NULL);
		if(FD_ISSET(sfd,&rset))
		{
			size = sizeof(peer);
			int newfd = accept(sfd,(struct sockaddr *)&peer,&size);
			printf("ip:%s,port:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
			
			hptr = gethostbyname(inet_ntoa(peer.sin_addr));
			printf("hptr->h_name:%s\nhptr->h_aliases:%s\nhptr->h_addrtype:%d\nhptr->h_length:%d\nhptr->h_addr_list:%s\n"
			,hptr->h_name,
			hptr->h_aliases,
			hptr->h_addrtype,
			hptr->h_length,
			(hptr->h_addr_list)
			);
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

