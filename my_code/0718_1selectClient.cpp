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
	short coordinatelens;	//�̶�����
	char totalface;			//��ǰ�������������
	char pictype;			//��Ƭ����0-������1-�������2-ȫ������
	char coordinate[60];	//����
};

/*
	function:�����������ݣ���ͼƬһ���Ž�����������
	parameter:void *Buffer�����뻺���������ݣ�int ldlens:���뻺���������ݴ�С
	return:����δ��������ݴ�С
*/
/*
1����Bufferȡ��ͷ��С����
2��ȷ����ͷ����ͷ�������ݴ�С�õ�������ͼƬ��С+1�Ŀռ�������ͼƬ
3����δ��������ݴ�Сlens��ã�������Buffer�������ƫ�ơ��ı�ldlens
4��ldlens��Ҫ���ظ�main(),���ý���������,���Ƿ���δ�������ɣ�����ldlens���ڽ��հ������lens
5���ٶ���һ������������δ��������ݴ�С��������Buffer�������ƫ�ơ��ı�ldlens��������Ҫ��
6����Ҫһ��ѭ����Buffer�������ѭ����ȡ����,������ldlens=δ��������ݴ�СunParselens;Bufferֻ��memmoveδ���������;����char *p,while(p!=Buffer+ldlens)
7��lens = ldlens:�õ���������С���������δ��������ݴ�С�����õ��������ͼƬ��ô����lens��piclens֮��Ĺ�ϵ
8��
*/
/*
1��û�п���ldlens��һֱ����
*/
int doParseRecvMessage(char *Buffer,int ldlens)
{
	char *p = Buffer;
	int PicLens = 0;
	int	doPicLens = 0;
	int lens = ldlens;//����δ��������ݴ�С
	static int count = 0;//ͼƬ���
	char filename[64] = {0};
	char *picBuff = NULL;//��ѭ�������ԭ�򣺷�ֹ����<ͼƬ���������С��ˢ����picBuff��������Ͳ��ᱻˢ���𣿲��ᣬ���ͼƬֻ����һ��
	int headlens = HEAD_SIZE+COORDINATE_SIZE;
	FILE *m_pFile = NULL;
	while(p!=(Buffer+ldlens))//����������β�������˳���
	{	
		//��Bufferȡ��ͷ��С����
		RuiweiDataHead *Phead = (RuiweiDataHead *)p;
		
		//ȷ����ͷ����ͷ�������ݴ�С�õ�������ͼƬ��С+1�Ŀռ�������ͼƬ
		if(Phead->headFlag == 0x55BB10A1&&Phead->direct == 0x01B1&&lens>headlens)//�ȷ�ͷ//�����ͷ�����ݻ�ҪС��
		{	
			PicLens = Phead->ldDataBufLen-COORDINATE_SIZE;
			printf("%d:Phead->ldDataBufLen = %d\n",__LINE__,Phead->ldDataBufLen);
			printf("PicLens = %d\n",PicLens);
			//����ͼƬ���ȵĿռ�
			picBuff = (char *)malloc(PicLens+1);
			printf("picBuff:%p\n",picBuff);
			if(lens-headlens>PicLens)//���յ�����>ͼƬ��Ҫ������
			{
				printf("%d:lens-headlens>PicLens\n",__LINE__);
				memcpy(picBuff,p+headlens,PicLens);
				doPicLens=PicLens;
				lens -= (headlens+PicLens);
				p += headlens+PicLens;
			}
			else if(lens-headlens<PicLens)//����̫С����������
			{
				printf("%d:lens-headlens<PicLens\n",__LINE__);
				free(picBuff);//���ⲻ������������ڴ�й©
				picBuff = NULL;
				break;
			}
			printf("%d:p+=headlens+doPicLens:len%d\n",__LINE__,headlens+doPicLens);
		}

		//��ͼƬ���ݷ���picBuff
		if(doPicLens == PicLens&&PicLens != 0)//��ֹ��ʼֻ��һ��ͷ��
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
			free(picBuff);//����Ҫÿ���ͷŵ�
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
		int cnt;
		int scnt;
		
		struct timeval to = {0};
		to.tv_sec = 3;//3��
		to.tv_usec= 0;//0΢��	
		
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
		
		
		FD_ZERO(&wset);
		FD_SET(cfd,&wset);
		if(scnt = select(maxfd+1,NULL,&wset,NULL,&to)>0)//select֮ǰ�Ѿ����ӣ�select������ֻ�ж�д�쳣����
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
			FD_ZERO(&rset);
			FD_SET(cfd,&rset);
			if(scnt = select(maxfd+1,&rset,&wset,NULL,&to)>0)
			{
				if(FD_ISSET(cfd,&rset))
				{
					printf("rset have something\n");    
					//����˲���һ��send�ĵ��ã��������������Ҫ���͵��ֽڴ�С������socket�����ݷ��뻺������һ�ζη�	
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
					
					//�������ݴ���������������ͼƬ
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
				printf("select scnt <=0,result = %d\n",scnt);//=0,û�����ݽ���
				sleep(2);
			}
		}
	}

	close(cfd);
	return 0;
}

