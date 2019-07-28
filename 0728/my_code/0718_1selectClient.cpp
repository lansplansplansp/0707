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

#define HEAD_SIZE     sizeof(RuiweiDataHead)
#define COORDINATE_SIZE     sizeof(FaceCoordinate)

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

/*
	function:解析接收数据，将图片一张张解析出来保存
	parameter:void *Buffer：放入缓存区的数据，int ldlens:放入缓存区的数据大小
	return:返回未处理的数据大小
*/
/*
1、将Buffer取出头大小解析
2、确定有头，将头带的数据大小得到，开辟图片大小+1的空间存放这张图片
3、将未处理的数据大小lens获得，用来做Buffer里的数据偏移、改变ldlens
4、ldlens需要返回给main(),引用将变量关联,还是返回未处理函数吧，否则ldlens会在接收包后干扰lens
5、再定义一个函数：返回未处理的数据大小，用来做Buffer里的数据偏移、改变ldlens（或许不需要）
6、需要一个循环将Buffer里的数据循环读取出来,条件：ldlens=未处理的数据大小unParselens;Buffer只能memmove未处理的数据;定义char *p,while(p!=Buffer+ldlens)
7、lens = ldlens:得到缓冲区大小，结果返回未处理的数据大小，但得到与否完整图片怎么处理lens跟piclens之间的关系
8、
*/
/*
1、没有考虑ldlens会一直不变
*/
int doParseRecvMessage(char *Buffer,int ldlens)
{
	char *p = Buffer;
	int PicLens = 0;
	int	doPicLens = 0;
	int lens = ldlens;//返回未处理的数据大小
	static int count = 0;//图片序号
	char filename[64] = {0};
	char *picBuff = NULL;//在循环外面的原因：防止数据<图片数据所需大小，刷新了picBuff，放外面就不会被刷新吗？不会，存放图片只处理一次
	int headlens = HEAD_SIZE+COORDINATE_SIZE;
	FILE *m_pFile = NULL;
	while(p!=(Buffer+ldlens))//不到缓冲区尾部不会退出来
	{	
		//将Buffer取出头大小解析
		RuiweiDataHead *Phead = (RuiweiDataHead *)p;
		
		//确定有头，将头带的数据大小得到，开辟图片大小+1的空间存放这张图片
		if(Phead->headFlag == 0x55BB10A1&&Phead->direct == 0x01B1&&lens>headlens)//先发头//如果比头的数据还要小呢
		{	
			PicLens = Phead->ldDataBufLen-COORDINATE_SIZE;
			printf("%d:Phead->ldDataBufLen = %d\n",__LINE__,Phead->ldDataBufLen);
			printf("PicLens = %d\n",PicLens);
			//开辟图片长度的空间
			picBuff = (char *)malloc(PicLens+1);
			printf("picBuff:%p\n",picBuff);
			if(lens-headlens>PicLens)//接收的数据>图片需要的数据
			{
				printf("%d:lens-headlens>PicLens\n",__LINE__);
				memcpy(picBuff,p+headlens,PicLens);
				doPicLens=PicLens;
				lens -= (headlens+PicLens);
				p += headlens+PicLens;
			}
			else if(lens-headlens<PicLens)//数据太小，不做处理
			{
				printf("%d:lens-headlens<PicLens\n",__LINE__);
				free(picBuff);//避免不满足条件造成内存泄漏
				picBuff = NULL;
				break;
			}
			printf("%d:p+=headlens+doPicLens:len%d\n",__LINE__,headlens+doPicLens);
		}

		//将图片数据放入picBuff
		if(doPicLens == PicLens&&PicLens != 0)//防止开始只发一个头包
		{
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
		int cnt;
		int scnt;
		
		struct timeval to = {0};
		to.tv_sec = 3;//3秒
		to.tv_usec= 0;//0微秒	
		
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
		
		
		FD_ZERO(&wset);
		FD_SET(cfd,&wset);
		if(scnt = select(maxfd+1,NULL,&wset,NULL,&to)>0)//select之前已经连接，select的作用只有读写异常作用
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
			FD_ZERO(&rset);
			FD_SET(cfd,&rset);
			if(scnt = select(maxfd+1,&rset,&wset,NULL,&to)>0)
			{
				if(FD_ISSET(cfd,&rset))
				{
					printf("rset have something\n");    
					//服务端不会一个send的调用，发送这个调用需要发送的字节大小，而是socket将数据放入缓冲区后一段段发	
					printf("recv before ldlens:%d\n",ldlens);    
					cnt = recv(cfd,Buffer+ldlens,Bufferlens-ldlens,0);	
					ldlens += cnt;
					printf("after recv\n");

					if(cnt == 0)
					{
						printf("rset go to die\n");            
						close(cfd);
						cfd = 0;
						break;
					}
					else if(cnt < 0&&errno != EAGAIN &&errno != EINTR)
					{
						close(cfd);
						cfd = 0;
						break;
					}
					printf("cnt :%d\n",cnt);
					
					//进入数据处理函数，解析保存图片
					printf("doParseRecvMessage before ldlens:%d\n",ldlens);    
					unParselens = doParseRecvMessage(Buffer,ldlens);	
					memmove(Buffer,Buffer+ldlens-unParselens,unParselens);
					ldlens = unParselens;
					if(ldlens == Bufferlens)
					{
						break;
					}
				}

			}
			else
			{
				printf("select scnt <=0,result = %d\n",scnt);//=0,没有数据接收
				sleep(2);
			}
		}
	}

	close(cfd);
	return 0;
}

