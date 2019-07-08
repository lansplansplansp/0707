#ifndef __UDP_SOCK_H__
#define __UDP_SOCK_H__

#include "IPMSG.H"

#include <stdio.h>     // 标准输入输出定义
#include <stdlib.h>     // 标准函数库定义
#include <string.h>             // memset
#include <unistd.h>     // Unix标准函数定义，read,write...
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 		// 文件控制定义
#include <errno.h>     // 错误号定义
#include <pthread.h>        // pthread_t,pthread_create...
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "user_list.h"

#define IPMSG_PORT 2425

#define MSGLEN    1024

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct ipmsg_msg {
    char version[BUFFLEN];
    char pkt_id[BUFFLEN];
    char username[BUFFLEN];
    char hostname[BUFFLEN];
    char msg_type[BUFFLEN];
    char msg_content[MSGLEN];
}ipmsg_pkg_t;

int  udp_init(int port);	//初始化udp网络
void *udp_send_routine(void* arg); //发送线程函数
void *udp_recv_routine(void *arg);	//接收线程函数

void login(int ufd);
void logout(int ufd);
extern char Filename[BUFFLEN];

#endif
