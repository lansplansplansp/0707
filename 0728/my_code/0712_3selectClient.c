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
		char buff[1024*1024];
		
		struct timeval to = {0};
		to.tv_sec = 3;//3��
		to.tv_usec= 0;//0΢��	
		
		int error = 1;
		int	error_len = sizeof(int);
		char filename[64] = {0};
		FILE *m_pFile = NULL;
		int count = 0;
		int PicLens;
		int ldlens = 0;
		char *picBuff = NULL;
		char Buffer[1024*1024*2+1];
		int Bufferlens = 0;
		FD_ZERO(&wset);
		FD_SET(cfd,&wset);
		if(scnt = select(maxfd+1,NULL,&wset,NULL,&to)>0)//select֮ǰ�Ѿ����ӣ�select������ֻ�ж�д�쳣����
		{
			if(FD_ISSET(cfd,&wset))//������û�����ݴ˴��ٴ�ѭ��
			{
				if (getsockopt(cfd, SOL_SOCKET, SO_ERROR, (char *)&error, (socklen_t *)&error_len) < 0)//�ɹ�����0
				{
					error = 1;
					printf("connect failed,cfd = %d,error = %d\n",cfd,error);
					sleep(2);
				}
				else
				{
					printf("socket success,cfd = %d,error = %d\n",cfd,error);//3 0��111��������δ������            
					FD_SET(cfd,&rset);
					sleep(2);
				}
			}
		}
		if(scnt < 0)
			return -1;
		while(1)//�����δ���
		{		
			FD_ZERO(&rset);
			FD_SET(cfd,&rset);
			if(scnt = select(maxfd+1,&rset,NULL,NULL,&to)>0)
			{
				if(FD_ISSET(cfd,&rset))
				{
					printf("rset have something\n");            
					memset(buff,0,1024*1024);
					cnt = read(cfd,buff,1024*1024);//����˲���һ��send�ĵ��ã��������������Ҫ���͵��ֽڴ�С������socket�����ݷ��뻺������һ�ζη�		
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
					//��������ͼƬ
					//printf("buff :%s\n",buff);һ������
					
					RuiweiDataHead *Phead = (RuiweiDataHead *)buff;
					if(Phead->flag1 == 0x10&&Phead->flag2 == 0x00)//�ȷ�ͷ
					{	
						PicLens = Phead->ldDataBufLen-COORDINATE_SIZE;
						printf("Phead->ldDataBufLen = %d\n",Phead->ldDataBufLen);
						printf("PicLens = %d\n",PicLens);
						//����ͼƬ���ȵĿռ�
						picBuff = (char *)malloc(PicLens+1);
						printf("picBuff:%p\n",picBuff);
						if(cnt-HEAD_SIZE-COORDINATE_SIZE<PicLens)//ͼƬ�󣬻����ٴν���ͼƬ
						{
							memcpy(picBuff,buff+HEAD_SIZE+COORDINATE_SIZE,cnt-HEAD_SIZE-COORDINATE_SIZE);
							ldlens+=cnt-HEAD_SIZE-COORDINATE_SIZE;
						}
						else//ͼƬС
						{
							memcpy(picBuff,buff+HEAD_SIZE+COORDINATE_SIZE,PicLens);
							ldlens+=PicLens;
						}
					}
					else//�ٷ�ͼƬ����
					{
						//��ͼƬ���ݷ���picBuff
						if(ldlens != PicLens)
						{
							if(ldlens+cnt < ldlens)
							{
								printf("ldlens+cnt < ldlens before ldlens:%d,PicLens:%d\n",ldlens,PicLens);
								memcpy(picBuff+ldlens,buff,cnt);
								ldlens+=cnt;
								printf("after ldlens:%d,PicLens:%d\n",ldlens,PicLens);
							}
							else if(ldlens+cnt > ldlens)//����Ĳ�������ͷ�ģ���Ҫ������Ļ���
							{
								printf("ldlens+cnt > ldlens before ldlens:%d,PicLens:%d\n",ldlens,PicLens);
								memcpy(picBuff+ldlens,buff,PicLens-ldlens);
								ldlens+=PicLens-ldlens;
								printf("after ldlens:%d,PicLens:%d\n",ldlens,PicLens);							
							}
						}
						else if(ldlens == PicLens)
						{
							sprintf( filename, "pic/picture%d.jpeg", count++);

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
							ldlens = 0;
							free(picBuff);
							picBuff = NULL;
							break;
						}	
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

