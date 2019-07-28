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
	printf("connect result = %d\n",ret);
	
	int cnt = 0;	
	
	int error = 1;
	int	error_len = sizeof(int);
	
	char Buffer[1024] = {0};
	
	char keepaliveSendBuf[1024] = {0};
	
	int pid = fork();//不建议使用fork,vfork还说的过去，但是使用线程才更正确
	if (pid < 0)
	{
		printf ("error!\n");
		exit(-1);
	}
	if (pid == 0)
	{
		while(1)
		{
			//每10s发送心跳包
			memset(keepaliveSendBuf,0,KEEPALIVE_PACKAGE_SIZE);
			makeDataMsgHead((KeepalivePacket *)keepaliveSendBuf);
			//why直接cnt = send(cfd,(char *)keepaliveSend,Bufferlens-ldlens,0);	类型转换无效
			cnt = send(cfd,keepaliveSendBuf,KEEPALIVE_PACKAGE_SIZE,0);	
			printf("%d:keepaliveSendBuf:%d,KEEPALIVE_PACKAGE_SIZE:%d,send:%d\n",__LINE__,strlen(keepaliveSendBuf),KEEPALIVE_PACKAGE_SIZE,cnt);    
			sleep(2);
		}
	}
	else
	{
		printf("%d:fork()in chid!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",__LINE__);
		while(1)
		{
			cnt = recv(cfd,Buffer,1024,0);//可能收到-1

			printf("%d:cnt:%d\n",__LINE__,cnt);
			if(cnt<0 && errno != EINTR && errno != EWOULDBLOCK && errno != EAGAIN)
			{
				break;
			}
			if(cnt > 0)
			{
				if(cnt == 0)
				{
					printf("rset go to die\n");            
					close(cfd);
					cfd = 0;
					break;
				}
				KeepalivePacket *phead = (KeepalivePacket *)Buffer;
				printf("phead->headFlag:0x%x,phead->direct:0x%x\n",phead->headFlag,phead->direct);
				if(phead->headFlag==0x55BB10A0&&phead->direct==0x01B0)
				{
					printf("SUCCESS!phead->headFlag==0x55BB10A0&&phead->direct==0x01B0 \n");
				}

			}
			else
			{	
				printf("%d:cnt:%d,break\n",__LINE__,cnt);
				break;
			}
		}
	}
	close(cfd);
	return 0;
}

