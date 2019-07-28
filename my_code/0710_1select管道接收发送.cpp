#include <stdio.h>

//有名管道

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
	//起管道
	int fdfifo[2];
	if(pipe(fdfifo)==-1)
	{
		perror("make pipe");
		return 1;//不能用exit(1);是个坑
	}
	pipe(fdfifo);
	int sfd = tcp_server_init(8765);
	fd_set read_set;
	int maxfd = 0;
	struct timeval tv;
	int ret = -1;
	struct sockaddr_in peer;
	socklen_t size;
	int newfd;
	int faddr[1024] = {0};
	int fid = 0;
	faddr[fid++] = sfd;
	while(1)
	{
		maxfd = 0;
		tv.sec = 0;
		tv.usec = 50000;
		FD_ZERO(&read_set);
		FD_SET(sfd,&read_set);
		ret = select(maxfd+1,&read_set,NULL,NULL,&tv);
		if(FD_ISSET(sfd,&read_set))
		{
			newfd = accept(sfd,(struct *sockaddr)&peer,&size);
			faddr[fid++] = newfd;
			printf("newfd = %d\n",newfd);
			if(maxfd<newfd)
				maxfd = newfd;
		}
		for(int i=0;i<fid;i++)
		{
			if(FD_ISSET(faddr[i],&read_set))
			{
				//管道读
			}
			
		}
	}
	return 0;
}