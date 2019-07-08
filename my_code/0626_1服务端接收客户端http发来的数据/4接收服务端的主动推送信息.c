#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <limits.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
//http://www.jvt.cc/faceinfo
//./a.out http://www.jvt.cc/faceinfo


const static char pContextBuf[] = "{Name:FaceInfo,DeviceId:,DeviceUUID:umksbhtsv6as,DeviceMac:00-11-04-00-19-e3,FaceID: 123456,FaceQuality: 5,Position: {top:0,bottom:0,left: 0,right:0},SnapTime:20180417T144000,img:,imgex:}";

//			  argv[1]	空的host_addr[256] 空的host_file[1024]		portnumber = 0;	
void GetHost(char* src, char* web, 			char* file, 			int* port)
{
    char* pA;
    char* pB;
    memset(web, 0, sizeof(web));
    memset(file, 0, sizeof(file));
    *port = 0;
    if(NULL == src || *src == '\0')
    {
        return;
    }
    pA = src;
    if(!strncmp(pA, "http://", strlen("http://")))
    {
        pA = src+strlen("http://");
    }
    else if(!strncmp(pA, "https://", strlen( "https://")))
    {
        pA = src+strlen( "https://");
    }
    pB = strchr(pA, '/');
    if(pB)
    {
        memcpy(web, pA, strlen(pA)-strlen(pB));//web = www.jvt.cc
        if(pB+1)
        {
            memcpy(file, pB+1, strlen(pB)-1);//file = faceinfo
            file[strlen(pB)-1] = '\0';
        }
        web[strlen(pA) - strlen(pB)] = 0;
    }
    else
    {
        memcpy(web, pA, strlen(pA));//web = www.jvt.cc
        web[strlen(pA)] = 0;
    }

    pA = strchr(web, ':');
    if(pA)
    {
        *port = atoi(pA + 1);
    }
    else
    {
        *port = 80;
    }
}
int main(int   argc,   char   *argv[])
{
    int sockfd = 0;
    char buffer[1024] = "";
    struct sockaddr_in   server_addr;
    struct hostent   *host;
    int portnumber = 0;
    int nbytes = 0;
    char host_addr[256] = "";
    char host_file[1024] = "";
    char request[1024] = "";
    int send = 0;
    int totalsend = 0;
    int i = 0;
    char *pt;
    if(argc!=2)
    {
        fprintf(stderr, "Usage:%s   web-address\a\n ",argv[0]);
        exit(1);
    }
    printf( "parameter.1 is: %s\n ", argv[1]);
    GetHost(argv[1], host_addr, host_file, &portnumber);
    printf( "webhost:%s\n ", host_addr);//www.jvt.cc
    printf( "hostfile:%s\n ", host_file);//faceinfo
    printf( "portnumber:%d\n\n ", portnumber);//80
    if((host=gethostbyname(host_addr)) == NULL)
    {
        fprintf(stderr, "Gethostname   error,   %s\n ",   strerror(errno));
        exit(1);
    }
    if((sockfd=socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        fprintf(stderr, "Socket   Error:%s\a\n ",strerror(errno));
        exit(1);
    }
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(portnumber);
    server_addr.sin_addr=*((struct in_addr*)host->h_addr);
	printf("ip:%s,port:%d\n",inet_ntoa(server_addr.sin_addr),ntohs(server_addr.sin_port));//ip:223.7.100.244,port:80
    if(connect(sockfd, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr, "Connect   Error:%s\a\n ",strerror(errno));
        exit(1);
    }
    sprintf(request,"POST %s HTTP/1.1\r\n"
					"Content-Type: application/json;charset=UTF-8\r\n"
					"User-Agent: Mozilla/4.0\r\nCache-Control: no-cache\r\nAccept: */*\r\n"
					"Host: %s:%d\r\n"
					"Content-Length: %d\r\n"
					"Connection: Close\r\n\r\n"
					"%s", host_file, host_addr, portnumber,strlen(pContextBuf),pContextBuf);

    printf( "%s\n", request);

    send = 0;
    totalsend = 0;
    nbytes=strlen(request);
    while(totalsend < nbytes)
    {
        send = write(sockfd, request+totalsend, nbytes-totalsend);
        if(send == -1)
        {
            printf( "send error!%s\n ", strerror(errno));
            exit(0);
        }
        totalsend += send;
        printf("%d bytes send OK!\n ", totalsend);
    }
    printf( "\nThe   following   is   the   response   header:\n ");
    i=0;
    while((nbytes=read(sockfd,buffer,1))==1)
    {
        if(i < 100000)
        {
            if(buffer[0] == '\r' || buffer[0] == '\n')
                i++;
            else
                i = 0;
            printf( "%c", buffer[0]);
        }
    }
    close(sockfd);
    exit(0);
}
