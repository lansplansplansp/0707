#include <stdio.h>
#include <arpa/inet.h>//fd_set
#include <errno.h>//errno
#include <string.h>//memset

#define RETURN_FAIL -1
#define RETURN_OK    0
#define ARRSIZE 1024


#ifndef ERR
#define ERR(fmt, args...) do { \
	 fprintf(stderr, "\033[1;31m""[ERR!] [%s:%5d] " fmt, (char *)__FILE__,__LINE__,## args);	\
 } while(0)
#endif

//							sfd			01			01		3000
int SelectFunction(int *fd_array, int fd_num, int fd_type, int time_out, const char *pFunc)
{
	int maxfd = 0;
	int index = 0;
	int ret   = 0;
	static int nCnt = 0;
	
	fd_set read_fd, *p_read_fd;
	fd_set write_fd, *p_write_fd;
	fd_set except_fd, *p_except_fd;
	struct timeval timeO, *p_time_out;
	int nSelectCnt = 0;

	if (fd_array == NULL || fd_num < 0)
	{
		printf("d_array == NULL || fd_num,fd_num = 0x%x\n",fd_num);
		return RETURN_FAIL;
	}

	p_time_out = NULL;
	if (time_out > 0)
	{
    	timeO.tv_sec = time_out / 1000;
    	timeO.tv_usec= (time_out % 1000)*1000;	
		p_time_out = &timeO;
	}

	p_read_fd = p_write_fd = p_except_fd = NULL;
	
	if (fd_type & 0x1)
	{
		p_read_fd = &read_fd;
		FD_ZERO(p_read_fd);
	}
	
	if (fd_type & 0x2)
	{
		p_write_fd = &write_fd;
		FD_ZERO(p_write_fd);
	}
	
	if (fd_type & 0x4)
	{
		p_except_fd = &except_fd;
		FD_ZERO(p_except_fd);
	}
	
	for (index = 0; index < fd_num; ++index)
	{
		if(fd_array[index] <= 0)
			continue;
		maxfd = maxfd > fd_array[index] ? maxfd : fd_array[index];

		if (p_read_fd)
			FD_SET(fd_array[index], p_read_fd);
		if (p_write_fd)
			FD_SET(fd_array[index], p_write_fd);
		if (p_except_fd)
			FD_SET(fd_array[index], p_except_fd);
	}

	if (maxfd <= 0)
	{
		printf("maxfd = %d\n",maxfd);
		return RETURN_FAIL;
	}
	
	maxfd += 1;

	while (1)
	{	//				&read_fd
		ret = select(maxfd, p_read_fd, p_write_fd, p_except_fd, p_time_out);
		if (ret < 0 && errno == EINTR)
		{
			if(nCnt < 100)
			{
				ERR("func = %s, LINE = %d, error = %d, ret = %d, nfunc = %s\n", __func__, __LINE__, errno, ret, pFunc);
			}
			else if(nCnt == 100 || nCnt == 101)
			{
				//system("netstat -an >> /param/netstat.txt");
			}
			
			nCnt++;
			nSelectCnt++;
			if(nSelectCnt >= 10)
			{
				printf("nSelectCnt >= 10,retunfunc = %s, LINE = %d, error = %d, ret = %d, nfunc = %s\n", __func__, __LINE__, errno, ret, pFunc);
				return RETURN_OK; 
			}
			continue;
		}
		else if (ret < 0)
		{		
			printf("ret < 0,func = %s, LINE = %d, error = %d, ret = %d\n", __func__, __LINE__, errno, ret);
			ERR("ret < 0,func = %s, LINE = %d, error = %d, ret = %d\n", __func__, __LINE__, errno, ret);
			return RETURN_FAIL;
		}
		else if (ret == 0)
		{
			printf("ret == 0\n");
			return RETURN_OK;
		}
		else
		{
			for (index = 0; index < fd_num; ++index)
			{
				if (fd_array[index] <= 0)  //socket error
					continue;
				
				if (p_read_fd)
				{
					if (FD_ISSET(fd_array[index], p_read_fd))
					{
						printf("0x01,fd_array[index] = %d\n",fd_array[index]);
						return fd_array[index] | 0x10000;
					}
				}
				else if (p_write_fd)
				{
					if (FD_ISSET(fd_array[index], p_write_fd))
					{
						printf("0x02,fd_array[index] = %d\n",fd_array[index]);
						return fd_array[index] | 0x20000;
					}
				}
				else if (p_except_fd)
				{
					if (FD_ISSET(fd_array[index], p_except_fd))
					{
						printf("0x04,fd_array[index] = %d\n",fd_array[index]);
						return fd_array[index] | 0x40000;
					}
				}			
			}
			printf("FD_ISSET is OK\n");
			return RETURN_OK;
		}
	}	

	ERR("func = %s, LINE = %d, error = %d, ret = %d\n", __func__, __LINE__, errno, ret);
	return RETURN_FAIL;	
}

int tcp_server_init(int port)
{
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	printf("sfd = %d\n",sfd);

	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	int on = 1;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	int ret = bind(sfd,(struct sockaddr *)&serv,sizeof(serv));
	printf("ret = %d\n",ret);
	listen(sfd,5);
	return sfd;
}

int main()
{
	int nRet;
	int sfd = tcp_server_init(9876); 	

	char buff[1024];
	struct sockaddr_in peer;
	socklen_t size;	

	int cnt;
//select关心读状态，listenfd的读、connectfd的读
	while(1)
	{
		int i;
		nRet = SelectFunction(&sfd,0x01,0x01,3000,__func__);//只完成返回listenfd可读状态
		if(-1 == nRet)
		{	
			close(&sfd);
			continue;
		}		
		else if (nRet == 0)
		{
			continue;
		}
		printf("listen nRet = %d\n",nRet);
		
		size = sizeof(peer);
		int newfd = accept(sfd,(struct sockaddr *)&peer,&size);
		printf("ip:%s,port:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
		printf("newfd = %d\n",newfd);
		
		nRet = SelectFunction(&newfd,0x01,0x01,3000,__func__);//只完成返回connectfd可读状态
		if(-1 == nRet)
		{	
			close(&sfd);
			continue;
		}		
		else if (nRet == 0)
		{
			continue;
		}
		printf("connect nRet = %d\n",nRet);
		memset(buff,0,1024);
		cnt = recv(newfd,buff,1024,0);
		printf("buff :%s",buff);
		
		printf("start send\n");
		send(newfd,buff,cnt,0);
					
		printf("after send\n");
		
	}
	return 0;
}
