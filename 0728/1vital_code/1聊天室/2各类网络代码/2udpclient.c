#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	int cfd = socket(AF_INET,SOCK_DGRAM,0);
	printf("cfd = %d\n",cfd);

	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(9876);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	int cnt;
	char buff[1024];
	while(1)
	{
		fgets(buff,1024,stdin);
		cnt = sendto(cfd,buff,strlen(buff)+1,0,(struct sockaddr *)&serv,sizeof(serv));
		memset(buff,0,1024);
		if(cnt == 0)break;
		recvfrom(cfd,buff,cnt,0,NULL,NULL);
		printf("%s\n",buff);
	}
	close(cfd);
	return 0;
}
