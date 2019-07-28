#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>

#define ARRSIZE 1024

#define HEAD_SIZE     sizeof(RuiweiDataHead)
#define COORDINATE_SIZE     sizeof(FaceCoordinate)
#define KEEPALIVE_PACKAGE_SIZE sizeof(KeepalivePacket)

typedef struct RUIWEI_DATA_HEAD RuiweiDataHead;
struct RUIWEI_DATA_HEAD
{
	int headFlag;
	int ldDataBufLen;
	char flag1;
	char flag2; 
	short direct;

};

typedef struct FACE_COORDINATE FaceCoordinate;
struct FACE_COORDINATE
{
	short coordinatelens;	//固定长度
	char totalface;			//当前画面的人脸数量
	char pictype;			//照片类型0-带背景1-最大人脸2-全部人脸
	char coordinate[60];	//坐标
};

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

/*
	function:解析接收数据，将图片一张张解析出来保存
	parameter:char *Buffer：放入缓存区的数据，int ldlens:放入缓存区的数据大小
	return:返回未处理的数据大小
*/
int doParseRecvMessage(char *Buffer,int ldlens)
{
	printf("%d:enter doParseRecvMessage\n",__LINE__);
	char *p = Buffer;
	int PicLens = 0;
	int	doPicLens = 0;
	int lens = ldlens;//返回未处理的数据大小
	static int count = 0;//图片序号
	char filename[64] = {0};
	char *picBuff = NULL;//在循环外面的原因：防止数据<图片数据所需大小，刷新了picBuff，放外面就不会被刷新吗？不会，存放图片只处理一次
	int headlens = HEAD_SIZE+COORDINATE_SIZE;
	int Kheadlens = KEEPALIVE_PACKAGE_SIZE;
	FILE *m_pFile = NULL;
	while(p!=(Buffer+ldlens))//不到缓冲区数据尾部不会退出来
	{	
		//将Buffer取出头大小解析
		RuiweiDataHead *Phead = (RuiweiDataHead *)p;
		KeepalivePacket *Kphead = (KeepalivePacket *)p;
		//printf("%d:enter doParseRecvMessage,enter while()\n",__LINE__);
		
		//确定有头，将头带的数据大小得到，开辟图片大小+1的空间存放这张图片
		if(Phead->headFlag == 0x55BB10A1&&Phead->direct == 0x01B1&&lens>=headlens)//先发头//如果比头的数据还要小呢
		{	
			PicLens = Phead->ldDataBufLen-COORDINATE_SIZE;
			printf("%d:Phead->ldDataBufLen = %d\n",__LINE__,Phead->ldDataBufLen);
			printf("%d:PicLens = %d\n",__LINE__,PicLens);
			//开辟图片长度的空间
			picBuff = (char *)malloc(PicLens+1);
			printf("picBuff:%p,lens:%d\n",picBuff,lens);
			if(lens-headlens >= PicLens)//接收的数据>图片需要的数据
			{
				if(lens-headlens == PicLens)
				{
					printf("%d:lens-headlens=PicLens\n",__LINE__);
				}
				else
				{
					printf("%d:lens-headlens>=PicLens\n",__LINE__);
				}
				memcpy(picBuff,p+headlens,PicLens);
				doPicLens=PicLens;
				lens -= (headlens+PicLens);
				p += headlens+PicLens;
			}
			else if(lens-headlens<PicLens)//数据太小，不做处理
			{
				printf("%d:lens-headlens<PicLens\n",__LINE__);
				printf("%d:%d-%d = %d < %d\n",__LINE__,lens,headlens,lens-headlens,PicLens);
				free(picBuff);//避免不满足条件造成内存泄漏
				picBuff = NULL;
				break;
			}
			printf("%d:p+=headlens+doPicLens:len%d\n",__LINE__,headlens+doPicLens);
		}
		else if(Kphead->headFlag==0x55BB10A0&&Kphead->direct==0x01B0&&lens>=Kheadlens)
		{			
			printf("%d:Kphead->headFlag:0x%x,Kphead->direct:0x%x\n",__LINE__,Kphead->headFlag,Kphead->direct);
			p += Kheadlens;
			lens -= Kheadlens;
			break;
		}

		//将图片数据放入picBuff
		if(doPicLens == PicLens&&PicLens != 0)//防止开始只发一个头包
		{
			printf("%d:count:%d\n%d:count:%d\n%d:count:%d\n%d:count:%d\n%d:count:%d\n",__LINE__,count,__LINE__,count,__LINE__,count,__LINE__,count,__LINE__,count);
			sprintf( filename, "pic/%dpicture.jpeg", count++);

			m_pFile = fopen(filename,"wb");
			if(NULL == m_pFile)
			{
				printf("file not exist\n");
				return 1;
			}					
			if (m_pFile)
			{
				fwrite(picBuff,1,PicLens,m_pFile);
				fclose(m_pFile);
				m_pFile = NULL;
			}	
			doPicLens = 0;
			free(picBuff);//是需要每次释放掉
			picBuff = NULL;
			break;
		}	
		else
		{
			p++;
			//lens--;//视为无用数据忽略掉//自己挖的坑，找不到头就丢，结果一张图片都得不到
		}
	}
	
	return lens;
}

int main()
{
	//				12					64							76								
	printf("HEAD_SIZE:%d,COORDINATE_SIZE:%d,HEAD_SIZE+COORDINATE_SIZE:%d\n",HEAD_SIZE,COORDINATE_SIZE,HEAD_SIZE+COORDINATE_SIZE);//总76
	int cfd = socket(AF_INET,SOCK_STREAM,0);
	if(cfd < 0)
    {
        perror("socket create cfd error\n");
        return 1;
    }
	/*获取flags标志*/
	int flags;
	flags = fcntl(cfd, F_GETFL, 0); 
	/*设置套接字为非阻塞*/
	fcntl(cfd, F_SETFL, flags | O_NONBLOCK);
	
	printf("cfd = %d\n",cfd);
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8102);
	serv.sin_addr.s_addr = inet_addr("128.128.255.128");
	int on = 1;
	setsockopt(cfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    int ret = connect(cfd,(struct sockaddr *)&serv,sizeof(serv));
	printf("connect result = %d\n",ret);//-1连接成功
	
	if (ret < 0 && errno == EINPROGRESS) 
	{
		fd_set rset;	
		fd_set wset;

		int maxfd = cfd;
		int cnt = 0;
		int scnt;
		struct timeval tv = {0};
		tv.tv_sec = 0;//0秒
		tv.tv_usec= 10000;//10毫秒	
		gettimeofday(&tv,NULL);
		int fruntime = tv.tv_sec*1000+tv.tv_usec/1000;	
		int curtime = 0;
		
		int error = 1;
		int	error_len = sizeof(int);
		//缓冲内存空间
		char *Buffer = NULL;
		int Bufferlens = 2*1024*1024;
		Buffer = (char *)malloc(Bufferlens+1);//当程序结束后，操作系统会回收该进程的内存空间，所以不用释放该内存
		//已经接收数据的大小
		int ldlens = 0;
		
		//未处理的数据大小unParselens
		int unParselens = 0;	
		char keepaliveSendBuf[1024] = {0};


		FD_ZERO(&wset);
		FD_SET(cfd,&wset);
		if(scnt = select(maxfd+1,NULL,&wset,NULL,&tv)>0)//select之前已经连接，select的作用只有读写异常作用
		{
			if(FD_ISSET(cfd,&wset))
			{
				if (getsockopt(cfd, SOL_SOCKET, SO_ERROR, (char *)&error, (socklen_t *)&error_len) < 0)//成功返回0
				{
					error = 1;
					printf("%d:connect failed,cfd = %d,error = %d\n",__LINE__,cfd,error);
					sleep(2);
				}
				else
				{
					printf("%d:connect success,cfd = %d,error = %d\n",__LINE__,cfd,error);//3 0/111（服务器未开启）            
				}
			}
		}
		printf("%d:scnt = %d\n",__LINE__,scnt);
		if(scnt < 0)
			return -1;
		while(1)
		{	
			tv.tv_sec = 0;//0秒
			tv.tv_usec= 10000;//10毫秒		
			FD_ZERO(&rset);
			FD_SET(cfd,&rset);
			if(scnt = select(maxfd+1,&rset,NULL,NULL,&tv)>0)
			{
				if(FD_ISSET(cfd,&rset))
				{
					printf("rset have something\n");    
					//服务端不会一个send的调用，发送这个调用需要发送的字节大小，而是socket将数据放入缓冲区后一段段发	
					printf("recv before ldlens:%d\n",ldlens);    
					cnt = recv(cfd,Buffer+ldlens,Bufferlens-ldlens,0);	
					printf("cnt :%d\n",cnt);
					ldlens += cnt;

					if(cnt == 0)
					{
						printf("rset go to die\n");            
						close(cfd);
						cfd = 0;
						break;
					}
					else if(cnt < 0&&errno != EAGAIN &&errno != EINTR)
					{
						printf("%d:fatal error,close cfd\n",__LINE__);
						close(cfd);
						cfd = 0;
						break;
					}
										
					//进入数据处理函数，解析保存图片
					printf("%d:doParseRecvMessage before ldlens:%d\n",__LINE__,ldlens);    
					unParselens = doParseRecvMessage(Buffer,ldlens);	
					memmove(Buffer,Buffer+ldlens-unParselens,unParselens);
					ldlens = unParselens;
					printf("%d:doParseRecvMessage after ldlens:%d\n",__LINE__,ldlens);    
					if(ldlens == Bufferlens)
					{
						break;
					}
				}

			}
			
			//每10s发送心跳包	
			gettimeofday(&tv,NULL);
			curtime = tv.tv_sec*1000+tv.tv_usec/1000;
			if(curtime>fruntime+10000)//超过10s
			{
				printf("%d:curtime:%d-fruntime:%d = %d\n",curtime,fruntime,(curtime-fruntime)%1000);
				memset(keepaliveSendBuf,0,KEEPALIVE_PACKAGE_SIZE);
				makeDataMsgHead((KeepalivePacket *)keepaliveSendBuf);
				//why直接cnt = send(cfd,(char *)keepaliveSend,Bufferlens-ldlens,0);	类型转换无效
				cnt = send(cfd,keepaliveSendBuf,strlen(keepaliveSendBuf),0);	
				printf("%d:strlen(keepaliveSendBuf):%d,send:%d,cfd:%d\n",__LINE__,strlen(keepaliveSendBuf),cnt,cfd);    
				gettimeofday(&tv,NULL);
				fruntime = tv.tv_sec*1000+tv.tv_usec/1000;				
			}		
		}
	}

	close(cfd);
	return 0;
}

