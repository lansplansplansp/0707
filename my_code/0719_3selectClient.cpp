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
	short coordinatelens;	//�̶�����
	char totalface;			//��ǰ�������������
	char pictype;			//��Ƭ����0-������1-�������2-ȫ������
	char coordinate[60];	//����
};

typedef struct RUIWEI_KEEPALIVE_PACKAGE KeepalivePacket;
struct RUIWEI_KEEPALIVE_PACKAGE//�ṹ�嶨��ʱ���ܳ�ʼ��
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
	function:�����������ݣ���ͼƬһ���Ž�����������
	parameter:char *Buffer�����뻺���������ݣ�int ldlens:���뻺���������ݴ�С
	return:����δ��������ݴ�С
*/
int doParseRecvMessage(char *Buffer,int ldlens)
{
	printf("%d:enter doParseRecvMessage\n",__LINE__);
	char *p = Buffer;
	int PicLens = 0;
	int	doPicLens = 0;
	int lens = ldlens;//����δ��������ݴ�С
	static int count = 0;//ͼƬ���
	char filename[64] = {0};
	char *picBuff = NULL;//��ѭ�������ԭ�򣺷�ֹ����<ͼƬ���������С��ˢ����picBuff��������Ͳ��ᱻˢ���𣿲��ᣬ���ͼƬֻ����һ��
	int headlens = HEAD_SIZE+COORDINATE_SIZE;
	int Kheadlens = KEEPALIVE_PACKAGE_SIZE;
	FILE *m_pFile = NULL;
	while(p!=(Buffer+ldlens))//��������������β�������˳���
	{	
		//��Bufferȡ��ͷ��С����
		RuiweiDataHead *Phead = (RuiweiDataHead *)p;
		KeepalivePacket *Kphead = (KeepalivePacket *)p;
		//printf("%d:enter doParseRecvMessage,enter while()\n",__LINE__);
		
		//ȷ����ͷ����ͷ�������ݴ�С�õ�������ͼƬ��С+1�Ŀռ�������ͼƬ
		if(Phead->headFlag == 0x55BB10A1&&Phead->direct == 0x01B1&&lens>=headlens)//�ȷ�ͷ//�����ͷ�����ݻ�ҪС��
		{	
			PicLens = Phead->ldDataBufLen-COORDINATE_SIZE;
			printf("%d:Phead->ldDataBufLen = %d\n",__LINE__,Phead->ldDataBufLen);
			printf("%d:PicLens = %d\n",__LINE__,PicLens);
			//����ͼƬ���ȵĿռ�
			picBuff = (char *)malloc(PicLens+1);
			printf("picBuff:%p,lens:%d\n",picBuff,lens);
			if(lens-headlens >= PicLens)//���յ�����>ͼƬ��Ҫ������
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
			else if(lens-headlens<PicLens)//����̫С����������
			{
				printf("%d:lens-headlens<PicLens\n",__LINE__);
				printf("%d:%d-%d = %d < %d\n",__LINE__,lens,headlens,lens-headlens,PicLens);
				free(picBuff);//���ⲻ������������ڴ�й©
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

		//��ͼƬ���ݷ���picBuff
		if(doPicLens == PicLens&&PicLens != 0)//��ֹ��ʼֻ��һ��ͷ��
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
			free(picBuff);//����Ҫÿ���ͷŵ�
			picBuff = NULL;
			break;
		}	
		else
		{
			p++;
			//lens--;//��Ϊ�������ݺ��Ե�//�Լ��ڵĿӣ��Ҳ���ͷ�Ͷ������һ��ͼƬ���ò���
		}
	}
	
	return lens;
}

int main()
{
	//				12					64							76								
	printf("HEAD_SIZE:%d,COORDINATE_SIZE:%d,HEAD_SIZE+COORDINATE_SIZE:%d\n",HEAD_SIZE,COORDINATE_SIZE,HEAD_SIZE+COORDINATE_SIZE);//��76
	int cfd = socket(AF_INET,SOCK_STREAM,0);
	if(cfd < 0)
    {
        perror("socket create cfd error\n");
        return 1;
    }
	/*��ȡflags��־*/
	int flags;
	flags = fcntl(cfd, F_GETFL, 0); 
	/*�����׽���Ϊ������*/
	fcntl(cfd, F_SETFL, flags | O_NONBLOCK);
	
	printf("cfd = %d\n",cfd);
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8102);
	serv.sin_addr.s_addr = inet_addr("128.128.255.128");
	int on = 1;
	setsockopt(cfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    int ret = connect(cfd,(struct sockaddr *)&serv,sizeof(serv));
	printf("connect result = %d\n",ret);//-1���ӳɹ�
	
	if (ret < 0 && errno == EINPROGRESS) 
	{
		fd_set rset;	
		fd_set wset;

		int maxfd = cfd;
		int cnt = 0;
		int scnt;
		struct timeval tv = {0};
		tv.tv_sec = 0;//0��
		tv.tv_usec= 10000;//10����	
		gettimeofday(&tv,NULL);
		int fruntime = tv.tv_sec*1000+tv.tv_usec/1000;	
		int curtime = 0;
		
		int error = 1;
		int	error_len = sizeof(int);
		//�����ڴ�ռ�
		char *Buffer = NULL;
		int Bufferlens = 2*1024*1024;
		Buffer = (char *)malloc(Bufferlens+1);//����������󣬲���ϵͳ����ոý��̵��ڴ�ռ䣬���Բ����ͷŸ��ڴ�
		//�Ѿ��������ݵĴ�С
		int ldlens = 0;
		
		//δ��������ݴ�СunParselens
		int unParselens = 0;	
		char keepaliveSendBuf[1024] = {0};


		FD_ZERO(&wset);
		FD_SET(cfd,&wset);
		if(scnt = select(maxfd+1,NULL,&wset,NULL,&tv)>0)//select֮ǰ�Ѿ����ӣ�select������ֻ�ж�д�쳣����
		{
			if(FD_ISSET(cfd,&wset))
			{
				if (getsockopt(cfd, SOL_SOCKET, SO_ERROR, (char *)&error, (socklen_t *)&error_len) < 0)//�ɹ�����0
				{
					error = 1;
					printf("%d:connect failed,cfd = %d,error = %d\n",__LINE__,cfd,error);
					sleep(2);
				}
				else
				{
					printf("%d:connect success,cfd = %d,error = %d\n",__LINE__,cfd,error);//3 0/111��������δ������            
				}
			}
		}
		printf("%d:scnt = %d\n",__LINE__,scnt);
		if(scnt < 0)
			return -1;
		while(1)
		{	
			tv.tv_sec = 0;//0��
			tv.tv_usec= 10000;//10����		
			FD_ZERO(&rset);
			FD_SET(cfd,&rset);
			if(scnt = select(maxfd+1,&rset,NULL,NULL,&tv)>0)
			{
				if(FD_ISSET(cfd,&rset))
				{
					printf("rset have something\n");    
					//����˲���һ��send�ĵ��ã��������������Ҫ���͵��ֽڴ�С������socket�����ݷ��뻺������һ�ζη�	
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
										
					//�������ݴ���������������ͼƬ
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
			
			//ÿ10s����������	
			gettimeofday(&tv,NULL);
			curtime = tv.tv_sec*1000+tv.tv_usec/1000;
			if(curtime>fruntime+10000)//����10s
			{
				printf("%d:curtime:%d-fruntime:%d = %d\n",curtime,fruntime,(curtime-fruntime)%1000);
				memset(keepaliveSendBuf,0,KEEPALIVE_PACKAGE_SIZE);
				makeDataMsgHead((KeepalivePacket *)keepaliveSendBuf);
				//whyֱ��cnt = send(cfd,(char *)keepaliveSend,Bufferlens-ldlens,0);	����ת����Ч
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

