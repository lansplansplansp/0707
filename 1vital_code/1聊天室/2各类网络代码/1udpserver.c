#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	int sfd = socket(AF_INET,SOCK_DGRAM,0);
	printf("sfd = %d\n",sfd);

	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(9876);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	int on = 1;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	int ret = bind(sfd,(struct sockaddr *)&serv,sizeof(serv));
	printf("ret = %d\n",ret);

	int cnt;
	char buff[1024];
	struct sockaddr_in peer;
	socklen_t size;
	while(1)
	{
		cnt = recvfrom(sfd,buff,1024,0,(struct sockaddr *)&peer,&size);
		printf("ip:%s,port:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
		if(cnt == 0)break;
		sendto(sfd,buff,cnt,0,(struct sockaddr *)&peer,sizeof(peer));
	}
	close(sfd);
	return 0;
}

