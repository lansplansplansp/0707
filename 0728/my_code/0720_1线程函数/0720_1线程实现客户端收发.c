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

static int fruntime;

#define KEEPALIVE_PACKAGE_SIZE sizeof(KeepalivePacket)
typedef struct RUIWEI_KEEPALIVE_PACKAGE KeepalivePacket;
struct RUIWEI_KEEPALIVE_PACKAGE//结构体定义时不能初始化
{
	int headFlag;
	char flag1;
	char flag2;
	short direct;
};

int makeDataMsgHead(KeepalivePacket *pxmMsgHeader)
{
	pxmMsgHeader->headFlag = 0x55BB10A0;
	pxmMsgHeader->flag1 = 0x10;
	pxmMsgHeader->flag2 = 0x00;
	pxmMsgHeader->direct = 0x01B0;

	return 0;
}

void *pthread_send(void *_val)
{
	printf("tid1(send)分离成功\n");
	int cfd = (int)_val;
	printf("%d:cfd:%d\n",__LINE__,cfd);
	struct timeval tv = {0};
	while(1)
	{
		gettimeofday(&tv,NULL);
		int curtime = tv.tv_sec*1000+tv.tv_usec/1000;
		char keepaliveSendBuf[128] = {0};
		int cnt = 0;
		if(curtime>fruntime+5000)//超过10s
		{
			memset(keepaliveSendBuf,0,KEEPALIVE_PACKAGE_SIZE);
			makeDataMsgHead((KeepalivePacket *)keepaliveSendBuf);
			//why直接cnt = send(cfd,(char *)keepaliveSend,Bufferlens-ldlens,0);	类型转换无效
			cnt = send(cfd,keepaliveSendBuf,KEEPALIVE_PACKAGE_SIZE,0);	
			printf("%d:send,KEEPALIVE_PACKAGE_SIZE:%d,cnt:%d,cfd:%d\n",__LINE__,KEEPALIVE_PACKAGE_SIZE,cnt,cfd);    
			gettimeofday(&tv,NULL);
			fruntime = tv.tv_sec*1000+tv.tv_usec/1000;				
		}	
	}	
}

void *pthread_recv(void *_val)
{
	printf("tid2(recv)分离成功\n");
	int cfd = (int)_val;
	printf("%d:cfd:%d\n",__LINE__,cfd);
	char Buffer[1024] = {0};
	int cnt=0;
	//循环接收心跳包
	while(1)
	{
		cnt = recv(cfd,Buffer,1024,0);//阻塞

		printf("%d:cnt:%d\n",__LINE__,cnt);
		KeepalivePacket *phead = (KeepalivePacket *)Buffer;
		printf("%d:phead->headFlag:0x%x,phead->direct:0x%x\n",__LINE__,phead->headFlag,phead->direct);
		if(phead->headFlag==0x55BB10A0&&phead->direct==0x01B0)
		{
			printf("%d:phead->headFlag:0x%x,phead->direct:0x%x\n",__LINE__,phead->headFlag,phead->direct);
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
	serv.sin_port = htons(8102);
	serv.sin_addr.s_addr = inet_addr("128.128.255.128");
	int on = 1;
	setsockopt(cfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    int ret = connect(cfd,(struct sockaddr *)&serv,sizeof(serv));
	if(ret < 0)
	{//perror
		printf("%d:connect error,ret:%d\n",__LINE__,ret);
		return 1;
	}
	
	struct timeval tv = {0};
	gettimeofday(&tv,NULL);
	fruntime = tv.tv_sec*1000+tv.tv_usec/1000;	
	printf("%d:fruntime:%d\n",__LINE__,fruntime);
	//线程实现客户端收发
	pthread_t tid1 = -1,tid2 = -1;
	printf("%d:tid1:%d\n",__LINE__,tid1);
	printf("%d:tid2:%d\n",__LINE__,tid2);
	int ret1 = pthread_create(&tid1,NULL,pthread_send,(void *)cfd);
	printf("%d:ret1:%d\n",__LINE__,ret1);//0
	printf("%d:tid1:%d\n",__LINE__,tid1);//0
	ret1 = pthread_create(&tid2,NULL,pthread_recv,(void *)cfd);
	printf("%d:ret1:%d\n",__LINE__,ret1);//0
	printf("%d:tid2:%d\n",__LINE__,tid2);//0

	printf("分离tid1、tdi2\n");
	pthread_detach(tid1);
	pthread_detach(tid2);
	while(1)
	{
		sleep(1);
	}

	close(cfd);
	return 0;
}

