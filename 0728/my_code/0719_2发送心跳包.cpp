#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define ARRSIZE 1024

#define KEEPALIVE_PACKAGE_SIZE sizeof(KeepalivePacket)
typedef struct RUIWEI_KEEPALIVE_PACKAGE KeepalivePacket;
struct RUIWEI_KEEPALIVE_PACKAGE//结构体定义时不能初始化
{
	RUIWEI_KEEPALIVE_PACKAGE()
	{
		headFlag = 0x55BB10A0;
		flag1 = 0x10;
		flag2 = 0x00;
		direct = 0x01B0;
	}
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

//10s发送一个心跳包
int main()
{		
	int cfd = socket(AF_INET,SOCK_STREAM,0);
	if(cfd < 0)
    {
        perror("socket create cfd error\n");
        return 1;
    }
	////*获取flags标志*/
	//int flags;
	//flags = fcntl(cfd, F_GETFL, 0); 
	////*设置套接字为非阻塞*/
	//fcntl(cfd, F_SETFL, flags | O_NONBLOCK);
	
	printf("cfd = %d\n",cfd);
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8102);
	serv.sin_addr.s_addr = inet_addr("128.128.255.128");
	int on = 1;
	setsockopt(cfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    int ret = connect(cfd,(struct sockaddr *)&serv,sizeof(serv));
	printf("connect result = %d\n",ret);//-1连接成功
	int pid = fork();
    if (pid < 0)
    {
        printf ("error!\n");
        exit(-1);
    }
    if (pid == 0)
    {
        while (1)
        {
            //每10s发送心跳包
			memset(keepaliveSendBuf,0,KEEPALIVE_PACKAGE_SIZE);
			makeDataMsgHead((KeepalivePacket *)keepaliveSendBuf);
			//why直接cnt = send(cfd,(char *)keepaliveSend,Bufferlens-ldlens,0);	类型转换无效
			cnt = send(cfd,keepaliveSendBuf,Bufferlens-ldlens,0);	
			printf("%d:FD_ISSET(cfd,&wset)\n",__LINE__);    
			sleep(2);
        }
    }
    else
    {
        while (1)
        {
			memset(buff,0,1024);
			if(read(cfd,buff,1024) <= 0)
				break;
			KeepalivePacket *PKhead = (KeepalivePacket *)p;
			else if(PKhead->headFlag == 0x55BB10A0&&PKhead->direct == 0x01B0&&lens>Kheadlens)
			{	
				printf("%d:is KeepalivePacket\n",__LINE__);
				//p跳过心跳包
				p += Kheadlens;
				
				//lens去掉心跳包长度
				lens -= Kheadlens;
				break;
			}			
        }
    }
    close(cfd);		/*
	KeepalivePacket keepaliveSend;
	char keepaliveSendBuf[1024] = {0};	
	int	Kheadlens = KEEPALIVE_PACKAGE_SIZE;

	KeepalivePacket *PKhead = (KeepalivePacket *)p;
	else if(PKhead->headFlag == 0x55BB10A0&&PKhead->direct == 0x01B0&&lens>Kheadlens)
	{	
		printf("%d:is KeepalivePacket\n",__LINE__);
		//p跳过心跳包
		p += Kheadlens;
		
		//lens去掉心跳包长度
		lens -= Kheadlens;
		break;
	}			
	if(FD_ISSET(cfd,&wset))
	{	
		//每10s发送心跳包
		memset(keepaliveSendBuf,0,KEEPALIVE_PACKAGE_SIZE);
		makeDataMsgHead((KeepalivePacket *)keepaliveSendBuf);
		//why直接cnt = send(cfd,(char *)keepaliveSend,Bufferlens-ldlens,0);	类型转换无效
		cnt = send(cfd,keepaliveSendBuf,Bufferlens-ldlens,0);	
		printf("%d:FD_ISSET(cfd,&wset)\n",__LINE__);    
		sleep(10);
	}
	*/
	return 0;
}