#ifndef QSOCKET_H
#define QSOCKET_H
 
#include "url.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h> 

/* struct for http header */
typedef struct Header {
    char      *content_type;
    int        status_code;
} Header;

typedef struct Response {
	
    Header *header;//״̬��+ ��Ϣͷ
    char   *body;	//����
    int     body_len;	//���ĳ���
    ourlnode_t *url;//�������ҳ��ȡ��
} Response;

typedef struct evso_arg {    
	int     fd;		    
	ourlnode_t *url;//ip/port/path  connect<->fd
} event_arg;


/* create socket and connect */
int build_connect(char *ip, int port);

/* write http request to socket */
int send_request(int cfd, ourlnode_t *ourl);

/* set socket nonblock */
void set_nonblocking(int cfd);

/* read and deal data from socket triggered by epoll_wait */
extern void * recv_response(void *arg);

#endif
