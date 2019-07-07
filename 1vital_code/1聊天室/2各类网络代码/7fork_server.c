#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	printf("%d\n",sfd);

	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(9876);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	int on = 1;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	int ret = bind(sfd,(struct sockaddr *)&serv,sizeof(serv));
	printf("ret = %d\n",ret);

	listen(sfd,5);
	int cnt;
	int newfd;
	char buff[1024];
	struct sockaddr_in peer;
	socklen_t size;
	while(1)
	{
		size = sizeof(peer);
		newfd = accept(sfd,(struct sockaddr *)&peer,&size);
		printf("ip:%s,port:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
		int pid = fork();
		if(pid < 0)
		{
			perror("fork\n");
			return -1;
		}
		if(pid == 0)
		{
			close(sfd);
			while(1)
			{
				cnt = recv(newfd,buff,1024,0);
				if(strncmp(buff,"exit",4)==0)
					break;
				write(newfd,buff,cnt,0);
			}
			close(newfd);
			return 0;
		}
		close(newfd);
	}
	close(newfd);
	close(sfd);
	return 0;
}


