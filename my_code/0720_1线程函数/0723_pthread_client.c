/*
	pthread achieve client recv and send
*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

void *pthread_send(void *_val)
{
	int cfd = (int)_val;
	printf("%d:cfd:%d\n",__LINE__,cfd);
	char buff[1024] = {0};
	while(1)
	{
		memset(buff,0,1024);
		fgets(buff,1024,stdin);
		printf("buff:%slen:%d\n",buff,strlen(buff));
		send(cfd,buff,strlen(buff),0);
	}	
}

void *pthread_recv(void *_val)
{
	int cfd = (int)_val;
	printf("%d:cfd:%d\n",__LINE__,cfd);
	char Buffer[1024] = {0};
	int cnt=0;
	//循环接收心跳包
	while(1)
	{
		cnt = recv(cfd,Buffer,1024,0);
        if(strncmp(Buffer,"exit",4)==0)
		{
			printf("Buffer:%s",Buffer);
			break;
		}
	}
}

int main()
{
	int cfd = socket(AF_INET,SOCK_STREAM,0);
	if(cfd < 0)
    {
        perror("socket create cfd error\n");
        return 1;
    }

	printf("cfd = %d\n",cfd);
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(9876);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	int on = 1;
	setsockopt(cfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    int ret = connect(cfd,(struct sockaddr *)&serv,sizeof(serv));
	if(ret < 0)
	{//perror
		printf("%d:connect error,ret:%d\n",__LINE__,ret);
		return 1;
	}
	
	//线程实现客户端收发
	pthread_t tid1 = -1,tid2 = -1;
	printf("%d:tid1:%d\n",__LINE__,tid1);
	printf("%d:tid2:%d\n",__LINE__,tid2);
	int ret1 = pthread_create(&tid1,NULL,pthread_send,(void *)cfd);
	printf("%d:ret1:%d\n",__LINE__,ret1);//0
	ret1 = pthread_create(&tid1,NULL,pthread_recv,(void *)cfd);
	printf("%d:ret1:%d\n",__LINE__,ret1);//0

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	//pthread_detach(tid1);//段错误
	//pthread_detach(tid2);	
	close(cfd);
	return 0;
}

