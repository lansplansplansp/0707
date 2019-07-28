#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

void *client(void *arg)
{
    int newfd = (int)arg;
    int cnt;
    char buff[1024];
    while(1)
    {
        cnt = read(newfd,buff,1024);
        if(strncmp(buff,"exit",4)==0)
		{
			printf("%s",buff);
            break;
		}
        write(newfd,buff,cnt);
    }	
    close(newfd);
}

int main()
{
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	printf("sfd = %d\n",sfd);

	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(9876);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	int on = 1;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	int ret = bind(sfd,(struct sockaddr *)&serv,sizeof(serv));
	printf("ret = %d\n",ret);

	listen(sfd,5);
	int newfd;
	struct sockaddr_in peer;
	socklen_t size;
	pthread_t tid;
	while(1)
	{
		size = sizeof(peer);
		newfd = accept(sfd,(struct sockaddr *)&peer,&size);
		printf("ip:%s,port:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
		pthread_create(&tid,NULL,client,(void *)newfd);
		pthread_detach(tid);
	}
	close(sfd);
	return 0;
}
